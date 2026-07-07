#include "RandomGenerator.h"

#include <utility>

#include "Ers/Api.h"

namespace Ers
{
    /// @brief Reset the seed of the random number generator.
    void RandomGenerator::Reset()
    {
        Ers::Engine::ERS_Random_Generator_Reset(CorePtr());
    }

    /// @brief Set the set of the random number generator.
    /// @param seed The seed to set.
    void RandomGenerator::SetSeed(size_t seed)
    {
        Ers::Engine::ERS_Random_Generator_Set_Seed(CorePtr(), seed);
    }

    /// @brief Sample a random value from the random number generator.
    /// @return The sampled value.
    double RandomGenerator::Sample()
    {
        return Ers::Engine::ERS_Random_Generator_Sample(CorePtr());
    }

    Ers::RandomGeneratorType RandomGenerator::GetRandomGeneratorType()
    {
        return static_cast<Ers::RandomGeneratorType>(Ers::Engine::ERS_Random_Generator_GetType(CorePtr()));
    }
    void* RandomGenerator::CorePtr()
    {
        return this;
    }
    const void* const RandomGenerator::CorePtr() const
    {
        return this;
    }
} // namespace Ers
