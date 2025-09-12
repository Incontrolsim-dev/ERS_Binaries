#pragma once

#include "Ers/Visualization/Camera2D.h"
#include "Ers/Visualization/Camera3D.h"
#include "Ers/Visualization/Model3D.h"
#include "Ers/Visualization/Texture.h"

namespace Ers::Visualization
{

    // Forward declarations
    class InstancedModel;
    class RenderContext
    {
      public:
        RenderContext(int screenWidth, int screenHeight);
        ~RenderContext();

        void ClearScreen();

        void DrawModel3D(Model3D& model);
        void DrawMesh(Mesh& mesh);
        void DrawInstancedModel3D(Mesh& mesh, InstancedModel& instancedModel);

        /// @brief Draw a 2D line.
        /// @param v0X The start X-position.
        /// @param v0Y The start Y-position.
        /// @param v1X The end X-position.
        /// @param v1Y The end Y-position.
        /// @param thickness The thickness of the line.
        /// @param colorR The red channel for the color.
        /// @param colorG The green channel for the color.
        /// @param colorB The blue channel for the color.
        /// @param colorA The alpha channel for the color.
        void DrawLine2D(
            float startX, float startY, float endX, float endY, float thickness, float colorR, float colorG, float colorB, float colorA);

        /// @brief Draw a 2D triangle based on three corner vertices.
        /// @param v0X The first vertex's X-position.
        /// @param v0Y The first vertex's Y-position.
        /// @param v1X The second vertex's X-position.
        /// @param v1Y The second vertex's Y-position.
        /// @param v2X The third vertex's X-position.
        /// @param v2Y The third vertex's Y-position.
        /// @param colorR The red color channel of the color.
        /// @param colorG The green color channel of the color.
        /// @param colorB The blue color channel of the color.
        /// @param colorA The alpha color channel of the color.
        void DrawTriangle2D(
            float v0X, float v0Y, float v1X, float v1Y, float v2X, float v2Y, float colorR, float colorG, float colorB, float colorA);

        /// @brief Draw a 2D triangle.
        /// The triangle is drawn as it would be inside a bounding box where the bottom-left and bottom-right vertices match the box's
        /// and the top vertex is in the middle of the top edge of the box.
        /// @param centerX The center X-position of the bounding box.
        /// @param centerY The center Y-position of the bounding box.
        /// @param sizeX The width of the bounding box.
        /// @param sizeY The height of the bounding box.
        /// @param angle The counterclockwise rotation of the triangle.
        /// @param colorR The red color channel of the color.
        /// @param colorG The green color channel of the color.
        /// @param colorB The blue color channel of the color.
        /// @param colorA The alpha color channel of the color.
        void DrawTriangle2D(
            float centerX, float centerY, float width, float height, float angle, float colorR, float colorG, float colorB, float colorA);

        /// @brief Draw a 2D rectangle.
        /// @param centerX The center X-position of the rectangle.
        /// @param centerY The center Y-position of the rectangle.
        /// @param sizeX The width of the rectangle.
        /// @param sizeY The height of the rectangle.
        /// @param angle The counterclockwise rotation in turns.
        /// @param colorR The red channel of the color.
        /// @param colorG The green channel of the color.
        /// @param colorB The blue channel of the color.
        /// @param colorA The alpha channel of the color.
        void DrawRect2D(
            float centerX,
            float centerY,
            float sizeX,
            float sizeY,
            float angle    = 0.0f,
            float colorR   = 1.0f,
            float colorG   = 1.0f,
            float colorB   = 1.0f,
            float colorA   = 1.0f,
            int64_t zIndex = 0);

        void DrawQuad2D(
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
            float colorA);

        /// @brief Draw an infinite 2D grid. The grid fades between different grid sizes based on the camera zoom.
        /// @param colorR The red color channel of the grid.
        /// @param colorG The green color channel of the grid.
        /// @param colorB The blue color channel of the grid.
        /// @param lineThickness The thickness of the grid lines.
        /// @param armLength The length of the grid arms. A value of 0.5 creates a full grid.
        /// @param targetPixelSize The target pixel size of the grid cells.
        void DrawInfiniteGrid2D(
            float colorR          = 0.0f,
            float colorG          = 0.0f,
            float colorB          = 0.0f,
            float lineThickness   = 1.0f,
            float armLength       = 0.1f,
            float targetPixelSize = 64.0f);

        void DrawText2D(const std::string& text, float x, float y, float scale, float colorR, float colorG, float colorB, float colorA);

        void DrawTexture2D(
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
            float uvMinX = 0,
            float uvMinY = 0,
            float uvMaxX = 1,
            float uvMaxY = 1);

        void DrawCube3D(
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
            float colorA);

        void DrawText3D(
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
            float colorA);

        void DrawTextBillboard(
            const std::string& text,
            float centerX,
            float centerY,
            float centerZ,
            float scale,
            float colorR,
            float colorG,
            float colorB,
            float colorA);

        void SetViewport(int width, int height);
        void Present();

        Camera2D GetCamera2D();
        Camera3D GetCamera3D();

        void Begin3D();
        void End3D();

        void Begin2D();
        void End2D();

        void* GetData() { return coreHandle; };

      private:
        void* coreHandle = nullptr;
    };
} // namespace Ers::Visualization
