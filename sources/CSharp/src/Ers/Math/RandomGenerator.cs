using Ers.Engine;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// A random number generator.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct RandomGenerator
    {
        internal readonly IntPtr Data;

        internal RandomGenerator(IntPtr data) { Data = data; }

        /// <summary>
        /// Reset the random number generator.
        /// </summary>
        public void Reset() => ErsEngine.ERS_Random_Generator_Reset(Data);

        /// <summary>
        /// Sample a random number between 0.0 and 1.0.
        /// </summary>
        /// <returns></returns>
        public double Sample() => ErsEngine.ERS_Random_Generator_Sample(Data);

        /// <summary>
        /// Set the seed of the random number generator.
        /// </summary>
        /// <param name="seed">The new seed.</param>
        public void SetSeed(nuint seed) => ErsEngine.ERS_Random_Generator_Set_Seed(Data, seed);

        /// <summary>
        /// Get the type of random number generator. See <see cref="RandomGeneratorType"/>.
        /// </summary>
        /// <returns></returns>
        public RandomGeneratorType GetRandomGeneratorType() => (RandomGeneratorType)ErsEngine.ERS_Random_Generator_GetType(Data);
    }
}
