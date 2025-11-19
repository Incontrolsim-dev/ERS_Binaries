#pragma once

#include "Ers/Math/HMM/VectorMath.h"

namespace Ers
{
    /// @brief Material containing color and texture information.
    class Material
    {
      public:
        explicit Material(void* corePointer);
        Material()                           = delete;
        Material(const Material&)            = default;
        Material(Material&&)                 = default;
        Material& operator=(const Material&) = default;
        Material& operator=(Material&&)      = default;
        ~Material()                          = default;

        /// @brief Get the base color of the material (RGB).
        /// @return The color as Vector3 (RGB, 0.0-1.0)
        [[nodiscard]] Ers::Vector3 Color() const;

        /// @brief Set the base color of the material (RGB).
        /// @param color The color as Vector3 (RGB, 0.0-1.0)
        void Color(const Ers::Vector3& color);

        void* Data();
        const void* const Data() const;

      private:
        void* data;
    };
} // namespace Ers
