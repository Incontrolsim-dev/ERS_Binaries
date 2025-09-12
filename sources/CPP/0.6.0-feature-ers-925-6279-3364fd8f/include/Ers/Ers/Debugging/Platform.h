#pragma once

#include "Ers/Api.h"
#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// Platform for debugging functionality
    class Platform
    {
      public:
        /// Creates a new platform instance
        Platform() { coreInstance = ersAPIFunctionPointers.ERS_Platform_Create(); }

        /// Destroys the platform instance
        ~Platform() { ersAPIFunctionPointers.ERS_Platform_Destroy(coreInstance); }

        /// Starts a new frame
        void BeginFrame() { ersAPIFunctionPointers.ERS_Platform_BeginFrame(coreInstance); }

        /// Ends the current frame
        void EndFrame() { ersAPIFunctionPointers.ERS_Platform_EndFrame(coreInstance); }

        /// Checks if platform should close
        bool WantsClose() { return ersAPIFunctionPointers.ERS_Platform_WantsClose(coreInstance); }

        /// Core platform instance pointer
        void* coreInstance = nullptr;
    };
} // namespace Ers
