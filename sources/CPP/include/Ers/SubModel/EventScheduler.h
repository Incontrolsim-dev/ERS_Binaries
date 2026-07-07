#pragma once

#include <atomic>
#include <cassert>
#include <functional>
#include <stdint.h>
#include <string>

#include "Ers/Api.h"
#include "Ers/IO/Serializer.h"
#include "Ers/Logger.h"
#include "Ers/SubModel/APILocalEvent.h"
#include "Ers/SubModel/ErsEvent.h"
#include "Ers/SubModel/LocalEventRegistry.h"
#include "Ers/SubModel/SyncEventRegistry.h"
#include "SyncEvent.h"
#include <type_traits>

namespace Ers
{
    using LocalEventKey = uint64_t;

    /// @brief Event scheduler for local and sync events
    ///
    /// EVENT REGISTRATION:
    /// - Event types are registered automatically on first use (lazy registration)
    /// - Event structs using ERS_EVENT macro have source location captured at compile-time
    /// - To register event types BEFORE simulation creation, call RegisterLocalEvent<T>() or RegisterSyncEvent<T>():
    ///   @code
    ///   // In your initialization code, right after Ers::Initialize():
    ///   Ers::EventScheduler::RegisterLocalEvent<MyEvent>();
    ///   Ers::EventScheduler::RegisterSyncEvent<MySyncEvent>();
    ///   @endcode
    /// - This ensures all event types are known before simulation starts
    class EventScheduler
    {
      public:
        using SenderSideFunction = void (*)();
        using TargetSideFunction = void (*)();

      public:
        /// @brief Register a local event type explicitly before simulation creation
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling multiple times is safe and results in a no-op.
        /// @tparam EventType The event struct type to register (must satisfy LocalEventConcept)
        template <typename EventType> static void RegisterLocalEvent()
        {
            // Validate that EventType has all required methods
            static_assert(
                LocalEventConcept<EventType>,
                "EventType must implement all required methods (OnEvent, Serialization, GetEventSourceLocation). "
                "Use the ERS_EVENT macro in your event struct. See ScheduleLocalEvent documentation for details.");

            // Delegate to the registry class which handles the actual registration
            LocalEventRegistry<EventType>::Register();
        }

        /// @brief Register a sync event type explicitly before simulation creation
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling multiple times is safe and results in a no-op.
        /// @tparam EventType The sync event struct type to register (must satisfy SyncEventConcept)
        template <typename EventType> static void RegisterSyncEvent()
        {
            // Validate that EventType has all required methods
            static_assert(
                SyncEventConcept<EventType>, "EventType must implement all required methods (GetName, OnSenderSide, OnTargetSide). "
                                             "See ISyncEvent documentation for details.");

            // Delegate to the registry class which handles the actual registration
            SyncEventRegistry<EventType>::Register();
        }

      public:
        /// @brief Schedule a local event
        /// @tparam EventType The event struct type (must have OnEvent() method)
        /// @param priority Event priority
        /// @param delayTime Delay before event fires
        /// @param event The event instance to schedule
        /// @return Event ID
        ///
        /// @note The EventType MUST implement void OnEvent() method.
        ///       This is enforced at compile-time with a clear error message.
        ///       It's recommended to use the ERS_EVENT macro for proper serialization support.
        ///
        /// @example
        /// struct MyEvent {
        ///     EntityID entity;
        ///     int value;
        ///     void OnEvent() { /* Your event logic */ }
        ///     ERS_EVENT(entity, value)  // Enables serialization
        /// };
        /// EventScheduler::ScheduleLocalEvent(0, 100, MyEvent{entity, value});
        template <typename EventType> static LocalEventKey ScheduleLocalEvent(int priority, SimulationTime delayTime, EventType&& event)
        {
            // Use std::decay_t to remove reference and cv-qualifiers for consistent type identity
            using DecayedEventType = std::decay_t<EventType>;

            // Compile-time check: Ensure EventType has all required methods
            static_assert(
                LocalEventConcept<DecayedEventType>, "EventType must implement all required methods for local events.\n"
                                                     "\n"
                                                     "Local events MUST use the ERS_EVENT macro which provides:\n"
                                                     "  - void Serialization(Ers::Serializer&) method\n"
                                                     "  - static GetEventSourceLocation() method\n"
                                                     "\n"
                                                     "Additionally, you must implement:\n"
                                                     "  - void OnEvent() method for your event logic\n"
                                                     "\n"
                                                     "Correct usage:\n"
                                                     "    struct MyEvent {\n"
                                                     "        EntityID entity;\n"
                                                     "        int value;\n"
                                                     "        void OnEvent() { /* event logic */ }\n"
                                                     "        ERS_EVENT(entity, value)\n"
                                                     "    };\n"
                                                     "\n"
                                                     "Note: Field type compatibility is validated by the Serializer at compile-time.\n"
                                                     "\n"
                                                     "For more information, see LocalEvent.h");

            // Get the event type handle (registers type on first call if not already registered)
            // Location is extracted from GetEventSourceLocation() if available
            void* eventTypeHandle = LocalEventRegistry<DecayedEventType>::EventHandle();

            assert(eventTypeHandle != nullptr);

            // Allocate memory and construct the event
            void* memoryLocation = LocalEventAllocator<DecayedEventType>(eventTypeHandle);
            new (memoryLocation) DecayedEventType(std::forward<EventType>(event));

            // Schedule the event
            return Ers::Engine::ERS_EventScheduler_ScheduleLocalEvent(priority, delayTime, memoryLocation, eventTypeHandle);
        }

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

