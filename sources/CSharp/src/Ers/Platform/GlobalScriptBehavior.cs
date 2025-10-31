using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ers
{
    internal class GlobalScriptBehavior
    {
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnAwake(IntPtr scriptInstancePtr)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnAwake();
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnCreation(IntPtr scriptInstancePtr)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnCreation();
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnStart(IntPtr scriptInstancePtr)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnStart();
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnUpdate(IntPtr scriptInstancePtr)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnUpdate();
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnLateUpdate(IntPtr scriptInstancePtr)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnLateUpdate();
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnDestroy(IntPtr scriptInstancePtr)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnDestroy();
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnEntering(IntPtr scriptInstancePtr, Entity entity)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnEntering(entity);
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnEntered(IntPtr scriptInstancePtr, Entity entity)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnEntered(entity);
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnExiting(IntPtr scriptInstancePtr, Entity entity)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnExiting(entity);
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnExited(IntPtr scriptInstancePtr, Entity entity)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.OnExited(entity);
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void Serialization(IntPtr scriptInstancePtr, nint nodeHandle)
        {
            var handle         = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.Serialization(new Serializer(nodeHandle));
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        public static void OnSubModelMove(IntPtr scriptInstancePtr, Entity newConnectedEntity)
        {
            var handle                     = GCHandle.FromIntPtr(scriptInstancePtr);
            var scriptBehavior             = (ScriptBehaviorComponent)handle.Target!;
            scriptBehavior.ConnectedEntity = newConnectedEntity;
            scriptBehavior.OnSubModelMove(newConnectedEntity);
        }
    }
}
