#include "Camera2DController.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera2DController::Camera2DController(Camera2D& camera)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Camera2DController_Create(camera.Data());
    }

    Camera2DController::~Camera2DController()
    {
        ersAPIFunctionPointers.ERS_Camera2DController_Destroy(coreInstance);
    }

    void Camera2DController::ControlCamera(int screenWidth, int screenHeight)
    {
        ersAPIFunctionPointers.ERS_Camera2DController_ControlCamera(coreInstance, screenWidth, screenHeight);
    }

    void Camera2DController::SetScreenSize(int width, int height)
    {
        ersAPIFunctionPointers.ERS_Camera2DController_SetScreenSize(coreInstance, width, height);
    }

    void Camera2DController::Update(float mouseX, float mouseY)
    {
        ersAPIFunctionPointers.ERS_Camera2DController_Update(coreInstance, mouseX, mouseY);
    }

    void Camera2DController::StartDragging(float mouseX, float mouseY)
    {
        ersAPIFunctionPointers.ERS_Camera2DController_StartDragging(coreInstance, mouseX, mouseY);
    }

    void Camera2DController::StopDragging()
    {
        ersAPIFunctionPointers.ERS_Camera2DController_StopDragging(coreInstance);
    }

    void Camera2DController::Zoom(float base, float power)
    {
        ersAPIFunctionPointers.ERS_Camera2DController_Zoom(coreInstance, base, power);
    }
} // namespace Ers
