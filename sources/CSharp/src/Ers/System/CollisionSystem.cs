using System.Numerics;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Functions related to the collision between different objects.
    /// </summary>
    public static class CollisionSystem
    {
        /// <summary>
        /// Check if an entity's bounding box collides with a 2D point (is the point inside the box).
        /// </summary>
        /// <param name="box">The <see cref="BoxComponent"/> to use.</param>
        /// <param name="transform">The <see cref="TransformComponent"/> to use.</param>
        /// <param name="point">The point to check collision with.</param>
        /// <returns>Whether the 2D point collides with the box.</returns>
        public static bool InCollision(Ref<BoxComponent> box, Ref<TransformComponent> transform, Vector2 point)
        {
            return ErsEngine.ERS_CollisionSystem_InCollision_Box_Point2D(box.Value.CorePtr, transform.Value.CorePtr, point.X, point.Y);
        }

        /// <summary>
        /// Check if an entity's bounding box collides with a 3D point (is the point inside the box).
        /// </summary>
        /// <param name="box">The <see cref="BoxComponent"/> to use.</param>
        /// <param name="transform">The <see cref="TransformComponent"/> to use.</param>
        /// <param name="point">The point to check collision with.</param>
        /// <returns>Whether the 3D point collides with the box.</returns>
        public static bool InCollision(Ref<BoxComponent> box, Ref<TransformComponent> transform, Vector3 point)
        {
            return ErsEngine.ERS_CollisionSystem_InCollision_Box_Point3D(
                box.Value.CorePtr, transform.Value.CorePtr, point.X, point.Y, point.Z);
        }

        /// <summary>
        /// Check if an entity's bounding box collides with a <see cref="Ray"/>.
        /// </summary>
        /// <param name="box">The <see cref="BoxComponent"/> to use.</param>
        /// <param name="transform">The <see cref="TransformComponent"/> to use.</param>
        /// <param name="ray">The ray to check collision with.</param>
        /// <returns>Whether the ray collides with the bounding box.</returns>
        public static bool InCollision(Ref<BoxComponent> box, Ref<TransformComponent> transform, Ray ray)
        {
            return ErsEngine.ERS_CollisionSystem_InCollision_Box_Ray(
                box.Value.CorePtr, transform.Value.CorePtr, ray.Position.X, ray.Position.Y, ray.Position.Z, ray.Direction.X,
                ray.Direction.Y, ray.Direction.Z);
        }
    }
}
