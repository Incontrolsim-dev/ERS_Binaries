using System.Numerics;

namespace Ers
{
    /// <summary>
    /// A ray with an origin position and a direction.
    /// </summary>
    public struct Ray
    {
        /// <summary>
        /// The origin position of the ray.
        /// </summary>
        public Vector3 Position;
        /// <summary>
        /// The direction of the ray.
        ///
        /// <para><b>Note</b>: is not guaranteed to be normalized.</para>
        /// </summary>
        public Vector3 Direction;

        /// <summary>
        /// Construct a new ray.
        /// </summary>
        /// <param name="position">The starting position of the ray.</param>
        /// <param name="direction">The direction of the ray.</param>
        public Ray(Vector3 position, Vector3 direction)
        {
            Position  = position;
            Direction = direction;
        }
    }
}
