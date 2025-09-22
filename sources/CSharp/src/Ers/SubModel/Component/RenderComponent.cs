using System.ComponentModel;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A component for rendering entities with color and mesh information.
    ///
    /// <para>The component should also have a <see cref="TransformComponent"/>.</para>
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct RenderComponent : ICoreComponent
    {
        /// <summary>
        /// The color of the rendered object.
        /// </summary>
        [Category("Rendering")]
        [Description("The color of the rendered object (RGBA).")]
        public Vector4 Color
        {
            get {
                unsafe
                {
                    float r, g, b, a;
                    ErsEngine.ERS_BasicRenderComponent_GetColor(CorePointer(), (IntPtr)(&r), (IntPtr)(&g), (IntPtr)(&b), (IntPtr)(&a));
                    return new Vector4(r, g, b, a);
                }
            }
            set {
                ErsEngine.ERS_BasicRenderComponent_SetColor(CorePointer(), value.X, value.Y, value.Z, value.W);
            }
        }

        /// <summary>
        /// The instanced mesh used for rendering.
        /// </summary>
        [Category("Rendering")]
        [Description("The model instance used for rendering this component.")]
        public IntPtr InstancedModel
        {
            get {
                return ErsEngine.ERS_BasicRenderComponent_GetInstancedModel(CorePointer());
            }
            set {
                ErsEngine.ERS_BasicRenderComponent_SetInstancedModel(CorePointer(), value);
            }
        }

        /// <summary>
        /// The type ID of the component in the ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_BasicRenderComponent_TypeId();

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed(RenderComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}
