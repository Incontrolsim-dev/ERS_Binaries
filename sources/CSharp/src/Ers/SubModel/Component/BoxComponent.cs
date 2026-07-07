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
                return new Vector3(
                    ErsEngine.ERS_BoxComponent_Get_Min_X(CorePtr),
                    ErsEngine.ERS_BoxComponent_Get_Min_Y(CorePtr),
                    ErsEngine.ERS_BoxComponent_Get_Min_Z(CorePtr));
            }
            set => ErsEngine.ERS_BoxComponent_Set_Min(CorePtr, value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The corner with the highest values.
        /// </summary>
        [Category("Bounding box")]
        [Description("The corner with the highest values.")]
        public Vector3 Max
        {
            get {
                return new Vector3(
                    ErsEngine.ERS_BoxComponent_Get_Max_X(CorePtr),
                    ErsEngine.ERS_BoxComponent_Get_Max_Y(CorePtr),
                    ErsEngine.ERS_BoxComponent_Get_Max_Z(CorePtr));
            }
            set => ErsEngine.ERS_BoxComponent_Set_Max(CorePtr, value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The dimensions of the bounding box.
        /// </summary>
        [Category("Bounding box")]
        [Description("The dimensions of the bounding box.")]
        public Vector3 Dimensions
        {
            get {
                Vector3 result = new Vector3();
                result.X       = ErsEngine.ERS_BoxComponent_Get_Dimensions_X(CorePtr);
                result.Y       = ErsEngine.ERS_BoxComponent_Get_Dimensions_Y(CorePtr);
                result.Z       = ErsEngine.ERS_BoxComponent_Get_Dimensions_Z(CorePtr);
                return result;
            }
            set => ErsEngine.ERS_BoxComponent_Set_Dimensions(CorePtr, value.X, value.Y, value.Z);
        }

        /// <summary>
        /// Check whether a 2D point is within the bounding box.
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public bool InCollision(Vector2 point) => ErsEngine.ERS_BoxComponent_InCollision_Point2D(CorePtr, point.X, point.Y);

        /// <summary>
        /// Check whether a ray intersects the bounding box.
        /// </summary>
        /// <param name="ray"></param>
        /// <returns></returns>
        public bool InCollision(Ray ray) => ErsEngine.ERS_BoxComponent_InCollision_Ray(
            CorePtr, ray.Position.X, ray.Position.Y, ray.Position.Z, ray.Direction.X, ray.Direction.Y, ray.Direction.Z);

        /// <summary>
        /// The type ID of the component in the ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_BoxComponent_TypeId();

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr
        {
            get {
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
}
