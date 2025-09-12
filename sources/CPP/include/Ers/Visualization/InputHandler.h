#pragma once

namespace Ers::Visualization
{
    class InputAction
    {
      public:
        InputAction(void* coreInstance);
        InputAction(const char* name);
        InputAction()                              = delete;
        InputAction(const InputAction&)            = default;
        InputAction(InputAction&&)                 = default;
        InputAction& operator=(const InputAction&) = default;
        InputAction& operator=(InputAction&&)      = default;
        ~InputAction()                             = default;

        bool IsTriggered() const;
        bool IsReleased() const;
        float GetStrength() const;

        void SetTriggered(bool triggered, float strength = 1.0f);

      private:
        void* coreInstance;
    };

    class InputHandler
    {
      public:
        static InputAction GetAction(const char* name);
        static bool ExistsAction(const char* name);
        static void Cycle();

        static void UpdateMousePos(int x, int y);
    };
} // namespace Ers::Visualization
