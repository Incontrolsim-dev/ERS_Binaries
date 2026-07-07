#include "Camera2DController.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera2DController::Camera2DController(Camera2D& camera)
    {
        corePtr = Ers::Engine::ERS_Camera2DController_Create(camera.CorePtr());
    }

    Camera2DController::~Camera2DController()
    {
        Ers::Engine::ERS_Camera2DController_Destroy(corePtr);
    }

    void Camera2DController::ControlCamera(int screenWidth, int screenHeight)
    {
        Ers::Engine::ERS_Camera2DController_ControlCamera(corePtr, screenWidth, screenHeight);
    }

    void Camera2DController::SetScreenSize(int width, int height)
    {
        Ers::Engine::ERS_Camera2DController_SetScreenSize(corePtr, width, height);
    }

    void Camera2DController::Update(float mouseX, float mouseY)
    {
        Ers::Engine::ERS_Camera2DController_Update(corePtr, mouseX, mouseY);
    }

    void Camera2DController::StartDragging(float mouseX, float mouseY)
    {
        Ers::Engine::ERS_Camera2DController_StartDragging(corePtr, mouseX, mouseY);
    }

    void Camera2DController::StopDragging()
    {
        Ers::Engine::ERS_Camera2DController_StopDragging(corePtr);
    }

    void Camera2DController::Zoom(float base, float power)
    {
        Ers::Engine::ERS_Camera2DController_Zoom(corePtr, base, power);
    }
} // namespace Ers
