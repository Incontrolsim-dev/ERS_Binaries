using System;

namespace Ers
{
    /// <summary>
    /// The type of simulaton a simulator is performing.
    /// </summary>
    public enum SimulatorType : byte
    {
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
        Unknown       = 99,
        DiscreteEvent = 0,
        AgentBased    = 1,
        Continuous    = 2,
        Emulation     = 3
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
    }
}
