#include "RenderContext.h"
#include "Ers/Api.h"

#include "InstancedModel.h"

namespace Ers
{
    RenderContext::RenderContext(int screenWidth, int screenHeight)
    {
        coreHandle = ersAPIFunctionPointers.ERS_RenderContext_Create(screenWidth, screenHeight);
    }

    RenderContext::RenderContext(void* corePtr) :
        coreHandle(corePtr)
    {
    }

    void RenderContext::Begin3D()
    {
        ersAPIFunctionPointers.ERS_RenderContext_Begin3D(coreHandle);
    }

    void RenderContext::End3D()
    {
        ersAPIFunctionPointers.ERS_RenderContext_End3D(coreHandle);
    }

    void RenderContext::Begin2D()
    {
        ersAPIFunctionPointers.ERS_RenderContext_Begin2D(coreHandle);
    }

    void RenderContext::End2D()
    {
        ersAPIFunctionPointers.ERS_RenderContext_End2D(coreHandle);
    }

    void RenderContext::ClearScreen()
    {
        ersAPIFunctionPointers.ERS_RenderContext_ClearScreen(coreHandle);
    }

    void RenderContext::DrawLine2D(Vector2 start, Vector2 end, float thickness, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawLine2D(coreHandle, start.X, start.Y, end.X, end.Y, thickness, color.Value);
    }

    void RenderContext::DrawTriangle2D(Vector2 v0, Vector2 v1, Vector2 v2, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTriangle2D(coreHandle, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, color.Value);
    }

    void RenderContext::DrawTriangle2D(Vector2 center, Vector2 size, float angle, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTriangle2D_Box(coreHandle, center.X, center.Y, size.X, size.Y, angle, color.Value);
    }

    void RenderContext::DrawRect2D(Vector2 center, Vector2 size, float angle, Color color, int64_t zIndex)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawRect2D(coreHandle, center.X, center.Y, size.X, size.Y, angle, color.Value, zIndex);
    }

    void RenderContext::DrawQuad2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawQuad2D(coreHandle, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, v3.X, v3.Y, color.Value);
    }

    void RenderContext::DrawInfiniteGrid2D(Color color, float lineThickness, float armLength, float targetPixelSize)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawInfiniteGrid2D(coreHandle, color.Value, lineThickness, armLength, targetPixelSize);
    }

    void RenderContext::DrawInfiniteGrid3D(Color color, float lineThickness, float targetPixelSize)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawInfiniteGrid3D(coreHandle, color.Value, lineThickness, targetPixelSize);
    }

    void
    RenderContext::DrawTexture2D(Texture& texture, Vector2 position, Vector2 size, float angle, Color color, Vector2 uvMin, Vector2 uvMax)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTexture2D(
            coreHandle, texture.Data(), position.X, position.Y, size.X, size.Y, uvMin.X, uvMin.Y, uvMax.X, uvMax.Y, angle, color.Value);
    }

    void RenderContext::DrawText2D(const std::string& text, Vector2 position, float scale, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawText2D(coreHandle, text.c_str(), position.X, position.Y, scale, color.Value);
    }

    void RenderContext::DrawCube3D(Vector3 position, Vector3 rotation, Vector3 scale, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawCube3D(
            coreHandle, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, scale.X, scale.Y, scale.Z, color.Value);
    }

    Camera2D RenderContext::GetCamera2D()
    {
        return Camera2D(ersAPIFunctionPointers.ERS_RenderContext_GetCamera2D(coreHandle));
    }

    Camera3D RenderContext::GetCamera3D()
    {
        return Camera3D(ersAPIFunctionPointers.ERS_RenderContext_GetCamera3D(coreHandle));
    }

    void RenderContext::DrawInstancedModel3D(Mesh& mesh, InstancedModel& instancedModel)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawInstancedModel3DWithMesh(coreHandle, mesh.Data(), instancedModel.Data());
    }

    void RenderContext::SetViewport(int width, int height)
    {
        ersAPIFunctionPointers.ERS_RenderContext_SetViewport(coreHandle, width, height);
    }

    void RenderContext::Present()
    {
        ersAPIFunctionPointers.ERS_RenderContext_Present(coreHandle);
    }

    void RenderContext::DrawModel3D(Model3D& model)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawModel3D(coreHandle, model.Data());
    }

    void RenderContext::DrawMesh(Mesh& mesh)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawMesh(coreHandle, mesh.Data());
    }

    void RenderContext::DrawText3D(const std::string& text, Vector3 center, Vector3 normal, Vector3 worldUp, float scale, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawText3D(
            coreHandle, text.c_str(), center.X, center.Y, center.Z, normal.X, normal.Y, normal.Z, worldUp.X, worldUp.Y, worldUp.Z, scale,
            color.Value);
    }

    void RenderContext::DrawTextBillboard(const std::string& text, Vector3 center, float scale, Color color)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTextBillboard(
            coreHandle, text.c_str(), center.X, center.Y, center.Z, scale, color.Value);
    }
} // namespace Ers
