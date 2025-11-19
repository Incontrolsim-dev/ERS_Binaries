#include "Interpreter.h"
#include "Ers/Api.h"

#include <memory>
#include <unordered_map>

namespace Ers::Interpreter
{
    // Storage for callbacks to keep them alive
    static std::unordered_map<std::string, std::unique_ptr<InterpreterFunctionCallback>> RegisteredFunctioncallbackStorage;

    // Unmanaged callback function wrapper
    static void* InterpreterFunctionUnmanaged(void* callbackPtr, void* scriptArgumentsPtr)
    {
        auto* callback = static_cast<InterpreterFunctionCallback*>(callbackPtr);
        InterpreterArgs interpreterArgs(scriptArgumentsPtr);
        InterpreterVariable result = (*callback)(interpreterArgs);
        return result.Data();
    }

    void Interpreter::RegisterInterpreterFunction(const std::string& functionName, InterpreterFunctionCallback function)
    {
        // Store the callback to keep it alive
        auto callbackPtr                                = std::make_unique<InterpreterFunctionCallback>(std::move(function));
        void* callbackRawPtr                            = callbackPtr.get();
        RegisteredFunctioncallbackStorage[functionName] = std::move(callbackPtr);
        static std::string noDocs                       = "no docs";

        // Register with the engine
        ersAPIFunctionPointers.ERS_Interpreter_RegisterFunction(
            functionName.c_str(), callbackRawPtr, &InterpreterFunctionUnmanaged, noDocs.c_str());
    }
} // namespace Ers::Interpreter
