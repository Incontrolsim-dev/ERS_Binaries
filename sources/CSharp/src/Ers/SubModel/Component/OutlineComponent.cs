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
                return new Vector3(
                    ErsEngine.ERS_OutlineComponent_Get_Center_X(CorePtr),
                    ErsEngine.ERS_OutlineComponent_Get_Center_Y(CorePtr),
                    ErsEngine.ERS_OutlineComponent_Get_Center_Z(CorePtr));
            }
            set {
                ErsEngine.ERS_OutlineComponent_Set_Center_X(CorePtr, value.X);
                ErsEngine.ERS_OutlineComponent_Set_Center_Y(CorePtr, value.Y);
                ErsEngine.ERS_OutlineComponent_Set_Center_Z(CorePtr, value.Z);
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
                return new Vector3(
                    ErsEngine.ERS_OutlineComponent_Get_Dimensions_X(CorePtr),
                    ErsEngine.ERS_OutlineComponent_Get_Dimensions_Y(CorePtr),
                    ErsEngine.ERS_OutlineComponent_Get_Dimensions_Z(CorePtr));
            }
            set => ErsEngine.ERS_OutlineComponent_Set_Dimensions(CorePtr, value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The type ID of the componennt in de ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_OutlineComponent_TypeId();

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr
        {
            get {
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
}
