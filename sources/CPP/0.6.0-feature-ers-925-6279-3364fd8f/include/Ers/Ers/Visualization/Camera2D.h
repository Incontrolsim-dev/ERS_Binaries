#pragma once

namespace Ers::Visualization
{
    class Camera2D
    {
      public:
        Camera2D(void* coreInstance);
        Camera2D()                           = delete;
        Camera2D(const Camera2D&)            = default;
        Camera2D(Camera2D&&)                 = delete;
        Camera2D& operator=(const Camera2D&) = default;
        Camera2D& operator=(Camera2D&&)      = delete;
        ~Camera2D()                          = default;

        void UpdateTransform(int screenWidth, int screenHeight);

        float Zoom() const;
        void Zoom(float value);

        /// @brief Get the size of an object if it should be rendered as a single pixel (1 / Zoom).
        ///
        /// Multiply the number of pixels (N) by the returned value to get the size of something that is N pixels in size.
        /// @return
        float SizePerPixel() const;

        void* Data();
        const void* const Data() const;

      private:
        void* coreInstance;
    };
} // namespace Ers::Visualization
