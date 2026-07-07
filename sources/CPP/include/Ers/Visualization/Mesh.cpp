#include "Mesh.h"

#include "Ers/Api.h"

namespace Ers
{
    Mesh::Mesh()
    {
        corePtr = Ers::Engine::ERS_Mesh_Create();
    }

    Mesh::Mesh(void* corePtr) :
        corePtr(corePtr)
    {
        Ers::Engine::ERS_Mesh_Increase(corePtr);
    }

    Mesh::~Mesh()
    {
        Ers::Engine::ERS_Mesh_Release(CorePtr());
    }

    void Mesh::PushVertex(Vector3 pos, Vector2 texCoord, Color color, Vector3 norm)
    {
        Ers::Engine::ERS_Mesh_PushVertex3D(CorePtr(), pos.X, pos.Y, pos.Z, texCoord.X, texCoord.Y, color.Value, norm.X, norm.Y, norm.Z);
    }

    void Mesh::PushIndex(uint32_t index)
    {
        Ers::Engine::ERS_Mesh_PushIndex(CorePtr(), index);
    }

    void Mesh::PushTriangle(Vector3 pos0, Vector2 uv0, Vector3 pos1, Vector2 uv1, Vector3 pos2, Vector2 uv2, Color color)
    {
        Ers::Engine::ERS_Mesh_PushTriangle(
            CorePtr(), pos0.X, pos0.Y, pos0.Z, uv0.X, uv0.Y, pos1.X, pos1.Y, pos1.Z, uv1.X, uv1.Y, pos2.X, pos2.Y, pos2.Z, uv2.X, uv2.Y,
            color.Value);
    }

    void Mesh::PushQuad(
        Vector3 pos0,
        Vector2 uv0,
        Vector3 pos1,
        Vector2 uv1,
        Vector3 pos2,
        Vector2 uv2,
        Vector3 pos3,
        Vector2 uv3,
        Color color,
        Vector3 norm)
    {
        Ers::Engine::ERS_Mesh_PushQuad(
            CorePtr(), pos0.X, pos0.Y, pos0.Z, uv0.X, uv0.Y, pos1.X, pos1.Y, pos1.Z, uv1.X, uv1.Y, pos2.X, pos2.Y, pos2.Z, uv2.X, uv2.Y,
            pos3.X, pos3.Y, pos3.Z, uv3.X, uv3.Y, color.Value, norm.X, norm.Y, norm.Z);
    }

    void Mesh::PushMesh(const Mesh& other, Vector3 pos, Vector3 axis, float turns, Vector3 scale)
    {
        Ers::Engine::ERS_Mesh_PushMesh(
            CorePtr(), other.CorePtr(), pos.X, pos.Y, pos.Z, axis.X, axis.Y, axis.Z, turns, scale.X, scale.Y, scale.Z);
    }

    void Mesh::TranslateToFloor()
    {
        Ers::Engine::ERS_Mesh_TranslateToFloor(CorePtr());
    }

    void Mesh::PushCube(Vector3 pos, Vector3 size, Color color)
    {
        Ers::Engine::ERS_Mesh_PushCube(CorePtr(), pos.X, pos.Y, pos.Z, size.X, size.Y, size.Z, color.Value);
    }

    void Mesh::PushSphere(Vector3 center, uint8_t subdivisions, float radius, Color color)
    {
        Ers::Engine::ERS_Mesh_PushSphere(CorePtr(), center.X, center.Y, center.Z, subdivisions, radius, color.Value);
    }

    void Mesh::PushPyramid(Vector3 center, Vector3 dims, Color color)
    {
        Ers::Engine::ERS_Mesh_PushPyramid(CorePtr(), center.X, center.Y, center.Z, dims.X, dims.Y, dims.Z, color.Value);
    }

    void Mesh::SetColor(Color color)
    {
        Ers::Engine::ERS_Mesh_SetColor(CorePtr(), color.Value);
    }

    Material Mesh::GetMaterial()
    {
        return Material(Ers::Engine::ERS_Mesh_Material(corePtr));
    }

    uint32_t Mesh::GetVertexCount() const
    {
        return Ers::Engine::ERS_Mesh_GetVertexCount(corePtr);
    }

    void Mesh::SetDefaultMaterial()
    {
        Ers::Engine::ERS_Mesh_SetDefaultMaterial(CorePtr());
    }

    uint32_t Mesh::GetIndexCount() const
    {
        return Ers::Engine::ERS_Mesh_GetIndexCount(corePtr);
    }

    void Mesh::Clear()
    {
        Ers::Engine::ERS_Mesh_Clear(CorePtr());
    }

    void* Mesh::CorePtr()
    {
        return corePtr;
    }

    const void* const Mesh::CorePtr() const
    {
        return corePtr;
    }
} // namespace Ers
