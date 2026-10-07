#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/CoreComponent.h"

#include <cstdint>

namespace Ers
{
    struct Ray;

    /// @brief A component to add collision detection to an entity.
    /// The component should also have a TransformComponent and an OutlineComponent.
    class BoxComponent : public CoreComponent
    {
      public:
        BoxComponent()                               = default;
        BoxComponent(const BoxComponent&)            = delete;
        BoxComponent(BoxComponent&&)                 = delete;
        BoxComponent& operator=(const BoxComponent&) = delete;
        BoxComponent& operator=(BoxComponent&&)      = delete;
        ~BoxComponent()                              = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the dimensions of the bounding box.
        /// @return The dimensions
        [[nodiscard]] Vector3 GetDimensions() const;

        /// @brief Set the dimensions of the bounding box.
        /// @param dims The new dimensions.
        void SetDimensions(Vector3 dims);
    };
} // namespace Ers
