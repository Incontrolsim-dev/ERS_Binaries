#include "InstancedModel.h"

#include "Ers/Api.h"

namespace Ers::Visualization
{
    InstancedModel::InstancedModel()
    {
        coreInstance = ersAPIFunctionPointers.ERS_InstancedModel_Create();
    }

    InstancedModel::~InstancedModel()
    {
        ersAPIFunctionPointers.ERS_InstancedModel_Release(Data());
    }

    void InstancedModel::PushInstance(const TransformComponent& globalTransform)
    {
        PushInstance(
            globalTransform.GlobalPositionX(), globalTransform.GlobalPositionY(), globalTransform.GlobalPositionZ(),
            globalTransform.GlobalRotationX(), globalTransform.GlobalRotationY(), globalTransform.GlobalRotationZ(),
            globalTransform.GlobalScaleX(), globalTransform.GlobalScaleY(), globalTransform.GlobalScaleZ());
    }

    void InstancedModel::PushInstance(
        float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ)
    {
        ersAPIFunctionPointers.ERS_InstancedModel_PushInstance(Data(), posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
    }

    void InstancedModel::Clear()
    {
        ersAPIFunctionPointers.ERS_InstancedModel_Clear(Data());
    }

    void* InstancedModel::Data()
    {
        return coreInstance;
    }

    const void* const InstancedModel::Data() const
    {
        return coreInstance;
    }
} // namespace Ers::Visualization
