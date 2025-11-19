using System.Numerics;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Material containing color and texture information.
    /// </summary>
    public class Material
    {
        internal readonly IntPtr Data;

        internal Material(IntPtr corePointer) { Data = corePointer; }

        /// <summary>
        /// The base color of the material.
        /// </summary>
        public Vector3 Color
        {
            get {
                unsafe
                {
                    // clang-format off
                    return new Vector3(
                        *(float*)ErsEngine.ERS_Material_Color_X(Data),
                        *(float*)ErsEngine.ERS_Material_Color_Y(Data),
                        *(float*)ErsEngine.ERS_Material_Color_Z(Data));
                    // clang-format on
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Material_Color_X(Data) = value.X;
                    *(float*)ErsEngine.ERS_Material_Color_Y(Data) = value.Y;
                    *(float*)ErsEngine.ERS_Material_Color_Z(Data) = value.Z;
                }
            }
        }
    }
}
