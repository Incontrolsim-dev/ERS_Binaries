#include "BoxComponent.h"
#include "Ers/Api.h"
#include "Ers/Math/Ray.h"

namespace Ers
{
    uint32_t BoxComponent::CoreTypeId()
    {
        return Ers::Engine::ERS_BoxComponent_TypeId();
    }

    Vector3 BoxComponent::GetDimensions() const
    {
        return Vec3(
            Ers::Engine::ERS_BoxComponent_Get_Dimensions_X(const_cast<BoxComponent*>(this)),
            Ers::Engine::ERS_BoxComponent_Get_Dimensions_Y(const_cast<BoxComponent*>(this)),
            Ers::Engine::ERS_BoxComponent_Get_Dimensions_Z(const_cast<BoxComponent*>(this)));
    }

    void BoxComponent::SetDimensions(Vector3 dims)
    {
        Ers::Engine::ERS_BoxComponent_Set_Dimensions(this, dims.X, dims.Y, dims.Z);
    }
} // namespace Ers
