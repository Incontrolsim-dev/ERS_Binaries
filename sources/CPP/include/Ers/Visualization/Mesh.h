#pragma once

#include <stdint.h>
#include <string>

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Visualization/Color.h"

namespace Ers
{
    class Mesh
    {
      public:
        Mesh();
        Mesh(void* coreInstance);
        Mesh(const Mesh&)            = delete;
        Mesh(Mesh&&)                 = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&)      = delete;
        ~Mesh();

        void SetDefaultMaterial();

        // Push triangle-based data

        /// @brief Add another mesh to this mesh. Transformations to the other mesh are performed before adding it to this mesh.
        /// @param other The other mesh to add.
        /// @param pos The local position for the other mesh.
        /// @param axis The axis around which to rotate the other mesh.
        /// @param turns The turns of counterclockwise rotation around the given axis, for the other mesh.
        /// @param scale The scale of the other mesh.
        void PushMesh(Mesh* other, Vector3 pos, Vector3 axis = Vec3(0, 0, 1), float turns = 0, Vector3 scale = Vec3(1, 1, 1));
        /// @brief Add a cube to this mesh. Transformation to are applied before the cube is added to the mesh.
        /// @param pos The position of the cube.
        /// @param size The dimensions of the cube.
        /// @param color The color of the cube.
        void PushCube(Vector3 pos, Vector3 scale, Color color);

        // Data transformations
        void TranslateToFloor();

        /// @brief Set color of the mesh.
        void SetColor(Color color);

        uint32_t GetVertexCount() const;
        uint32_t GetIndexCount() const;
        void Clear();

        void* Data();
        const void* const Data() const;

      protected:
        void* coreInstance;
    };
} // namespace Ers
