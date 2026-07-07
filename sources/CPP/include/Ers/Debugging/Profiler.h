#pragma once

#include "Ers/Api.h"

namespace Ers
{
    struct Profiler
    {
        /// @brief Starts a debugging session resets all counters.
        static void StartSession() { Ers::Engine::ERS_Profiler_StartSession(); }

        /// @brief Prints the results of the current profiling session
        static void PrintResults() { Ers::Engine::ERS_Profiler_PrintResults(); }
    };
} // namespace Ers