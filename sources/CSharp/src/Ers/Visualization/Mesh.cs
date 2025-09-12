using System.Numerics;
using Ers.Engine;

namespace Ers.Visualization
{
    /// <summary>
    /// Raw mesh data (vertices and indices).
    /// </summary>
    public class Mesh : IDisposable
    {
        internal IntPtr Data;

        internal Mesh(IntPtr corePointer)
        {
            Data = corePointer;
            ErsEngine.ERS_Mesh_Increase(Data);
        }

        /// <summary>
        /// Create a new empty mesh.
        /// </summary>
        public Mesh() { Data = ErsEngine.ERS_Mesh_Create(); }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~Mesh() => DisposeInner();

        /// <summary>
        /// Indicate the Mesh is no longer required and can be freed from memory.
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
                ErsEngine.ERS_Mesh_Release(Data);
                Data = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Push a vertex to the mesh.
        /// </summary>
        /// <param name="pos">The position of the vertex.</param>
        /// <param name="texCoord">The UV texture coordinates of the vertex.</param>
        /// <param name="color">The color of the vertex. Each color channel is in range [0,1].</param>
        /// <param name="norm">The normal vector of the vertex.</param>
        public void PushVertex(Vector3 pos, Vector2 texCoord, Vector3 color, Vector3 norm)
        {
            ErsEngine.ERS_Mesh_PushVertex3D(
                Data, pos.X, pos.Y, pos.Z, norm.X, norm.Y, norm.Z, texCoord.X, texCoord.Y, color.X, color.Y, color.Z);
        }

        /// <summary>
        /// Push an index to the mesh.
        /// </summary>
        /// <param name="index">The index to push.</param>
        public void PushIndex(UInt32 index) => ErsEngine.ERS_Mesh_PushIndex(Data, index);

        /// <summary>
        /// Push a quad built from two triangles to the mesh.
        /// </summary>
        /// <param name="pos0">The first corner of the quad.</param>
        /// <param name="uv0">The UV coordinate of the first corner.</param>
        /// <param name="pos1">The second corner of the quad.</param>
        /// <param name="uv1">The UV coordinate of the second corner.</param>
        /// <param name="pos2">The third corner of the quad.</param>
        /// <param name="uv2">The UV coordinate of the third corner.</param>
        /// <param name="pos3">The fourth corner of the quad.</param>
        /// <param name="uv3">The UV coordinate of the fourth corner.</param>
        /// <param name="color">The color of the quad. Each color channel is in range [0,1].</param>
        /// <param name="norm">The normal vector of the quad.</param>
        public void PushQuad(
            Vector3 pos0,
            Vector2 uv0,
            Vector3 pos1,
            Vector2 uv1,
            Vector3 pos2,
            Vector2 uv2,
            Vector3 pos3,
            Vector2 uv3,
            Vector3 color,
            Vector3 norm)
        {
            ErsEngine.ERS_Mesh_PushQuad(
                Data, pos0.X, pos0.Y, pos0.Z, uv0.X, uv0.Y, pos1.X, pos1.Y, pos1.Z, uv1.X, uv1.Y, pos2.X, pos2.Y, pos2.Z, uv2.X, uv2.Y,
                pos3.X, pos3.Y, pos3.Z, uv3.X, uv3.Y, color.X, color.Y, color.Z, norm.X, norm.Y, norm.Z);
        }

        /// <summary>
        /// Push a 3D cube to the mesh.
        /// </summary>
        /// <param name="pos">The center position of the cube.</param>
        /// <param name="dims">The dimensions of the cube.</param>
        /// <param name="color">The color of the cube. Each color channel is in range [0,1].</param>
        public void PushCube(Vector3 pos, Vector3 dims, Vector3 color)
        {
            ErsEngine.ERS_Mesh_PushCube(Data, pos.X, pos.Y, pos.Z, dims.X, dims.Y, dims.Z, color.X, color.Y, color.Z);
        }

        /// <summary>
        /// Push a 3D rectangular beam between two positions.
        /// </summary>
        /// <param name="from">One end of the beam.</param>
        /// <param name="to">The other end of the beam.</param>
        /// <param name="up">The up vector for the beam.</param>
        /// <param name="size">The size (width, height, depth) of the beam.</param>
        /// <param name="color">The color of the beam. Each color channel is in range [0,1].</param>
        public void PushBeam(Vector3 from, Vector3 to, Vector3 up, float width, float height, Vector3 color)
        {
            ErsEngine.ERS_Mesh_PushBeam(
                Data, from.X, from.Y, from.Z, to.X, to.Y, to.Z, up.X, up.Y, up.Z, width, height, color.X, color.Y, color.Z);
        }

