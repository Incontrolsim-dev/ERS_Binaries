#pragma once

#include "Ers/IO/Serializer.h"
#include "Ers/Utility/Util.h"
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Ers
{
    // Source location information for event types
    struct EventSourceLocation
    {
        const char* File;
        int Line;
    };

    // Type validation traits for ERS_EVENT fields
    namespace EventFieldValidation
    {
        // Check if a type is a pointer type (including smart pointers)
        template <typename T> struct IsPointerType : std::false_type
        {
        };

        // Specialization for raw pointers
        template <typename T> struct IsPointerType<T*> : std::true_type
        {
        };

        // Specialization for std::shared_ptr
        template <typename T> struct IsPointerType<std::shared_ptr<T>> : std::true_type
        {
        };

        // Specialization for std::unique_ptr
        template <typename T> struct IsPointerType<std::unique_ptr<T>> : std::true_type
        {
        };

        // Specialization for std::weak_ptr
        template <typename T> struct IsPointerType<std::weak_ptr<T>> : std::true_type
        {
        };

        // Check if a type is in the allowed primitive types list
        template <typename T> struct IsAllowedPrimitiveType
        {
            using BaseType = std::remove_cv_t<std::remove_reference_t<T>>;
            static constexpr bool value =
                std::is_same_v<BaseType, uint32_t> || std::is_same_v<BaseType, int32_t> || std::is_same_v<BaseType, uint64_t> ||
                std::is_same_v<BaseType, int64_t> || std::is_same_v<BaseType, double> || std::is_same_v<BaseType, float> ||
                std::is_same_v<BaseType, bool> || std::is_same_v<BaseType, std::string> || std::is_same_v<BaseType, EntityID> ||
                std::is_same_v<BaseType, ComponentType> || std::is_same_v<BaseType, SimulationTime>;
        };

        // Check if a type is an allowed container of primitive types
        template <typename T, typename = void> struct IsAllowedContainerType : std::false_type
        {
        };

        // std::vector of allowed types
        template <typename T>
        struct IsAllowedContainerType<std::vector<T>, std::enable_if_t<IsAllowedPrimitiveType<T>::value>> : std::true_type
        {
        };

        // std::queue of allowed types
        template <typename T>
        struct IsAllowedContainerType<std::queue<T>, std::enable_if_t<IsAllowedPrimitiveType<T>::value>> : std::true_type
        {
        };

        // std::map of allowed types
        template <typename TKey, typename TValue>
        struct IsAllowedContainerType<
            std::map<TKey, TValue>,
            std::enable_if_t<IsAllowedPrimitiveType<TKey>::value && IsAllowedPrimitiveType<TValue>::value>> : std::true_type
        {
        };

        // std::unordered_map of allowed types
        template <typename TKey, typename TValue>
        struct IsAllowedContainerType<
            std::unordered_map<TKey, TValue>,
            std::enable_if_t<IsAllowedPrimitiveType<TKey>::value && IsAllowedPrimitiveType<TValue>::value>> : std::true_type
        {
        };

        // Check if a type is allowed in ERS_EVENT
        template <typename T> struct IsValidEventField
        {
            using BaseType = std::remove_cv_t<std::remove_reference_t<T>>;

            // Type must not be a pointer
            static_assert(
                !IsPointerType<BaseType>::value,
                "ERS_EVENT fields cannot be pointer types (including raw pointers, std::shared_ptr, std::unique_ptr, std::weak_ptr). "
                "Event fields must be serializable value types.");

            // Type must not have a custom Serialization method (except for allowed containers)
            static_assert(
                !Serializer::HasCustomSerialization<BaseType> || IsAllowedContainerType<BaseType>::value,
                "ERS_EVENT fields cannot be types with custom Serialization methods. "
                "Only primitive types (int32_t, uint32_t, int64_t, uint64_t, float, double, bool, std::string, "
                "EntityID, ComponentType, SimulationTime) and standard containers (std::vector, std::queue, std::map, std::unordered_map) of these types are allowed.");

            // Type must be either a primitive or allowed container
            static_assert(
                IsAllowedPrimitiveType<BaseType>::value || IsAllowedContainerType<BaseType>::value,
                "ERS_EVENT fields must be one of the allowed types: "
                "int32_t, uint32_t, int64_t, uint64_t, float, double, bool, std::string, "
                "EntityID, ComponentType, SimulationTime, "
                "or std::vector/std::queue/std::map/std::unordered_map of these types.");

            static constexpr bool value = true;
        };

        // Helper to validate a field and trigger static_asserts
        template <typename T> constexpr bool ValidateField()
        {
            return IsValidEventField<T>::value;
        }
    } // namespace EventFieldValidation
} // namespace Ers

