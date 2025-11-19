#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/Component/TransformComponent.h"
#include "Ers/Visualization/Model3D.h"

namespace Ers
{
    class InstancedModel
    {
      public:
        InstancedModel();
        InstancedModel(const InstancedModel&)            = delete;
        InstancedModel(InstancedModel&&)                 = delete;
        InstancedModel& operator=(const InstancedModel&) = delete;
        InstancedModel& operator=(InstancedModel&&)      = delete;
        ~InstancedModel();

        void PushInstance(const TransformComponent& globalTransform);
        void PushInstance(Vector3 pos, Vector3 rotation = Vec3(0, 0, 0), Vector3 scale = Vec3(1, 1, 1));
        void Clear();

        void* Data();
        const void* const Data() const;

      private:
        void* coreInstance;
    };
} // namespace Ers
