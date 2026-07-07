#pragma once

#include <cstring>
#include <functional>
#include <type_traits>

#include "Ers/IO/Serializer.h"
#include "Ers/Logger.h"

namespace Ers
{

    // Templated callback function - executes the event
    template <typename EventType> void LocalEventCallback(void* dataPtr, void* eventHandle)
    {
        auto* event = static_cast<EventType*>(dataPtr);
        event->OnEvent(); // Call the event's OnEvent() method
        event->~EventType();
        Ers::Engine::ERS_EventScheduler_FreeLocalEvent(dataPtr, eventHandle);
    }

    // Templated destructor function
    template <typename EventType> void LocalEventDestroyCallback(void* dataPtr, void* eventHandle)
    {
        auto* event = static_cast<EventType*>(dataPtr);
        event->~EventType();
        Ers::Engine::ERS_EventScheduler_FreeLocalEvent(dataPtr, eventHandle);
    }

    // Templated serialization function
    template <typename EventType> void LocalEventSerialize(void* dataPtr, void* serializerHandle)
    {
        auto* event = static_cast<EventType*>(dataPtr);
        Serializer serializer(serializerHandle);

        // Check if EventType has Serialization method (from ERS_EVENT macro)
        if constexpr (Serializer::HasCustomSerialization<EventType>)
        {
            event->Serialization(serializer);
        }
        else
        {
            // Log warning for non-serializable types
            Ers::Logger::Warning(
                "LocalEvent cannot be serialized: The event struct does not provide a Serialization method.\n"
                "To enable serialization, use the ERS_EVENT macro in your event struct:\n"
                "  Example:\n"
                "  struct MyEvent {\n"
                "      EntityID entity;\n"
                "      int value;\n"
                "      void OnEvent() { /* event logic */ }\n"
                "      ERS_EVENT(entity, value)\n"
                "  };\n"
                "For more information, see LocalEvent.h");
        }
    }

    // Allocator callback: Creates a new instance of EventType with default construction
    // The event fields will be populated via Serialization() immediately after allocation
    template <typename EventType> void* LocalEventAllocator(void* eventHandle)
    {
        if constexpr (std::is_default_constructible_v<EventType>)
        {
            // Allocate and default-construct the event
            // The Serialization() call will populate the fields with saved data
            void* corePtr = Ers::Engine::ERS_EventScheduler_AllocLocalEvent(eventHandle);
            new (corePtr) EventType();
            return corePtr;
        }
        else
        {
            static_assert(
                std::is_default_constructible_v<EventType>, "Event types must be default constructible for serialization support");
            return nullptr;
        }
    }

} // namespace Ers
