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

        /// @brief Whether to draw a background grid (applies to both 2D and 3D).
        /// @return True when the background grid is drawn, false when not.
        bool GetDrawBackgroundGrid() const;
        /// @brief Set whether to draw a background grid (applies to both 2D and 3D).
        /// @param value True to draw the background grid, false to not draw it.
        void SetDrawBackgroundGrid(bool value);

        /// @brief Get the color of the background.
        /// @return
        Color GetBackgroundColor() const;
        /// @brief Set the color of the background.
        /// @param color
        void SetBackgroundColor(Color color);

        /// @brief Get the color of the background grid.
        /// @return
        Color GetBackgroundGridColor() const;
        /// @brief Set the color of the background grid.
        /// @param color
        void SetBackgroundGridColor(Color color);

        void DrawModel3D(Model3D& model);
        void DrawMesh(Mesh& mesh);
        void DrawInstancedModel3D(Mesh& mesh, InstancedModel& instancedModel);

        /// @brief Draw a 2D line.
        /// @param start The start position.
        /// @param end The end position.
        /// @param thickness The thickness of the line.
        /// @param color The color of the line.
        /// @param zIndex The z-index for layering.
        void DrawLine2D(Vector2 start, Vector2 end, float thickness, Color color, int64_t zIndex = 0);

        /// @brief Draw a 2D triangle based on three corner vertices.
        /// @param v0 The first vertex position.
        /// @param v1 The second vertex position.
        /// @param v2 The third vertex position.
        /// @param color The color of the triangle.
        /// @param zIndex The z-index for layering.
        void DrawTriangle2D(Vector2 v0, Vector2 v1, Vector2 v2, Color color, int64_t zIndex = 0);

        /// @brief Draw a 2D triangle.
        /// The triangle is drawn as it would be inside a bounding box where the bottom-left and bottom-right vertices match the box's
        /// and the top vertex is in the middle of the top edge of the box.
        /// @param center The center position of the bounding box.
        /// @param size The size of the bounding box.
        /// @param angle The counterclockwise rotation of the triangle.
        /// @param color The color of the triangle.
        /// @param zIndex The z-index for layering.
        void DrawTriangle2D(Vector2 center, Vector2 size, float angle, Color color, int64_t zIndex = 0);

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
        /// @param zIndex The z-index for layering.
        void DrawQuad2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, Color color, int64_t zIndex = 0);

        /// @brief Draw a 2D circle.
        /// @param center The center of the circle.
        /// @param size The width and height of the circle.
        /// @param segments The number of segments the circle is made of.
        /// @param angle The counterclockwise rotation in turns.
        /// @param color The color of the circle.
        /// @param zIndex The z-index for layering.
        void DrawCircle2D(Vector2 center, Vector2 size, int segments, float angle, Color color, int64_t zIndex = 0);

        /// @brief Draw a 2D arc.
        /// @param center The center of the arc.
        /// @param radius The radius of the arc.
        /// @param width The width of the arc.
        /// @param beginAngle The angle (in turns) at the start of the arc (1 turn = 360 degrees).
        /// @param endAngle The angle (in turns) at the end of the arc (1 turn = 360 degrees).
        /// @param color The color of the arc.
        /// @param segments The number of segments the arc consists of.
        /// @param zIndex The z-index for layering.
        void DrawArc2D(
            Vector2 center,
            float radius,
            float width,
            float beginAngle,
            float endAngle,
            Color color    = Color::FromBytes(255, 255, 255),
            int segments   = 10,
            int64_t zIndex = 0);

        /// @brief Draw 2D text. Text is drawn from the top-left of the first character.
        /// @param text The text to draw.
        /// @param position The position to draw the text.
        /// @param scale The scale of the text.
        /// @param color The color of the text.
        /// @param zIndex The z-index for layering.
        void DrawText2D(const std::string& text, Vector2 position, float scale, Color color, int64_t zIndex = 0);

        /// @brief Draw a 2D texture.
        /// @param texture The texture to draw.
        /// @param position The center position of the texture.
        /// @param size The size of the texture.
        /// @param angle The rotation angle in turns (1 turn = 360 degrees).
        /// @param color The color tint.
        /// @param uvMin The minimum UV coordinates.
        /// @param uvMax The maximum UV coordinates.
        /// @param zIndex The z-index for layering.
        void DrawTexture2D(
            Texture& texture,
            Vector2 position,
            Vector2 size,
            float angle,
            Color color,
            Vector2 uvMin  = Vec2(0, 0),
            Vector2 uvMax  = Vec2(1, 1),
            int64_t zIndex = 0);

        /// @brief Draw a 3D cube.
        /// @param position The position of the cube.
        /// @param rotation The rotation of the cube.
        /// @param size The size of the cube.
        /// @param color The color of the cube.
        void DrawCube3D(Vector3 position, Vector3 rotation, Vector3 size, Color color);

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

        Camera2D GetCamera2D();
        Camera3D GetCamera3D();

        void Begin3D();
        void End3D();

        void Begin2D();
        void End2D();

        void* CorePtr() { return corePtr; };

      private:
        void* corePtr = nullptr;
    };
} // namespace Ers