        public void PusHelicalBeam(
            Vector3 center,
            float radius,
            float beginAngle,
            float endAngle,
            float endZ,
            float beamWidth,
            float beamHeight,
            int segments,
            Vector4 color = default)
        {
            if (color == default)
            {
                color = new Vector4(0.5f, 0.5f, 0.5f, 1.0f);
            }
            ErsEngine.ERS_Mesh_PushHelicalBeam(
                Data, center.X, center.Y, center.Z, radius, beginAngle, endAngle, endZ, beamWidth, beamHeight, color.X, color.Y, color.Z,
                segments);
        }

        /// <summary>
        /// Add another mesh to this mesh.
        /// <para>Transformations to the other mesh are performed before adding it to the this mesh.</para>
        /// </summary>
        /// <param name="other">The other mesh to add.</param>
        /// <param name="pos">The position for the mesh to add.</param>
        /// <param name="axis">The axis around which to rotate the mesh to add.</param>
        /// <param name="turns">The turns of counterclockwise rotation for the mesh to add.</param>
        /// <param name="scale">The scale of the mesh to add.</param>
        public void PushMesh(Mesh other, Vector3 pos, Vector3 axis = default, float turns = 0.0f, Vector3 scale = default)
        {
            if (axis == default)
                axis = Vector3.UnitZ;
            if (scale == default)
                scale = Vector3.One;

            ErsEngine.ERS_Mesh_PushMesh(Data, other.Data, pos.X, pos.Y, pos.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
        }

        /// <summary>
        /// Apply a transformation to the vertices of the mesh.
        /// </summary>
        /// <param name="translation">The translation to apply.</param>
        /// <param name="axis">The axis around which to rotate.</param>
        /// <param name="turns">The turns of counterclockwise rotation to apply.</param>
        /// <param name="scale">The scale to apply.</param>
        public void TransformVertices(Vector3 translation, Vector3 axis = default, float turns = 0.0f, Vector3 scale = default)
        {
            if (axis == default)
                axis = Vector3.UnitZ;
            if (scale == default)
                scale = Vector3.One;

            ErsEngine.ERS_Mesh_TransformVertices2(
                Data, translation.X, translation.Y, translation.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
        }

        /// <summary>
        /// Translate the mesh along the XYZ-axes such that the vertices are centered around the origin.
        /// </summary>
        public void CenterAtOrigin() => ErsEngine.ERS_Mesh_CenterAtOrigin(Data);

        /// <summary>
        /// Translate the mesh along the Z-axis such that it's lowest point is on at Z=0.
        /// </summary>
        public void TranslateToFloor() => ErsEngine.ERS_Mesh_TranslateToFloor(Data);

        /// <summary>
        /// Set the color of the mesh.
        /// </summary>
        /// <param name="color">The color as an RGB vector with channels in range of [0,1].</param>
        public void SetColor(Vector3 color) => ErsEngine.ERS_Mesh_SetColor(Data, color.X, color.Y, color.Z);

        /// <summary>
        /// Normalize the scale of the mesh so it longest axis becomes length 1.
        /// </summary>
        public void Normalize() => ErsEngine.ERS_Mesh_Normalize(Data);

        /// <summary>
        /// Get the number of vertices in the mesh.
        /// </summary>
        /// <returns></returns>
        public UInt32 GetVertexCount() => (UInt32)ErsEngine.ERS_Mesh_GetVertexCount(Data);

        /// <summary>
        /// Get the number of indices in the mesh.
        /// </summary>
        /// <returns></returns>
        public UInt32 GetIndexCount() => (UInt32)ErsEngine.ERS_Mesh_GetIndexCount(Data);

        public void SetDefaultMaterial() => ErsEngine.ERS_Mesh_SetDefaultMaterial(Data);

        /// <summary>
        /// Calculate the highest XYZ-values in the vertices.
        /// </summary>
        /// <returns></returns>
        public Vector3 Max()
        {
            unsafe
            {
                Vector3 result;
                ErsEngine.ERS_Mesh_GetMax(Data, (IntPtr)(&result.X), (IntPtr)(&result.Y), (IntPtr)(&result.Z));
                return result;
            }
        }

        /// <summary>
        /// Calculate the lowest XYZ-values in the vertices.
        /// </summary>
        /// <returns></returns>
        public Vector3 Min()
        {
            unsafe
            {
                Vector3 result;
                ErsEngine.ERS_Mesh_GetMin(Data, (IntPtr)(&result.X), (IntPtr)(&result.Y), (IntPtr)(&result.Z));
                return result;
            }
        }

        /// <summary>
        /// Clear / empty the mesh data.
        /// </summary>
        public void Clear() => ErsEngine.ERS_Mesh_Clear(Data);
    }
}
