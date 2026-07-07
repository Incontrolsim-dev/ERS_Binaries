#pragma once

#include <stdint.h>
#include <string>
#include <typeinfo>

#include "Ers/Api.h"
#include "Ers/IO/Serializer.h"
#include "Ers/SubModel/APILocalEvent.h"
#include "Ers/SubModel/ErsEvent.h"

namespace Ers
{
    // Concept to ensure LocalEvent has all required methods from ERS_EVENT macro
    template <typename T>
    concept LocalEventConcept = requires(T t, Serializer& serializer) {
        // Required: OnEvent method for event execution
        { t.OnEvent() } -> std::same_as<void>;
        // Required: Serialization method (provided by ERS_EVENT macro)
        { t.Serialization(serializer) } -> std::same_as<void>;
        // Required: GetEventSourceLocation static method (provided by ERS_EVENT macro)
        { T::GetEventSourceLocation().File } -> std::convertible_to<const char*>;
        { T::GetEventSourceLocation().Line } -> std::convertible_to<int>;
    };

    /// @brief Static registration of local event type - templated per event type
    /// Each unique event struct gets its own registration with type-specific callbacks
    template <typename EventType> class LocalEventRegistry
    {
      public:
        static void* EventHandle()
        {
            // Static local - initialized once per EventType, thread-safe (C++11 magic statics)
            static void* handle = []()
            {
                // Type identifier for this specific EventType
                uint64_t typeIdentifier = reinterpret_cast<uint64_t>(&typeid(EventType));

                // Register with type-specific callbacks
                void (*callbackPtr)(void*) = [](void* dataPtr)
                { LocalEventCallback<EventType>(dataPtr, LocalEventRegistry<EventType>::EventHandle()); };
                void (*destructorPtr)(void*) = [](void* dataPtr)
                { LocalEventDestroyCallback<EventType>(dataPtr, LocalEventRegistry<EventType>::EventHandle()); };
                void (*serializePtr)(void*, void*) = &LocalEventSerialize<EventType>;
                void* (*allocatorPtr)() = []() { return LocalEventAllocator<EventType>(LocalEventRegistry<EventType>::EventHandle()); };

                // Generate unique name based on type
                std::string uniqueName    = std::string("event_") + typeid(EventType).name();
                const char* sourceLibrary = "cpp_binding";
                size_t size               = sizeof(EventType);

                // Location information for debugging - extract from ERS_EVENT macro's GetEventSourceLocation
                // This is guaranteed to exist due to LocalEventConcept validation at ScheduleLocalEvent
                auto loc             = EventType::GetEventSourceLocation();
                const char* filePath = loc.File;
                int lineNumber       = loc.Line;

                return Ers::Engine::ERS_EventScheduler_RegisterLocalEventType(
                    typeIdentifier, callbackPtr, destructorPtr, serializePtr, allocatorPtr, uniqueName.c_str(), sourceLibrary, size,
                    filePath, lineNumber);
            }();

            return handle;
        }

        /// @brief Register a local event type explicitly before simulation creation
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling multiple times is safe and results in a no-op.
        static void Register()
        {
            // Simply accessing EventHandle() triggers registration via static initialization
            (void)EventHandle();
        }
    };

} // namespace Ers
