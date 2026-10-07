#include "Camera2D.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera2D::Camera2D(void* corePtr) :
        corePtr(corePtr)
    {
    }

    void Camera2D::UpdateTransform(int viewportWidth, int viewportHeight)
    {
        Ers::Engine::ERS_Camera2D_UpdateTransform(corePtr, viewportWidth, viewportHeight);
    }

    Vector2 Camera2D::GetPosition() const
    {
        return Ers::Vec2(Ers::Engine::ERS_Camera2D_GetPositionX(corePtr), Ers::Engine::ERS_Camera2D_GetPositionY(corePtr));
    }

    void Camera2D::SetPosition(Vector2 pos)
    {
        Ers::Engine::ERS_Camera2D_SetPositionX(corePtr, pos.X);
        Ers::Engine::ERS_Camera2D_SetPositionY(corePtr, pos.Y);
    }

    float Camera2D::Zoom() const
    {
        return Ers::Engine::ERS_Camera2D_GetZoom(corePtr);
    }

    void Camera2D::Zoom(float value)
    {
        Ers::Engine::ERS_Camera2D_SetZoom(corePtr, value);
    }

    Vector2 Camera2D::GetSize() const
    {
        return Ers::Vec2(Ers::Engine::ERS_Camera2D_Size_Get_X(corePtr), Ers::Engine::ERS_Camera2D_Size_Get_Y(corePtr));
    }

    Vector2 Camera2D::GetMin() const
    {
        return Ers::Vec2(Ers::Engine::ERS_Camera2D_Min_Get_X(corePtr), Ers::Engine::ERS_Camera2D_Min_Get_Y(corePtr));
    }

    Vector2 Camera2D::GetMax() const
    {
        return Ers::Vec2(Ers::Engine::ERS_Camera2D_Max_Get_X(corePtr), Ers::Engine::ERS_Camera2D_Max_Get_Y(corePtr));
    }

    float Camera2D::SizePerPixel() const
    {
        return Ers::Engine::ERS_Camera2D_SizePerPixel(corePtr);
    }

    Vector2 Camera2D::GetWorldPos(Vector2 viewportPos) const
    {
        Vector2 result = Vec2(0, 0);
        Ers::Engine::ERS_Camera2D_GetWorldPos(corePtr, viewportPos.X, viewportPos.Y, &result.X, &result.Y);
        return result;
    }

    void* Camera2D::CorePtr()
    {
        return corePtr;
    }

    const void* const Camera2D::CorePtr() const
    {
        return corePtr;
    }
} // namespace Ers
