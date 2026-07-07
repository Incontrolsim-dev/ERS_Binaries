#pragma once

#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    class RenderFramework
    {
      public:
        RenderFramework(void* windowHandle, void* displayHandle, int screenWidth, int screenHeight);
        ~RenderFramework();

        void DrawRenderContext(RenderContext& renderContext);

        void Present();

      private:
        void* corePtr;
    };
} // namespace Ers
