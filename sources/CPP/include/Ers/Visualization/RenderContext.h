#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Visualization/Camera2D.h"
#include "Ers/Visualization/Camera3D.h"
#include "Ers/Visualization/Color.h"
#include "Ers/Visualization/Model3D.h"
#include "Ers/Visualization/Texture.h"

namespace Ers
{

    // Forward declarations
    class InstancedModel;
    class RenderContext
    {
      public:
        RenderContext(int screenWidth, int screenHeight);
        RenderContext(void* corePtr);

        void ClearScreen();

        void DrawModel3D(Model3D& model);
        void DrawMesh(Mesh& mesh);
        void DrawInstancedModel3D(Mesh& mesh, InstancedModel& instancedModel);

        /// @brief Draw a 2D line.
        /// @param start The start position.
        /// @param end The end position.
        /// @param thickness The thickness of the line.
        /// @param color The color of the line.
        void DrawLine2D(Vector2 start, Vector2 end, float thickness, Color color);

        /// @brief Draw a 2D triangle based on three corner vertices.
        /// @param v0 The first vertex position.
        /// @param v1 The second vertex position.
        /// @param v2 The third vertex position.
        /// @param color The color of the triangle.
        void DrawTriangle2D(Vector2 v0, Vector2 v1, Vector2 v2, Color color);

        /// @brief Draw a 2D triangle.
        /// The triangle is drawn as it would be inside a bounding box where the bottom-left and bottom-right vertices match the box's
        /// and the top vertex is in the middle of the top edge of the box.
        /// @param center The center position of the bounding box.
        /// @param size The size of the bounding box.
        /// @param angle The counterclockwise rotation of the triangle.
        /// @param color The color of the triangle.
        void DrawTriangle2D(Vector2 center, Vector2 size, float angle, Color color);

        /// @brief Draw a 2D rectangle.
        /// @param center The center position of the rectangle.
        /// @param size The size of the rectangle.
        /// @param angle The counterclockwise rotation in turns.
        /// @param color The color of the rectangle.
        /// @param zIndex The z-index for layering.
        void DrawRect2D(Vector2 center, Vector2 size, float angle, Color color = Color::FromFloats(1.0f, 1.0f, 1.0f), int64_t zIndex = 0);

        /// @brief Draw a 2D quadrilateral.
        /// @param v0 The first vertex position.
        /// @param v1 The second vertex position.
        /// @param v2 The third vertex position.
        /// @param v3 The fourth vertex position.
        /// @param color The color of the quad.
        void DrawQuad2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, Color color);

        /// @brief Draw an infinite 2D grid. The grid fades between different grid sizes based on the camera zoom.
        /// @param color The color of the grid (RGB only, alpha ignored).
        /// @param lineThickness The thickness of the grid lines.
        /// @param armLength The length of the grid arms. A value of 0.5 creates a full grid.
        /// @param targetPixelSize The target pixel size of the grid cells.
        void DrawInfiniteGrid2D(
            Color color           = Color::FromFloats(0.0f, 0.0f, 0.0f),
            float lineThickness   = 1.0f,
            float armLength       = 0.1f,
            float targetPixelSize = 64.0f);

        /// @brief Draw an infinite 3D grid. The grid fades between different grid sizes based on the camera zoom.
        /// @param color The color of the grid (RGB only, alpha ignored).
        /// @param lineThickness The thickness of the grid lines.
        /// @param targetPixelSize The target pixel size of the grid cells.
        void
        DrawInfiniteGrid3D(Color color = Color::FromFloats(0.0f, 0.0f, 0.0f), float lineThickness = 1.0f, float targetPixelSize = 64.0f);

        /// @brief Draw 2D text. Text is drawn from the top-left of the first character.
        /// @param text The text to draw.
        /// @param position The position to draw the text.
        /// @param scale The scale of the text.
        /// @param color The color of the text.
        void DrawText2D(const std::string& text, Vector2 position, float scale, Color color);

        /// @brief Draw a 2D texture.
        /// @param texture The texture to draw.
        /// @param position The center position of the texture.
        /// @param size The size of the texture.
        /// @param angle The rotation angle in turns (1 turn = 360 degrees).
        /// @param color The color tint.
        /// @param uvMin The minimum UV coordinates.
        /// @param uvMax The maximum UV coordinates.
        void DrawTexture2D(
            Texture& texture,
            Vector2 position,
            Vector2 size,
            float angle,
            Color color,
            Vector2 uvMin = Vec2(0, 0),
            Vector2 uvMax = Vec2(1, 1));

        /// @brief Draw a 3D cube.
        /// @param position The position of the cube.
        /// @param rotation The rotation of the cube.
        /// @param scale The scale of the cube.
        /// @param color The color of the cube.
        void DrawCube3D(Vector3 position, Vector3 rotation, Vector3 scale, Color color);

        /// @brief Draw 3D text.
        /// @param text The text to draw.
        /// @param center The center position of the text.
        /// @param normal The normal direction of the text.
        /// @param worldUp The world up direction.
        /// @param scale The scale of the text.
        /// @param color The color of the text.
        void DrawText3D(const std::string& text, Vector3 center, Vector3 normal, Vector3 worldUp, float scale, Color color);

        /// @brief Draw billboard text that always faces the camera.
        /// @param text The text to draw.
        /// @param center The center position of the text.
        /// @param scale The scale of the text.
        /// @param color The color of the text.
        void DrawTextBillboard(const std::string& text, Vector3 center, float scale, Color color);

        void SetViewport(int width, int height);
        void Present();

        Camera2D GetCamera2D();
        Camera3D GetCamera3D();

        void Begin3D();
        void End3D();

        void Begin2D();
        void End2D();

        void* Data() { return coreHandle; };

      private:
        void* coreHandle = nullptr;
    };
} // namespace Ers
