#include "Camera3DController.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera3DController::Camera3DController(Camera3D camera)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Camera3DController_Create(camera.Data());
    }

    Camera3DController::~Camera3DController()
    {
        ersAPIFunctionPointers.ERS_Camera3DController_Destroy(coreInstance);
    }

    void Camera3DController::ControlCamera(int screenWidth, int screenHeight, float deltaTime, float lookAtZ)
    {
        ersAPIFunctionPointers.ERS_Camera3DController_ControlCamera(coreInstance, screenWidth, screenHeight, deltaTime, lookAtZ);
    }

    void Camera3DController::Update(float deltaTime)
    {
        ersAPIFunctionPointers.ERS_Camera3DController_Update(coreInstance, deltaTime);
    }

    void Camera3DController::SwitchCameraMode(int mode)
    {
        ersAPIFunctionPointers.ERS_Camera3DController_SwitchCameraMode(coreInstance, mode);
    }

    void Camera3DController::HeadBobbingIntensity(float intensity)
    {
        *ersAPIFunctionPointers.ERS_Camera3DController_HeadBobbingIntensity(coreInstance) = intensity;
    }

    float Camera3DController::HeadBobbingIntensity()
    {
        return *ersAPIFunctionPointers.ERS_Camera3DController_HeadBobbingIntensity(coreInstance);
    }
} // namespace Ers
