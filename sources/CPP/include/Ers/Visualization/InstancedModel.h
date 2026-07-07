#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/Component/TransformComponent.h"
#include "Ers/Visualization/Mesh.h"

namespace Ers
{
    class InstancedModel
    {
      public:
        InstancedModel();
        InstancedModel(Mesh& mesh);
        InstancedModel(const InstancedModel&)            = delete;
        InstancedModel(InstancedModel&&)                 = delete;
        InstancedModel& operator=(const InstancedModel&) = delete;
        InstancedModel& operator=(InstancedModel&&)      = delete;
        ~InstancedModel();

        void SetMesh(Mesh& mesh);
        void PushInstance(const TransformComponent& globalTransform);
        void PushInstance(Vector3 pos, Vector3 rotation = Vec3(0, 0, 0), Vector3 scale = Vec3(1, 1, 1));
        /// @brief Clear all pushed instances. Call this every frame so instances don't spill over.
        void Clear();

        void* CorePtr();
        const void* const CorePtr() const;

      private:
        void* corePtr;
    };
} // namespace Ers
