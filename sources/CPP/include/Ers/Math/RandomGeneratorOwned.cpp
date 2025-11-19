#include "RandomGeneratorOwned.h"

#include <utility>

#include "Ers/Api.h"

namespace Ers
{
    /// @brief Creates a random number generator with the given pointer to the RandomGenerator in the core.
    /// @param coreInstance The pointer to the instance of an existing RandomGenerator in the core.
    /// @param owned Whether the RandomGenerator is owned and thus may be destroyed on deconstruction.
    RandomGeneratorOwned::RandomGeneratorOwned(void* coreInstance) :
        coreRandomGeneratorInstance(coreInstance)
    {
    }

    RandomGeneratorOwned::~RandomGeneratorOwned()
    {
        if (coreRandomGeneratorInstance == nullptr)
            return;

        ersAPIFunctionPointers.ERS_Random_Generator_Destroy(coreRandomGeneratorInstance);
    }

    RandomGeneratorOwned::RandomGeneratorOwned(RandomGeneratorOwned&& other) :
        coreRandomGeneratorInstance(std::exchange(other.coreRandomGeneratorInstance, nullptr))
    {
    }

    RandomGeneratorOwned& RandomGeneratorOwned::operator=(RandomGeneratorOwned&& other)
    {
        coreRandomGeneratorInstance = std::exchange(other.coreRandomGeneratorInstance, nullptr);
        return *this;
    }

    /// @brief Create a new owned Wichmann Hill pseudo-random number generator.
    /// @return The created random number generator instance.
    RandomGeneratorOwned RandomGeneratorOwned::CreateWichmannHill()
    {
        RandomGeneratorOwned generator = RandomGeneratorOwned(ersAPIFunctionPointers.ERS_Random_Generator_WichmannHill_Create());
        return generator;
    }

    /// @brief Create a new owned Mersenne Twister pseudo-random number generator.
    /// @return The created random number generator instance.
    RandomGeneratorOwned RandomGeneratorOwned::CreateMersenneTwister()
    {
        RandomGeneratorOwned generator = RandomGeneratorOwned(ersAPIFunctionPointers.ERS_Random_Generator_MersenneTwister_Create());
        return generator;
    }

    /// @brief Reset the seed of the random number generator.
    void RandomGeneratorOwned::Reset()
    {
        ersAPIFunctionPointers.ERS_Random_Generator_Reset(coreRandomGeneratorInstance);
    }

    /// @brief Set the set of the random number generator.
    /// @param seed The seed to set.
    void RandomGeneratorOwned::SetSeed(size_t seed)
    {
        ersAPIFunctionPointers.ERS_Random_Generator_Set_Seed(coreRandomGeneratorInstance, seed);
    }

    /// @brief Sample a random value from the random number generator.
    /// @return The sampled value.
    double RandomGeneratorOwned::Sample()
    {
        return ersAPIFunctionPointers.ERS_Random_Generator_Sample(coreRandomGeneratorInstance);
    }

    Ers::RandomGeneratorType RandomGeneratorOwned::GetRandomGeneratorType()
    {
        return static_cast<Ers::RandomGeneratorType>(ersAPIFunctionPointers.ERS_Random_Generator_GetType(coreRandomGeneratorInstance));
    }
} // namespace Ers
