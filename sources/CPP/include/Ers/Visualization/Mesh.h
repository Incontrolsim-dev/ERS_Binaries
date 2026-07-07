#pragma once

#include <stdint.h>
#include <string>

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Visualization/Color.h"
#include "Ers/Visualization/Material.h"

namespace Ers
{
    class Mesh
    {
      public:
        Mesh();
        Mesh(void* corePtr);
        Mesh(const Mesh&)            = delete;
        Mesh(Mesh&&)                 = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&)      = delete;
        ~Mesh();

        void SetDefaultMaterial();

        /// @brief Push a vertex to the mesh.
        /// @param pos The position of the vertex.
        /// @param texCoord The UV texture coordinate of the vertex.
        /// @param color The color of the vertex.
        /// @param norm The normal vector of the vertex.
        void PushVertex(Vector3 pos, Vector2 texCoord, Color color, Vector3 norm);
        /// @brief Push an index to the mesh.
        /// @param index The index to push.
        void PushIndex(uint32_t index);
        /// @brief Push a triangle to the mesh. Vertices should be given in counter-clockwise order.
        /// @param pos0 The first corner of the triangle.
        /// @param uv0 The UV coordinate of the first corner.
        /// @param pos1 The second corner of the triangle.
        /// @param uv1 The UV coordinate of the second corner.
        /// @param pos2 The third corner of the triangle.
        /// @param uv2 The UV coordinate of the third corner.
        /// @param color The color of the triangle.
        void PushTriangle(Vector3 pos0, Vector2 uv0, Vector3 pos1, Vector2 uv1, Vector3 pos2, Vector2 uv2, Color color);
        /// @brief Push a quad built from two triangles to the mesh.
        /// @param pos0 The first corner of the quad.
        /// @param uv0 The UV coordinate of the first corner.
        /// @param pos1 The second corner of the quad.
        /// @param uv1 The UV coordinate of the second corner.
        /// @param pos2 The third corner of the quad.
        /// @param uv2 The UV coordinate of the third corner.
        /// @param pos3 The fourth corner of the quad.
        /// @param uv3 The UV coordinate of the fourth corner.
        /// @param color The color color of the quad.
        /// @param norm The normal vector of the quad.
        void PushQuad(
            Vector3 pos0,
            Vector2 uv0,
            Vector3 pos1,
            Vector2 uv1,
            Vector3 pos2,
            Vector2 uv2,
            Vector3 pos3,
            Vector2 uv3,
            Color color,
            Vector3 norm);
        /// @brief Add another mesh to this mesh. Transformations to the other mesh are performed before adding it to this mesh.
        /// @param other The other mesh to add.
        /// @param pos The local position for the other mesh.
        /// @param axis The axis around which to rotate the other mesh.
        /// @param turns The turns of counterclockwise rotation around the given axis, for the other mesh.
        /// @param scale The scale of the other mesh.
        void PushMesh(const Mesh& other, Vector3 pos, Vector3 axis = Vec3(0, 0, 1), float turns = 0, Vector3 scale = Vec3(1, 1, 1));
        /// @brief Add a cube to this mesh. Transformation to are applied before the cube is added to the mesh.
        /// @param pos The position of the cube.
        /// @param size The size of the cube.
        /// @param color The color of the cube.
        void PushCube(Vector3 pos, Vector3 size, Color color);
        /// @brief Push a new icosphere to the mesh.
        /// @param center The center of the sphere.
        /// @param subdivisions The number of subdivisions to apply.
        /// @param radius The radius of the sphere.
        /// @param color The color of the sphere.
        void PushSphere(Vector3 center, uint8_t subdivisions, float radius, Color color);
        /// @brief Push a new pyramid to the mesh.
        /// @param center The center of the pyramid (the center of its bounding box).
        /// @param dims The dimensions of the bounding box of the pyramid.
        /// @param color The color of the pyramid.
        void PushPyramid(Vector3 center, Vector3 dims, Color color);

        // Data transformations
        void TranslateToFloor();

        /// @brief Set color of the mesh.
        void SetColor(Color color);

        Material GetMaterial();

        uint32_t GetVertexCount() const;
        uint32_t GetIndexCount() const;

        void Clear();

        void* CorePtr();
        const void* const CorePtr() const;

      protected:
        void* corePtr;
    };
} // namespace Ers
