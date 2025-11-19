using System.ComponentModel;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A component to add collision detection to an entity.
    ///
    /// <para>The component should also have a <see cref="TransformComponent"/> and a <see cref="OutlineComponent"/>.</para>
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct BoxComponent : ICoreComponent
    {
        /// <summary>
        /// The corner with the lowest values.
        /// </summary>
        [Category("Bounding box")]
        [Description("The corner with the lowest values.")]
        public Vector3 Min
        {
            get {
                unsafe
                {
                    return new Vector3(
                        *(float*)ErsEngine.ERS_BoxComponent_Min_X(CorePointer()), *(float*)ErsEngine.ERS_BoxComponent_Min_Y(CorePointer()),
                        *(float*)ErsEngine.ERS_BoxComponent_Min_Z(CorePointer()));
                }
            }
        }

        /// <summary>
        /// The corner with the highest values.
        /// </summary>
        [Category("Bounding box")]
        [Description("The corner with the highest values.")]
        public Vector3 Max
        {
            get {
                unsafe
                {
                    return new Vector3(
                        *(float*)ErsEngine.ERS_BoxComponent_Max_X(CorePointer()), *(float*)ErsEngine.ERS_BoxComponent_Max_Y(CorePointer()),
                        *(float*)ErsEngine.ERS_BoxComponent_Max_Z(CorePointer()));
                }
            }
        }

        /// <summary>
        /// The dimensions of the bounding box.
        /// </summary>
        [Category("Bounding box")]
        [Description("The dimensions of the bounding box.")]
        public Vector3 Dimensions
        {
            get {
                unsafe
                {
                    Vector3 result = new Vector3();
                    result.X       = *(float*)ErsEngine.ERS_BoxComponent_Dimensions_X(CorePointer());
                    result.Y       = *(float*)ErsEngine.ERS_BoxComponent_Dimensions_Y(CorePointer());
                    result.Z       = *(float*)ErsEngine.ERS_BoxComponent_Dimensions_Z(CorePointer());
                    return result;
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_BoxComponent_Dimensions_X(CorePointer()) = value.X;
                    *(float*)ErsEngine.ERS_BoxComponent_Dimensions_Y(CorePointer()) = value.Y;
                    *(float*)ErsEngine.ERS_BoxComponent_Dimensions_Z(CorePointer()) = value.Z;
                }
            }
        }

        /// <summary>
        /// Check whether a 2D point is within the bounding box.
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public bool InCollision(Vector2 point) => ErsEngine.ERS_BoxComponent_InCollision_Point2D(CorePointer(), point.X, point.Y);

        /// <summary>
        /// Check whether a ray intersects the bounding box.
        /// </summary>
        /// <param name="ray"></param>
        /// <returns></returns>
        public bool InCollision(Ray ray) => ErsEngine.ERS_BoxComponent_InCollision_Ray(
            CorePointer(), ray.Position.X, ray.Position.Y, ray.Position.Z, ray.Direction.X, ray.Direction.Y, ray.Direction.Z);

        /// <summary>
        /// The type ID of the component in the ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_BoxComponent_TypeId();

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed(BoxComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}
