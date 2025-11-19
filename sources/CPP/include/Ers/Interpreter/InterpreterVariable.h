#pragma once

namespace Ers::Interpreter
{
    /// @brief Wrapper for interpreter variables.
    class InterpreterVariable
    {
      public:
        explicit InterpreterVariable(void* data);
        InterpreterVariable()                                      = delete;
        InterpreterVariable(const InterpreterVariable&)            = default;
        InterpreterVariable(InterpreterVariable&&)                 = default;
        InterpreterVariable& operator=(const InterpreterVariable&) = default;
        InterpreterVariable& operator=(InterpreterVariable&&)      = default;
        ~InterpreterVariable()                                     = default;

        void* Data();
        const void* const Data() const;

      private:
        void* data;
    };
} // namespace Ers::Interpreter
