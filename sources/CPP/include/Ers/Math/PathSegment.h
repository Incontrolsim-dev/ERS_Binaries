#pragma once

#include "HMM/VectorMath.h"

namespace Ers
{
    /// @brief Enum for path segment types.
    enum class PathSegmentType
    {
        Straight = 0,
        Helical  = 1
    };

    /// @brief Represents a segment of a path.
    class PathSegment
    {
      public:
        PathSegment()                              = delete;
        PathSegment(const PathSegment&)            = delete;
        PathSegment(PathSegment&&)                 = delete;
        PathSegment& operator=(const PathSegment&) = delete;
        PathSegment& operator=(PathSegment&&)      = delete;
        ~PathSegment()                             = default;

        /// @brief Get the type of this path segment.
        /// @return The segment type
        [[nodiscard]] PathSegmentType GetType() const;

        /// @brief Get the starting point of the segment.
        /// @return The starting point
        [[nodiscard]] Vector3 From() const;

        /// @brief Get the ending point of the segment.
        /// @return The ending point
        [[nodiscard]] Vector3 To() const;

        /// @brief Get the center point (for helical segments).
        /// @return The center point
        [[nodiscard]] Vector3 Center() const;

        /// @brief Get the radius (for helical segments).
        /// @return The radius
        [[nodiscard]] float GetRadius() const;

        /// @brief Get the beginning angle (for helical segments).
        /// @return The beginning angle in radians
        [[nodiscard]] float GetBeginAngle() const;

        /// @brief Get the ending angle (for helical segments).
        /// @return The ending angle in radians
        [[nodiscard]] float GetEndAngle() const;

        /// @brief Get the ending Z coordinate (for helical segments).
        /// @return The ending Z coordinate
        [[nodiscard]] float GetEndZ() const;

        /// @brief Get a point along the path at parameter t.
        /// @param t Parameter value (0.0 to 1.0)
        /// @return The point along the path
        [[nodiscard]] Vector3 GetPointAlongPath(float t) const;

        /// @brief Get the rotation along the path at parameter t.
        /// @param t Parameter value (0.0 to 1.0)
        /// @return The rotation along the path
        [[nodiscard]] Vector3 GetRotationAlongPath(float t) const;

        [[nodiscard]] Vector3 GetP0() const;

        [[nodiscard]] Vector3 GetP1() const;

        [[nodiscard]] Vector3 GetP2() const;

        [[nodiscard]] Vector3 GetP3() const;

        void* Data();
        const void* const Data() const;

      private:
    };
} // namespace Ers
