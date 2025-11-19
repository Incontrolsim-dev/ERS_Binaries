#include "Camera3D.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera3D::Camera3D(void* coreInstance) :
        coreInstance(coreInstance)
    {
    }

    float Camera3D::GetFovInTurns() const
    {
        return *ersAPIFunctionPointers.ERS_Camera3D_FovInTurns(coreInstance);
    }

    void Camera3D::SetFovInTurns(float value)
    {
        *(ersAPIFunctionPointers.ERS_Camera3D_FovInTurns(coreInstance)) = value;
    }

    float Camera3D::GetZNear() const
    {
        return *ersAPIFunctionPointers.ERS_Camera3D_ZNear(coreInstance);
    }

    void Camera3D::SetZNear(float value)
    {
        *(ersAPIFunctionPointers.ERS_Camera3D_ZNear(coreInstance)) = value;
    }

    float Camera3D::GetZFar() const
    {
        return *ersAPIFunctionPointers.ERS_Camera3D_ZFar(coreInstance);
    }

    void Camera3D::SetZFar(float value)
    {
        *(ersAPIFunctionPointers.ERS_Camera3D_ZFar(coreInstance)) = value;
    }

    void Camera3D::SetLookAt(float x, float y, float z)
    {
        ersAPIFunctionPointers.ERS_Camera3D_SetLookAt(coreInstance, x, y, z);
    }

    void* Camera3D::Data()
    {
        return coreInstance;
    }

    const void* const Camera3D::Data() const
    {
        return coreInstance;
    }
} // namespace Ers
