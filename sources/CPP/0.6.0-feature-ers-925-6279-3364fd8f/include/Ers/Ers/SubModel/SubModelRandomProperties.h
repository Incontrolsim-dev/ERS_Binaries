#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

#include "Ers/Math/RandomGenerator.h"
#include "Ers/Math/RandomGeneratorType.h"

namespace Ers
{
    class SubModelRandomProperties
    {
      public:
        SubModelRandomProperties()                                           = delete;
        SubModelRandomProperties(const SubModelRandomProperties&)            = delete;
        SubModelRandomProperties(SubModelRandomProperties&&)                 = delete;
        SubModelRandomProperties& operator=(SubModelRandomProperties&&)      = delete;
        SubModelRandomProperties& operator=(const SubModelRandomProperties&) = delete;
        ~SubModelRandomProperties()                                          = delete;

        void SetRandomGenerator(Ers::Math::RandomGeneratorType randomNumberGeneratorType);
        void SetRepetitive(bool value);
        void SetAntithetical(bool value);
        void SetSeed(size_t seed);
        bool IsRepetitive();
        bool IsAntithetical();

        [[nodiscard]] size_t GetOriginalSeed() const;

        [[nodiscard]] Ers::Math::RandomGenerator& GetRandomNumberGenerator();

        void* Data();
        const void* const Data() const;
    };
} // namespace Ers
