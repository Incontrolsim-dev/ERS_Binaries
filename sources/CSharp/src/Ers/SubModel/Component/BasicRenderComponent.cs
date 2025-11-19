using System;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A component for a quick rendering setup.
    ///
    /// <para>
    /// Apply just a color to render a rectangle in 2D and a cube in 3D.
    /// Add an <see cref="Ers.InstancedModel"/> to set a custom 3D model.
    /// </para>
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct BasicRenderComponent : ICoreComponent
    {
        /// <summary>
        /// The color of the entity.
        /// </summary>
        public Color Color
        {
            get => Color.FromInt(ErsEngine.ERS_BasicRenderComponent_GetColor(CorePointer()));
            set => ErsEngine.ERS_BasicRenderComponent_SetColor(CorePointer(), value.Value);
        }

        /// <summary>
        /// The <see cref="Ers.InstancedModel"/> used for 3D rendering.
        /// </summary>
        public InstancedModel InstancedModel
        {
            get {
                unsafe
                {
                    IntPtr ptr = ErsEngine.ERS_BasicRenderComponent_GetInstancedModel(CorePointer());
                    return new InstancedModel(ptr);
                }
            }
            set {
                ErsEngine.ERS_BasicRenderComponent_SetInstancedModel(CorePointer(), value.Data);
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
                fixed(BasicRenderComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}
