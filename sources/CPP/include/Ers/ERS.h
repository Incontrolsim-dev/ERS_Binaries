#pragma once

#include <stdint.h>

namespace Ers
{
    /// @brief Get the major version number of ERS (MAJOR.MINOR.PATCH).
    /// @return
    uint32_t MajorVersion();
    /// @brief Get the minor version number of ERS (MAJOR.MINOR.PATCH).
    /// @return
    uint32_t MinorVersion();
    /// @brief Get the patch version number of ERS (MAJOR.MINOR.PATCH).
    /// @return
    uint32_t PatchVersion();

    /// @brief Whether the ERS platform was built in Debug mode.
    /// @return True if the platform was built in Debug mode, false if it was built in Release mode.
    bool IsDebugBuild();

} // namespace Ers
