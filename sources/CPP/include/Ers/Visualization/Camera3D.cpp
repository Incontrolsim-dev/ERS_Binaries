#include "Camera3D.h"

#include "Ers/Api.h"

namespace Ers
{
    Camera3D::Camera3D(void* corePtr) :
        corePtr(corePtr)
    {
    }

    float Camera3D::GetFovInTurns() const
    {
        return Ers::Engine::ERS_Camera3D_GetFovInTurns(corePtr);
    }

    void Camera3D::SetFovInTurns(float value)
    {
        Ers::Engine::ERS_Camera3D_SetFovInTurns(corePtr, value);
    }

    float Camera3D::GetZNear() const
    {
        return Ers::Engine::ERS_Camera3D_GetZNear(corePtr);
    }

    void Camera3D::SetZNear(float value)
    {
        Ers::Engine::ERS_Camera3D_SetZNear(corePtr, value);
    }

    float Camera3D::GetZFar() const
    {
        return Ers::Engine::ERS_Camera3D_GetZFar(corePtr);
    }

    void Camera3D::SetZFar(float value)
    {
        Ers::Engine::ERS_Camera3D_SetZFar(corePtr, value);
    }

    void Camera3D::SetLookAt(float x, float y, float z)
    {
        Ers::Engine::ERS_Camera3D_SetLookAt(corePtr, x, y, z);
    }

    Ray Camera3D::GetPickRay(Vector2 viewportPos) const
    {
        Ray ray = Ray(Vec3(0, 0, 0), Vec3(0, 0, 0));
        Ers::Engine::ERS_Camera3D_GetPickRay(
            corePtr, viewportPos.X, viewportPos.Y, &ray.position.X, &ray.position.Y, &ray.position.Z, &ray.direction.X, &ray.direction.Y,
            &ray.direction.Z);
        return ray;
    }

    void* Camera3D::CorePtr()
    {
        return corePtr;
    }

    const void* const Camera3D::CorePtr() const
    {
        return corePtr;
    }
} // namespace Ers
