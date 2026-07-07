#pragma once

#include "Ers/Visualization/Color.h"

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

        /// @brief Get the base color of the material.
        /// @return The color.
        [[nodiscard]] Ers::Color GetColor() const;

        /// @brief Set the base color of the material.
        /// @param color The color
        void SetColor(Ers::Color color);

        void* CorePtr();
        const void* const CorePtr() const;

      private:
        void* data;
    };
} // namespace Ers
