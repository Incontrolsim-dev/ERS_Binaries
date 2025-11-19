#include "PathSegment.h"
#include "Ers/Api.h"

namespace Ers
{
    PathSegmentType PathSegment::GetType() const
    {
        return static_cast<PathSegmentType>(ersAPIFunctionPointers.ERS_PathSegment_GetType((void*)this));
    }

    Vector3 PathSegment::From() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetFromX((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetFromY((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetFromZ((void*)this));
    }

    Vector3 PathSegment::To() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetToX((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetToY((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetToZ((void*)this));
    }

    Vector3 PathSegment::Center() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetCenterX((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetCenterY((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetCenterZ((void*)this));
    }

    float PathSegment::GetRadius() const
    {
        return ersAPIFunctionPointers.ERS_PathSegment_GetRadius((void*)this);
    }

    float PathSegment::GetBeginAngle() const
    {
        return ersAPIFunctionPointers.ERS_PathSegment_GetBeginAngle((void*)this);
    }

    float PathSegment::GetEndAngle() const
    {
        return ersAPIFunctionPointers.ERS_PathSegment_GetEndAngle((void*)this);
    }

    float PathSegment::GetEndZ() const
    {
        return ersAPIFunctionPointers.ERS_PathSegment_GetEndZ((void*)this);
    }

    Vector3 PathSegment::GetPointAlongPath(float t) const
    {
        float result[3];
        ersAPIFunctionPointers.ERS_PathSegment_GetPointAlongPath((void*)this, t, result);
        return Vec3(result[0], result[1], result[2]);
    }

    Vector3 PathSegment::GetRotationAlongPath(float t) const
    {
        float result[3];
        ersAPIFunctionPointers.ERS_PathSegment_GetRotationAlongPath((void*)this, t, result);
        return Vec3(result[0], result[1], result[2]);
    }

    Vector3 PathSegment::GetP0() const
    {
        return Ers::Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetP0X((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetP0Y((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetP0Z((void*)this));
    }

    Vector3 PathSegment::GetP1() const
    {
        return Ers::Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetP1X((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetP1Y((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetP1Z((void*)this));
    }

    Vector3 PathSegment::GetP2() const
    {
        return Ers::Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetP2X((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetP2Y((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetP2Z((void*)this));
    }

    Vector3 PathSegment::GetP3() const
    {
        return Ers::Vec3(
            ersAPIFunctionPointers.ERS_PathSegment_GetP3X((void*)this), ersAPIFunctionPointers.ERS_PathSegment_GetP3Y((void*)this),
            ersAPIFunctionPointers.ERS_PathSegment_GetP3Z((void*)this));
    }

    void* PathSegment::Data()
    {
        return this;
    }

    const void* const PathSegment::Data() const
    {
        return this;
    }
} // namespace Ers
