#pragma once

#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// @brief Debugger tool for ERS models. Opens a debugger window.
    class Debugger
    {
      public:
        /// @brief Construct a the Debugger, attached to the given ModelContainer.
        /// @param modelContainer The model to debug.
        Debugger(Ers::ModelContainer& modelContainer);
        Debugger(const Debugger&)            = delete;
        Debugger(Debugger&&)                 = delete;
        Debugger& operator=(const Debugger&) = delete;
        Debugger& operator=(Debugger&&)      = delete;
        ~Debugger();

        /// @brief Update loop for the debugger. Be sure to call this in a loop for the debugger to work.
        void Update();

      private:
        void* coreInstance;
    };
} // namespace Ers
