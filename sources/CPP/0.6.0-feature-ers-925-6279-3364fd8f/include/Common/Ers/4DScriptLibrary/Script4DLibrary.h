#pragma once
#include "Ers/Utility/Util.h"

#include <variant>

namespace Ers::Script4DLibrary
{
    /// @brief 4DScript parameter types
    enum Script4DParameterType : uint8_t
    {
        String = 0,
        Double = 1,
        Entity = 2,

        Internal = 9 // This is reserved for non variable types inside the engine, that must be evaluated before returning a value. For
                     // example this could be a callback
    };

    enum TreeNodeValueType : uint8_t
    {
        Function = 0,
        Variable = 1
    };
} // namespace Ers::Script4DLibrary
