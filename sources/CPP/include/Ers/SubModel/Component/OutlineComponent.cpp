#include "OutlineComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t OutlineComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_OutlineComponent_TypeId();
    }

    Vector3 OutlineComponent::Center() const
    {
        return Vec3(
            *ersAPIFunctionPointers.ERS_OutlineComponent_Center_X(const_cast<OutlineComponent*>(this)),
            *ersAPIFunctionPointers.ERS_OutlineComponent_Center_Y(const_cast<OutlineComponent*>(this)),
            *ersAPIFunctionPointers.ERS_OutlineComponent_Center_Z(const_cast<OutlineComponent*>(this)));
    }

    void OutlineComponent::Center(const Vector3& center)
    {
        *ersAPIFunctionPointers.ERS_OutlineComponent_Center_X(this) = center.X;
        *ersAPIFunctionPointers.ERS_OutlineComponent_Center_Y(this) = center.Y;
        *ersAPIFunctionPointers.ERS_OutlineComponent_Center_Z(this) = center.Z;
    }

    Vector3 OutlineComponent::Dimensions() const
    {
        return Vec3(
            *ersAPIFunctionPointers.ERS_OutlineComponent_Dimensions_X(const_cast<OutlineComponent*>(this)),
            *ersAPIFunctionPointers.ERS_OutlineComponent_Dimensions_Y(const_cast<OutlineComponent*>(this)),
            *ersAPIFunctionPointers.ERS_OutlineComponent_Dimensions_Z(const_cast<OutlineComponent*>(this)));
    }

    void OutlineComponent::Dimensions(const Vector3& dimensions)
    {
        ersAPIFunctionPointers.ERS_OutlineComponent_SetDimensions(this, dimensions.X, dimensions.Y, dimensions.Z);
    }
} // namespace Ers
