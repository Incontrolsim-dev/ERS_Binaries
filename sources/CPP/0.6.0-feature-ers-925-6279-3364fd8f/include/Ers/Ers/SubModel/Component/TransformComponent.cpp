#include "TransformComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t TransformComponent::TypeId()
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_TypeId();
    }

    void* TransformComponent::CreateCallback()
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_CreateCallback();
    }

    void TransformComponent::RegisterType(void* submodelInstance)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_RegisterType(submodelInstance);
    }

    // Position Getters and Setters
    float TransformComponent::PositionX() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Position_X(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::PositionX(float x)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetPosition_X(this, x);
    }

    float TransformComponent::PositionY() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Position_Y(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::PositionY(float y)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetPosition_Y(this, y);
    }

    float TransformComponent::PositionZ() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Position_Z(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::PositionZ(float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetPosition_Z(this, z);
    }

    void TransformComponent::Position(float x, float y, float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetPosition(this, x, y, z);
    }

    // Scale Getters and Setters
    float TransformComponent::ScaleX() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Scale_X(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::ScaleX(float x)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetScale_X(this, x);
    }

    float TransformComponent::ScaleY() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Scale_Y(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::ScaleY(float y)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetScale_Y(this, y);
    }

    float TransformComponent::ScaleZ() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Scale_Z(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::ScaleZ(float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetScale_Z(this, z);
    }

    void TransformComponent::Scale(float scale)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetScale(this, scale, scale, scale);
    }

    void TransformComponent::Scale(float x, float y, float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetScale(this, x, y, z);
    }

    // Rotation (Euler Angles) Getters and Setters
    float TransformComponent::RotationX() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Rotation_X(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::RotationX(float x)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetRotation_X(this, x);
    }

    float TransformComponent::RotationY() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Rotation_Y(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::RotationY(float y)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetRotation_Y(this, y);
    }

    float TransformComponent::RotationZ() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_Rotation_Z(const_cast<TransformComponent*>(this));
    }

    void TransformComponent::RotationZ(float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetRotation_Z(this, z);
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

    void TransformComponent::RotationEuler(float x, float y, float z)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetRotationEuler(this, x, y, z);
    }

    // Quaternion Setter
    void TransformComponent::SetQuaternion(float x, float y, float z, float w)
    {
        ersAPIFunctionPointers.ERS_TransformComponent_SetQuaternion(this, x, y, z, w);
    }

    // Global Position Getters
    float TransformComponent::GlobalPositionX() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalPosition_X(this);
    }

    float TransformComponent::GlobalPositionY() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalPosition_Y(this);
    }

    float TransformComponent::GlobalPositionZ() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalPosition_Z(this);
    }

    // Global Scale Getters
    float TransformComponent::GlobalScaleX() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalScale_X(this);
    }

    float TransformComponent::GlobalScaleY() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalScale_Y(this);
    }

    float TransformComponent::GlobalScaleZ() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalScale_Z(this);
    }

    // Global Rotation Getters
    float TransformComponent::GlobalRotationX() const 
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalRotation_X(this);
    }

    float TransformComponent::GlobalRotationY() const 
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalRotation_Y(this);
    }

    float TransformComponent::GlobalRotationZ() const
    {
        return ersAPIFunctionPointers.ERS_TransformComponent_GlobalRotation_Z(this);
    }
} // namespace Ers
