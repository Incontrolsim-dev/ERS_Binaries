#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Math/PathSegment.h"
#include "Ers/SubModel/CoreComponent.h"

#include <cstdint>

namespace Ers
{

    /// @brief Component representing a path with multiple segments.
    class PathComponent : public CoreComponent
    {
      public:
        PathComponent()                                = default;
        PathComponent(const PathComponent&)            = delete;
        PathComponent(PathComponent&&)                 = delete;
        PathComponent& operator=(const PathComponent&) = delete;
        PathComponent& operator=(PathComponent&&)      = delete;
        ~PathComponent()                               = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the number of segments in the path.
        /// @return The number of segments
        [[nodiscard]] int GetNumSegments() const;

        /// @brief Get a specific segment by index.
        /// @param index The index of the segment
        /// @return Pointer to the path segment
        [[nodiscard]] PathSegment* GetSegment(int index);

        /// @brief Add a straight path segment.
        /// @param from Starting point
        /// @param to Ending point
        void AddStraight(const Vector3& from, const Vector3& to);

        /// @brief Add a helical path segment.
        /// @param center Center point
        /// @param radius Radius of the helix
        /// @param beginAngle Starting angle in radians
        /// @param endAngle Ending angle in radians
        /// @param endZ Ending Z coordinate
        void AddHelical(const Vector3& center, float radius, float beginAngle, float endAngle, float endZ);

        void AddCubicBezier(Ers::Vector3 p0, Ers::Vector3 p1, Ers::Vector3 p2, Ers::Vector3 p3);
        void
        AddCubicBezierFromDirections(Ers::Vector3 start, Ers::Vector3 startDir, Ers::Vector3 end, Ers::Vector3 endDir, float curvature);
    };
} // namespace Ers