        template <typename T> static LocalEventKey ScheduleSyncEvent(SimulationTime delay, int32_t targetSimulatorId, T& data);

        static void DelayEvent(LocalEventKey key, SimulationTime updatedDelayTime);

        /// @brief Get the unique identifier from the last scheduled sync event
        /// @return
        static uint32_t GetSyncEventUID()
        {
            return Ers::Engine::ERS_SyncEvent_GetSyncEventUID(Ers::Engine::ERS_EventScheduler_LastScheduledSyncEvent());
        }

      private:
        template <typename T> static T& GetLastScheduledEventData()
        {
            return Ers::SyncEvent::GetData<T>(Ers::Engine::ERS_EventScheduler_LastScheduledSyncEvent());
        }

        // Templated version with per-type static handle caching for ZERO-COST access
        template <typename T>
        static void* ScheduleSyncEvent(
            const char* eventName,
            const char* sourceLibrary,
            uint64_t eventTypeIdentifier,
            SimulationTime delay,
            int32_t targetSimulatorId,
            void (*senderSide)(),
            void (*targetSide)());
    };

// This macro ensures that a sync event has the correct methods, and informs the user how to implement them, otherwise error messages are
// confusing because we can't rely on pure virtual functions because we have to implement static functions
#define ENFORCE_SYNC_EVENT_CONCEPTS                                            \
    static_assert(SyncEventConcept<T>, "T must satisfy SyncEventConcept");     \
                                                                               \
    if constexpr (std::is_base_of_v<ISyncEvent<T>, T> && !SyncEventConcept<T>) \
    {                                                                          \
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
)");                                                                           \
    }

    template <typename T> inline LocalEventKey EventScheduler::ScheduleSyncEvent(SimulationTime delay, int32_t targetSimulatorId, T& data)
    {
        ENFORCE_SYNC_EVENT_CONCEPTS;
        // Get source library from the OnSenderSide callback function pointer
        const char* sourceLibrary = GetLibraryNameFromFunctionPointer((void*)T::OnSenderSidePlain);
        auto* syncEvent           = ScheduleSyncEvent<T>(
            T::GetName(), sourceLibrary, SyncEvent::TypeIdentifier<T>(), delay, targetSimulatorId, T::OnSenderSidePlain,
            T::OnTargetSidePlain);
        if (syncEvent == nullptr)
            return 0; // Invalid sync-event (failed to schedule)

        // Data is automatically allocated when scheduling - copy provided data
        T& syncEventData = GetLastScheduledEventData<T>();
        memcpy(&syncEventData, &data, sizeof(T));
        return Ers::Engine::ERS_EventScheduler_ExchangeSyncEventForEventID(syncEvent);
    }

    // Private templated implementation with per-type static handle caching for ZERO-COST access
    template <typename T>
    inline void* EventScheduler::ScheduleSyncEvent(
        const char* eventName,
        const char* sourceLibrary,
        uint64_t eventTypeIdentifier,
        SimulationTime delay,
        int32_t targetSimulatorId,
        void (*senderSide)(),
        void (*targetSide)())
    {
        // Static local variable in template function - each T gets its own instance
        // Initialized once per T in a thread-safe manner (C++11 magic statics)
        static void* syncEventTypeHandle = [&]()
        {
            // Generate serialization function pointer for this type
            void (*serializeDataPtr)(void*, void*) = &SyncEventDataSerialize<T>;

            // Data block size for automatic allocation
            uint32_t dataBlockSize = sizeof(T);

            // Location information for debugging - extract from ERS_EVENT macro's GetEventSourceLocation if available
            const char* filePath = "";
            int lineNumber       = 0;
            if constexpr (HasEventSourceLocation<T>)
            {
                auto loc   = T::GetEventSourceLocation();
                filePath   = loc.File;
                lineNumber = loc.Line;
            }

            // This lambda runs exactly once per T, thread-safely
            return Ers::Engine::ERS_EventScheduler_RegisterSyncEventType(
                eventTypeIdentifier, senderSide, targetSide, serializeDataPtr, dataBlockSize, eventName, sourceLibrary, filePath,
                lineNumber);
        }();

        // Call C API with cached handle - ZERO COST! Direct pointer, no lookups!
        void* syncEventHandle = Ers::Engine::ERS_EventScheduler_ScheduleSyncEvent(delay, targetSimulatorId, syncEventTypeHandle);

        return syncEventHandle;
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
