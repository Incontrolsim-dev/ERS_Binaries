#pragma once

#include "Ers/SubModel/TypeInfo.h"

namespace Ers
{
    /// @brief The DataComponent class is there to identify components as an Data component
    class DataComponent
    {
      public:
        static constexpr bool IsCore() { return false; }

        /// @brief Overridable function to define the type information of the component.
        /// @return
        static TypeInfo* GetTypeInfo() { return nullptr; };

      protected:
        DataComponent() = default; // Force Users to inherit from component
    };
} // namespace Ers
