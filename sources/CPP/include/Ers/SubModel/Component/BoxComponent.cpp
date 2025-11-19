#include "BoxComponent.h"
#include "Ers/Api.h"
#include "Ers/Math/Ray.h"

namespace Ers
{
    uint32_t BoxComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_BoxComponent_TypeId();
    }

    Vector3 BoxComponent::Min() const
    {
        return Vec3(
            *ersAPIFunctionPointers.ERS_BoxComponent_Min_X(const_cast<BoxComponent*>(this)),
            *ersAPIFunctionPointers.ERS_BoxComponent_Min_Y(const_cast<BoxComponent*>(this)),
            *ersAPIFunctionPointers.ERS_BoxComponent_Min_Z(const_cast<BoxComponent*>(this)));
    }

    Vector3 BoxComponent::Max() const
    {
        return Vec3(
            *ersAPIFunctionPointers.ERS_BoxComponent_Max_X(const_cast<BoxComponent*>(this)),
            *ersAPIFunctionPointers.ERS_BoxComponent_Max_Y(const_cast<BoxComponent*>(this)),
            *ersAPIFunctionPointers.ERS_BoxComponent_Max_Z(const_cast<BoxComponent*>(this)));
    }

    Vector3 BoxComponent::GetDimensions() const
    {
        return Vec3(
            *ersAPIFunctionPointers.ERS_BoxComponent_Dimensions_X(const_cast<BoxComponent*>(this)),
            *ersAPIFunctionPointers.ERS_BoxComponent_Dimensions_Y(const_cast<BoxComponent*>(this)),
            *ersAPIFunctionPointers.ERS_BoxComponent_Dimensions_Z(const_cast<BoxComponent*>(this)));
    }

    void BoxComponent::SetDimensions(Vector3 dims)
    {
        *ersAPIFunctionPointers.ERS_BoxComponent_Dimensions_X(this) = dims.X;
        *ersAPIFunctionPointers.ERS_BoxComponent_Dimensions_Y(this) = dims.Y;
        *ersAPIFunctionPointers.ERS_BoxComponent_Dimensions_Z(this) = dims.Z;
    }

    bool BoxComponent::InCollision(const Vector2& point) const
    {
        return ersAPIFunctionPointers.ERS_BoxComponent_InCollision_Point2D(const_cast<BoxComponent*>(this), point.X, point.Y);
    }

    bool BoxComponent::InCollision(const Ray& ray) const
    {
        return ersAPIFunctionPointers.ERS_BoxComponent_InCollision_Ray(
            const_cast<BoxComponent*>(this), ray.position.X, ray.position.Y, ray.position.Z, ray.direction.X, ray.direction.Y,
            ray.direction.Z);
    }
} // namespace Ers
