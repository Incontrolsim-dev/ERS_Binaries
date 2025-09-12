#pragma once

#include <cstddef>

#include "Ers/Math/RandomGeneratorType.h"

namespace Ers::Math
{
    struct RandomGenerator
    {
      public:
        RandomGenerator()                                  = delete;
        RandomGenerator(const RandomGenerator&)            = delete;
        RandomGenerator(RandomGenerator&&)                 = delete;
        RandomGenerator& operator=(const RandomGenerator&) = delete;
        RandomGenerator& operator=(RandomGenerator&&)      = delete;
        ~RandomGenerator()                                 = delete;

        void Reset();
        void SetSeed(size_t seed);
        double Sample();

        Ers::Math::RandomGeneratorType GetRandomGeneratorType();

        void* Data();
        const void* const Data() const;
    };
} // namespace Ers::Math
