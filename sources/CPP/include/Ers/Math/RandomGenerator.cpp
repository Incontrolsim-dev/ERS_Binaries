#include "RandomGenerator.h"

#include <utility>

#include "Ers/Api.h"

namespace Ers::Math
{
    /// @brief Reset the seed of the random number generator.
    void RandomGenerator::Reset()
    {
        ersAPIFunctionPointers.ERS_Random_Generator_Reset(Data());
    }

    /// @brief Set the set of the random number generator.
    /// @param seed The seed to set.
    void RandomGenerator::SetSeed(size_t seed)
    {
        ersAPIFunctionPointers.ERS_Random_Generator_Set_Seed(Data(), seed);
    }

    /// @brief Sample a random value from the random number generator.
    /// @return The sampled value.
    double RandomGenerator::Sample()
    {
        return ersAPIFunctionPointers.ERS_Random_Generator_Sample(Data());
    }

    Ers::Math::RandomGeneratorType RandomGenerator::GetRandomGeneratorType()
    {
        return static_cast<Ers::Math::RandomGeneratorType>(ersAPIFunctionPointers.ERS_Random_Generator_GetType(Data()));
    }
    void* RandomGenerator::Data()
    {
        return this;
    }
    const void* const RandomGenerator::Data() const
    {
        return this;
    }
} // namespace Ers::Math
