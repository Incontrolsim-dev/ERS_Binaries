#pragma once

#include "Ers/Api.h"

namespace Ers
{
    struct Profiler
    {
        /// @brief Starts a debugging session resets all counters.
        static void StartSession() { ersAPIFunctionPointers.ERS_Profiler_StartSession(); }

        /// @brief Prints the results of the current profiling session
        static void PrintResults() { ersAPIFunctionPointers.ERS_Profiler_PrintResults(); }
    };
} // namespace Ers