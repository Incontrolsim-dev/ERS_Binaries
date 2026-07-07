#include "Camera3DController.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera3DController::Camera3DController(Camera3D camera)
    {
        corePtr = Ers::Engine::ERS_Camera3DController_Create(camera.CorePtr());
    }

    Camera3DController::~Camera3DController()
    {
        Ers::Engine::ERS_Camera3DController_Destroy(corePtr);
    }

    void Camera3DController::ControlCamera(int screenWidth, int screenHeight, float deltaTime, float lookAtZ)
    {
        Ers::Engine::ERS_Camera3DController_ControlCamera(corePtr, screenWidth, screenHeight, deltaTime, lookAtZ);
    }

    void Camera3DController::Update(float deltaTime)
    {
        Ers::Engine::ERS_Camera3DController_Update(corePtr, deltaTime);
    }

    void Camera3DController::SwitchCameraMode(int mode)
    {
        Ers::Engine::ERS_Camera3DController_SwitchCameraMode(corePtr, mode);
    }
    float Camera3DController::HeadBobbingIntensity()
    {
        return Ers::Engine::ERS_Camera3DController_GetHeadBobbingIntensity(corePtr);
    }

    void Camera3DController::HeadBobbingIntensity(float intensity)
    {
        Ers::Engine::ERS_Camera3DController_SetHeadBobbingIntensity(corePtr, intensity);
    }
} // namespace Ers
