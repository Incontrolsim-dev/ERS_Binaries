#include "Camera2D.h"

#include "Ers/Api.h"

namespace Ers::Visualization
{
    Camera2D::Camera2D(void* coreInstance) :
        coreInstance(coreInstance)
    {
    }

    void Camera2D::UpdateTransform(int screenWidth, int screenHeight)
    {
        ersAPIFunctionPointers.ERS_Camera2D_UpdateTransform(coreInstance, screenWidth, screenHeight);
    }

    float Camera2D::Zoom() const
    {
        return *ersAPIFunctionPointers.ERS_Camera2D_Zoom(coreInstance);
    }

    void Camera2D::Zoom(float value)
    {
        *(ersAPIFunctionPointers.ERS_Camera2D_Zoom(coreInstance)) = value;
    }

    float Camera2D::SizePerPixel() const
    {
        return ersAPIFunctionPointers.ERS_Camera2D_SizePerPixel(coreInstance);
    }

    void* Camera2D::Data()
    {
        return coreInstance;
    }

    const void* const Camera2D::Data() const
    {
        return coreInstance;
    }
} // namespace Ers::Visualization
