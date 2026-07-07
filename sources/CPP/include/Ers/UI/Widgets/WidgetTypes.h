#pragma once

#include <cstdint>

namespace Ers
{
    /// @brief Possible selected types.
    enum class SelectedType : uint8_t
    {
        /// @brief No type is selected.
        None = 0,
        /// @brief A ModelContainer is selected.
        ModelContainer = 1,
        /// @brief A Simulator is selected.
        Simulator = 2,
        /// @brief An Entity is selected.
        Entity = 3,
        /// @brief An Event is selected (using a PersistentEvent).
        Event = 4,
    };
} // namespace Ers
