using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// <see cref="Simulator"/> and <see cref="SimEvent"/> pair to persistently store a <see cref="SimEvent"/>, even after the event has
    /// been executed.
    /// </summary>
    public class PersistentEvent
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Whether the internal <see cref="Simulator"/> and <see cref="SimEvent"/> are set.
        /// Returns true when they are not set, false if they are.
        /// </summary>
        public bool IsEmpty => ErsEngine.ERS_PersistentEvent_IsEmpty(CorePtr);

        /// <summary>
        /// The internal <see cref="Simulator"/>.
        ///
        /// <para>This assumes the <see cref="PersistentEvent"/> is not empty, so be sure to call <see cref="IsEmpty"/> first!</para>
        /// </summary>
        public Simulator Simulator => new Simulator(ErsEngine.ERS_PersistentEvent_GetSimulator(CorePtr));

        /// <summary>
        /// The internal <see cref="SimEvent"/>.
        ///
        /// <para>This assumes the <see cref="PersistentEvent"/> is not empty, so be sure to call <see cref="IsEmpty"/> first!</para>
        /// </summary>
        public SimEvent SimEvent => new SimEvent(ErsEngine.ERS_PersistentEvent_GetSimEvent(CorePtr));

        /// <summary>
        /// Create a new empty <see cref="PersistentEvent"/> instance.
        /// </summary>
        public PersistentEvent() { CorePtr = ErsEngine.ERS_PersistentEvent_Create(); }

        /// <summary>
        /// Finalizer that cleans up the core instance.
        /// </summary>
        ~PersistentEvent() { ErsEngine.ERS_PersistentEvent_Release(CorePtr); }
    }
}
