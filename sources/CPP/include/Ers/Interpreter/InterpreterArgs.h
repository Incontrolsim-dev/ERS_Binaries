#pragma once

namespace Ers::Interpreter
{
    /// @brief Arguments passed to interpreter functions.
    class InterpreterArgs
    {
      public:
        explicit InterpreterArgs(void* scriptArgumentsPtr);
        InterpreterArgs()                                  = delete;
        InterpreterArgs(const InterpreterArgs&)            = default;
        InterpreterArgs(InterpreterArgs&&)                 = default;
        InterpreterArgs& operator=(const InterpreterArgs&) = default;
        InterpreterArgs& operator=(InterpreterArgs&&)      = default;
        ~InterpreterArgs()                                 = default;

        void* Data();
        const void* const Data() const;

      private:
        void* scriptArgumentsPtr;
    };
} // namespace Ers::Interpreter
