#pragma once

#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    class Window
    {
      public:
        Window(void* windowHandle, void* displayHandle, int screenWidth, int screenHeight);
        ~Window();

        void DrawRenderContext(RenderContext& renderContext);

        void Present();

      private:
        void* data;
    };
} // namespace Ers