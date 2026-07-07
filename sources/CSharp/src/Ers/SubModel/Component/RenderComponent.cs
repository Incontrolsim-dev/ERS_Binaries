using System;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A component for the standard render system.
    ///
    /// <para>
    /// Apply just a color to render a point in 2D and a small cube in 3D.
    /// Add an <see cref="Ers.InstancedModel"/> to set a custom 3D model.
    /// </para>
    /// <para>Requires a <see cref="TransformComponent"/> to be rendered.</para>
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct RenderComponent : ICoreComponent
    {
        /// <summary>
        /// The shape to render.
        /// </summary>
        public RenderComponentShape Shape
        {
            get => (RenderComponentShape)ErsEngine.ERS_RenderComponent_GetShape(CorePtr);
            set => ErsEngine.ERS_RenderComponent_SetShape(CorePtr, (byte)value);
        }

        /// <summary>
        /// The color of the entity.
        /// </summary>
        public Color Color
        {
            get => Color.FromInt(ErsEngine.ERS_RenderComponent_GetColor(CorePtr));
            set => ErsEngine.ERS_RenderComponent_SetColor(CorePtr, value.Value);
        }

        /// <summary>
        /// The texture used for the 2D shapes.
        /// </summary>
        public Texture Texture2D
        {
            get {
                unsafe
                {
                    IntPtr ptr = ErsEngine.ERS_RenderComponent_GetTexture2D(CorePtr);
                    return new Texture(ptr);
                }
            }
            set => ErsEngine.ERS_RenderComponent_SetTexture2D(CorePtr, value.CorePtr);
        }

        /// <summary>
        /// The <see cref="Ers.InstancedModel"/> used for 3D rendering.
        /// </summary>
        public InstancedModel InstancedModel
        {
            get {
                unsafe
                {
                    IntPtr ptr = ErsEngine.ERS_RenderComponent_GetInstancedModel(CorePtr);
                    return new InstancedModel(ptr);
                }
            }
            set {
                ErsEngine.ERS_RenderComponent_SetInstancedModel(CorePtr, value.CorePtr);
            }
        }

        /// <summary>
        /// Remove the texture for 2D shapes.
        /// Shapes will then be drawn using the given color.
        /// </summary>
        public void RemoveTexture2D() => ErsEngine.ERS_RenderComponent_RemoveTexture2D(CorePtr);

        /// <summary>
        /// The type ID of the component in the ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_RenderComponent_TypeId();

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr
        {
            get {
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

    /// <summary>
    /// The available shapes to render using the <see cref="RenderComponent"/>.
    /// </summary>
    public enum RenderComponentShape : byte
    {
        /// <summary>
        /// In 2D a point that remains the same size, regardless of zoom level.
        /// In 3D a small cube of size (0.1, 0.1, 0.1).
        /// </summary>
        Point,
        /// <summary>
        /// A rectangle in 2D, or a box in 3D.
        /// </summary>
        Rectangle,
        /// <summary>
        /// A circle in 2D, or a sphere in 3D.
        /// </summary>
        Circle,
        /// <summary>
        /// A triangle in 2D, or a pyramid in 3D.
        /// </summary>
        Triangle
    }
}
