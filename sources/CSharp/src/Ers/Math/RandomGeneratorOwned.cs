using Ers.Engine;

namespace Ers.Math
{
    /// <summary>
    /// A random number generator that is not owned by user-code, not the ERS core.
    /// Therefore, it can be created and destroyed at will.
    /// </summary>
    public class RandomGeneratorOwned : IDisposable
    {
        private IntPtr coreRandomGeneratorInstance;

        internal RandomGeneratorOwned(IntPtr coreInstance) { coreRandomGeneratorInstance = coreInstance; }

        /// <summary>
        /// Destroy the random generator.
        /// </summary>
        public void Dispose()
        {
            if (coreRandomGeneratorInstance != IntPtr.Zero)
                return;

            ErsEngine.ERS_Random_Generator_Destroy(coreRandomGeneratorInstance);
            coreRandomGeneratorInstance = IntPtr.Zero;
        }

        /// <summary>
        /// Construct a new RandomGeneratorOwned of the Whichmann-Hill type.
        /// </summary>
        /// <returns></returns>
        public static RandomGeneratorOwned CreateWichmannHill()
        {
            return new RandomGeneratorOwned(ErsEngine.ERS_Random_Generator_WichmannHill_Create());
        }

        /// <summary>
        /// Construct a new RandomGeneratorOwned of the Mersenne Twister type.
        /// </summary>
        /// <returns></returns>
        public static RandomGeneratorOwned CreateMersenneTwister()
        {
            return new RandomGeneratorOwned(ErsEngine.ERS_Random_Generator_MersenneTwister_Create());
        }

        /// <summary>
        /// Reset the random number generator.
        /// </summary>
        public void Reset() => ErsEngine.ERS_Random_Generator_Reset(coreRandomGeneratorInstance);

        /// <summary>
        /// Sample a random number between 0.0 and 1.0.
        /// </summary>
        /// <returns></returns>
        public double Sample() => ErsEngine.ERS_Random_Generator_Sample(coreRandomGeneratorInstance);

        /// <summary>
        /// Set the seed of the random number generator.
        /// </summary>
        /// <param name="seed">The new seed.</param>
        public void SetSeed(nuint seed) => ErsEngine.ERS_Random_Generator_Set_Seed(coreRandomGeneratorInstance, seed);

        /// <summary>
        /// Get the type of random number generator. See <see cref="RandomGeneratorType"/>.
        /// </summary>
        /// <returns></returns>
        public RandomGeneratorType GetRandomGeneratorType()
        {
            return (RandomGeneratorType)ErsEngine.ERS_Random_Generator_GetType(coreRandomGeneratorInstance);
        }
    }
}
