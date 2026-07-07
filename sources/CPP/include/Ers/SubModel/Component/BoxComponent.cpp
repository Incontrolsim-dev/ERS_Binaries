#include "BoxComponent.h"
#include "Ers/Api.h"
#include "Ers/Math/Ray.h"

namespace Ers
{
    uint32_t BoxComponent::CoreTypeId()
    {
        return Ers::Engine::ERS_BoxComponent_TypeId();
    }

    Vector3 BoxComponent::GetMin() const
    {
        return Vec3(
            Ers::Engine::ERS_BoxComponent_Get_Min_X(const_cast<BoxComponent*>(this)),
            Ers::Engine::ERS_BoxComponent_Get_Min_Y(const_cast<BoxComponent*>(this)),
            Ers::Engine::ERS_BoxComponent_Get_Min_Z(const_cast<BoxComponent*>(this)));
    }

    void BoxComponent::SetMin(Vector3 min)
    {
        Ers::Engine::ERS_BoxComponent_Set_Min(this, min.X, min.Y, min.Z);
    }

    Vector3 BoxComponent::GetMax() const
    {
        return Vec3(
            Ers::Engine::ERS_BoxComponent_Get_Max_X(const_cast<BoxComponent*>(this)),
            Ers::Engine::ERS_BoxComponent_Get_Max_Y(const_cast<BoxComponent*>(this)),
            Ers::Engine::ERS_BoxComponent_Get_Max_Z(const_cast<BoxComponent*>(this)));
    }

    void BoxComponent::SetMax(Vector3 max)
    {
        Ers::Engine::ERS_BoxComponent_Set_Max(this, max.X, max.Y, max.Z);
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

    bool BoxComponent::InCollision(Vector2 point) const
    {
        return Ers::Engine::ERS_BoxComponent_InCollision_Point2D(const_cast<BoxComponent*>(this), point.X, point.Y);
    }

    bool BoxComponent::InCollision(const Ray& ray) const
    {
        return Ers::Engine::ERS_BoxComponent_InCollision_Ray(
            const_cast<BoxComponent*>(this), ray.position.X, ray.position.Y, ray.position.Z, ray.direction.X, ray.direction.Y,
            ray.direction.Z);
    }
} // namespace Ers
