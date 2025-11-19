using Ers.Engine;
using System.Numerics;
using System.Runtime.CompilerServices;

namespace Ers
{
    /// <summary>
    /// A 3D model consisting of one or more meshes, materials and transforms.
    ///
    /// <para>
    /// Each material and transform is matched to the mesh by index.
    /// For example, the mesh at index 1 uses the material and transform at index 1.
    /// </para>
    /// </summary>
    public class Model3D : IDisposable
    {
        internal IntPtr Data;

        internal Model3D(IntPtr corePointer) { Data = corePointer; }

        /// <summary>
        /// Create an empty 3D model.
        /// </summary>
        public Model3D() { Data = ErsEngine.ERS_Model3D_Create(); }
        public Model3D(string modelDataPath)
        {
            Data         = ErsEngine.ERS_Model3D_Create();
            var textUtf8 = modelDataPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_Model3D_Load(Data, textByte);
                }
            }
        }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~Model3D() => DisposeInner();

        /// <summary>
        /// Indicate the Model3D is no longer required and can be freed from memory.
        /// </summary>
        public void Dispose()
        {
            DisposeInner();
            GC.SuppressFinalize(this);
        }

        private void DisposeInner()
        {
            if (Data != IntPtr.Zero)
            {
                ErsEngine.ERS_Model3D_Destroy(Data);
                Data = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Get the mesh at the given index.
        /// </summary>
        /// <param name="index">The index of the mesh to get.</param>
        /// <returns></returns>
        public Mesh GetMesh(int index) { return new Mesh(ErsEngine.ERS_Model3D_GetMesh(Data, index)); }

        /// <summary>
        /// Set the transform of this model.
        /// </summary>
        /// <param name="pos">The translation for the transform.</param>
        /// <param name="axis">The axis around which to rotate.</param>
        /// <param name="turns">The turns of rotation.</param>
        /// <param name="scale">The scale for the transform.</param>
        public void SetTransform(Vector3 pos, Vector3 axis = default, float turns = 0.0f, Vector3 scale = default)
        {
            if (axis == default)
                axis = Vector3.UnitZ;
            if (scale == default)
                scale = Vector3.One;

            ErsEngine.ERS_Model3D_SetTransform(Data, pos.X, pos.Y, pos.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
        }

        /// <summary>
        /// Get the number of meshes in this model.
        /// </summary>
        /// <returns></returns>
        public nuint NumMeshes() { return (nuint)ErsEngine.ERS_Model3D_GetMeshCount(Data); }
    }
}
