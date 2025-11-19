#pragma once

#include <cstdint>

namespace Ers
{
    /// @brief Enum for random generator types.
    enum class RandomGeneratorType : uint8_t
    {
        WichmannHill    = 0,
        MersenneTwister = 1,
        Invalid         = 2
    };
} // namespace Ers