// Helper macros for counting arguments (supports 0-20 fields)
// Uses C++20 __VA_OPT__ for portable empty __VA_ARGS__ handling across all compilers

// Argument counter
#define ERS_EVENT_ARG_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, N, ...) N

// Count arguments: returns 0 if empty, otherwise 1-20
// Uses __VA_OPT__ (C++20) for proper empty handling on all conforming compilers
#define ERS_EVENT_NARG(...) \
    ERS_EVENT_ARG_N(0 __VA_OPT__(, ) __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

// Serialization helpers - one serializer.Serialize call per field
#define ERS_EVENT_IMPL_0(...) // Empty case for events with no fields (variadic to handle empty __VA_ARGS__)

#define ERS_EVENT_IMPL_1(field1)                                                                                    \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);

#define ERS_EVENT_IMPL_2(field1, field2)                                                                            \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);

#define ERS_EVENT_IMPL_3(field1, field2, field3)                                                                    \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);

#define ERS_EVENT_IMPL_4(field1, field2, field3, field4)                                                            \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);                                                                          \
    serializer.Serialize(#field4, field4);

#define ERS_EVENT_IMPL_5(field1, field2, field3, field4, field5)                                                    \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);                                                                          \
    serializer.Serialize(#field4, field4);                                                                          \
    serializer.Serialize(#field5, field5);

#define ERS_EVENT_IMPL_6(field1, field2, field3, field4, field5, field6)                                            \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);                                                                          \
    serializer.Serialize(#field4, field4);                                                                          \
    serializer.Serialize(#field5, field5);                                                                          \
    serializer.Serialize(#field6, field6);

#define ERS_EVENT_IMPL_7(field1, field2, field3, field4, field5, field6, field7)                                    \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);                                                                          \
    serializer.Serialize(#field4, field4);                                                                          \
    serializer.Serialize(#field5, field5);                                                                          \
    serializer.Serialize(#field6, field6);                                                                          \
    serializer.Serialize(#field7, field7);

#define ERS_EVENT_IMPL_8(field1, field2, field3, field4, field5, field6, field7, field8)                            \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);                                                                          \
    serializer.Serialize(#field4, field4);                                                                          \
    serializer.Serialize(#field5, field5);                                                                          \
    serializer.Serialize(#field6, field6);                                                                          \
    serializer.Serialize(#field7, field7);                                                                          \
    serializer.Serialize(#field8, field8);

#define ERS_EVENT_IMPL_9(field1, field2, field3, field4, field5, field6, field7, field8, field9)                    \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                          \
    serializer.Serialize(#field2, field2);                                                                          \
    serializer.Serialize(#field3, field3);                                                                          \
    serializer.Serialize(#field4, field4);                                                                          \
    serializer.Serialize(#field5, field5);                                                                          \
    serializer.Serialize(#field6, field6);                                                                          \
    serializer.Serialize(#field7, field7);                                                                          \
    serializer.Serialize(#field8, field8);                                                                          \
    serializer.Serialize(#field9, field9);

#define ERS_EVENT_IMPL_10(field1, field2, field3, field4, field5, field6, field7, field8, field9, field10)           \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                           \
    serializer.Serialize(#field2, field2);                                                                           \
    serializer.Serialize(#field3, field3);                                                                           \
    serializer.Serialize(#field4, field4);                                                                           \
    serializer.Serialize(#field5, field5);                                                                           \
    serializer.Serialize(#field6, field6);                                                                           \
    serializer.Serialize(#field7, field7);                                                                           \
    serializer.Serialize(#field8, field8);                                                                           \
    serializer.Serialize(#field9, field9);                                                                           \
    serializer.Serialize(#field10, field10);

#define ERS_EVENT_IMPL_11(field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11)  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT"); \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT"); \
    serializer.Serialize(#field1, field1);                                                                           \
    serializer.Serialize(#field2, field2);                                                                           \
    serializer.Serialize(#field3, field3);                                                                           \
    serializer.Serialize(#field4, field4);                                                                           \
    serializer.Serialize(#field5, field5);                                                                           \
    serializer.Serialize(#field6, field6);                                                                           \
    serializer.Serialize(#field7, field7);                                                                           \
    serializer.Serialize(#field8, field8);                                                                           \
    serializer.Serialize(#field9, field9);                                                                           \
    serializer.Serialize(#field10, field10);                                                                         \
    serializer.Serialize(#field11, field11);

#define ERS_EVENT_IMPL_12(field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12) \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");          \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");         \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");         \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");         \
    serializer.Serialize(#field1, field1);                                                                                   \
    serializer.Serialize(#field2, field2);                                                                                   \
    serializer.Serialize(#field3, field3);                                                                                   \
    serializer.Serialize(#field4, field4);                                                                                   \
    serializer.Serialize(#field5, field5);                                                                                   \
    serializer.Serialize(#field6, field6);                                                                                   \
    serializer.Serialize(#field7, field7);                                                                                   \
    serializer.Serialize(#field8, field8);                                                                                   \
    serializer.Serialize(#field9, field9);                                                                                   \
    serializer.Serialize(#field10, field10);                                                                                 \
    serializer.Serialize(#field11, field11);                                                                                 \
    serializer.Serialize(#field12, field12);

#define ERS_EVENT_IMPL_13(field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13) \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");                   \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");                  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");                  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");                  \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");                  \
    serializer.Serialize(#field1, field1);                                                                                            \
    serializer.Serialize(#field2, field2);                                                                                            \
    serializer.Serialize(#field3, field3);                                                                                            \
    serializer.Serialize(#field4, field4);                                                                                            \
    serializer.Serialize(#field5, field5);                                                                                            \
    serializer.Serialize(#field6, field6);                                                                                            \
    serializer.Serialize(#field7, field7);                                                                                            \
    serializer.Serialize(#field8, field8);                                                                                            \
    serializer.Serialize(#field9, field9);                                                                                            \
    serializer.Serialize(#field10, field10);                                                                                          \
    serializer.Serialize(#field11, field11);                                                                                          \
    serializer.Serialize(#field12, field12);                                                                                          \
    serializer.Serialize(#field13, field13);

#define ERS_EVENT_IMPL_14(                                                                                               \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14) \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");     \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");     \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");     \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");     \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");     \
    serializer.Serialize(#field1, field1);                                                                               \
    serializer.Serialize(#field2, field2);                                                                               \
    serializer.Serialize(#field3, field3);                                                                               \
    serializer.Serialize(#field4, field4);                                                                               \
    serializer.Serialize(#field5, field5);                                                                               \
    serializer.Serialize(#field6, field6);                                                                               \
    serializer.Serialize(#field7, field7);                                                                               \
    serializer.Serialize(#field8, field8);                                                                               \
    serializer.Serialize(#field9, field9);                                                                               \
    serializer.Serialize(#field10, field10);                                                                             \
    serializer.Serialize(#field11, field11);                                                                             \
    serializer.Serialize(#field12, field12);                                                                             \
    serializer.Serialize(#field13, field13);                                                                             \
    serializer.Serialize(#field14, field14);

#define ERS_EVENT_IMPL_15(                                                                                                        \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14, field15) \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");              \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");              \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");              \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");              \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");              \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field15)>(), "Invalid field type in ERS_EVENT");              \
    serializer.Serialize(#field1, field1);                                                                                        \
    serializer.Serialize(#field2, field2);                                                                                        \
    serializer.Serialize(#field3, field3);                                                                                        \
    serializer.Serialize(#field4, field4);                                                                                        \
    serializer.Serialize(#field5, field5);                                                                                        \
    serializer.Serialize(#field6, field6);                                                                                        \
    serializer.Serialize(#field7, field7);                                                                                        \
    serializer.Serialize(#field8, field8);                                                                                        \
    serializer.Serialize(#field9, field9);                                                                                        \
    serializer.Serialize(#field10, field10);                                                                                      \
    serializer.Serialize(#field11, field11);                                                                                      \
    serializer.Serialize(#field12, field12);                                                                                      \
    serializer.Serialize(#field13, field13);                                                                                      \
    serializer.Serialize(#field14, field14);                                                                                      \
    serializer.Serialize(#field15, field15);

#define ERS_EVENT_IMPL_16(                                                                                                                 \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14, field15, field16) \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field15)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field16)>(), "Invalid field type in ERS_EVENT");                       \
    serializer.Serialize(#field1, field1);                                                                                                 \
    serializer.Serialize(#field2, field2);                                                                                                 \
    serializer.Serialize(#field3, field3);                                                                                                 \
    serializer.Serialize(#field4, field4);                                                                                                 \
    serializer.Serialize(#field5, field5);                                                                                                 \
    serializer.Serialize(#field6, field6);                                                                                                 \
    serializer.Serialize(#field7, field7);                                                                                                 \
    serializer.Serialize(#field8, field8);                                                                                                 \
    serializer.Serialize(#field9, field9);                                                                                                 \
    serializer.Serialize(#field10, field10);                                                                                               \
    serializer.Serialize(#field11, field11);                                                                                               \
    serializer.Serialize(#field12, field12);                                                                                               \
    serializer.Serialize(#field13, field13);                                                                                               \
    serializer.Serialize(#field14, field14);                                                                                               \
    serializer.Serialize(#field15, field15);                                                                                               \
    serializer.Serialize(#field16, field16);

#define ERS_EVENT_IMPL_17(                                                                                                                 \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14, field15, field16, \
    field17)                                                                                                                               \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field15)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field16)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field17)>(), "Invalid field type in ERS_EVENT");                       \
    serializer.Serialize(#field1, field1);                                                                                                 \
    serializer.Serialize(#field2, field2);                                                                                                 \
    serializer.Serialize(#field3, field3);                                                                                                 \
    serializer.Serialize(#field4, field4);                                                                                                 \
    serializer.Serialize(#field5, field5);                                                                                                 \
    serializer.Serialize(#field6, field6);                                                                                                 \
    serializer.Serialize(#field7, field7);                                                                                                 \
    serializer.Serialize(#field8, field8);                                                                                                 \
    serializer.Serialize(#field9, field9);                                                                                                 \
    serializer.Serialize(#field10, field10);                                                                                               \
    serializer.Serialize(#field11, field11);                                                                                               \
    serializer.Serialize(#field12, field12);                                                                                               \
    serializer.Serialize(#field13, field13);                                                                                               \
    serializer.Serialize(#field14, field14);                                                                                               \
    serializer.Serialize(#field15, field15);                                                                                               \
    serializer.Serialize(#field16, field16);                                                                                               \
    serializer.Serialize(#field17, field17);

#define ERS_EVENT_IMPL_18(                                                                                                                 \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14, field15, field16, \
    field17, field18)                                                                                                                      \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field15)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field16)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field17)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field18)>(), "Invalid field type in ERS_EVENT");                       \
    serializer.Serialize(#field1, field1);                                                                                                 \
    serializer.Serialize(#field2, field2);                                                                                                 \
    serializer.Serialize(#field3, field3);                                                                                                 \
    serializer.Serialize(#field4, field4);                                                                                                 \
    serializer.Serialize(#field5, field5);                                                                                                 \
    serializer.Serialize(#field6, field6);                                                                                                 \
    serializer.Serialize(#field7, field7);                                                                                                 \
    serializer.Serialize(#field8, field8);                                                                                                 \
    serializer.Serialize(#field9, field9);                                                                                                 \
    serializer.Serialize(#field10, field10);                                                                                               \
    serializer.Serialize(#field11, field11);                                                                                               \
    serializer.Serialize(#field12, field12);                                                                                               \
    serializer.Serialize(#field13, field13);                                                                                               \
    serializer.Serialize(#field14, field14);                                                                                               \
    serializer.Serialize(#field15, field15);                                                                                               \
    serializer.Serialize(#field16, field16);                                                                                               \
    serializer.Serialize(#field17, field17);                                                                                               \
    serializer.Serialize(#field18, field18);

#define ERS_EVENT_IMPL_19(                                                                                                                 \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14, field15, field16, \
    field17, field18, field19)                                                                                                             \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field15)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field16)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field17)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field18)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field19)>(), "Invalid field type in ERS_EVENT");                       \
    serializer.Serialize(#field1, field1);                                                                                                 \
    serializer.Serialize(#field2, field2);                                                                                                 \
    serializer.Serialize(#field3, field3);                                                                                                 \
    serializer.Serialize(#field4, field4);                                                                                                 \
    serializer.Serialize(#field5, field5);                                                                                                 \
    serializer.Serialize(#field6, field6);                                                                                                 \
    serializer.Serialize(#field7, field7);                                                                                                 \
    serializer.Serialize(#field8, field8);                                                                                                 \
    serializer.Serialize(#field9, field9);                                                                                                 \
    serializer.Serialize(#field10, field10);                                                                                               \
    serializer.Serialize(#field11, field11);                                                                                               \
    serializer.Serialize(#field12, field12);                                                                                               \
    serializer.Serialize(#field13, field13);                                                                                               \
    serializer.Serialize(#field14, field14);                                                                                               \
    serializer.Serialize(#field15, field15);                                                                                               \
    serializer.Serialize(#field16, field16);                                                                                               \
    serializer.Serialize(#field17, field17);                                                                                               \
    serializer.Serialize(#field18, field18);                                                                                               \
    serializer.Serialize(#field19, field19);

#define ERS_EVENT_IMPL_20(                                                                                                                 \
    field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field11, field12, field13, field14, field15, field16, \
    field17, field18, field19, field20)                                                                                                    \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field1)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field2)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field3)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field4)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field5)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field6)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field7)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field8)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field9)>(), "Invalid field type in ERS_EVENT");                        \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field10)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field11)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field12)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field13)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field14)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field15)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field16)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field17)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field18)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field19)>(), "Invalid field type in ERS_EVENT");                       \
    static_assert(Ers::EventFieldValidation::ValidateField<decltype(field20)>(), "Invalid field type in ERS_EVENT");                       \
    serializer.Serialize(#field1, field1);                                                                                                 \
    serializer.Serialize(#field2, field2);                                                                                                 \
    serializer.Serialize(#field3, field3);                                                                                                 \
    serializer.Serialize(#field4, field4);                                                                                                 \
    serializer.Serialize(#field5, field5);                                                                                                 \
    serializer.Serialize(#field6, field6);                                                                                                 \
    serializer.Serialize(#field7, field7);                                                                                                 \
    serializer.Serialize(#field8, field8);                                                                                                 \
    serializer.Serialize(#field9, field9);                                                                                                 \
    serializer.Serialize(#field10, field10);                                                                                               \
    serializer.Serialize(#field11, field11);                                                                                               \
    serializer.Serialize(#field12, field12);                                                                                               \
    serializer.Serialize(#field13, field13);                                                                                               \
    serializer.Serialize(#field14, field14);                                                                                               \
    serializer.Serialize(#field15, field15);                                                                                               \
    serializer.Serialize(#field16, field16);                                                                                               \
    serializer.Serialize(#field17, field17);                                                                                               \
    serializer.Serialize(#field18, field18);                                                                                               \
    serializer.Serialize(#field19, field19);                                                                                               \
    serializer.Serialize(#field20, field20);

// Dispatcher macro - concatenates ERS_EVENT_IMPL_ with the argument count
#define ERS_EVENT_CONCAT(a, b) a##b
#define ERS_EVENT_DISPATCH(N, ...) ERS_EVENT_CONCAT(ERS_EVENT_IMPL_, N)(__VA_ARGS__)
#define ERS_EVENT_DISPATCH2(N, ...) ERS_EVENT_DISPATCH(N __VA_OPT__(, ) __VA_ARGS__)

/// @brief Macro to generate serialization and source location methods for events
/// Place inside your event struct to auto-generate Serialization() method and location tracking.
/// Works for both local events and sync events.
/// Supports 0-20 fields.
///
/// TYPE RESTRICTIONS (enforced at compile-time):
/// - Only primitive types: int32_t, uint32_t, int64_t, uint64_t, float, double, bool, std::string
/// - ERS types: EntityID, ComponentType, SimulationTime
/// - STL containers: std::vector, std::queue, std::map, std::unordered_map (of allowed types)
/// - NO pointer types (raw pointers, std::shared_ptr, std::unique_ptr, std::weak_ptr)
/// - NO types with custom Serialization methods
///
/// See ERS_EVENT_TYPE_VALIDATION.md for complete documentation and migration guide.
///
/// @example
/// struct MyEvent {
///     EntityID entity;
///     int32_t value;
///     void OnEvent() { /* event logic */ }
///     ERS_EVENT(entity, value)
/// };
#define ERS_EVENT(...)                                                              \
    void Serialization(Ers::Serializer& serializer)                                 \
    {                                                                               \
        ERS_EVENT_DISPATCH2(ERS_EVENT_NARG(__VA_ARGS__) __VA_OPT__(, ) __VA_ARGS__) \
    }                                                                               \
    static Ers::EventSourceLocation GetEventSourceLocation()                        \
    {                                                                               \
        static Ers::EventSourceLocation loc{__FILE__, __LINE__};                    \
        return loc;                                                                 \
    }
