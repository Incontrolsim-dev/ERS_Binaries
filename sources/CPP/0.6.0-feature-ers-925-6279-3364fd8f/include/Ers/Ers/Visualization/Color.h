#pragma once

#include <cstdint>

namespace Ers::Visualization
{
    union Color
    {
        uint32_t value;
        struct
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        };

        // Default constructor
        constexpr Color() :
            value(0xFFFFFFFF)
        {
        } // Default to white

        // Constructor from uint32_t
        constexpr explicit Color(uint32_t val) :
            value(val)
        {
        }

        // Constructor from components
        constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) :
            r(red),
            g(green),
            b(blue),
            a(alpha)
        {
        }

        // Create from hex value (0xRRGGBB or 0xRRGGBBAA format)
        static constexpr Color FromHex(uint32_t hex)
        {
            // If only 24 bits provided (0xRRGGBB), assume full alpha
            if (hex <= 0xFFFFFF)
            {
                return Color{
                    static_cast<uint8_t>((hex >> 16) & 0xFF), // R
                    static_cast<uint8_t>((hex >> 8) & 0xFF),  // G
                    static_cast<uint8_t>(hex & 0xFF),         // B
                    255                                       // A
                };
            }
            else
            {
                return Color{
                    static_cast<uint8_t>((hex >> 24) & 0xFF), // R
                    static_cast<uint8_t>((hex >> 16) & 0xFF), // G
                    static_cast<uint8_t>((hex >> 8) & 0xFF),  // B
                    static_cast<uint8_t>(hex & 0xFF)          // A
                };
            }
        }

        // Create from RGBA components (0-255)
        static constexpr Color FromRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        {
            return Color{red, green, blue, alpha};
        }

        // Create from RGBA components (0.0-1.0)
        static constexpr Color FromRGBAFloat(float red, float green, float blue, float alpha = 1.0f)
        {
            return Color{
                static_cast<uint8_t>(red * 255.0f + 0.5f), static_cast<uint8_t>(green * 255.0f + 0.5f),
                static_cast<uint8_t>(blue * 255.0f + 0.5f), static_cast<uint8_t>(alpha * 255.0f + 0.5f)};
        }

        // Create from RGB components (0-255), full alpha
        static constexpr Color FromRGB(uint8_t red, uint8_t green, uint8_t blue) { return Color{red, green, blue, 255}; }

        // Create from RGB components (0.0-1.0), full alpha
        static constexpr Color FromRGBFloat(float red, float green, float blue) { return FromRGBAFloat(red, green, blue, 1.0f); }

        // Create from HSV (hue: 0-360, saturation: 0-1, value: 0-1)
        static constexpr Color FromHSV(float hue, float saturation, float value, float alpha = 1.0f)
        {
            float c = value * saturation;
            float x = c * (1.0f - ((hue / 60.0f - static_cast<int>(hue / 60.0f)) * 2.0f - 1.0f));
            if (x < 0.0f)
                x = -x; // abs
            float m = value - c;

            float r = 0.0f, g = 0.0f, b = 0.0f;
            if (hue < 60.0f)
            {
                r = c;
                g = x;
                b = 0.0f;
            }
            else if (hue < 120.0f)
            {
                r = x;
                g = c;
                b = 0.0f;
            }
            else if (hue < 180.0f)
            {
                r = 0.0f;
                g = c;
                b = x;
            }
            else if (hue < 240.0f)
            {
                r = 0.0f;
                g = x;
                b = c;
            }
            else if (hue < 300.0f)
            {
                r = x;
                g = 0.0f;
                b = c;
            }
            else
            {
                r = c;
                g = 0.0f;
                b = x;
            }

            return FromRGBA(r + m, g + m, b + m, alpha);
        }

        // Utility functions
        constexpr Color WithAlpha(uint8_t newAlpha) const { return Color{r, g, b, newAlpha}; }

        constexpr Color WithAlpha(float newAlpha) const { return WithAlpha(static_cast<uint8_t>(newAlpha * 255.0f + 0.5f)); }

        // Interpolate between two colors
        static constexpr Color Lerp(const Color& from, const Color& to, float t)
        {
            if (t <= 0.0f)
                return from;
            if (t >= 1.0f)
                return to;

            return Color{
                static_cast<uint8_t>(from.r + (to.r - from.r) * t + 0.5f), static_cast<uint8_t>(from.g + (to.g - from.g) * t + 0.5f),
                static_cast<uint8_t>(from.b + (to.b - from.b) * t + 0.5f), static_cast<uint8_t>(from.a + (to.a - from.a) * t + 0.5f)};
        }

        // Get normalized float values (0.0-1.0)
        constexpr float GetRedFloat() const { return r / 255.0f; }
        constexpr float GetGreenFloat() const { return g / 255.0f; }
        constexpr float GetBlueFloat() const { return b / 255.0f; }
        constexpr float GetAlphaFloat() const { return a / 255.0f; }

        // Operators
        constexpr bool operator==(const Color& other) const { return value == other.value; }
        constexpr bool operator!=(const Color& other) const { return value != other.value; }
    };

    // Predefined colors (constexpr constants)
    namespace Colors
    {
        // Basic colors
        constexpr Color WHITE       = Color::FromRGBA(255, 255, 255, 255);
        constexpr Color BLACK       = Color::FromRGBA(0, 0, 0, 255);
        constexpr Color RED         = Color::FromRGBA(255, 0, 0, 255);
        constexpr Color GREEN       = Color::FromRGBA(0, 255, 0, 255);
        constexpr Color BLUE        = Color::FromRGBA(0, 0, 255, 255);
        constexpr Color YELLOW      = Color::FromRGBA(255, 255, 0, 255);
        constexpr Color CYAN        = Color::FromRGBA(0, 255, 255, 255);
        constexpr Color MAGENTA     = Color::FromRGBA(255, 0, 255, 255);
        constexpr Color TRANSPARENT = Color::FromRGBA(0, 0, 0, 0);

        // Grays
        constexpr Color LIGHT_GRAY = Color::FromRGBA(192, 192, 192, 255);
        constexpr Color GRAY       = Color::FromRGBA(128, 128, 128, 255);
        constexpr Color DARK_GRAY  = Color::FromRGBA(64, 64, 64, 255);

        // Common UI colors
        constexpr Color ORANGE = Color::FromRGBA(255, 165, 0, 255);
        constexpr Color PURPLE = Color::FromRGBA(128, 0, 128, 255);
        constexpr Color PINK   = Color::FromRGBA(255, 192, 203, 255);
        constexpr Color BROWN  = Color::FromRGBA(165, 42, 42, 255);
        constexpr Color LIME   = Color::FromRGBA(0, 255, 0, 255);

        // Material design inspired
        constexpr Color SUCCESS = Color::FromHex(0x4CAF50); // Green
        constexpr Color WARNING = Color::FromHex(0xFFC107); // Amber
        constexpr Color ERROR   = Color::FromHex(0xF44336); // Red
        constexpr Color INFO    = Color::FromHex(0x00BCD4); // Cyan

        // Common mesh/debug colors
        constexpr Color DEBUG_RED   = Color::FromRGBA(255, 100, 100, 255);
        constexpr Color DEBUG_GREEN = Color::FromRGBA(100, 255, 100, 255);
        constexpr Color DEBUG_BLUE  = Color::FromRGBA(100, 100, 255, 255);
    } // namespace Colors

} // namespace Ers::Visualization
