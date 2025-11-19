#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/CoreComponent.h"

#include <cstdint>

namespace Ers
{
    /// @brief A component to attach physical dimensions to an entity.
    /// Note: by default, it is assumed a TransformComponent's position is at the back top-left corner (-X, -Y, +Z).
    /// Setting the dimensions will automatically set the center of the outline to follow this style.
    /// If you wish to offset the outline, manually adjust the center variable after setting the dimensions.
    class OutlineComponent : public CoreComponent
    {
      public:
        OutlineComponent()                                   = default;
        OutlineComponent(const OutlineComponent&)            = delete;
        OutlineComponent(OutlineComponent&&)                 = delete;
        OutlineComponent& operator=(const OutlineComponent&) = delete;
        OutlineComponent& operator=(OutlineComponent&&)      = delete;
        ~OutlineComponent()                                  = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the center of the entity.
        /// @return The center point
        [[nodiscard]] Vector3 Center() const;

        /// @brief Set the center of the entity.
        /// Note: always set the dimensions first, otherwise the custom center will be overwritten.
        /// @param center The new center point
        void Center(const Vector3& center);

        /// @brief Get the dimensions of the entity.
        /// @return The dimensions
        [[nodiscard]] Vector3 Dimensions() const;

        /// @brief Set the dimensions of the entity.
        /// @param dimensions The new dimensions
        void Dimensions(const Vector3& dimensions);
    };
} // namespace Ers
