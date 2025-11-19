using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    static class ComponentTraitsExtensions
    {
        // Unmanaged callback function
        // The create function is passed as a handle because C# doesn't allow generics during an unmanaged invocation
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static nint CreateScriptBehaviorInstance(nint createInstanceHandle)
        {
            return (nint)((Delegate)GCHandle.FromIntPtr(createInstanceHandle).Target!).DynamicInvoke()!;
        }
    }

    // Non-generic delegate type for DataComponent serialization - must be outside the generic class
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    internal delegate void DataComponentSerializationDelegate(IntPtr componentPtr, IntPtr serializerHandle);

    static class ComponentTraits<T>
        where T : IComponentBase
    {
        private delegate nint CreateInstanace();

        private static UInt32 componentTypeId         = UInt32.MaxValue;
        private static readonly bool isScriptBehavior = false;
        private static readonly CreateInstanace createInstanceCallback;
        private static readonly nint createInstanceCallbackHandle;
        // Note: createInstanceCallbackHandle and serializationCallback should not need freeing as allocs are freed upon unloading of the
        // library

        // Data component specific
        private static readonly DataComponentSerializationDelegate? serializationCallback;
        private static readonly bool hasCustomSerialization = false;
        private static readonly IntPtr serializationFunctionPointer;

        static ComponentTraits()
        {
            createInstanceCallback = static () =>
            { return GCHandle.ToIntPtr(GCHandle.Alloc(Activator.CreateInstance<T>(), GCHandleType.Normal)); };
            createInstanceCallbackHandle = GCHandle.ToIntPtr(GCHandle.Alloc(createInstanceCallback, GCHandleType.Normal));

            // Ensure correct disposing of the handle to a callback
            AppDomain.CurrentDomain.ProcessExit += OnProcessExit;

            // Check if T has a static CoreTypeId() method (for core components)
            var coreTypeIdMethod =
                typeof(T).GetMethod("CoreTypeId", BindingFlags.Public | BindingFlags.Static, null, Type.EmptyTypes, null);

            if (coreTypeIdMethod != null && coreTypeIdMethod.ReturnType == typeof(nuint))
            {
                // This is a core component - call CoreTypeId() once and cache the result
                componentTypeId = (UInt32)(nuint)coreTypeIdMethod.Invoke(null, null)!;
            }
            else
            {
                // Later initialization. But already determine if this class is a scriptbehavior.
                isScriptBehavior = typeof(T).IsSubclassOf(typeof(ScriptBehaviorComponent));

                // Check if this DataComponent has a custom Serialization method
                if (!isScriptBehavior && typeof(IDataComponent).IsAssignableFrom(typeof(T)))
                {
                    var method = typeof(T).GetMethod(
                        "Serialization", BindingFlags.Public | BindingFlags.Instance, null, new Type[] { typeof(Serializer) }, null);

                    if (method != null && !method.IsStatic && method.ReturnType == typeof(void))
                    {
                        Unsafe.SkipInit(out hasCustomSerialization);
                        hasCustomSerialization = true;

                        // Create a concrete, non-generic method using DynamicMethod
                        // This avoids the "generic type" error with Marshal.GetFunctionPointerForDelegate
                        var dm = new DynamicMethod(
                            name: $"DataComponentSerialize_{typeof(T).FullName?.Replace('.', '_')}", returnType: typeof(void),
                            parameterTypes: new[] { typeof(IntPtr), typeof(IntPtr) }, owner: typeof(ComponentTraits<T>),
                            skipVisibility: true);

                        var il = dm.GetILGenerator();

                        // Get the GetCustomSerializationMethod<T>() method
                        var getCustomMethod =
                            typeof(Serializer)
                                .GetMethod("GetCustomSerializationMethod", BindingFlags.Public | BindingFlags.Static)!.MakeGenericMethod(
                                    typeof(T));

                        // Local variables
                        var componentLocal  = il.DeclareLocal(typeof(T).MakeByRefType(), pinned: false);
                        var serializerLocal = il.DeclareLocal(typeof(Serializer));
                        var delegateLocal   = il.DeclareLocal(typeof(Delegate));

                        // ref T component = ref Unsafe.AsRef<T>((void*)componentPtr);
                        il.Emit(OpCodes.Ldarg_0); // componentPtr
                        il.Emit(
                            OpCodes.Call, typeof(Unsafe)
                                              .GetMethod(
                                                  "AsRef", BindingFlags.Public | BindingFlags.Static, null, new[] { typeof(void*) },
                                                  null)!.MakeGenericMethod(typeof(T)));
                        il.Emit(OpCodes.Stloc, componentLocal);

                        // Serializer serializer = new Serializer(serializerHandle);
                        il.Emit(OpCodes.Ldarg_1); // serializerHandle
                        il.Emit(
                            OpCodes.Newobj,
                            typeof(Serializer)
                                .GetConstructor(BindingFlags.NonPublic | BindingFlags.Instance, null, new[] { typeof(nint) }, null)!);
                        il.Emit(OpCodes.Stloc, serializerLocal);

                        // Delegate customSerialize = Serializer.GetCustomSerializationMethod<T>();
                        il.Emit(OpCodes.Call, getCustomMethod);
                        il.Emit(OpCodes.Stloc, delegateLocal);

                        // if (customSerialize == null) return;
                        il.Emit(OpCodes.Ldloc, delegateLocal);
                        var notNullLabel = il.DefineLabel();
                        il.Emit(OpCodes.Brtrue_S, notNullLabel);
                        il.Emit(OpCodes.Ret);
                        il.MarkLabel(notNullLabel);

                        // ((Serializer.ByRefSerializeOnCustomType<T>)customSerialize)(ref component, serializer);
                        il.Emit(OpCodes.Ldloc, delegateLocal);
                        il.Emit(OpCodes.Castclass, typeof(Serializer.ByRefSerializeOnCustomType<T>));
                        il.Emit(OpCodes.Ldloc, componentLocal);
                        il.Emit(OpCodes.Ldloc, serializerLocal);
                        il.Emit(OpCodes.Callvirt, typeof(Serializer.ByRefSerializeOnCustomType<T>).GetMethod("Invoke")!);
                        il.Emit(OpCodes.Ret);

                        // Create the delegate and get its function pointer
                        Unsafe.SkipInit(out serializationCallback);
                        serializationCallback =
                            (DataComponentSerializationDelegate)dm.CreateDelegate(typeof(DataComponentSerializationDelegate));

                        Unsafe.SkipInit(out serializationFunctionPointer);
                        serializationFunctionPointer = Marshal.GetFunctionPointerForDelegate(serializationCallback);
                    }
                }
            }
        }

        public static UInt32 RegisterType()
        {
            var typeInfo      = typeof(T).GetCustomAttribute<Ers.TypeInfoAttribute>();
            string? nameAlias = typeInfo != null ? typeInfo.Name : null;

            IntPtr typeInfoPtr = TypeInfoRegister.RegisterType(typeof(T));

            string name  = nameAlias ?? typeof(T).Name;
            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    if (IsScriptBehavior())
                    {
                        componentTypeId = ErsEngine.ERS_GlobalComponentRegistry_RegisterScriptBehavior(
                            nameByte, &ComponentTraitsExtensions.CreateScriptBehaviorInstance, createInstanceCallbackHandle,
                            &GlobalScriptBehavior.OnCreation, &GlobalScriptBehavior.OnAwake, &GlobalScriptBehavior.OnStart,
                            &GlobalScriptBehavior.OnUpdate, &GlobalScriptBehavior.OnLateUpdate, &GlobalScriptBehavior.OnDestroy,
                            &GlobalScriptBehavior.OnEntering, &GlobalScriptBehavior.OnEntered, &GlobalScriptBehavior.OnExiting,
                            &GlobalScriptBehavior.OnExited, &GlobalScriptBehavior.Serialization, &GlobalScriptBehavior.OnSubModelMove);
                    }
                    else if (componentTypeId == UInt32.MaxValue)
                    {
                        int size = Marshal.SizeOf<T>();
                        // Pass custom serialization function pointer if available
                        IntPtr customSerializePtr = hasCustomSerialization ? serializationFunctionPointer : IntPtr.Zero;
                        componentTypeId =
                            ErsEngine.ERS_GlobalComponentRegistry_RegisterComponent(nameByte, (nuint)size, typeInfoPtr, customSerializePtr);
                    }
                }
            }
            return componentTypeId;
        }

        public static UInt32 GetComponentTypeId() { return componentTypeId; }

        public static bool IsScriptBehavior() { return isScriptBehavior; }

        public static bool IsRegistered() { return componentTypeId != UInt32.MaxValue; }

        private static void OnProcessExit(object? sender, EventArgs e)
        {
            GCHandle handle = GCHandle.FromIntPtr(createInstanceCallbackHandle);
            handle.Free(); // Should always be allocated
        }
    }

    /// <summary>
    /// Information about all registered component types.
    /// </summary>
    public static class RegisteredComponentTypes
    {
        private static readonly Dictionary<IntPtr, List<Type>> subModelTypes = [];

        internal static void AddType(in SubModel subModel, Type type)
        {
            if (!subModelTypes.ContainsKey(subModel.Data))
            {
                // Add core components by default
                subModelTypes.Add(subModel.Data, [
                    // typeof(NameComponent),
                    typeof(RelationComponent),
                    typeof(TransformComponent),
                    typeof(BoxComponent),
                    typeof(OutlineComponent),
                ]);
            }
            subModelTypes[subModel.Data].Add(type);
        }

        /// <summary>
        /// Get the component types that are registered on a given <see cref="SubModel"/>.
        /// </summary>
        /// <param name="subModel">The SubModel of which to get the registered component types.</param>
        /// <returns></returns>
        public static List<Type> GetTypes(in SubModel subModel) => subModelTypes[subModel.Data];
    }
}
