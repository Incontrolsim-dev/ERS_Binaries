using System;
using System.Numerics;

namespace Ers
{
    /// <summary>
    /// Extension methods for <see cref="Vector2"/>.
    /// </summary>
    public static class Vector2Extensions
    {
        /// <summary>
        /// Calculate the angle between two vectors.
        /// </summary>
        /// <param name="vector">The first vector.</param>
        /// <param name="other">The second vector.</param>
        /// <returns>The angle in radians.</returns>
        public static float Angle(this Vector2 vector, Vector2 other)
        {
            float dot = Vector2.Dot(vector, other);
            float cosTheta = dot / (vector.Length() * other.Length());
            return MathF.Acos(cosTheta);
        }
    }

    /// <summary>
    /// Extension methods for <see cref="Vector3"/>.
    /// </summary>
    public static class Vector3Extensions
    {
        /// <summary>
        /// Get the 2D vector consisting of the vector's X and Y components.
        /// </summary>
        /// <param name="vector"></param>
        /// <returns></returns>
        public static Vector2 XY(this Vector3 vector)
        {
            return new Vector2(vector.X, vector.Y);
        }
    }

    /// <summary>
    /// Extension methods for <see cref="Vector4"/>.
    /// </summary>
    public static class Vector4Extensions
    {
        /// <summary>
        /// Get the 3D vector consisting of the vector's X, Y and Z components.
        /// </summary>
        /// <param name="vector"></param>
        /// <returns></returns>
        public static Vector3 XYZ(this Vector4 vector)
        {
            return new Vector3(vector.X, vector.Y, vector.Z);
        }
    }
}
