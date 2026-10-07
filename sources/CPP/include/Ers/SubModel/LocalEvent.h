#pragma once
#include "ErsEvent.h"
#include <concepts>
#include <typeinfo>

namespace Ers
{
    // Concept to ensure LocalEvent has all required methods from ERS_EVENT macro
    template <typename T>
    concept LocalEventConcept = requires(T t, Serializer& serializer) {
        { t.OnEvent() } -> std::same_as<void>;
        // Required: Serialization method (provided by ERS_EVENT macro)
        { t.Serialization(serializer) } -> std::same_as<void>;
        // Required: GetEventSourceLocation static method (provided by ERS_EVENT macro)
        { T::GetEventSourceLocation().File } -> std::convertible_to<const char*>;
        { T::GetEventSourceLocation().Line } -> std::convertible_to<int>;
    };

    /// @brief Base class for local events. Be sure to include the ERS_EVENT macro in your subclasses!
    struct ILocalEvent
    {
        static void OnEvent();
    };
} // namespace Ers