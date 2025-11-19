using Ers.Engine;
using System.Numerics;

namespace Ers
{
    /// <summary>
    /// A model of which multiple instances are drawn in one draw call.
    /// </summary>
    public class InstancedModel : IDisposable
    {
        internal IntPtr Data;

        /// <summary>
        /// A model of which multiple instances are drawn in one draw call.
        /// </summary>
        public InstancedModel() { Data = ErsEngine.ERS_InstancedModel_Create(); }

        public InstancedModel(Mesh mesh)
        {
            Data = ErsEngine.ERS_InstancedModel_Create();
            ErsEngine.ERS_InstancedModel_SetMesh(Data, mesh.Data);
        }

        internal InstancedModel(IntPtr corePtr) { Data = corePtr; }

        public void SetMesh(Mesh mesh) { ErsEngine.ERS_InstancedModel_SetMesh(Data, mesh.Data); }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~InstancedModel() => DisposeInner();

        /// <summary>
        /// Indicate the InstancedModel is no longer required and can be freed from memory.
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
                ErsEngine.ERS_InstancedModel_Release(Data);
                Data = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Clear all instances from the instanced model.
        /// </summary>
        public void Clear() => ErsEngine.ERS_InstancedModel_Clear(Data);

        /// <summary>
        /// Push a new instance of the instanced model to be rendered.
        /// </summary>
        /// <param name="position">The position of the instance.</param>
        /// <param name="rotation">The rotation of the instance in turns (1 turn = 360 degrees).</param>
        /// <param name="scale">The scale of the instance.</param>
        public void PushInstance(Vector3 position, Vector3 rotation = default, Vector3 scale = default)
        {
            if (rotation == default)
                rotation = Vector3.Zero;
            if (scale == default)
                scale = Vector3.One;

            ErsEngine.ERS_InstancedModel_PushInstance(
                Data, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, scale.X, scale.Y, scale.Z);
        }
    }
}
