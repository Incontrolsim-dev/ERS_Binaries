#include "TransformComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t TransformComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_TypeId();
    }

    uint32_t TransformComponent::TypeId()
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_TypeId();
    }

    void TransformComponent::RegisterType(void* submodelInstance)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_RegisterType(submodelInstance);
    }

    Vector3 TransformComponent::GetPosition() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_TransformComponent_Position_X(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_Position_Y(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_Position_Z(const_cast<TransformComponent*>(this)));
    }

    void TransformComponent::SetPosition(Vector3 pos)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetPosition(this, pos.X, pos.Y, pos.Z);
    }

    Vector3 TransformComponent::GetGlobalPosition() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalPosition_X(this),
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalPosition_Y(this),
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalPosition_Z(this));
    }

    Vector3 TransformComponent::GetRotation() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_TransformComponent_Rotation_X(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_Rotation_Y(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_Rotation_Z(const_cast<TransformComponent*>(this)));
    }

    void TransformComponent::SetRotation(Vector3 rotation)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetRotationEuler(this, rotation.X, rotation.Y, rotation.Z);
    }

    Vector3 TransformComponent::GetGlobalRotation() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalRotation_X(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalRotation_Y(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalRotation_Z(const_cast<TransformComponent*>(this)));
    }

    Vector3 TransformComponent::GetScale() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_TransformComponent_Scale_X(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_Scale_Y(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_Scale_Z(const_cast<TransformComponent*>(this)));
    }

    void TransformComponent::SetScale(Vector3 scale)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetScale(this, scale.X, scale.Y, scale.Z);
    }

    Vector3 TransformComponent::GetGlobalScale() const
    {
        return Vec3(
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalScale_X(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalScale_Y(const_cast<TransformComponent*>(this)),
            ersAPIFunctionPointers.ERS_TransformComponent_GlobalScale_Z(const_cast<TransformComponent*>(this)));
    }

    void TransformComponent::RotateX(float radians)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_Rotate_X(this, radians);
    }

    void TransformComponent::RotateY(float radians)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_Rotate_Y(this, radians);
    }

    void TransformComponent::RotateZ(float radians)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_Rotate_Z(this, radians);
    }

    void TransformComponent::SetRotationEuler(float x, float y, float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetRotationEuler(this, x, y, z);
    }

    // Quaternion Setter
    void TransformComponent::SetQuaternion(float x, float y, float z, float w)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetQuaternion(this, x, y, z, w);
    }
} // namespace Ers
