#pragma once

#include <atomic>
#include <cassert>
#include <functional>
#include <stdint.h>

#include "Ers/Api.h"
#include "SyncEvent.h"
#include <type_traits>

namespace Ers
{
    using LocalEventKey = uint64_t;

    // Concept to ensure required static methods exist
    template <typename T>
    concept SyncEventConcept = requires(T t) {
        { T::GetName() } -> std::convertible_to<const char*>;
        { t.OnSenderSide() } -> std::same_as<void>;
        { t.OnTargetSide() } -> std::same_as<void>;
    };

    template <typename T>
    concept SyncEventCombinedConcept = requires(T t) {
        { T::GetName() } -> std::convertible_to<const char*>;
        { t.OnSyncEvent() } -> std::same_as<void>;
    };

    class EventScheduler
    {
      public:
        using SenderSideFunction = void (*)();
        using TargetSideFunction = void (*)();

      public:
        static LocalEventKey ScheduleLocalEvent(int priority, SimulationTime delayTime, std::function<void()> eventCallback);

        static void CancelEvent(LocalEventKey eventKey);

        /// @brief Register a static delay, this promises that this submodel will never send sync events with a delay lower than the
        /// promised delay time
        /// @param delayTime
        /// @param outgoingSimulatorID Apply the static delay to a specific outgoing dependency, leaving it -1 applies to effect to all
        /// outgoing dependencies
        /// @return
        static void SetPromise(int32_t outgoingSimulatorID, SimulationTime delayTime);
        static SimulationTime GetPromise(int32_t outgoingSimulatorID);
        static void* GetLastScheduledSyncEvent();

        /// @brief Get event code of sync event
        /// @param syncEvent
        /// @return
        static uint32_t GetEventCodeFromSyncEvent(void* syncEvent);

        /// @brief Get event code from last scheduled SyncEvent
        /// @return
        static uint32_t GetEventCodeFromSyncEvent();

        // Note inside core only for testing
        template <typename T> static T& ScheduleSyncEvent(SimulationTime delay, int32_t targetSimulatorId);

        // Note inside core only for testing
        template <typename T>
        static LocalEventKey ScheduleSyncEvent(SimulationTime delay, int32_t targetSimulatorId, void (*onEventCallback)(), T& data);

        static void DelayEvent(LocalEventKey key, SimulationTime updatedDelayTime);

        /// @brief Get the unique identifier from the last scheduled sync event
        /// @return
        static uint32_t GetSyncEventUID()
        {
            return ersAPIFunctionPointers.ERS_SyncEvent_GetSyncEventUID(ersAPIFunctionPointers.ERS_EventScheduler_LastScheduledSyncEvent());
        }

      private:
        template <typename T> static T& SetData()
        {
            return Ers::SyncEvent::GetData<T>(ersAPIFunctionPointers.ERS_EventScheduler_LastScheduledSyncEvent());
        }

        static void ExecuteSyncEvent();

        static void* ScheduleSyncEvent(
            const char* eventName,
            uint64_t eventTypeIdentifier,
            SimulationTime delay,
            int32_t targetSimulatorId,
            void (*senderSide)(),
            void (*targetSide)());
    };

// This macro ensures that a sync event has the correct methods, and informs the user how to implement them, otherwise error messages are
// confusing because we can't rely on pure virtual functions because we have to implement static functions
#define ENFORCE_SYNC_EVENT_CONCEPTS                                                                            \
    static_assert(                                                                                             \
        SyncEventConcept<T> || SyncEventCombinedConcept<T>,                                                    \
        "T must satisfy at least one of SyncEventConcept or SyncEventCombinedConcept");                        \
                                                                                                               \
    if constexpr (std::is_base_of_v<ISyncEvent<T>, T> && !SyncEventConcept<T>)                                 \
    {                                                                                                          \
        static_assert(SyncEventConcept<T>, R"(Derived class must implement the following static methods:

static const char* GetName() {
    return "YourEventName";
}

void OnSenderSide() {
    Derived& data = Ers::SyncEvent::GetData<Data>();
    return data;
}

void OnTargetSide() {
    Data& data = Ers::SyncEvent::GetData<Data>();
    return data;
}
)");                                                                                                           \
    }

    template <typename T> inline T& EventScheduler::ScheduleSyncEvent(SimulationTime delay, int32_t targetSimulatorId)
    {
        ENFORCE_SYNC_EVENT_CONCEPTS;
        auto* syncEvent = ScheduleSyncEvent(
            T::GetName(), SyncEvent::TypeIdentifier<T>(), delay, targetSimulatorId, T::OnSenderSidePlain, T::OnTargetSidePlain);
        T& data = SetData<T>();
        return data;
    }
    template <typename T>
    inline LocalEventKey
    EventScheduler::ScheduleSyncEvent(SimulationTime delay, int32_t targetSimulatorId, void (*onEventCallback)(), T& data)
    {
        ENFORCE_SYNC_EVENT_CONCEPTS;
        auto* syncEvent = ScheduleSyncEvent(
            T::GetName(), SyncEvent::TypeIdentifier<T>(), delay, targetSimulatorId, T::OnSenderSidePlain, T::OnTargetSidePlain);
        auto& syncEventData = SetData<T>();
        memcpy(&syncEventData, &data, sizeof(T)); // Copy data
        return syncEvent->LocalEventIdx;
    }

    template <typename Derived> inline void ISyncEvent<Derived>::OnSenderSidePlain()
    {
        auto& data = SyncEvent::GetData<Derived>();
        data.OnSenderSide();
    }

    template <typename Derived> inline void ISyncEvent<Derived>::OnTargetSidePlain()
    {
        auto& data = SyncEvent::GetData<Derived>();
        data.OnTargetSide();
    }
#undef ENFORCE_SYNC_EVENT_CONCEPTS

} // namespace Ers
