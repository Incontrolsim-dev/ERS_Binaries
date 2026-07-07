using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// An ERS event (either local- or sync-event).
    ///
    /// <para>
    /// IMPORTANT: Event should always be scheduled using
    /// <see cref="EventScheduler.ScheduleLocalEvent{TContext}(int, ulong, TContext)"/> or <see
    /// cref="EventScheduler.ScheduleSyncEvent{SyncEventType}(ulong, int)"/>.
    /// Only use this type if you wish to use it as a temporary local variable.
    /// </para>
    /// <para>
    /// DO NOT store this as a variable. Store a <see cref="PersistentEvent"/> instead.
    /// </para>
    /// </summary>
    public ref struct SimEvent
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Create a new empty <see cref="SimEvent"/> instance.
        /// </summary>
        public SimEvent() { CorePtr = IntPtr.Zero; }

        internal SimEvent(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// The simulation time at which the event is scheduled to be executed.
        /// </summary>
        public readonly SimulationTime Time => ErsEngine.ERS_SimEvent_Get_Time(CorePtr);

        /// <summary>
        /// The priority of the event.
        /// </summary>
        public readonly uint Priority => ErsEngine.ERS_SimEvent_Get_Priority(CorePtr);

        /// <summary>
        /// Whether the event is a sync-event.
        /// </summary>
        public readonly bool IsSyncEvent => ErsEngine.ERS_SimEvent_IsSyncEvent(CorePtr);
    }
}
