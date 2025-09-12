#pragma once

#include "Entity.h"

namespace Ers
{
    /// @brief The DataComponent class is there to identify components as an Data component
    class DataComponent
    {
      public:
        static constexpr bool IsCore() { return false; }

        // This is intentionally empty for now

      protected:
        DataComponent() = default; // Force Users to inherit from component
    };

} // namespace Ers
