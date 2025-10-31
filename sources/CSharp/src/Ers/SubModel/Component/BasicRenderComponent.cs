using System;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;
using Ers.Visualization;

namespace Ers
{
    /// <summary>
    /// A component for a quick rendering setup.
    ///
    /// <para>
    /// Apply just a color to render a rectangle in 2D and a cube in 3D.
    /// Add an <see cref="Ers.Visualization.InstancedModel"/> to set a custom 3D model.
    /// </para>
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct BasicRenderComponent : ICoreComponent
    {
        /// <summary>
        /// The color of the entity.
        /// </summary>
        public Vector4 Color
        {
            get {
                unsafe
                {
                    IntPtr r = IntPtr.Zero;
                    IntPtr g = IntPtr.Zero;
                    IntPtr b = IntPtr.Zero;
                    IntPtr a = IntPtr.Zero;
                    ErsEngine.ERS_BasicRenderComponent_GetColor(CorePointer(), r, g, b, a);
                    return new Vector4(*(float*)r, *(float*)g, *(float*)b, *(float*)a);
                }
            }
            set {
                ErsEngine.ERS_BasicRenderComponent_SetColor(CorePointer(), value.X, value.Y, value.Z, value.W);
            }
        }

        /// <summary>
        /// The <see cref="Ers.Visualization.InstancedModel"/> used for 3D rendering.
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
