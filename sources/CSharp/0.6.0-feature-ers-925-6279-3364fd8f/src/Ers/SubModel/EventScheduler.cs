using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Ers.Engine;

// Ensure that the JIT does not patch functions for optimizations, can be removed after this is fixed
// https://github.com/dotnet/runtime/issues/102767
[assembly:Debuggable(DebuggableAttribute.DebuggingModes.DisableOptimizations)]
namespace Ers
{
    /// <summary>
    /// Controlling events in ERS.
    /// </summary>
    public static class EventScheduler
    {
        /// <summary>
        /// Local event type signature.
        /// </summary>
        public delegate void LocalEventCallback();

#if true // This enabled delegate object based routing (much slower, but doesn't suffer from runtime crashes)

        // Debug Mode: Use marshaled delegate for compatibility. Remove this when patch skipping is solved.
        // TODO: Remove when the C# runtime is fixed and the patch skipping bug is solved.
        // https://github.com/dotnet/runtime/issues/102767

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void UnmanagedCallback(nint handlePtr);

        private static readonly UnmanagedCallback _callbackDelegate       = ScheduleLocalEvent_EventCallbackFunction;
        private static readonly UnmanagedCallback _cancelCallbackDelegate = ScheduleLocalEvent_CancelEventCallbackFunction;

