#include "Logger.h"
#include "Ers/Api.h"

void Ers::Logger::Trace(const std::string_view& message)
{
    Ers::Engine::ERS_Logger_Trace(message.data());
}

void Ers::Logger::Debug(const std::string_view& message)
{
    Ers::Engine::ERS_Logger_Debug(message.data());
}

void Ers::Logger::Info(const std::string_view& message)
{
    Ers::Engine::ERS_Logger_Info(message.data());
}

void Ers::Logger::Warning(const std::string_view& message)
{
    Ers::Engine::ERS_Logger_Warning(message.data());
}

void Ers::Logger::Error(const std::string_view& message)
{
    Ers::Engine::ERS_Logger_Error(message.data());
}

void Ers::Logger::Critical(const std::string_view& message)
{
    Ers::Engine::ERS_Logger_Critical(message.data());
}

void Ers::Logger::SetLogLevel(LogLevel level)
{
    Ers::Engine::ERS_Logger_SetLogLevel(static_cast<int>(level));
}

static void CallbackWrapper(int level, const char* message, void* userData)
{
    using CallbackSignature = void (*)(Ers::Logger::LogLevel level, const char* message);
    auto callback           = reinterpret_cast<CallbackSignature>(userData);
    callback(static_cast<Ers::Logger::LogLevel>(level), message);
}

size_t Ers::Logger::AddCallback(void (*callback)(LogLevel level, const char* message))
{
    return Ers::Engine::ERS_Logger_AddCallback(CallbackWrapper, reinterpret_cast<void*>(callback));
}

void Ers::Logger::RemoveCallback(size_t index)
{
    Ers::Engine::ERS_Logger_RemoveCallback(index);
}
