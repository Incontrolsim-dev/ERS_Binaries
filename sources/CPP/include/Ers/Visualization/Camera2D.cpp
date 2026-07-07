#include "Camera2D.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera2D::Camera2D(void* corePtr) :
        corePtr(corePtr)
    {
    }

    void Camera2D::UpdateTransform(int screenWidth, int screenHeight)
    {
        Ers::Engine::ERS_Camera2D_UpdateTransform(corePtr, screenWidth, screenHeight);
    }

    float Camera2D::Zoom() const
    {
        return Ers::Engine::ERS_Camera2D_GetZoom(corePtr);
    }

    void Camera2D::Zoom(float value)
    {
        Ers::Engine::ERS_Camera2D_SetZoom(corePtr, value);
    }

    float Camera2D::SizePerPixel() const
    {
        return Ers::Engine::ERS_Camera2D_SizePerPixel(corePtr);
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
