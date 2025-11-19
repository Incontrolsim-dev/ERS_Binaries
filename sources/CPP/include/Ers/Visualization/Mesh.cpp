#include "Mesh.h"

#include "Ers/Api.h"

namespace Ers
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

    void Mesh::PushMesh(Mesh* other, Vector3 pos, Vector3 axis, float turns, Vector3 scale)
    {
        ersAPIFunctionPointers.ERS_Mesh_PushMesh(
            Data(), other->Data(), pos.X, pos.Y, pos.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
    }

    void Mesh::TranslateToFloor()
    {
        ersAPIFunctionPointers.ERS_Mesh_TranslateToFloor(Data());
    }

    void Mesh::PushCube(Vector3 pos, Vector3 scale, Color color)
    {
        ersAPIFunctionPointers.ERS_Mesh_PushCube(Data(), pos.X, pos.Y, pos.Z, scale.X, scale.Y, scale.Z, color.Value);
    }

    void Mesh::SetColor(Color color)
    {
        ersAPIFunctionPointers.ERS_Mesh_SetColor(Data(), color.Value);
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
} // namespace Ers
