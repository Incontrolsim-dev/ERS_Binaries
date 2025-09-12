using System;

namespace Ers
{
    /// <summary>
    /// Available types of random number generator.
    /// </summary>
    public enum RandomGeneratorType
    {
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
        WichmannHill    = 0,
        MersenneTwister = 1,
        Invalid         = 2
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
    }
}
