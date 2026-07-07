#pragma once

#include "Ers/Utility/Util.h"

namespace Ers
{
    /// @brief An ERS Event (either local- or sync-event).
    ///
    /// IMPORTANT: Events should always be scheduled using EventScheduler::ScheduleLocalEvent
    /// or EventScheduler::ScheduleSyncEvent.
    /// Only use this type if you wish to use it as a temporary variable.
    ///
    /// DO NOT store this as a variable. Store a PersistentEvent instead.
    struct SimEvent
    {
      public:
        SimEvent() = delete;
        /// @brief Constructor for internal use.
        /// @param corePtr
        SimEvent(void* corePtr);

        /// @brief Get the simulation time at which the event is scheduled to be executed.
        /// @return
        SimulationTime GetTime() const;
        /// @brief Get the priority of the event.
        /// @return
        uint32_t GetPriority() const;
        /// @brief Whether the event is a sync-event.
        /// @return
        bool IsSyncEvent() const;

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
