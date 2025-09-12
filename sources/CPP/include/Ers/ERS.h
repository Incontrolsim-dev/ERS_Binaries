#pragma once

#include <stdint.h>

namespace Ers::Platform
{

    /// @brief Initialize ERS platform
    void Initialize();

    /// @brief Uninitialize ERS Platform
    void Uninitialize();

    uint32_t MajorVersion();
    uint32_t MinorVersion();
    uint32_t PatchVersion();

    /// @brief Whether the ERS platform was built in Debug mode.
    /// @return True if the platform was built in Debug mode, false if it was built in Release mode.
    bool IsDebugBuild();

} // namespace Ers::Platform
