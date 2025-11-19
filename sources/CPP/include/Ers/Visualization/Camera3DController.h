#pragma once

#include "Ers/Visualization/Camera3D.h"

namespace Ers
{
    /// @brief Movement controller for 3D cameras.
    class Camera3DController
    {
      public:
        Camera3DController(Camera3D camera);
        Camera3DController()                                     = delete;
        Camera3DController(const Camera3DController&)            = delete;
        Camera3DController(Camera3DController&&)                 = delete;
        Camera3DController& operator=(const Camera3DController&) = delete;
        Camera3DController& operator=(Camera3DController&&)      = delete;
        ~Camera3DController();

        void ControlCamera(int screenWidth, int screenHeight, float deltaTime, float lookAtZ);
        /// @brief Update the controller.
        /// @param deltaTime The elapsed time in ms since the last update.
        void Update(float deltaTime);

        void SwitchCameraMode(int mode);

        void HeadBobbingIntensity(float intensity);
        /// @brief The intensity of the head (camera height) moving up and down when walking in first person mode.
        /// @return
        float HeadBobbingIntensity();

      private:
        void* coreInstance;
    };
} // namespace Ers
