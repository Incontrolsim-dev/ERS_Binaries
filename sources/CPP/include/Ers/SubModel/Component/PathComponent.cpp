#include "PathComponent.h"
#include "Ers/Api.h"
#include "Ers/Math/PathSegment.h"

namespace Ers
{
    uint32_t PathComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_PathComponent_TypeId();
    }

    int PathComponent::GetNumSegments() const
    {
        return ersAPIFunctionPointers.ERS_PathComponent_GetNumSegments(const_cast<PathComponent*>(this));
    }

    PathSegment* PathComponent::GetSegment(int index)
    {
        void* ptr = ersAPIFunctionPointers.ERS_PathComponent_GetSegment(this, index);
        return static_cast<PathSegment*>(ptr);
    }

    void PathComponent::AddStraight(const Vector3& from, const Vector3& to)
    {
        ersAPIFunctionPointers.ERS_PathComponent_AddStraight(this, from.X, from.Y, from.Z, to.X, to.Y, to.Z);
    }

    void PathComponent::AddHelical(const Vector3& center, float radius, float beginAngle, float endAngle, float endZ)
    {
        ersAPIFunctionPointers.ERS_PathComponent_AddHelical(this, center.X, center.Y, center.Z, radius, beginAngle, endAngle, endZ);
    }

    void PathComponent::AddCubicBezier(Ers::Vector3 p0, Ers::Vector3 p1, Ers::Vector3 p2, Ers::Vector3 p3)
    {
        ersAPIFunctionPointers.ERS_PathComponent_AddCubicBezier(
            this, p0.X, p0.Y, p0.Z, p1.X, p1.Y, p1.Z, p2.X, p2.Y, p2.Z, p3.X, p3.Y, p3.Z);
    }

    void PathComponent::AddCubicBezierFromDirections(
        Ers::Vector3 start, Ers::Vector3 startDir, Ers::Vector3 end, Ers::Vector3 endDir, float curvature)
    {
        ersAPIFunctionPointers.ERS_PathComponent_AddCubicBezierFromDirections(
            this, start.X, start.Y, start.Z, startDir.X, startDir.Y, startDir.Z, end.X, end.Y, end.Z, endDir.X, endDir.Y, endDir.Z,
            curvature);
    }
} // namespace Ers
