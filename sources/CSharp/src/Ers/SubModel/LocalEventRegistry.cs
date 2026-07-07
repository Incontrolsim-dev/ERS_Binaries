using Ers.Engine;
using System.Numerics;
using System.Reflection;
using System.Reflection.Emit;
using System.Reflection.Metadata;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ers
{

    public interface ILocalEvent<T>
        where T : struct, ILocalEvent<T> {

        public abstract void OnEvent();

        public void Serialization(Serializer serializer)
        {
            // Use Unsafe.Unbox to get a ref to the data inside the boxed struct
            // This allows both reading and writing to the actual stored data
            ref T self = ref Unsafe.Unbox<T>((object)this);
            LocalEventSerializationHelper<T>.SerializeFields(ref self, serializer);
        }
    }

    /// <summary>
    /// Helper class that generates and caches field serialization logic for ILocalEvent types.
    /// Uses reflection once per type to build efficient serialization delegates.
    /// </summary>
    internal static class LocalEventSerializationHelper<T>
        where T : struct, ILocalEvent<T>
    {
        private delegate void SerializeFieldsRef(ref T value, Serializer serializer);
        private static readonly SerializeFieldsRef? _serializeFieldsRefDelegate;

        static LocalEventSerializationHelper() { _serializeFieldsRefDelegate = BuildSerializeFieldsDelegate(); }

        private static SerializeFieldsRef? BuildSerializeFieldsDelegate()
        {
            Type tType = typeof(T);
            var fields = tType.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);

            if (fields.Length == 0)
                return null;

            // Build a DynamicMethod that serializes all fields
            var dm = new DynamicMethod(
                name: $"SerializeFields_{tType.FullName}", returnType: typeof(void),
                parameterTypes: new[] { tType.MakeByRefType(), typeof(Serializer) }, owner: typeof(LocalEventSerializationHelper<T>),
                skipVisibility: true);

            var il = dm.GetILGenerator();

            // Get the generic Serialize<TField> method from Serializer
            var serializeMethod =
                typeof(Serializer)
                    .GetMethods(BindingFlags.Public | BindingFlags.Instance)
                    .FirstOrDefault(
                        m => m.Name == "Serialize" && m.IsGenericMethodDefinition && m.GetParameters().Length == 2 &&
                             m.GetParameters()[0].ParameterType == typeof(string) && m.GetParameters()[1].ParameterType.IsByRef);

            if (serializeMethod == null)
                throw new InvalidOperationException("Could not find Serialize<T>(string, ref T) method on Serializer.");

            foreach (var field in fields)
            {
                // Skip backing fields for auto-properties and compiler-generated fields
                if (field.Name.StartsWith("<") || field.GetCustomAttribute<CompilerGeneratedAttribute>() != null)
                    continue;

                // Get the specific Serialize<FieldType> method
                var fieldSerializeMethod = serializeMethod.MakeGenericMethod(field.FieldType);

                // Load serializer (arg 1)
                il.Emit(OpCodes.Ldarg_1);

                // Load field name as string
                il.Emit(OpCodes.Ldstr, field.Name);

                // Load address of the field from ref T (arg 0)
                il.Emit(OpCodes.Ldarg_0);
                il.Emit(OpCodes.Ldflda, field);

                // Call serializer.Serialize<FieldType>(fieldName, ref fieldValue)
                il.Emit(OpCodes.Callvirt, fieldSerializeMethod);
            }

            il.Emit(OpCodes.Ret);

            return (SerializeFieldsRef)dm.CreateDelegate(typeof(SerializeFieldsRef));
        }

        public static void SerializeFields(ref T value, Serializer serializer)
        {
            _serializeFieldsRefDelegate?.Invoke(ref value, serializer);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct LocalEventNativeData
    {
        public delegate* unmanaged[Cdecl]<nint, void> Callback;
        public delegate* unmanaged[Cdecl]<nint, void> Destructor;
        public delegate* unmanaged[Cdecl]<nint, nint, void> Serialize;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct LocalEventNative
    {
        public IntPtr ContextHandle;
        public LocalEventNativeData* NativeDataPtr;
    }

    public static unsafe class LocalEventRegistry
    {
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static void EventCallback(nint handle)
        {
            LocalEventNative* handlePtr = (LocalEventNative*)handle;
            handlePtr->NativeDataPtr->Callback(handle);
        }

        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static void LocalEventDestructor(nint handle)
        {
            LocalEventNative* handlePtr = (LocalEventNative*)handle;
            handlePtr->NativeDataPtr->Destructor(handle);
        }

        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static void LocalEventDataSerialize(nint handle, nint serializer)
        {
            LocalEventNative* handlePtr = (LocalEventNative*)handle;
            handlePtr->NativeDataPtr->Serialize(handle, serializer);
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate nint LocalEventAllocatorCallback();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void LocalEventCallbackDelegate(nint handle);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void LocalEventSerializeDelegate(nint handle, nint serializer);

        private static List<Delegate> registeredTypedCallbackFunctions = new List<Delegate>();

        /// <summary>
        /// Creates a non-generic function pointer that directly calls a type-specific static method for LocalEvent callback.
        /// </summary>
        internal static delegate* unmanaged[Cdecl]<nint, void> CreateLocalEventCallback(Type eventType, MethodInfo targetMethod)
        {
            var dynamicMethod = new DynamicMethod(
                $"NativeCallable_LocalEventCallback_{eventType.Name}_{Guid.NewGuid():N}", typeof(void), new[] { typeof(nint) },
                typeof(EventScheduler).Module, skipVisibility: true);

            var il = dynamicMethod.GetILGenerator();

            // Load argument and directly call the target static method - no delegate indirection
            il.Emit(OpCodes.Ldarg_0); // handle
            il.Emit(OpCodes.Call, targetMethod);
            il.Emit(OpCodes.Ret);

            var nativeDelegate = (LocalEventCallbackDelegate)dynamicMethod.CreateDelegate(typeof(LocalEventCallbackDelegate));
            registeredTypedCallbackFunctions.Add(nativeDelegate);
            return (delegate * unmanaged[Cdecl]<nint, void>)Marshal.GetFunctionPointerForDelegate(nativeDelegate);
        }

        /// <summary>
        /// Creates a non-generic function pointer that directly calls a type-specific static method for LocalEvent destructor.
        /// </summary>
        internal static delegate* unmanaged[Cdecl]<nint, void> CreateLocalEventDestructor(Type eventType, MethodInfo targetMethod)
        {
            var dynamicMethod = new DynamicMethod(
                $"NativeCallable_LocalEventDestructor_{eventType.Name}_{Guid.NewGuid():N}", typeof(void), new[] { typeof(nint) },
                typeof(EventScheduler).Module, skipVisibility: true);

            var il = dynamicMethod.GetILGenerator();

            // Load argument and directly call the target static method - no delegate indirection
            il.Emit(OpCodes.Ldarg_0); // handle
            il.Emit(OpCodes.Call, targetMethod);
            il.Emit(OpCodes.Ret);

            var nativeDelegate = (LocalEventCallbackDelegate)dynamicMethod.CreateDelegate(typeof(LocalEventCallbackDelegate));
            registeredTypedCallbackFunctions.Add(nativeDelegate);
            return (delegate * unmanaged[Cdecl]<nint, void>)Marshal.GetFunctionPointerForDelegate(nativeDelegate);
        }

        /// <summary>
        /// Creates a non-generic function pointer that directly calls a type-specific static method for LocalEvent serialization.
        /// </summary>
        internal static delegate* unmanaged[Cdecl]<nint, nint, void> CreateLocalEventSerialize(Type eventType, MethodInfo targetMethod)
        {
            var dynamicMethod = new DynamicMethod(
                $"NativeCallable_LocalEventSerialize_{eventType.Name}_{Guid.NewGuid():N}", typeof(void),
                new[] { typeof(nint), typeof(nint) }, typeof(EventScheduler).Module, skipVisibility: true);

            var il = dynamicMethod.GetILGenerator();

            // Load arguments and directly call the target static method - no delegate indirection
            il.Emit(OpCodes.Ldarg_0); // handle
            il.Emit(OpCodes.Ldarg_1); // serializer
            il.Emit(OpCodes.Call, targetMethod);
            il.Emit(OpCodes.Ret);

            var nativeDelegate = (LocalEventSerializeDelegate)dynamicMethod.CreateDelegate(typeof(LocalEventSerializeDelegate));
            registeredTypedCallbackFunctions.Add(nativeDelegate);
            return (delegate * unmanaged[Cdecl]<nint, nint, void>)Marshal.GetFunctionPointerForDelegate(nativeDelegate);
        }

        /// <summary>
        /// Creates a non-generic function pointer that directly calls a type-specific static method for LocalEvent allocation.
        /// </summary>
        internal static delegate* unmanaged[Cdecl]<nint> CreateLocalEventAllocator(Type eventType, MethodInfo targetMethod)
        {
            var dynamicMethod = new DynamicMethod(
                $"NativeCallable_LocalEventAllocator_{eventType.Name}_{Guid.NewGuid():N}", typeof(nint), Type.EmptyTypes,
                typeof(EventScheduler).Module, skipVisibility: true);

            var il = dynamicMethod.GetILGenerator();

            // Directly call the target static method - no delegate indirection
            il.Emit(OpCodes.Call, targetMethod);
            il.Emit(OpCodes.Ret);

            var nativeDelegate = (LocalEventAllocatorCallback)dynamicMethod.CreateDelegate(typeof(LocalEventAllocatorCallback));
            registeredTypedCallbackFunctions.Add(nativeDelegate);
            return (delegate * unmanaged[Cdecl]<nint>)Marshal.GetFunctionPointerForDelegate(nativeDelegate);
        }
    }

    /// <summary>
    /// Generic static class for caching LocalEvent type handles per closure type TContext.
    /// Each unique closure type gets its own registration with proper serialization support.
    /// This provides ZERO-COST access - direct static field access with no dictionary lookups!
    /// </summary>
    public static unsafe class LocalEventRegistry<TContext>
        where TContext : struct, ILocalEvent<TContext>
    {

        private static LocalEventNativeData* nativeCallbacks;

        public static readonly nint Handle;

        // Create truly non-generic function pointers via helper methods in non-generic LocalEventRegistry class
        // These directly call the static methods - no delegate indirection needed
        private static readonly delegate* unmanaged[Cdecl]<nint> allocatorFunctionPtr = LocalEventRegistry.CreateLocalEventAllocator(
            typeof(TContext),
            typeof(LocalEventRegistry<TContext>).GetMethod(nameof(LocalEventAllocator), BindingFlags.Static | BindingFlags.NonPublic)!);

        private static readonly delegate* unmanaged[Cdecl]<nint, void> callbackFunctionPtr = LocalEventRegistry.CreateLocalEventCallback(
            typeof(TContext),
            typeof(LocalEventRegistry<TContext>).GetMethod(nameof(LocalEventCallback), BindingFlags.Static | BindingFlags.NonPublic)!);

        private static readonly delegate* unmanaged[Cdecl]<nint, void> destructorFunctionPtr =
            LocalEventRegistry.CreateLocalEventDestructor(
                typeof(TContext),
                typeof(LocalEventRegistry<TContext>)
                    .GetMethod(nameof(LocalEventDestructor), BindingFlags.Static | BindingFlags.NonPublic)!);

        private static readonly delegate* unmanaged[Cdecl]<nint, nint, void> serializeFunctionPtr =
            LocalEventRegistry.CreateLocalEventSerialize(
                typeof(TContext),
                typeof(LocalEventRegistry<TContext>)
                    .GetMethod(nameof(LocalEventDataSerialize), BindingFlags.Static | BindingFlags.NonPublic)!);

        /// <summary>
        /// Register a local event type explicitly before simulation creation.
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling this multiple times for the same type is safe and results in a no-op.
        /// </summary>
        public static void Register()
        {
            // Empty stub to call the static constructor
            // The static constructor only runs once per type - subsequent calls are no-ops.
            _ = Handle;
        }

        /// <summary>
        /// Type-specific callback that knows how to invoke TContext delegates.
        /// </summary>
        static void LocalEventCallback(nint nativeMemory)
        {
            LocalEventNative* eventHandle = (LocalEventNative*)nativeMemory;

            GCHandle handle = GCHandle.FromIntPtr(eventHandle->ContextHandle);

            ((TContext)handle.Target!).OnEvent();

            handle.Free();

            // Free the native memory
            ErsEngine.ERS_EventScheduler_FreeLocalEvent(nativeMemory, Handle);
        }

        /// <summary>
        /// Type-specific destructor that knows how to destroy TContext events.
        /// Called when an event is cancelled before execution.
        /// </summary>
        static void LocalEventDestructor(nint nativeMemory)
        {
            LocalEventNative* eventHandle = (LocalEventNative*)nativeMemory;

            GCHandle handle = GCHandle.FromIntPtr(eventHandle->ContextHandle);

            handle.Free();

            // Free the native memory
            ErsEngine.ERS_EventScheduler_FreeLocalEvent(nativeMemory, Handle);
        }

        static void LocalEventDataSerialize(nint nativeMemory, nint serializerPtr)
        {
            Serializer serializer = new Serializer(serializerPtr);

            if (nativeMemory == IntPtr.Zero)
                return;

            LocalEventNative* eventHandle = (LocalEventNative*)nativeMemory;

            GCHandle handle = GCHandle.FromIntPtr(eventHandle->ContextHandle);

            // Get a direct reference to the struct inside the boxed object
            // This avoids making a copy and ensures deserialization writes to the actual stored data
            ref TContext targetRef = ref Unsafe.Unbox<TContext>(handle.Target!);

            // Serialize/deserialize fields directly via the ref to avoid copies
            LocalEventSerializationHelper<TContext>.SerializeFields(ref targetRef, serializer);
        }

        public static nint AllocateEventData(in TContext eventData)
        {
            // Allocate native memory using ERS allocator
            nint nativeMemory = ErsEngine.ERS_EventScheduler_AllocLocalEvent(Handle);

            LocalEventNative localEvent = default;
            localEvent.NativeDataPtr    = nativeCallbacks;

            localEvent.ContextHandle = GCHandle.ToIntPtr(GCHandle.Alloc(
                eventData, GCHandleType.Normal)); // TODO once we change the struct type to be bittable we can remove this handle allocation

            // Store the GCHandle in the native memory
            Unsafe.Write((void*)nativeMemory, localEvent);

            return nativeMemory;
        }

        static nint LocalEventAllocator() { return AllocateEventData(default); }

        static LocalEventRegistry()
        {
            // Register the LocalEvent type once per TContext in the static constructor
            // Allocate the native callbacks struct in unmanaged memory so the GC won't move it
            // This is critical because native code reads function pointers from this struct
            nativeCallbacks = (LocalEventNativeData*)NativeMemory.Alloc((nuint)sizeof(LocalEventNativeData));

            // Use the pre-created unmanaged function pointers (created via DynamicMethod + Marshal.GetFunctionPointerForDelegate)
            // This is required because methods in generic types cannot be called directly from unmanaged code
            nativeCallbacks->Callback   = callbackFunctionPtr;
            nativeCallbacks->Destructor = destructorFunctionPtr;
            nativeCallbacks->Serialize  = serializeFunctionPtr;

            Type contextType       = typeof(TContext);
            string contextTypeName = contextType.FullName;

            string uniqueName = $"LocalEvent_{contextTypeName}";
            // Use the assembly name where the closure type is defined as the source library
            string sourceLibrary = contextType.Assembly.GetName().Name ?? "UnknownAssembly";

            var nameUtf8          = System.Text.Encoding.UTF8.GetBytes(uniqueName + "\0");
            var sourceLibraryUtf8 = System.Text.Encoding.UTF8.GetBytes(sourceLibrary + "\0");

            // Source location is not easily available in C# - leave empty (will show "location not registered" in debugger)
            var filePathUtf8 = System.Text.Encoding.UTF8.GetBytes("\0");
            int lineNumber   = 0;

            uint eventSize = (uint)sizeof(LocalEventNative);

            fixed(byte* namePtr = nameUtf8) fixed(byte* sourceLibraryPtr = sourceLibraryUtf8) fixed(byte* filePathPtr = filePathUtf8)
            {
                Handle = ErsEngine.ERS_EventScheduler_RegisterLocalEventType(
                    (ulong)contextType.TypeHandle.Value, &LocalEventRegistry.EventCallback, &LocalEventRegistry.LocalEventDestructor,
                    &LocalEventRegistry.LocalEventDataSerialize, allocatorFunctionPtr, namePtr, sourceLibraryPtr, eventSize, filePathPtr,
                    lineNumber); // Size of IntPtr to store GCHandle
            }
        }
    }
}
