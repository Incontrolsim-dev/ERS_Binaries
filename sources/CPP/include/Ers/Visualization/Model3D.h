#pragma once

#include "Ers/Visualization/Font.h"
#include "Ers/Visualization/Mesh.h"

namespace Ers::Visualization
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

        void* Data() { return coreInstance; }
        const void* const Data() const { return coreInstance; }

        int GetMeshCount() const;
        Mesh GetMesh(int index);

      private:
        void* coreInstance;
    };
} // namespace Ers::Visualization
