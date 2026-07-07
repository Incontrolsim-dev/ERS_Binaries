using Ers.Engine;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ers
{
    internal unsafe class SyncEventRegistry
    {

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void SyncEventDataSerializationCallback(nint dataPtr, nint serializerPtr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void SyncEventCallback();

        private static List<Delegate> registeredTypedCallbackFunctions = new List<Delegate>();

        // ============================================
        // Non-generic helper methods to create function pointers
        // These exist outside any generic type context
        // ============================================

        /// <summary>
        /// Creates a non-generic function pointer that directly calls a type-specific static method for SyncEvent callbacks.
        /// </summary>
        internal static delegate* unmanaged[Cdecl]<void> CreateSyncEventCallbackFunctionPointer(Type eventType, MethodInfo targetMethod)
        {
            var dynamicMethod = new DynamicMethod(
                $"NativeCallable_SyncEventCallback_{eventType.Name}_{Guid.NewGuid():N}", typeof(void), Type.EmptyTypes,
                typeof(EventScheduler).Module, skipVisibility: true);

            var il = dynamicMethod.GetILGenerator();

            // Directly call the target static method - no delegate indirection
            il.Emit(OpCodes.Call, targetMethod);
            il.Emit(OpCodes.Ret);

            var nativeDelegate = (SyncEventCallback)dynamicMethod.CreateDelegate(typeof(SyncEventCallback));
            registeredTypedCallbackFunctions.Add(nativeDelegate);
            return (delegate * unmanaged[Cdecl]<void>)Marshal.GetFunctionPointerForDelegate(nativeDelegate);
        }

        /// <summary>
        /// Creates a non-generic function pointer that directly calls a type-specific static method for SyncEvent data serialization.
        /// </summary>
        internal static delegate* unmanaged[Cdecl]<nint, nint, void> CreateSyncEventDataSerializationFunctionPointer(
            Type eventType, MethodInfo targetMethod)
        {
            var dynamicMethod = new DynamicMethod(
                $"NativeCallable_SyncEventDataSerialize_{eventType.Name}_{Guid.NewGuid():N}", typeof(void),
                new[] { typeof(nint), typeof(nint) }, typeof(EventScheduler).Module, skipVisibility: true);

            var il = dynamicMethod.GetILGenerator();

            // Load arguments and directly call the target static method - no delegate indirection
            il.Emit(OpCodes.Ldarg_0); // dataPtr
            il.Emit(OpCodes.Ldarg_1); // serializerPtr
            il.Emit(OpCodes.Call, targetMethod);
            il.Emit(OpCodes.Ret);

            var nativeDelegate =
                (SyncEventDataSerializationCallback)dynamicMethod.CreateDelegate(typeof(SyncEventDataSerializationCallback));
            registeredTypedCallbackFunctions.Add(nativeDelegate);
            return (delegate * unmanaged[Cdecl]<nint, nint, void>)Marshal.GetFunctionPointerForDelegate(nativeDelegate);
        }
    }

    /// <summary>
    /// Generic static class for caching SyncEvent type handles per type T.
    /// Each instantiation of this class for a specific T has its own static Handle field.
    /// This provides ZERO-COST access - direct static field access with no dictionary lookups!
    /// </summary>
    public static unsafe class SyncEventRegistry<T>
        where T : unmanaged, ISyncEvent<T>
    {
        public static readonly nint Handle;

        /// <summary>
        /// Register a sync event type explicitly before simulation creation.
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling this multiple times for the same type is safe and results in a no-op.
        /// </summary>
        public static void Register() { _ = Handle; }

        // Pre-created unmanaged function pointers for sender/target side callbacks
        // These directly call the static methods
        public static readonly delegate* unmanaged[Cdecl]<void> OnSenderSideFunctionPtr =
            SyncEventRegistry.CreateSyncEventCallbackFunctionPointer(
                typeof(T),
                typeof(SyncEventRegistry<T>).GetMethod(nameof(OnSenderSidePlain), BindingFlags.Static | BindingFlags.NonPublic)!);

        public static readonly delegate* unmanaged[Cdecl]<void> OnTargetSideFunctionPtr =
            SyncEventRegistry.CreateSyncEventCallbackFunctionPointer(
                typeof(T),
                typeof(SyncEventRegistry<T>).GetMethod(nameof(OnTargetSidePlain), BindingFlags.Static | BindingFlags.NonPublic)!);

        // Create truly non-generic function pointer via helper method
        // The function pointer directly calls SyncEventDataSerialize - no delegate indirection
        private static readonly delegate* unmanaged[Cdecl]<nint, nint, void> SyncEventDataSerializePtr =
            SyncEventRegistry.CreateSyncEventDataSerializationFunctionPointer(
                typeof(T),
                typeof(SyncEventRegistry<T>).GetMethod(nameof(SyncEventDataSerialize), BindingFlags.Static | BindingFlags.NonPublic)!);

        /// <summary>
        /// Type-specific sender side callback that wraps ISyncEvent&lt;T&gt;.OnSenderSidePlain
        /// </summary>
        private static void OnSenderSidePlain()
        {
            Ref<T> instance = SyncEvent.GetData<T>();
            instance.Value.OnSenderSide();
        }

        /// <summary>
        /// Type-specific target side callback that wraps ISyncEvent&lt;T&gt;.OnTargetSidePlain
        /// </summary>
        private static void OnTargetSidePlain()
        {
            Ref<T> instance = SyncEvent.GetData<T>();
            instance.Value.OnTargetSide();
        }

        static void SyncEventDataSerialize(nint dataPtr, nint serializerPtr)
        {
            // Use the Serializer's built-in functionality to handle ref types with Serialization methods
            ref T data            = ref Unsafe.AsRef<T>((void*)dataPtr);
            Serializer serializer = new Serializer(serializerPtr);

            // The Serializer automatically detects and calls Serialization methods on custom types
            serializer.Serialize("data", ref data);
        }

        static SyncEventRegistry()
        {
            // Register the SyncEvent type once per T in the static constructor
            // Use the assembly name where the event type is defined as the source library
            string sourceLibrary  = typeof(T).Assembly.GetName().Name ?? "UnknownAssembly";
            var nameUtf8          = System.Text.Encoding.UTF8.GetBytes(T.Name + "\0");
            var sourceLibraryUtf8 = System.Text.Encoding.UTF8.GetBytes(sourceLibrary + "\0");

            // Source location is not easily available in C# - leave empty (will show "location not registered" in debugger)
            var filePathUtf8   = System.Text.Encoding.UTF8.GetBytes("\0");
            int lineNumber     = 0;
            uint dataBlockSize = (uint)sizeof(T);

            fixed(byte* namePtr = nameUtf8) fixed(byte* sourceLibraryPtr = sourceLibraryUtf8) fixed(byte* filePathPtr = filePathUtf8)
            {
                Handle = ErsEngine.ERS_EventScheduler_RegisterSyncEventType(
                    SyncEvent.TypeIdentifier<T>(), OnSenderSideFunctionPtr, OnTargetSideFunctionPtr, SyncEventDataSerializePtr,
                    dataBlockSize, namePtr, sourceLibraryPtr, filePathPtr, lineNumber);
            }
        }
    }
}
