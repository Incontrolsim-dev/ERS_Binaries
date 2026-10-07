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
