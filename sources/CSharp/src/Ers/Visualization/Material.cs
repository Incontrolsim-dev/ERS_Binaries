using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Material containing color and texture information.
    /// </summary>
    public class Material
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal Material(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// The diffuse color of the material.
        /// </summary>
        public Color Color
        {
            get => Color.FromInt(ErsEngine.ERS_Material_GetDiffuseColor(CorePtr));
            set => ErsEngine.ERS_Material_SetDiffuseColor(CorePtr, value.Value);
        }
    }
}
