#include "OutlineComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t OutlineComponent::CoreTypeId()
    {
        return Ers::Engine::ERS_OutlineComponent_TypeId();
    }

    Vector3 OutlineComponent::Center() const
    {
        return Vec3(
            Ers::Engine::ERS_OutlineComponent_Get_Center_X(const_cast<OutlineComponent*>(this)),
            Ers::Engine::ERS_OutlineComponent_Get_Center_Y(const_cast<OutlineComponent*>(this)),
            Ers::Engine::ERS_OutlineComponent_Get_Center_Z(const_cast<OutlineComponent*>(this)));
    }

    void OutlineComponent::Center(Vector3 center)
    {
        Ers::Engine::ERS_OutlineComponent_Set_Center_X(this, center.X);
        Ers::Engine::ERS_OutlineComponent_Set_Center_Y(this, center.Y);
        Ers::Engine::ERS_OutlineComponent_Set_Center_Z(this, center.Z);
    }

    Vector3 OutlineComponent::Dimensions() const
    {
        return Vec3(
            Ers::Engine::ERS_OutlineComponent_Get_Dimensions_X(const_cast<OutlineComponent*>(this)),
            Ers::Engine::ERS_OutlineComponent_Get_Dimensions_Y(const_cast<OutlineComponent*>(this)),
            Ers::Engine::ERS_OutlineComponent_Get_Dimensions_Z(const_cast<OutlineComponent*>(this)));
    }

    void OutlineComponent::Dimensions(Vector3 dimensions)
    {
        Ers::Engine::ERS_OutlineComponent_Set_Dimensions(this, dimensions.X, dimensions.Y, dimensions.Z);
    }
} // namespace Ers
