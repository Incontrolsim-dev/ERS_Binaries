#include "CollisionSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    bool CollisionSystem::InCollision(const BoxComponent& box, TransformComponent& transform, Vector2 point)
    {
        return Ers::Engine::ERS_CollisionSystem_InCollision_Box_Point2D(&box, &transform, point.X, point.Y);
    }

    bool CollisionSystem::InCollision(const BoxComponent& box, TransformComponent& transform, Vector3 point)
    {
        return Ers::Engine::ERS_CollisionSystem_InCollision_Box_Point3D(&box, &transform, point.X, point.Y, point.Z);
    }

    bool CollisionSystem::InCollision(const BoxComponent& box, TransformComponent& transform, const Ray& ray)
    {
        return Ers::Engine::ERS_CollisionSystem_InCollision_Box_Ray(
            &box, &transform, ray.position.X, ray.position.Y, ray.position.Z, ray.direction.X, ray.direction.Y, ray.direction.Z);
    }
} // namespace Ers
