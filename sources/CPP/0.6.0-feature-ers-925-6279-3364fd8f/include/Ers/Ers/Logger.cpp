#include "Logger.h"
#include "Ers/Api.h"

void Ers::Logger::Trace(const std::string_view& message)
{
    ersAPIFunctionPointers.ERS_Logger_Trace(message.data());
}

void Ers::Logger::Debug(const std::string_view& message)
{
    ersAPIFunctionPointers.ERS_Logger_Debug(message.data());
}

void Ers::Logger::Info(const std::string_view& message)
{
    ersAPIFunctionPointers.ERS_Logger_Info(message.data());
}

void Ers::Logger::Warning(const std::string_view& message)
{
    ersAPIFunctionPointers.ERS_Logger_Warning(message.data());
}

void Ers::Logger::Error(const std::string_view& message)
{
    ersAPIFunctionPointers.ERS_Logger_Error(message.data());
}

void Ers::Logger::Critical(const std::string_view& message)
{
    ersAPIFunctionPointers.ERS_Logger_Critical(message.data());
}

void Ers::Logger::SetLogLevel(LogLevel level)
{
    ersAPIFunctionPointers.ERS_Logger_SetLogLevel(static_cast<int>(level));
}

static void CallbackWrapper(int level, const char* message, void* userData)
{
    using CallbackSignature = void (*)(int level, const char* message);
    auto callback           = reinterpret_cast<CallbackSignature>(userData);
    callback(level, message);
}

void Ers::Logger::AddCallback(void (*callback)(int level, const char* message))
{
    ersAPIFunctionPointers.ERS_Logger_AddCallback(CallbackWrapper, reinterpret_cast<void*>(callback));
}
