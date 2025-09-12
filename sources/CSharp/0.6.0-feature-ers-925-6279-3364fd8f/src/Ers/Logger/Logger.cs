using Ers.Engine;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// Available log levels for the <see cref="Logger"/>.
    /// </summary>
    public enum LogLevel : int
    {
        /// <summary>
        /// Trace.
        /// </summary>
        Trace = 0,
        /// <summary>
        /// Debug.
        /// </summary>
        Debug = 1,
        /// <summary>
        /// Info.
        /// </summary>
        Info = 2,
        /// <summary>
        /// Warning.
        /// </summary>
        Warning = 3,
        /// <summary>
        /// Error.
        /// </summary>
        Error = 4,
        /// <summary>
        /// Critical.
        /// </summary>
        Critical = 5,
    }

    /// <summary>
    /// Logging system to log with different log levels.
    /// </summary>
    public class Logger
    {
        /// <summary>
        /// Log a trace level message.
        /// </summary>
        /// <param name="message">The message.</param>
        public static void Trace(string message)
        {
            unsafe
            {
                fixed(byte* utf8 = message.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_Logger_Trace(utf8);
                }
            }
        }

        /// <summary>
        /// Log a trace level message.
        /// </summary>
        /// <param name="format">The format of the message <see cref="string.Format(string, object?[])"/></param>
        /// <param name="args">The arguments for the string formatting</param>
        public static void Trace(string format, params object[] args) { Trace(string.Format(format, args)); }

        /// <summary>
        /// Log a debug level message.
        /// </summary>
        /// <param name="message">The message.</param>
        public static void Debug(string message)
        {
            var messageUtf8 = message.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* messageByte = messageUtf8)
                {
                    ErsEngine.ERS_Logger_Debug(messageByte);
                }
            }
        }

        /// <summary>
        /// Log a debug level message.
        /// </summary>
        /// <param name="format">The format of the message <see cref="string.Format(string, object?[])"/></param>
        /// <param name="args">The arguments for the string formatting</param>
        public static void Debug(string format, params object[] args) { Debug(string.Format(format, args)); }

        /// <summary>
        /// Log an info level message.
        /// </summary>
        /// <param name="message">The message.</param>
        public static void Info(string message)
        {
            var messageUtf8 = message.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* messageByte = messageUtf8)
                {
                    ErsEngine.ERS_Logger_Info(messageByte);
                }
            }
        }

        /// <summary>
        /// Log an info level message.
        /// </summary>
        /// <param name="format">The format of the message <see cref="string.Format(string, object?[])"/></param>
        /// <param name="args">The arguments for the string formatting</param>
        public static void Info(string format, params object[] args) { Info(string.Format(format, args)); }

        /// <summary>
        /// Log a warning level message.
        /// </summary>
        /// <param name="message">The message.</param>
        public static void Warning(string message)
        {
            var messageUtf8 = message.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* messageByte = messageUtf8)
                {
                    ErsEngine.ERS_Logger_Warning(messageByte);
                }
            }
        }

        /// <summary>
        /// Log a warning level message.
        /// </summary>
        /// <param name="format">The format of the message <see cref="string.Format(string, object?[])"/></param>
        /// <param name="args">The arguments for the string formatting</param>
        public static void Warning(string format, params object[] args) { Warning(string.Format(format, args)); }

        /// <summary>
        /// Log an error level message.
        /// </summary>
        /// <param name="message">The message.</param>
        public static void Error(string message)
        {
            var messageUtf8 = message.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* messageByte = messageUtf8)
                {
                    ErsEngine.ERS_Logger_Error(messageByte);
                }
            }
        }

        /// <summary>
        /// Log an error level message.
        /// </summary>
        /// <param name="format">The format of the message <see cref="string.Format(string, object?[])"/></param>
        /// <param name="args">The arguments for the string formatting</param>
        public static void Error(string format, params object[] args) { Error(string.Format(format, args)); }

        /// <summary>
        /// Log a critical level message.
        /// </summary>
        /// <param name="message">The message.</param>
        public static void Critical(string message)
        {
            var messageUtf8 = message.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* messageByte = messageUtf8)
                {
                    ErsEngine.ERS_Logger_Critical(messageByte);
                }
            }
        }

        /// <summary>
        /// Log a critical level message.
        /// </summary>
        /// <param name="format">The format of the message <see cref="string.Format(string, object?[])"/></param>
        /// <param name="args">The arguments for the string formatting</param>
        public static void Critical(string format, params object[] args) { Critical(string.Format(format, args)); }

        /// <summary>
        /// Set the minimum level at which messages are logged.
        /// </summary>
        /// <param name="level"></param>
        public static void SetLogLevel(LogLevel level) => ErsEngine.ERS_Logger_SetLogLevel((int)level);

        /// <summary>
        /// Callback signature for logger callbacks.
        /// </summary>
        /// <param name="level">The level of the logged message.</param>
        /// <param name="message">The message.</param>
        public delegate void LoggerCallback(int level, string message);

        // Unmanaged callback function
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        static void ScheduleLocalEvent_EventCallbackFunction(int level, IntPtr message, IntPtr handlePtr)
        {
            string msg = Marshal.PtrToStringAnsi(message)!;

            GCHandle handle   = GCHandle.FromIntPtr(handlePtr);
            LoggerCallback cb = (LoggerCallback)handle.Target!;
            cb(level, msg);
        }

        /// <summary>
        /// Add a callback function that is called on each logged message.
        /// </summary>
        /// <param name="callback">The callback to call.</param>
        public static void AddCallback(LoggerCallback callback)
        {
            var handle = GCHandle.Alloc(callback, GCHandleType.Normal);
            unsafe
            {
                ErsEngine.ERS_Logger_AddCallback(&ScheduleLocalEvent_EventCallbackFunction, GCHandle.ToIntPtr(handle));
            }
        }
    }
}
