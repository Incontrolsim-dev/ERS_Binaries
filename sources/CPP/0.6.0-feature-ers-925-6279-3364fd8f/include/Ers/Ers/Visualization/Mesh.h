#pragma once

#include <stdint.h>
#include <string>

namespace Ers::Visualization
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

        void PushMesh(Mesh* other, float posX, float posY, float posZ);
        void PushMesh(Mesh* other, float posX, float posY, float posZ, float axisX, float axisY, float axisZ, float turns, float scale);
        void PushCube(float x, float y, float z, float sizeX, float sizeY, float sizeZ, float colorR, float colorG, float colorB);
        void SetPosition(float x, float y, float z);

        // Data transformations
        void TranslateToFloor();

        // @brief Set color of the mesh
        void SetColor(float colorR, float colorG, float colorB);

        uint32_t GetVertexCount() const;
        uint32_t GetIndexCount() const;
        void Clear();

        void* Data();
        const void* const Data() const;

      protected:
        void* coreInstance;
    };
} // namespace Ers::Visualization
