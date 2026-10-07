#pragma once

#include "Ers/Math/HMM/VectorMath.h"

namespace Ers
{
    class Camera2D
    {
      public:
        Camera2D(void* corePtr);
        Camera2D()                           = delete;
        Camera2D(const Camera2D&)            = default;
        Camera2D(Camera2D&&)                 = delete;
        Camera2D& operator=(const Camera2D&) = default;
        Camera2D& operator=(Camera2D&&)      = delete;
        ~Camera2D()                          = default;

        void UpdateTransform(int viewportWidth, int viewportHeight);

        /// @brief Get the position of the camera.
        /// @return
        Vector2 GetPosition() const;
        /// @brief Set the position of the camera.
        /// @param pos
        void SetPosition(Vector2 pos);

        /// @brief Get the zoom factor of the camera.
        /// @return
        float Zoom() const;
        /// @brief Set the zoom factor of the camera.
        /// @param value
        void Zoom(float value);

        /// @brief Get the width and height of the camera's viewport.
        /// @return
        Vector2 GetSize() const;

        /// @brief Get the minimum XY-positions of the camera's viewport.
        /// @return
        Vector2 GetMin() const;
        /// @brief Get the maximum XY-positions of the camera's viewport.
        /// @return
        Vector2 GetMax() const;

        /// @brief Get the size of an object if it should be rendered as a single pixel (1 / Zoom).
        ///
        /// Multiply the number of pixels (N) by the returned value to get the size of something that is N pixels in size.
        /// @return
        float SizePerPixel() const;

        /// @brief Get the world position of a point on the screen.
        /// @param viewportPos The viewport position to get the world position of.
        /// @return
        Vector2 GetWorldPos(Vector2 viewportPos) const;

        void* CorePtr();
        const void* const CorePtr() const;

      private:
        void* corePtr;
    };
} // namespace Ers
