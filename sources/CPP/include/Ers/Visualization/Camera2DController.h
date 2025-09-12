#pragma once

#include "Ers/Visualization/Camera2D.h"

namespace Ers::Visualization
{
    /**
     * @brief Movement controller for 2D cameras using dragging and zooming.
     */
    class Camera2DController
    {
      public:
        Camera2DController(Camera2D& camera);
        Camera2DController(const Camera2DController&)            = delete;
        Camera2DController(Camera2DController&&)                 = delete;
        Camera2DController& operator=(const Camera2DController&) = delete;
        Camera2DController& operator=(Camera2DController&&)      = delete;
        ~Camera2DController();

        /**
         * @brief The default dragging and zooming behaviour.
         * This function will automatically manage all other functions in the controller.
         *
         * @param screenWidth The width of the camera.
         * @param screenHeight The height of the camera.
         */
        void ControlCamera(int screenWidth, int screenHeight);

        /**
         * @brief Set the camera controller's known camera width and height.
         *
         * @param width The width of the camera.
         * @param height The height of the camera.
         */
        void SetScreenSize(int width, int height);

        /**
         * @brief Update the controller.
         *
         * @param mouseX The mouse X-position.
         * @param mouseY The mouse Y-position.
         */
        void Update(float mouseX, float mouseY);

        /**
         * @brief Notify the controller that the user starts dragging the camera.
         *
         * @param mouseX The mouse X-position at the start of dragging.
         * @param mouseY The mouse Y-position at the start of dragging.
         */
        void StartDragging(float mouseX, float mouseY);

        /**
         * @brief Notify the controller that the user has stopped dragging the camera.
         */
        void StopDragging();

        /**
         * @brief Notify the controller that the user is zooming in or out.
         * Calculates a zoom factor by doing base to the power of power.
         *
         * @param base The base zoom factor.
         * @param power The power of the zoom.
         * Positive values zoom in, negative values zoom out. Larger values increase speed.
         */
        void Zoom(float base, float power);

      private:
        void* coreInstance;
    };
} // namespace Ers::Visualization
