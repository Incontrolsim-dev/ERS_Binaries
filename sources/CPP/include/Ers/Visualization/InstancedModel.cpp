#include "InstancedModel.h"

#include "Ers/Api.h"
#include "Ers/Math/HMM/VectorMath.h"

namespace Ers
{
    InstancedModel::InstancedModel()
    {
        corePtr = Ers::Engine::ERS_InstancedModel_Create();
    }

    InstancedModel::InstancedModel(Mesh& mesh)
    {
        corePtr = Ers::Engine::ERS_InstancedModel_Create();
        Ers::Engine::ERS_InstancedModel_SetMesh(corePtr, mesh.CorePtr());
    }

    InstancedModel::~InstancedModel()
    {
        Ers::Engine::ERS_InstancedModel_Destroy(CorePtr());
    }

    void InstancedModel::SetMesh(Mesh& mesh)
    {
        Ers::Engine::ERS_InstancedModel_SetMesh(CorePtr(), mesh.CorePtr());
    }

    void InstancedModel::PushInstance(const TransformComponent& globalTransform)
    {
        PushInstance(globalTransform.GetGlobalPosition(), globalTransform.GetGlobalRotation(), globalTransform.GetGlobalScale());
    }

    void InstancedModel::PushInstance(Vector3 pos, Vector3 rotation, Vector3 scale)
    {
        Ers::Engine::ERS_InstancedModel_PushInstance(
            CorePtr(), pos.X, pos.Y, pos.Z, rotation.X, rotation.Y, rotation.Z, scale.X, scale.Y, scale.Z);
    }

    void InstancedModel::Clear()
    {
        Ers::Engine::ERS_InstancedModel_Clear(CorePtr());
    }

    void* InstancedModel::CorePtr()
    {
        return corePtr;
    }

    const void* const InstancedModel::CorePtr() const
    {
        return corePtr;
    }
} // namespace Ers
