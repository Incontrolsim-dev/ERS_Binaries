#include "RenderContext.h"
#include "Ers/Api.h"

#include "InstancedModel.h"

namespace Ers::Visualization
{
    RenderContext::RenderContext(int screenWidth, int screenHeight)
    {
        coreHandle = ersAPIFunctionPointers.ERS_RenderContext_Create(screenWidth, screenHeight);
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

    void RenderContext::DrawLine2D(
        float startX, float startY, float endX, float endY, float thickness, float colorR, float colorG, float colorB, float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawLine2D(
            coreHandle, startX, startY, endX, endY, thickness, colorR, colorG, colorB, colorA);
    }

    void RenderContext::DrawTriangle2D(
        float v0X, float v0Y, float v1X, float v1Y, float v2X, float v2Y, float colorR, float colorG, float colorB, float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTriangle2D(coreHandle, v0X, v0Y, v1X, v1Y, v2X, v2Y, colorR, colorG, colorB, colorA);
    }

    void RenderContext::DrawTriangle2D(
        float centerX, float centerY, float sizeX, float sizeY, float angle, float colorR, float colorG, float colorB, float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTriangle2D_Box(
            coreHandle, centerX, centerY, sizeX, sizeY, angle, colorR, colorG, colorB, colorA);
    }

    void RenderContext::DrawRect2D(
        float centerX,
        float centerY,
        float sizeX,
        float sizeY,
        float angle,
        float colorR,
        float colorG,
        float colorB,
        float colorA,
        int64_t zIndex)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawRect2D(
            coreHandle, centerX, centerY, sizeX, sizeY, angle, colorR, colorG, colorB, colorA, zIndex);
    }

    void RenderContext::DrawQuad2D(
        float x0,
        float y0,
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        float colorR,
        float colorG,
        float colorB,
        float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawQuad2D(coreHandle, x0, y0, x1, y1, x2, y2, x3, y3, colorR, colorG, colorB, colorA);
    }

    void
    RenderContext::DrawInfiniteGrid2D(float colorR, float colorG, float colorB, float lineThickness, float armLength, float targetPixelSize)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawInfiniteGrid2D(
            coreHandle, colorR, colorG, colorB, lineThickness, armLength, targetPixelSize);
    }

    void RenderContext::DrawTexture2D(
        Texture& texture,
        float x,
        float y,
        float width,
        float height,
        float angle,
        float r,
        float g,
        float b,
        float a,
        float uvMinX,
        float uvMinY,
        float uvMaxX,
        float uvMaxY)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTexture2D(
            coreHandle, texture.Data(), x, y, width, height, uvMinX, uvMinY, uvMaxX, uvMaxY, angle, r, g, b, a);
    }

    void RenderContext::DrawText2D(
        const std::string& text, float x, float y, float scale, float colorR, float colorG, float colorB, float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawText2D(coreHandle, text.c_str(), x, y, scale, colorR, colorG, colorB, colorA);
    }

    void RenderContext::DrawCube3D(
        float x,
        float y,
        float z,
        float xRotation,
        float yRotation,
        float zRotation,
        float xScale,
        float yScale,
        float zScale,
        float colorR,
        float colorG,
        float colorB,
        float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawCube3D(
            coreHandle, x, y, z, xRotation, yRotation, zRotation, xScale, yScale, zScale, colorR, colorG, colorB, colorA);
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

    void RenderContext::DrawText3D(
        const std::string& text,
        float centerX,
        float centerY,
        float centerZ,
        float normalX,
        float normalY,
        float normalZ,
        float worldUpX,
        float worldUpY,
        float worldUpZ,
        float scale,
        float colorR,
        float colorG,
        float colorB,
        float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawText3D(
            coreHandle, text.c_str(), centerX, centerY, centerZ, normalX, normalY, normalZ, worldUpX, worldUpY, worldUpZ, scale, colorR,
            colorG, colorB, colorA);
    }

    void RenderContext::DrawTextBillboard(
        const std::string& text,
        float centerX,
        float centerY,
        float centerZ,
        float scale,
        float colorR,
        float colorG,
        float colorB,
        float colorA)
    {
        ersAPIFunctionPointers.ERS_RenderContext_DrawTextBillboard(
            coreHandle, text.c_str(), centerX, centerY, centerZ, scale, colorR, colorG, colorB, colorA);
    }

    RenderContext::~RenderContext()
    {
        ersAPIFunctionPointers.ERS_RenderContext_Dispose(coreHandle);
    }
} // namespace Ers::Visualization
