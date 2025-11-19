#include "InstancedModel.h"

#include "Ers/Api.h"
#include "Ers/Math/HMM/VectorMath.h"

namespace Ers
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
        PushInstance(globalTransform.GetGlobalPosition(), globalTransform.GetGlobalRotation(), globalTransform.GetGlobalScale());
    }

    void InstancedModel::PushInstance(Vector3 pos, Vector3 rotation, Vector3 scale)
    {
        ersAPIFunctionPointers.ERS_InstancedModel_PushInstance(
            Data(), pos.X, pos.Y, pos.Z, rotation.X, rotation.Y, rotation.Z, scale.X, scale.Y, scale.Z);
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
} // namespace Ers
