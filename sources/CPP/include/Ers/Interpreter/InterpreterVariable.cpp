#include "InterpreterVariable.h"

namespace Ers::Interpreter
{
    InterpreterVariable::InterpreterVariable(void* data) :
        data(data)
    {
    }

    void* InterpreterVariable::Data()
    {
        return data;
    }

    const void* const InterpreterVariable::Data() const
    {
        return data;
    }
} // namespace Ers::Interpreter
