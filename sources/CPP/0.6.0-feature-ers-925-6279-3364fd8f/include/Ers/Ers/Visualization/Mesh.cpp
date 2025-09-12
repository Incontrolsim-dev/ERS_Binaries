#include "Mesh.h"

#include "Ers/Api.h"

namespace Ers::Visualization
{
    Mesh::Mesh()
    {
        coreInstance = ersAPIFunctionPointers.ERS_Mesh_Create();
    }

    Mesh::Mesh(void* coreInstance) :
        coreInstance(coreInstance)
    {
        ersAPIFunctionPointers.ERS_Mesh_Increase(coreInstance);
    }

    Mesh::~Mesh()
    {
        ersAPIFunctionPointers.ERS_Mesh_Release(Data());
    }

    void Mesh::PushMesh(Mesh* other, float posX, float posY, float posZ)
    {
        ersAPIFunctionPointers.ERS_Mesh_PushMesh(Data(), other->Data(), posX, posY, posZ, 0, 0, 1, 0, 1, 1, 1);
    }

    void Mesh::PushMesh(Mesh* other, float posX, float posY, float posZ, float axisX, float axisY, float axisZ, float turns, float scale)
    {
        ersAPIFunctionPointers.ERS_Mesh_PushMesh(Data(), other->Data(), posX, posY, posZ, axisX, axisY, axisZ, turns, scale, scale, scale);
    }

    void Mesh::TranslateToFloor()
    {
        ersAPIFunctionPointers.ERS_Mesh_TranslateToFloor(Data());
    }

    void Mesh::PushCube(float x, float y, float z, float sizeX, float sizeY, float sizeZ, float colorR, float colorG, float colorB)
    {
        ersAPIFunctionPointers.ERS_Mesh_PushCube(Data(), x, y, z, sizeX, sizeY, sizeZ, colorR, colorG, colorB);
    }

    void Mesh::SetColor(float colorR, float colorG, float colorB)
    {
        ersAPIFunctionPointers.ERS_Mesh_SetColor(Data(), colorR, colorG, colorB);
    }

    uint32_t Mesh::GetVertexCount() const
    {
        return ersAPIFunctionPointers.ERS_Mesh_GetVertexCount(coreInstance);
    }

    void Mesh::SetDefaultMaterial()
    {
        ersAPIFunctionPointers.ERS_Mesh_SetDefaultMaterial(Data());
    }

    uint32_t Mesh::GetIndexCount() const
    {
        return ersAPIFunctionPointers.ERS_Mesh_GetIndexCount(coreInstance);
    }

    void Mesh::Clear()
    {
        ersAPIFunctionPointers.ERS_Mesh_Clear(Data());
    }

    void* Mesh::Data()
    {
        return coreInstance;
    }

    const void* const Mesh::Data() const
    {
        return coreInstance;
    }
} // namespace Ers::Visualization
