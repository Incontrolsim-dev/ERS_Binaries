#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Visualization/Font.h"
#include "Ers/Visualization/Mesh.h"

namespace Ers
{
    class Model3D
    {
      public:
        Model3D();
        Model3D(const std::string& path);
        Model3D(const Model3D&)            = delete;
        Model3D(Model3D&&)                 = default;
        Model3D& operator=(const Model3D&) = default;
        Model3D& operator=(Model3D&&)      = default;
        ~Model3D();

        uint32_t MeshCount() const;

        Mesh GetMesh(int index);

        void SetTransform(Vector3 pos, Vector3 axis = Vec3(0, 0, 1), float turns = 0.0f, Vector3 scale = Vec3(1, 1, 1));

        void* CorePtr() { return corePtr; }
        const void* const CorePtr() const { return corePtr; }

      private:
        void* corePtr;
    };
} // namespace Ers
