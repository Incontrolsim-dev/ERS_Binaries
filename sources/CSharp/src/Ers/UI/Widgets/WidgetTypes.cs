using System;

namespace Ers
{
    /// <summary>
    /// Possible selected types.
    /// </summary>
    public enum SelectedType : byte
    {
        /// <summary>
        /// No type is selected.
        /// </summary>
        None = 0,
        /// <summary>
        /// A <see cref="ModelContainer"/> is selected.
        /// </summary>
        ModelContainer = 1,
        /// <summary>
        /// A <see cref="Simulator"/> is selected.
        /// </summary>
        Simulator = 2,
        /// <summary>
        /// An Entity is selected.
        /// </summary>
        Entity = 3,
        /// <summary>
        /// A <see cref="SimEvent"/> is selected (using a <see cref="PersistentEvent"/>).
        /// </summary>
        Event = 4,
    }
}
