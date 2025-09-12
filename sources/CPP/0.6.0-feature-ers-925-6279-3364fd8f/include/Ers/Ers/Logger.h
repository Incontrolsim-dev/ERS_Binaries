#pragma once

#include <string_view>

namespace Ers::Logger
{
    enum class LogLevel
    {
        Trace    = 0,
        Debug    = 1,
        Info     = 2,
        Warning  = 3,
        Error    = 4,
        Critical = 5,
    };

    void Trace(const std::string_view& message);
    void Debug(const std::string_view& message);
    void Info(const std::string_view& message);
    void Warning(const std::string_view& message);
    void Error(const std::string_view& message);
    void Critical(const std::string_view& message);

    void SetLogLevel(LogLevel level);
    void AddCallback(void (*callback)(int level, const char* message));
} // namespace Ers::Logger
