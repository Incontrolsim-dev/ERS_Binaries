#pragma once

#include "InterpreterArgs.h"
#include "InterpreterVariable.h"

#include <functional>
#include <string>

namespace Ers::Interpreter
{
    /// @brief Callback function type for interpreter functions.
    using InterpreterFunctionCallback = std::function<InterpreterVariable(InterpreterArgs)>;

    /// @brief Manages functions registered with the interpreter.
    class Interpreter
    {
      public:
        /// @brief Register a C++ function to be used in the interpreter.
        /// Function can now be called from the interpreted environment.
        /// Make sure to register all functions before starting any scripting environment.
        /// @param functionName The name of the function in the interpreter
        /// @param function The callback function
        static void RegisterInterpreterFunction(const std::string& functionName, InterpreterFunctionCallback function);
    };
} // namespace Ers::Interpreter
