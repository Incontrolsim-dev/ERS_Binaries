#include "RenderContext.h"
#include "Ers/Api.h"

#include "InstancedModel.h"

namespace Ers
{
    RenderContext::RenderContext(int screenWidth, int screenHeight)
    {
        corePtr = Ers::Engine::ERS_RenderContext_Create(screenWidth, screenHeight);
    }

    RenderContext::RenderContext(void* corePtr) :
        corePtr(corePtr)
    {
    }

    void RenderContext::Begin3D()
    {
        Ers::Engine::ERS_RenderContext_Begin3D(corePtr);
    }

    void RenderContext::End3D()
    {
        Ers::Engine::ERS_RenderContext_End3D(corePtr);
    }

    void RenderContext::Begin2D()
    {
        Ers::Engine::ERS_RenderContext_Begin2D(corePtr);
    }

    void RenderContext::End2D()
    {
        Ers::Engine::ERS_RenderContext_End2D(corePtr);
    }

    void RenderContext::ClearScreen()
    {
        Ers::Engine::ERS_RenderContext_ClearScreen(corePtr);
    }

    bool RenderContext::GetDrawBackgroundGrid() const
    {
        return Ers::Engine::ERS_RenderContext_Get_DrawBackgroundGrid(corePtr);
    }

    void RenderContext::SetDrawBackgroundGrid(bool value)
    {
        Ers::Engine::ERS_RenderContext_Set_DrawBackgroundGrid(corePtr, value);
    }

    Color RenderContext::GetBackgroundColor() const
    {
        return Color::FromInt(Ers::Engine::ERS_RenderContext_Get_BackgroundColor(corePtr));
    }

    void RenderContext::SetBackgroundColor(Color color)
    {
        Ers::Engine::ERS_RenderContext_Set_BackgroundColor(corePtr, color.Value);
    }

    Color RenderContext::GetBackgroundGridColor() const
    {
        return Color::FromInt(Ers::Engine::ERS_RenderContext_Get_BackgroundGridColor(corePtr));
    }

    void RenderContext::SetBackgroundGridColor(Color color)
    {
        Ers::Engine::ERS_RenderContext_Set_BackgroundGridColor(corePtr, color.Value);
    }

    void RenderContext::DrawLine2D(Vector2 start, Vector2 end, float thickness, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawLine2D(corePtr, start.X, start.Y, end.X, end.Y, thickness, color.Value, zIndex);
    }

    void RenderContext::DrawTriangle2D(Vector2 v0, Vector2 v1, Vector2 v2, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawTriangle2D(corePtr, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, color.Value, zIndex);
    }

    void RenderContext::DrawTriangle2D(Vector2 center, Vector2 size, float angle, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawTriangle2D_Box(corePtr, center.X, center.Y, size.X, size.Y, angle, color.Value, zIndex);
    }

    void RenderContext::DrawRect2D(Vector2 center, Vector2 size, float angle, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawRect2D(corePtr, center.X, center.Y, size.X, size.Y, angle, color.Value, zIndex);
    }

    void RenderContext::DrawQuad2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawQuad2D(corePtr, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, v3.X, v3.Y, color.Value, zIndex);
    }

    void RenderContext::DrawCircle2D(Vector2 center, Vector2 size, int segments, float angle, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawCircle2D(corePtr, center.X, center.Y, size.X, size.Y, segments, angle, color.Value, zIndex);
    }

    void RenderContext::DrawArc2D(
        Vector2 center, float radius, float width, float beginAngle, float endAngle, Color color, int segments, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawArc2D(
            corePtr, center.X, center.Y, radius, width, beginAngle, endAngle, segments, color.Value, zIndex);
    }

    void RenderContext::DrawTexture2D(
        Texture& texture, Vector2 position, Vector2 size, float angle, Color color, Vector2 uvMin, Vector2 uvMax, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawTexture2D(
            corePtr, texture.CorePtr(), position.X, position.Y, size.X, size.Y, uvMin.X, uvMin.Y, uvMax.X, uvMax.Y, angle, color.Value,
            zIndex);
    }

    void RenderContext::DrawText2D(const std::string& text, Vector2 position, float scale, Color color, int64_t zIndex)
    {
        Ers::Engine::ERS_RenderContext_DrawText2D(corePtr, text.c_str(), position.X, position.Y, scale, color.Value, zIndex);
    }

    void RenderContext::DrawCube3D(Vector3 position, Vector3 rotation, Vector3 size, Color color)
    {
        Ers::Engine::ERS_RenderContext_DrawCube3D(
            corePtr, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, size.X, size.Y, size.Z, color.Value);
    }

    Camera2D RenderContext::GetCamera2D()
    {
        return Camera2D(Ers::Engine::ERS_RenderContext_GetCamera2D(corePtr));
    }

    Camera3D RenderContext::GetCamera3D()
    {
        return Camera3D(Ers::Engine::ERS_RenderContext_GetCamera3D(corePtr));
    }

    void RenderContext::DrawInstancedModel3D(Mesh& mesh, InstancedModel& instancedModel)
    {
        Ers::Engine::ERS_RenderContext_DrawInstancedModel3DWithMesh(corePtr, mesh.CorePtr(), instancedModel.CorePtr());
    }

    void RenderContext::SetViewport(int width, int height)
    {
        Ers::Engine::ERS_RenderContext_SetViewport(corePtr, width, height);
    }

    void RenderContext::DrawModel3D(Model3D& model)
    {
        Ers::Engine::ERS_RenderContext_DrawModel3D(corePtr, model.CorePtr());
    }

    void RenderContext::DrawMesh(Mesh& mesh)
    {
        Ers::Engine::ERS_RenderContext_DrawMesh(corePtr, mesh.CorePtr());
    }

    void RenderContext::DrawText3D(const std::string& text, Vector3 center, Vector3 normal, Vector3 worldUp, float scale, Color color)
    {
        Ers::Engine::ERS_RenderContext_DrawText3D(
            corePtr, text.c_str(), center.X, center.Y, center.Z, normal.X, normal.Y, normal.Z, worldUp.X, worldUp.Y, worldUp.Z, scale,
            color.Value);
    }

    void RenderContext::DrawTextBillboard(const std::string& text, Vector3 center, float scale, Color color)
    {
        Ers::Engine::ERS_RenderContext_DrawTextBillboard(corePtr, text.c_str(), center.X, center.Y, center.Z, scale, color.Value);
    }
} // namespace Ers
