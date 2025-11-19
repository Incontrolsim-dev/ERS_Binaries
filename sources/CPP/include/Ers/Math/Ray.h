#pragma once

#include "HMM/VectorMath.h"

namespace Ers
{
    /// @brief A ray with an origin position and a direction.
    struct Ray
    {
        /// @brief The origin position of the ray.
        Vector3 position;

        /// @brief The direction of the ray.
        /// Note: is not guaranteed to be normalized.
        Vector3 direction;

        /// @brief Construct a new ray.
        /// @param position The origin position
        /// @param direction The direction vector
        Ray(const Vector3& position, const Vector3& direction) :
            position(position),
            direction(direction)
        {
        }

        /// @brief Default constructor.
        Ray() :
            position(Vec3(0.0f, 0.0f, 0.0f)),
            direction(Vec3(0.0f, 0.0f, 1.0f))
        {
        }
    };
} // namespace Ers
