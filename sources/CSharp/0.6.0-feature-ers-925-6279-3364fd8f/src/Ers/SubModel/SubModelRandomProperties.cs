using Ers.Engine;
using Ers.Math;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// The properties of the <see cref="RandomGenerator"/> attached to a <see cref="SubModel"/>.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct SubModelRandomProperties
    {
        internal readonly IntPtr Data;

        internal SubModelRandomProperties(IntPtr data) { Data = data; }

        /// <summary>
        /// Set the random number generator by its type.
        /// </summary>
        /// <param name="randomNumberGeneratorType">The type of the new random number generator. See <see
        /// cref="RandomGeneratorType"/>.</param>
        public void SetRandomGenerator(RandomGeneratorType randomNumberGeneratorType)
        {
            ErsEngine.ERS_SubModelRandomProperties_SetRandomGenerator_Type(Data, (int)randomNumberGeneratorType);
        }

        /// <summary>
        /// Get the random number generator attached to the <see cref="SubModel"/>.
        /// </summary>
        /// <returns></returns>
        public RandomGenerator GetRandomNumberGenerator()
        {
            IntPtr coreRandomGeneratorInstance = ErsEngine.ERS_SubModelRandomProperties_GetRandomNumberGenerator(Data);

            unsafe
            {
                return new RandomGenerator(coreRandomGeneratorInstance);
            }
        }
    }
}
