#pragma once

#include "Ers/Api.h"
#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// Window for creating a User Interface (UI) using ImGui.
    class Window
    {
      public:
        /// Creates a new window instance
        Window() { corePtr = Ers::Engine::ERS_Window_Create(); }

        /// @brief Creates a new window instance with a given title.
        /// @param title The title for the window.
        Window(const char* title) { corePtr = Ers::Engine::ERS_Window_Create_Title(title); }

        /// @brief Create a new Window instance from an existing core instance.
        /// @param ptr The pointer to the core instance.
        Window(void* ptr) :
            corePtr(ptr)
        {
        }

        /// Destroys the window instance
        ~Window() { Ers::Engine::ERS_Window_Destroy(corePtr); }

        /// Starts a new frame
        void BeginFrame() { Ers::Engine::ERS_Window_BeginFrame(corePtr); }

        /// Ends the current frame
        void EndFrame() { Ers::Engine::ERS_Window_EndFrame(corePtr); }

        /// @brief Begin creation / configuration of the default root dock space.
        /// @return Returns true on the first frame, use this to set up the layout.
        bool BeginRootDockSpace() { return Ers::Engine::ERS_Window_BeginRootDockSpace(corePtr); }

        /// @brief Finish the creation / configuration of the root dock space.
        void EndRootDockSpace() { Ers::Engine::ERS_Window_EndRootDockSpace(corePtr); }

        /// @brief Get the ImGuiID of the root dock space.
        /// @return
        unsigned int GetRootDockSpaceID() { return Ers::Engine::ERS_Window_GetRootDockSpaceID(corePtr); }

        /// @brief Get whether the window should close.
        /// @return True when the window wants to close, false when not.
        bool WantsClose() { return Ers::Engine::ERS_Window_Get_WantsClose(corePtr); }

        /// @brief Set whether the window should close.
        /// @param value True if the window should close, false if not.
        void WantsClose(bool value) { Ers::Engine::ERS_Window_Set_WantsClose(corePtr, value); }

        /// @brief Set the title of the window.
        /// @param title
        void SetWindowTitle(const char* title) { Ers::Engine::ERS_Window_SetWindowTitle(corePtr, title); }

        /// @brief Set the icon of the window.
        /// @param imagePath The path to the image to use (relative to the ers-engine.dll file).
        ///
        /// Supported image file formats are: JPEG, PNG, TGA, BMP, and GIF (first frame is used).
        /// @return True when the icon was successfully set, false if not.
        bool SetWindowIcon(const char* imagePath) { return Ers::Engine::ERS_Window_SetWindowIcon(corePtr, imagePath); }

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core window instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
