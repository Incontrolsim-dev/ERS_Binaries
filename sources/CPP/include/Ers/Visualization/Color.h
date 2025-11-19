#pragma once

#include <cstdint>

namespace Ers
{
    /// <summary>
    /// Color union with RGBA components.
    /// Memory layout: R-G-B-A (ABGR when read as uint32).
    /// </summary>
    union Color
    {
        uint32_t Value;
        struct
        {
            uint8_t R;
            uint8_t G;
            uint8_t B;
            uint8_t A;
        };

        Color() = default;

        /// @brief Create new color from a uint32_t value.
        /// @param value The color value (ABGR format)
        /// @return
        static constexpr Color FromInt(uint32_t value)
        {
            Color color;
            color.Value = value;
            return color;
        }

        /// @brief Create new color from RGBA byte components.
        /// @param red Red (0-255)
        /// @param green Green (0-255)
        /// @param blue Blue (0-255)
        /// @param alpha Alpha (0-255)
        /// @return
        static constexpr Color FromBytes(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        {
            Color color;
            color.R = red;
            color.G = green;
            color.B = blue;
            color.A = alpha;
            return color;
        }

        /// @brief Create new color from RGBA components as floats (0.0-1.0).
        /// @param red Red (0.0-1.0)
        /// @param green Green (0.0-1.0)
        /// @param blue Blue (0.0-1.0)
        /// @param alpha Alpha (0.0-1.0)
        static constexpr Color FromFloats(float red, float green, float blue, float alpha = 1.0f)
        {
            Color color;
            color.R = static_cast<uint8_t>(red * 255.0f);
            color.G = static_cast<uint8_t>(green * 255.0f);
            color.B = static_cast<uint8_t>(blue * 255.0f);
            color.A = static_cast<uint8_t>(alpha * 255.0f);
            return color;
        }

        // Operators
        constexpr bool operator==(const Color& other) const { return Value == other.Value; }
        constexpr bool operator!=(const Color& other) const { return Value != other.Value; }
    };

} // namespace Ers
