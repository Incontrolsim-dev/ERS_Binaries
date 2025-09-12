using System.ComponentModel;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A component to attach physical dimensions to an entity.
    ///
    /// <para>
    ///     <b>Note</b>: by default, it is assumed a <see cref="TransformComponent"/>'s position is at the back top-left corner (-X, -Y,
    ///     +Z). Setting the dimensions will automatically set the center of the outline to follow this style.<br/> If you wish offset the
    ///     outline, manually adjust the center variable <i>after</i> setting the dimensions.
    /// </para>
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct OutlineComponent : ICoreComponent
    {
        /// <summary>
        /// The center of an entity.
        ///
        /// <para><b>Note</b>: always set the dimensions first, otherwise the custom center will be overwritten.</para>
        /// </summary>
        [Category("Outline")]
        [Description("The center of the entity.")]
        public Vector3 Center
        {
            get {
                unsafe
                {
                    return new Vector3(
                        *(float*)ErsEngine.ERS_OutlineComponent_Center_X(CorePointer()),
                        *(float*)ErsEngine.ERS_OutlineComponent_Center_Y(CorePointer()),
                        *(float*)ErsEngine.ERS_OutlineComponent_Center_Z(CorePointer()));
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_OutlineComponent_Center_X(CorePointer()) = value.X;
                    *(float*)ErsEngine.ERS_OutlineComponent_Center_Y(CorePointer()) = value.Y;
                    *(float*)ErsEngine.ERS_OutlineComponent_Center_Z(CorePointer()) = value.Z;
                }
            }
        }

        /// <summary>
        /// The dimensions of an entity.
        /// </summary>
        [Category("Outline")]
        [Description("The dimensions of the entity.")]
        public Vector3 Dimensions
        {
            get {
                unsafe
                {
                    return new Vector3(
                        ErsEngine.ERS_OutlineComponent_Dimensions_X(CorePointer()),
                        ErsEngine.ERS_OutlineComponent_Dimensions_Y(CorePointer()),
                        ErsEngine.ERS_OutlineComponent_Dimensions_Z(CorePointer()));
                }
            }
            set => ErsEngine.ERS_OutlineComponent_SetDimensions(CorePointer(), value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The type ID of the componennt in de ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_OutlineComponent_TypeId();

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed(OutlineComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}
