using Ers.Engine;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// The properties of the <see cref="RandomGenerator"/> attached to a <see cref="SubModel"/>.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct SubModelRandomProperties
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal SubModelRandomProperties(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// Set the random number generator by its type.
        /// </summary>
        /// <param name="randomNumberGeneratorType">The type of the new random number generator. See <see
        /// cref="RandomGeneratorType"/>.</param>
        public void SetRandomGenerator(RandomGeneratorType randomNumberGeneratorType)
        {
            ErsEngine.ERS_SubModelRandomProperties_SetRandomGenerator_Type(CorePtr, (int)randomNumberGeneratorType);
        }

        /// <summary>
        /// Get the random number generator attached to the <see cref="SubModel"/>.
        /// </summary>
        /// <returns></returns>
        public RandomGenerator GetRandomNumberGenerator()
        {
            IntPtr coreRandomGeneratorInstance = ErsEngine.ERS_SubModelRandomProperties_GetRandomNumberGenerator(CorePtr);

            unsafe
            {
                return new RandomGenerator(coreRandomGeneratorInstance);
            }
        }
    }
}
