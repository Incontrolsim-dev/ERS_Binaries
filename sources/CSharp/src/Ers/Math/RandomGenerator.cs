using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A random number generator.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct RandomGenerator
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal RandomGenerator(IntPtr data) { CorePtr = data; }

        /// <summary>
        /// Reset the random number generator.
        /// </summary>
        public void Reset() => ErsEngine.ERS_Random_Generator_Reset(CorePtr);

        /// <summary>
        /// Sample a random number between 0.0 and 1.0.
        /// </summary>
        /// <returns></returns>
        public double Sample() => ErsEngine.ERS_Random_Generator_Sample(CorePtr);

        /// <summary>
        /// Set the seed of the random number generator.
        /// </summary>
        /// <param name="seed">The new seed.</param>
        public void SetSeed(nuint seed) => ErsEngine.ERS_Random_Generator_Set_Seed(CorePtr, seed);

        /// <summary>
        /// Get the type of random number generator. See <see cref="RandomGeneratorType"/>.
        /// </summary>
        /// <returns></returns>
        public readonly RandomGeneratorType RandomGeneratorType
        {
            get => (RandomGeneratorType)ErsEngine.ERS_Random_Generator_GetType(CorePtr);
        }
    }
}
