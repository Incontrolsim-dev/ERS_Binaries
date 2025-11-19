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

        /// @brief Get the corner with the lowest values.
        /// @return The minimum corner
        [[nodiscard]] Vector3 Min() const;

        /// @brief Get the corner with the highest values.
        /// @return The maximum corner
        [[nodiscard]] Vector3 Max() const;

        /// @brief Get the dimensions of the bounding box.
        /// @return The dimensions
        [[nodiscard]] Vector3 GetDimensions() const;

        /// @brief Set the dimensions of the bounding box.
        /// @param dims The new dimensions.
        void SetDimensions(Vector3 dims);

        /// @brief Check whether a 2D point is within the bounding box.
        /// @param point The 2D point to test
        /// @return True if the point is within the box
        [[nodiscard]] bool InCollision(const Vector2& point) const;

        /// @brief Check whether a ray intersects the bounding box.
        /// @param ray The ray to test
        /// @return True if the ray intersects the box
        [[nodiscard]] bool InCollision(const Ray& ray) const;
    };
} // namespace Ers
