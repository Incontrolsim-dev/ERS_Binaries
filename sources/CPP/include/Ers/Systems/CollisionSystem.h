#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Math/Ray.h"
#include "Ers/SubModel/Component/BoxComponent.h"
#include "Ers/SubModel/Component/TransformComponent.h"

namespace Ers
{
    /// @brief System for collision between different object.
    class CollisionSystem
    {
      public:
        /// @brief Check if an entity's bounding box collides with a 2D point (is the point inside the box).
        /// @param box The box component to use.
        /// @param transform The transform component to use.
        /// @param point The point to check collision with.
        /// @return Whether the 2D point collides with the bounding box.
        static bool InCollision(const BoxComponent& box, TransformComponent& transform, Vector2 point);
        /// @brief Check if an entity's bounding box collides with a 3D point (is the point inside the box).
        /// @param box The box component to use.
        /// @param transform The transform component to use.
        /// @param point The point to check collision with.
        /// @return Whether the 3D point collides with the bounding box.
        static bool InCollision(const BoxComponent& box, TransformComponent& transform, Vector3 point);
        /// @brief Check if an entity's bounding box collides with a ray.
        /// @param box The box component to use.
        /// @param transform The transform component to use.
        /// @param point The ray to check collision with.
        /// @return Whether the ray collides with the bounding box.
        static bool InCollision(const BoxComponent& box, TransformComponent& transform, const Ray& ray);
    };
} // namespace Ers
