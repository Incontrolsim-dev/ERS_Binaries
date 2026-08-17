#pragma once

#include <functional>
#include <string_view>

namespace Ers::Logger
{
    /// @brief Available log levels for the logger.
    enum class LogLevel : int
    {
        Trace    = 0,
        Debug    = 1,
        Info     = 2,
        Warning  = 3,
        Error    = 4,
        Critical = 5,
    };

    /// @brief Log a trace level message.
    /// @param message
    void Trace(const std::string_view& message);
    /// @brief Log a debug level message.
    /// @param message
    void Debug(const std::string_view& message);
    /// @brief Log an info level message.
    /// @param message
    void Info(const std::string_view& message);
    /// @brief Log a warning level message.
    /// @param message
    void Warning(const std::string_view& message);
    /// @brief Log an error level message.
    /// @param message
    void Error(const std::string_view& message);
    /// @brief Log a critical level message.
    /// @param message
    void Critical(const std::string_view& message);

    /// @brief Set the minimum level at which messages are logged.
    /// @param level
    void SetLogLevel(LogLevel level);
    /// @brief Add a callback function that is called on each logged message.
    /// @param callback The callback to call.
    /// @return The index of the added callback. It can be used later to remove the callback.
    size_t AddCallback(void (*callback)(LogLevel level, const char* message));
    /// @brief Remove a logger callback function.
    /// @param index The index of the callback to remove. This index was returned when adding the callback.
    void RemoveCallback(size_t index);
} // namespace Ers::Logger
