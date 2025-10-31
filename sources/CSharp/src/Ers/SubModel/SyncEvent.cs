using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;
using static Ers.SyncEvent;

namespace Ers
{
    /// <summary>
    /// A simple interface that can be scheduled easily with a sync event
    /// </summary>
    public interface ISyncEvent<T> : IHasName<T>
        where T : unmanaged, ISyncEvent<T> {

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
    /// Utility functions when inside of a sync event
    /// </summary>
    public static class SyncEvent
    {
        /// <summary>
        /// Get data from the current sync event that matches T
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        internal static Ref<T> GetData<T>(nint syncEventHandle)
            where T : unmanaged
        {
            unsafe
            {
                ushort globalidx = ErsEngine.ERS_SyncEvent_GetOrRegisterDataContext(syncEventHandle, TypeIdentifier<T>(), (uint)sizeof(T));
                return new Ref<T>((T*)ErsEngine.ERS_SyncEvent_GetData(syncEventHandle, globalidx));
            }
        }

        /// <summary>
        /// Get data from the current sync event that matches T
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        internal static Ref<T> GetData<T>()
            where T : unmanaged { return GetData<T>(ErsEngine.ERS_ThreadLocal_GetCurrentSyncEvent()); }

        /// <summary>
        /// Get a process stable value tied to type T, that won't change while the process is running
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        internal static ulong TypeIdentifier<T>() { return (ulong) typeof(T).TypeHandle.Value; }

        /// <summary>
        /// Checks if the current thread is executing a sync event
        /// </summary>
        /// <returns></returns>
        public static bool IsInsideSyncEvent() { return ErsEngine.ERS_ThreadLocal_IsInsideSyncEvent(); }

        /// <summary>
        /// If inside a sync event, get the target simulator id of the sync event
        /// </summary>
        /// <returns></returns>
        public static Int32 GetTargetSimulatorId() { return ErsEngine.ERS_ThreadLocal_GetSyncEventTarget(); }

        /// <summary>
        /// If inside a sync event get the sender simulator id of the sync event
        /// </summary>
        /// <returns></returns>
        public static Int32 GetSenderSimulatorId() { return ErsEngine.ERS_ThreadLocal_GetSyncEventSender(); }
    }
}
