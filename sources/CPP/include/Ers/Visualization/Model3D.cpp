#include "Model3D.h"

#include "Ers/Api.h"

namespace Ers
{
    Model3D::Model3D()
    {
        coreInstance = ersAPIFunctionPointers.ERS_Model3D_Create();
    }

    Model3D::Model3D(const std::string& path)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Model3D_Create();
        ersAPIFunctionPointers.ERS_Model3D_Load(coreInstance, path.c_str());
    }

    Model3D::~Model3D()
    {
        ersAPIFunctionPointers.ERS_Model3D_Destroy(coreInstance);
    }

    int Model3D::GetMeshCount() const
    {
        return ersAPIFunctionPointers.ERS_Model3D_GetMeshCount(coreInstance);
    }

    Mesh Model3D::GetMesh(int index)
    {
        return Mesh(ersAPIFunctionPointers.ERS_Model3D_GetMesh(coreInstance, index));
    }
} // namespace Ers
