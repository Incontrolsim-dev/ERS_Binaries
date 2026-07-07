#pragma once

namespace Ers
{
    class Camera3D
    {
      public:
        Camera3D(void* corePtr);
        Camera3D()                           = delete;
        Camera3D(const Camera3D&)            = default;
        Camera3D(Camera3D&&)                 = delete;
        Camera3D& operator=(const Camera3D&) = default;
        Camera3D& operator=(Camera3D&&)      = delete;
        ~Camera3D()                          = default;

        float GetFovInTurns() const;
        void SetFovInTurns(float value);
        float GetZNear() const;
        void SetZNear(float value);
        float GetZFar() const;
        void SetZFar(float value);

        void UpdateTransform(int screenWidth, int screenHeight);

        void SetLookAt(float x, float y, float z);

        void* CorePtr();
        const void* const CorePtr() const;

      private:
        void* corePtr;
    };
} // namespace Ers