        [MethodImpl(MethodImplOptions.NoOptimization)]
        static void ScheduleLocalEvent_EventCallbackFunction(nint handlePtr)
        {
            GCHandle handle = GCHandle.FromIntPtr(handlePtr);
            var callback    = (LocalEventCallback)handle.Target!;
            callback();
            handle.Free();
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        static void ScheduleLocalEvent_CancelEventCallbackFunction(nint handlePtr)
        {
            GCHandle handle = GCHandle.FromIntPtr(handlePtr);
            handle.Free();
        }

        public static UInt32 ScheduleLocalEvent(int priority, SimulationTime delayTime, LocalEventCallback eventCallback)
        {
            GCHandle handle  = GCHandle.Alloc(eventCallback, GCHandleType.Normal);
            IntPtr handlePtr = GCHandle.ToIntPtr(handle);

            // Get function pointer for delegate (Debug Mode)
            IntPtr callbackPtr           = Marshal.GetFunctionPointerForDelegate(_callbackDelegate);
            IntPtr destructorCallbackPtr = Marshal.GetFunctionPointerForDelegate(_cancelCallbackDelegate);

            unsafe
            {
                return ErsEngine.ERS_EventScheduler_ScheduleLocalEvent(
                    priority, delayTime, handlePtr, (delegate * unmanaged[Cdecl]<nint, void>)callbackPtr,
                    (delegate * unmanaged[Cdecl]<nint, void>)destructorCallbackPtr);
            }
        }

#else
        // Release Mode: Use UnmanagedCallersOnly for direct interop
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        [MethodImpl(MethodImplOptions.NoOptimization)]
        static void ScheduleLocalEvent_EventCallbackFunction(nint handlePtr)
        {
            GCHandle handle = GCHandle.FromIntPtr(handlePtr);
            var callback    = (LocalEventCallback)handle.Target!;
            callback();
            handle.Free();
        }

        // Release Mode: Use UnmanagedCallersOnly for direct interop
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        [MethodImpl(MethodImplOptions.NoOptimization)]
        static void ScheduleLocalEvent_CancelEventCallbackFunction(nint handlePtr)
        {
            GCHandle handle = GCHandle.FromIntPtr(handlePtr);
            handle.Free();
        }

        public static UInt32 ScheduleLocalEvent(int priority, SimulationTime delayTime, LocalEventCallback eventCallback)
        {
            GCHandle handle  = GCHandle.Alloc(eventCallback, GCHandleType.Normal);
            IntPtr handlePtr = GCHandle.ToIntPtr(handle);

            unsafe
            {
                delegate* unmanaged[Cdecl]<nint, void> callbackPtr   = &ScheduleLocalEvent_EventCallbackFunction;
                delegate* unmanaged[Cdecl]<nint, void> destructorPtr = &ScheduleLocalEvent_CancelEventCallbackFunction;

                return ErsEngine.ERS_EventScheduler_ScheduleLocalEvent(priority, delayTime, handlePtr, callbackPtr, destructorPtr);
            }
        }
#endif

        /// <summary>
        /// Cancel a Local or Sync event in the current SubModel.
        /// </summary>
        /// <param name="eventKey">The ID of the event.</param>
        public static void CancelEvent(UInt32 eventKey) { ErsEngine.ERS_EventScheduler_CancelEvent(eventKey); }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        static void ScheduleSyncEvent_CoreOnSenderSideEvent()
        {
            unsafe
            {
                ((delegate *
                  managed<void>*)ErsEngine.ERS_SyncEvent_GetSyncEventMetaData(ErsEngine.ERS_ThreadLocal_GetCurrentSyncEvent()))[0]();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
        static void ScheduleSyncEvent_CoreOnTargetSideEvent()
        {
            unsafe
            {
                ((delegate *
                  managed<void>*)ErsEngine.ERS_SyncEvent_GetSyncEventMetaData(ErsEngine.ERS_ThreadLocal_GetCurrentSyncEvent()))[1]();
            }
        }

        /// <summary>
        /// (Base) Schedule a sync event between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="eventName">Name to identify this event by: Note this must be an interned string</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        /// <param name="eventTypeIdentifier"></param>
        /// <param name="senderSide">The function that is called in this SubModel's simulator when the sync event is triggered.</param>
        /// <param name="targetSide">The function that is called in target SubModel's simulator when the sync event is triggered</param>
        private static unsafe nint CoreScheduleSyncEvent(
            byte* eventName,
            SimulationTime delayTime,
            int targetSimulatorId,
            ulong eventTypeIdentifier,
            delegate* managed<void> senderSide,
            delegate* managed<void> targetSide)
        {
            nint syncEventHandle = ErsEngine.ERS_EventScheduler_ScheduleSyncEvent(
                delayTime, targetSimulatorId, eventTypeIdentifier, &ScheduleSyncEvent_CoreOnSenderSideEvent,
                &ScheduleSyncEvent_CoreOnTargetSideEvent);

            nint* metaData = (nint*)ErsEngine.ERS_SyncEvent_GetSyncEventMetaData(syncEventHandle);
#if DEBUG
            // Ensure that senderside and targetside are never different for every type of sync event
            nint previousSenderSide = metaData[0];
            Debug.Assert(previousSenderSide == (nint)senderSide || previousSenderSide == 0);

            nint previousTargetSide = metaData[1];
            Debug.Assert(previousTargetSide == (nint)targetSide || previousTargetSide == 0);
#endif
            // Set name on the identifier
            ErsEngine.ERS_SyncEvent_SetSyncEventName(syncEventHandle, eventName);

            // Set managed callbacks
            metaData[0] = (nint)senderSide;
            metaData[1] = (nint)targetSide;

            return syncEventHandle;
        }

        /// <summary>
        /// Schedule a sync event between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="eventName">Name to identify this event by: Note this must be an interned string</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        /// <param name="eventTypeIdentifier"></param>
        /// <param name="senderSide">The function that is called in this SubModel's simulator when the sync event is triggered.</param>
        /// <param name="targetSide">The function that is called in target SubModel's simulator when the sync event is triggered</param>
        private static unsafe nint InternalScheduleSyncEvent(
            ReadOnlySpan<byte> eventName,
            SimulationTime delayTime,
            int targetSimulatorId,
            ulong eventTypeIdentifier,
            delegate* managed<void> senderSide,
            delegate* managed<void> targetSide)
        {
            fixed(byte* firstCharacter = eventName)
            {
                return CoreScheduleSyncEvent(firstCharacter, delayTime, targetSimulatorId, eventTypeIdentifier, senderSide, targetSide);
            }
        }

        /// <summary>
        /// Schedule a sync event between the current SubModel's simulator and another.
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        /// <param name="data">An additional datafield, this will be directly send to along with the sync event</param>
        public static uint ScheduleSyncEvent<SyncEventType>(SimulationTime delayTime, int targetSimulatorId, ref SyncEventType data)
            where SyncEventType : unmanaged, ISyncEvent<SyncEventType>
        {
            unsafe
            {
                nint syncEvent = InternalScheduleSyncEvent(
                    NameUtf8Helper<SyncEventType>.NameUtf8Bytes, delayTime, targetSimulatorId, SyncEvent.TypeIdentifier<SyncEventType>(),
                    &ISyncEvent<SyncEventType>.OnSenderSidePlain, &ISyncEvent<SyncEventType>.OnTargetSidePlain);

                Ref<SyncEventType> syncEventData = SetData<SyncEventType>();
                fixed(SyncEventType* syncEventDataPtr = &syncEventData.Value)
                {
                    Unsafe.Write(syncEventDataPtr, data);
                }

                return ErsEngine.ERS_EventScheduler_ExchangeSyncEventForEventID(syncEvent);
            }
        }

        /// <summary>
        /// (Zero Copy) Schedule a sync event between the current SubModel's simulator and another.
        /// T is allocated directly in the core, for fast lazy initialization
        /// </summary>
        /// <param name="delayTime">The time from now until the event is triggered.</param>
        /// <param name="targetSimulatorId">The ID of the simulator to which data is sent.</param>
        public static Ref<SyncEventType> ScheduleSyncEvent<SyncEventType>(SimulationTime delayTime, int targetSimulatorId)
            where SyncEventType : unmanaged, ISyncEvent<SyncEventType>
        {
            unsafe
            {
                nint syncEvent = InternalScheduleSyncEvent(
                    NameUtf8Helper<SyncEventType>.NameUtf8Bytes, delayTime, targetSimulatorId, SyncEvent.TypeIdentifier<SyncEventType>(),
                    &ISyncEvent<SyncEventType>.OnSenderSidePlain, &ISyncEvent<SyncEventType>.OnTargetSidePlain);

                var data = SetData<SyncEventType>();
                return data;
            }
        }

        /// <summary>
        /// Delay a local event in the current SubModel.
        /// </summary>
        /// <param name="key">The ID of the event.</param>
        /// <param name="updatedDelayTime">The additional delay time for the event.</param>
        public static void DelayEvent(int key, SimulationTime updatedDelayTime)
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

        private static Ref<T> SetData<T>()
            where T : unmanaged { return SyncEvent.GetData<T>(ErsEngine.ERS_EventScheduler_LastScheduledSyncEvent()); }

        public static UInt32 GetLastSyncEventEventCode()
        {
            return ErsEngine.ERS_EventScheduler_ExchangeSyncEventForEventID(ErsEngine.ERS_EventScheduler_LastScheduledSyncEvent());
        }
    }
}
