#include "Model3D.h"

#include "Ers/Api.h"

namespace Ers
{
    Model3D::Model3D()
    {
        corePtr = Ers::Engine::ERS_Model3D_Create();
    }

    Model3D::Model3D(const std::string& path)
    {
        corePtr = Ers::Engine::ERS_Model3D_Create();
        Ers::Engine::ERS_Model3D_Load(corePtr, path.c_str());
    }

    Model3D::~Model3D()
    {
        Ers::Engine::ERS_Model3D_Destroy(corePtr);
    }

    uint32_t Model3D::MeshCount() const
    {
        return Ers::Engine::ERS_Model3D_GetMeshCount(corePtr);
    }

    Mesh Model3D::GetMesh(int index)
    {
        return Mesh(Ers::Engine::ERS_Model3D_GetMesh(corePtr, index));
    }

    void Model3D::SetTransform(Vector3 pos, Vector3 axis, float turns, Vector3 scale)
    {
        Ers::Engine::ERS_Model3D_SetTransform(corePtr, pos.X, pos.Y, pos.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
    }
} // namespace Ers
