#include "InterpreterArgs.h"

namespace Ers::Interpreter
{
    InterpreterArgs::InterpreterArgs(void* scriptArgumentsPtr) :
        scriptArgumentsPtr(scriptArgumentsPtr)
    {
    }

    void* InterpreterArgs::Data()
    {
        return scriptArgumentsPtr;
    }

    const void* const InterpreterArgs::Data() const
    {
        return scriptArgumentsPtr;
    }
} // namespace Ers::Interpreter
