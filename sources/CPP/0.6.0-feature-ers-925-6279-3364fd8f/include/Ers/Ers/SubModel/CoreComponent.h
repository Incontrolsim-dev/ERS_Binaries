#pragma once

namespace Ers
{

    /// @brief The CoreComponent class is there to identify components inheriting as a core component
    class CoreComponent
    {
      public:
        static constexpr bool IsCore() { return true; }
    };

} // namespace Ers
