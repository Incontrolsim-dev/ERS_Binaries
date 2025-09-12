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

    static class ComponentTraits<T>
        where T : IComponentBase
    {
        private delegate nint CreateInstanace();

        private static UInt32 componentTypeId         = UInt32.MaxValue;
        private static readonly bool isScriptBehavior = false;
        private static readonly CreateInstanace createInstanceCallback;
        private static readonly nint createInstanceCallbackHandle;
        // Note: createInstanceCallbackHandle should not need freeing as allocs are freed upon unloading of the library

        static ComponentTraits()
        {
            createInstanceCallback = static () =>
            { return GCHandle.ToIntPtr(GCHandle.Alloc(Activator.CreateInstance<T>(), GCHandleType.Normal)); };
            createInstanceCallbackHandle = GCHandle.ToIntPtr(GCHandle.Alloc(createInstanceCallback, GCHandleType.Normal));

            // Ensure correct disposing of the handle to a callback
            AppDomain.CurrentDomain.ProcessExit += OnProcessExit;

            // Check for core components
            // TODO: Check if this is needed. Is this not already handled by GetTYpeId() in the components themselves?
            if (typeof(T) == typeof(NameComponent))
            {
                componentTypeId = ErsEngine.ERS_NameComponent_TypeId();
            }
            else if (typeof(T) == typeof(RelationComponent))
            {
                componentTypeId = ErsEngine.ERS_RelationComponent_TypeId();
            }
            else if (typeof(T) == typeof(TransformComponent))
            {
                componentTypeId = ErsEngine.ERS_TransformComponent_TypeId();
            }
            else if (typeof(T) == typeof(BoxComponent))
            {
                componentTypeId = ErsEngine.ERS_BoxComponent_TypeId();
            }
            else if (typeof(T) == typeof(PathComponent))
            {
                componentTypeId = ErsEngine.ERS_PathComponent_TypeId();
            }
            else if (typeof(T) == typeof(OutlineComponent))
            {
                componentTypeId = ErsEngine.ERS_OutlineComponent_TypeId();
            }
            else if (typeof(T) == typeof(ResourceComponent))
            {
                componentTypeId = ErsEngine.ERS_ResourceComponent_TypeId();
            }
            else if (typeof(T) == typeof(ChannelComponent))
            {
                componentTypeId = ErsEngine.ERS_ChannelComponent_TypeId();
            }
            else
            {
                // Later initialization. But already determine if this class is a scriptbehavior.
                isScriptBehavior = typeof(T).IsSubclassOf(typeof(ScriptBehaviorComponent));
            }
        }

        public static UInt32 RegisterType()
        {
            string name  = typeof(T).Name;
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
                        int size        = Marshal.SizeOf<T>();
                        componentTypeId = ErsEngine.ERS_GlobalComponentRegistry_RegisterComponent(nameByte, (nuint)size);
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
