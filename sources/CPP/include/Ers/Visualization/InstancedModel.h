#pragma once

#include "Ers/SubModel/Component/TransformComponent.h"
#include "Model3D.h"

namespace Ers::Visualization
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
        void PushInstance(
            float posX,
            float posY,
            float posZ,
            float rotX   = 0.0f,
            float rotY   = 0.0f,
            float rotZ   = 0.0f,
            float scaleX = 1.0f,
            float scaleY = 1.0f,
            float scaleZ = 1.0f);
        void Clear();

        void* Data();
        const void* const Data() const;

      private:
        void* coreInstance;
    };
} // namespace Ers::Visualization
