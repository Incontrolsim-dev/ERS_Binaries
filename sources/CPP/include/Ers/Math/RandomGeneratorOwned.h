#pragma once

#include <cstddef>

#include "Ers/Math/RandomGeneratorType.h"

namespace Ers
{
    class RandomGeneratorOwned
    {
      public:
        RandomGeneratorOwned(void* coreInstance);
        ~RandomGeneratorOwned();
        static RandomGeneratorOwned CreateWichmannHill();
        static RandomGeneratorOwned CreateMersenneTwister();

        RandomGeneratorOwned()                            = delete;
        RandomGeneratorOwned(const RandomGeneratorOwned&) = delete;
        RandomGeneratorOwned(RandomGeneratorOwned&&);
        RandomGeneratorOwned& operator=(const RandomGeneratorOwned&) = delete;
        RandomGeneratorOwned& operator=(RandomGeneratorOwned&&);

        void Reset();
        void SetSeed(size_t seed);
        double Sample();

        Ers::RandomGeneratorType GetRandomGeneratorType();

      private:
        void* coreRandomGeneratorInstance = nullptr;
    };
} // namespace Ers
