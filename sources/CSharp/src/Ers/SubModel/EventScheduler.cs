using Ers.Engine;
using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;

[assembly:Debuggable(DebuggableAttribute.DebuggingModes.DisableOptimizations)]
namespace Ers
{
    /// <summary>
    /// Controlling events in ERS.
    /// </summary>
    public static class EventScheduler
    {
        /// <summary>
        /// Register a local event type explicitly before simulation creation.
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling this multiple times for the same type is safe and results in a no-op.
        /// </summary>
        public static void RegisterLocalEvent<TContext>()
            where TContext : struct, ILocalEvent<TContext>
        {
            // Delegate to the registry class which handles the actual registration
            LocalEventRegistry<TContext>.Register();
        }

        /// <summary>
        /// Register a sync event type explicitly before simulation creation.
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling this multiple times for the same type is safe and results in a no-op.
        /// </summary>
        public static void RegisterSyncEvent<T>()
            where T : unmanaged, ISyncEvent<T>
        {
            // Delegate to the registry class which handles the actual registration
            SyncEventRegistry<T>.Register();
        }

        /// <summary>
        /// Schedule a local event with the specified closure type.
        /// Direct static field access provides zero-cost registration lookup.
        /// Use this overload when you know the closure type at compile time for maximum performance.
        /// </summary>
        /// <typeparam name="TContext">The closure type for lambda captures, or NoClosureContext for static methods</typeparam>
        /// <param name="priority">Event priority</param>
        /// <param name="delayTime">Delay before event fires</param>
        /// <param name="eventCallback">The callback to invoke</param>
        /// <returns>Event handle</returns>
        public static ErsLocalEvent ScheduleLocalEvent<TContext>(int priority, SimulationTime delayTime, TContext eventCallback)
            where TContext : struct, ILocalEvent<TContext>
        {
            return ErsEngine.ERS_EventScheduler_ScheduleLocalEvent(
                priority, delayTime, LocalEventRegistry<TContext>.AllocateEventData(eventCallback), LocalEventRegistry<TContext>.Handle);
        }

        /// <summary>
        /// Cancel a Local or Sync event in the current SubModel.
        /// </summary>
        /// <param name="eventKey">The ID of the event.</param>
        public static void CancelEvent(ErsLocalEvent eventKey) { ErsEngine.ERS_EventScheduler_CancelEvent(eventKey); }

        /// <summary>
        /// (Base) Schedule a sync event between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        /// <param name="syncEventTypeHandle">Direct pointer to the registered event type (from SyncEventTypeCache)</param>
        private static unsafe nint CoreScheduleSyncEvent<T>(SimulationTime delayTime, int targetSimulatorId, nint syncEventTypeHandle)
            where T : unmanaged, ISyncEvent<T>
        {
            nint syncEventHandle = ErsEngine.ERS_EventScheduler_ScheduleSyncEvent(delayTime, targetSimulatorId, syncEventTypeHandle);

            return syncEventHandle;
        }

        /// <summary>
        /// Schedule a sync event between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        private static unsafe nint InternalScheduleSyncEvent<T>(SimulationTime delayTime, int targetSimulatorId)
            where T : unmanaged, ISyncEvent<T>
        {
            // Direct static field access - ZERO COST! No dictionary, no hash lookup!
            // Use pre-created unmanaged function pointers from SyncEventRegistry<T>
            return CoreScheduleSyncEvent<T>(delayTime, targetSimulatorId, SyncEventRegistry<T>.Handle);
        }

        /// <summary>
        /// Schedule a sync event between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        /// <param name="data">An additional datafield, this will be directly send to along with the sync event</param>
        /// <returns>The event ID of the scheduled sync-event. The value is 0 if the sync event failed to schedule.</returns>
        public static uint ScheduleSyncEvent<SyncEventType>(SimulationTime delayTime, int targetSimulatorId, in SyncEventType data)
            where SyncEventType : unmanaged, ISyncEvent<SyncEventType>
        {
            unsafe
            {
                nint syncEvent = InternalScheduleSyncEvent<SyncEventType>(delayTime, targetSimulatorId);
                if (syncEvent == IntPtr.Zero)
                    return 0; // Invalid sync-event (failed to schedule)

                Ref<SyncEventType> syncEventData = GetLastScheduledEventData<SyncEventType>();
                fixed(SyncEventType* syncEventDataPtr = &syncEventData.Value)
                {
                    Unsafe.Write(syncEventDataPtr, data);
                }

                return ErsEngine.ERS_EventScheduler_ExchangeSyncEventForEventID(syncEvent);
            }
        }

        /// <summary>
        /// Delay a local event in the current SubModel.
        /// </summary>
        /// <param name="key">The ID of the event.</param>
        /// <param name="updatedDelayTime">The additional delay time for the event.</param>
        public static void DelayEvent(ErsLocalEvent key, SimulationTime updatedDelayTime)
        {
            ErsEngine.ERS_EventScheduler_DelayEvent(key, updatedDelayTime);
        }

        /// <summary>
        /// Set a promise between the current SubModel's simulator and another.
        ///
        /// <para>
        /// A promise is the minimum time between scheduling an event and executing it on the target simulator.
        /// Used for optimizing the event schedule.
        /// </para>
        /// </summary>
        /// <param name="toSimulatorID">The simulator to which will be scheduled.</param>
        /// <param name="delayTime"></param>
        public static void SetPromise(int toSimulatorID, SimulationTime delayTime)
        {
            ErsEngine.ERS_EventScheduler_SetPromise(delayTime, toSimulatorID);
        }

        /// <summary>
        /// Get the promise between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="toSimulatorID">The simulator to which is scheduled.</param>
        /// <returns></returns>
        public static SimulationTime GetPromise(int toSimulatorID) { return ErsEngine.ERS_EventScheduler_GetPromise(toSimulatorID); }

        /// <summary>
        /// Get a unique identifier of the type of last scheduled sync event.
        /// All sync events with the same name, share this identifier, if the event name string was stable
        /// </summary>
        /// <returns></returns>
        public static UInt32 GetSyncEventUID()
        {
            return ErsEngine.ERS_SyncEvent_GetSyncEventUID(ErsEngine.ERS_EventScheduler_LastScheduledSyncEvent());
        }

        private static Ref<T> GetLastScheduledEventData<T>()
            where T : unmanaged { return SyncEvent.GetData<T>(ErsEngine.ERS_EventScheduler_LastScheduledSyncEvent()); }

        public static UInt32 GetLastSyncEventEventCode()
        {
            return ErsEngine.ERS_EventScheduler_ExchangeSyncEventForEventID(ErsEngine.ERS_EventScheduler_LastScheduledSyncEvent());
        }
    }
}
