using System.Numerics;
using Ers.Engine;

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
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        internal Model3D(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// Create an empty 3D model.
        /// </summary>
        public Model3D() { CorePtr = ErsEngine.ERS_Model3D_Create(); }

        /// <summary>
        /// Construct a Model3D from a path to a 3D model file.
        /// </summary>
        /// <param name="path"></param>
        public Model3D(string path)
        {
            CorePtr      = ErsEngine.ERS_Model3D_Create();
            var textUtf8 = path.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_Model3D_Load(CorePtr, textByte);
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
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_Model3D_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Get the mesh at the given index.
        /// </summary>
        /// <param name="index">The index of the mesh to get.</param>
        /// <returns></returns>
        public Mesh GetMesh(int index) => new Mesh(ErsEngine.ERS_Model3D_GetMesh(CorePtr, index));

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

            ErsEngine.ERS_Model3D_SetTransform(CorePtr, pos.X, pos.Y, pos.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
        }

        /// <summary>
        /// Get the number of meshes in this model.
        /// </summary>
        /// <returns></returns>
        public UInt32 MeshCount
        {
            get => ErsEngine.ERS_Model3D_GetMeshCount(CorePtr);
        }
    }
}
