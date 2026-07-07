#pragma once

#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SimEvent.h"

namespace Ers
{
    /// @brief Simulator and SimEvent pair to persistently store a SimEvent, event after the event has been executed.
    class PersistentEvent
    {
      public:
        PersistentEvent();
        ~PersistentEvent();

        /// @brief Whether the internal Simulator and SimEvent are set.
        /// @return True when they are not set, false if they are.
        bool IsEmpty() const;
        /// @brief Get the internal Simulator.
        ///
        /// This assumes the PersistentEvent is not empty, so be sure to call IsEmpty first.
        /// @return
        Simulator GetSimulator();
        /// @brief Get the internal SimEvent.
        ///
        /// This assumes the PersistentEvent is not empty, so be sure to call IsEmpty first.
        /// @return
        SimEvent GetSimEvent();

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
