#pragma once

#include <stdint.h>
#include <string>

namespace Ers
{
    /// @brief The type of the field.
    ///
    /// Used by ERS to know how to interpret the component's fields data.
    enum class FieldType : uint32_t
    {
        /// @brief A 32-bit float.
        Float32 = 0,
        /// @brief A boolean.
        Bool = 1,
        /// @brief A 32-bit signed integer.
        Int32 = 2,
        /// @brief A 32-bit unsigned integer.
        UInt32 = 3,
        /// @brief A 64-bit signed integer.
        Int64 = 4,
        /// @brief A 64-bit unsigned integer.
        UInt64 = 5,
        /// @brief An ERS Entity.
        Entity = 6,
        /// @brief A list of any known registered type.
        List = 7,
        /// @brief A string.
        String = 8,
        /// @brief A 2D vector.
        Vector2 = 9,
        /// @brief A 3D vector.
        Vector3 = 10,
        /// @brief A 4D vector.
        Vector4 = 11,
    };

    /// @brief Type information for a component.
    class TypeInfo
    {
      public:
        TypeInfo()                           = delete;
        TypeInfo(const TypeInfo&)            = delete;
        TypeInfo(TypeInfo&&)                 = delete;
        TypeInfo& operator=(const TypeInfo&) = delete;
        TypeInfo& operator=(TypeInfo&&)      = delete;
        ~TypeInfo()                          = delete;

        /// @brief Register the type information for a component.
        /// @param name The name of the component.
        /// @return A TypeInfo object, which can be used to add fields.
        static TypeInfo* RegisterStruct(const char* name);
        /// @brief Add field information to the component's type information.
        /// @param name The name of the field.
        /// @param type The type ID of the field (see FieldType).
        /// @param offset The memory offset of the field (use `offsetof(ComponentType, Field)`).
        void AddField(const char* name, FieldType type, size_t offset);
        /// @brief Add field information to the component's type information.
        /// @param name The name of the field.
        /// @param type The type ID of the field (see FieldType).
        /// @param offset The memory offset of the field (use `offsetof(ComponentType, Field)`).
        void AddField(const char* name, uint32_t type, size_t offset);

        /// @brief The name of the component.
        const char* GetName();
    };
} // namespace Ers
