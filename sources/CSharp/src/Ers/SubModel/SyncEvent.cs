using System;
using Ers.Engine;
using static Ers.SyncEvent;

namespace Ers
{
    /// <summary>
    /// A simple interface that can be scheduled easily with a sync event.
    /// </summary>
    public interface ISyncEvent<T>
        where T : unmanaged, ISyncEvent<T> {

        static abstract string Name { get; }

        public abstract void OnSenderSide();

        public abstract void OnTargetSide();

        static void OnSenderSidePlain()
        {

            Ref<T> instance = GetData<T>();
            instance.Value.OnSenderSide();
        }

        static void OnTargetSidePlain()
        {
            Ref<T> instance = GetData<T>();
            instance.Value.OnTargetSide();
        }
    }

    /// <summary>
    /// Utility functions when inside of a sync event.
    /// </summary>
    public static class SyncEvent
    {
        /// <summary>
        /// Get data from a specific sync event.
        /// Data is automatically allocated when the sync event is scheduled.
        /// </summary>
        /// <typeparam name="T">The data type</typeparam>
        /// <param name="syncEventHandle">Pointer to the sync event</param>
        /// <returns>Reference to the data</returns>
        internal static Ref<T> GetData<T>(nint syncEventHandle)
            where T : unmanaged
        {
            unsafe
            {
                return new Ref<T>((T*)ErsEngine.ERS_SyncEvent_GetData(syncEventHandle));
            }
        }

        /// <summary>
        /// Get data from the current sync event (for use in callbacks).
        /// </summary>
        /// <typeparam name="T">The data type</typeparam>
        /// <returns>Reference to the data</returns>
        internal static Ref<T> GetData<T>()
            where T : unmanaged
        {
            unsafe
            {
                return new Ref<T>((T*)ErsEngine.ERS_SyncEvent_GetData(ErsEngine.ERS_ThreadLocal_GetCurrentSyncEvent()));
            }
        }

        /// <summary>
        /// Get a process stable value tied to type T, that won't change while the process is running.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        internal static ulong TypeIdentifier<T>() { return (ulong) typeof(T).TypeHandle.Value; }

        /// <summary>
        /// Whether the current thread is executing a sync event.
        /// </summary>
        /// <returns></returns>
        public static bool IsInsideSyncEvent
        {
            get => ErsEngine.ERS_ThreadLocal_IsInsideSyncEvent();
        }

        /// <summary>
        /// If inside a sync event, get the target simulator id of the sync event.
        /// </summary>
        /// <returns></returns>
        public static Int32 TargetSimulatorId
        {
            get => ErsEngine.ERS_ThreadLocal_GetSyncEventTarget();
        }

        /// <summary>
        /// If inside a sync event, get the sender simulator id of the sync event.
        /// </summary>
        /// <returns></returns>
        public static Int32 SenderSimulatorId
        {
            get => ErsEngine.ERS_ThreadLocal_GetSyncEventSender();
        }
    }
}
