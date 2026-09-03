#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace Ers
{
    /// @brief TypeInfo types that are built into ERS.
    enum class BuiltinType : uint32_t
    {
        /// @brief A 32-bit float.
        Float32 = 0,
        /// @brief A boolean.
        Bool = 1,
        /// @brief An 8-bit unsigned integer.
        UInt8 = 2,
        /// @brief A 32-bit signed integer.
        Int32 = 3,
        /// @brief A 32-bit unsigned integer.
        UInt32 = 4,
        /// @brief A 64-bit signed integer.
        Int64 = 5,
        /// @brief A 64-bit unsigned integer.
        UInt64 = 6,
        /// @brief An ERS Entity.
        Entity = 7,
        /// @brief A list of any known registered type.
        List = 8,
        /// @brief A string.
        String = 9,
        /// @brief A 2D vector.
        Vector2 = 10,
        /// @brief A 3D vector.
        Vector3 = 11,
        /// @brief A 4D vector.
        Vector4 = 12,
        /// @brief An RGBA color (Ers::Color).
        Color = 13,
    };

    class Field;

    /// @brief Type information for a type in ERS.
    class TypeInfo
    {
      public:
        TypeInfo() = delete;
        TypeInfo(void* corePtr_);

        /// @brief Add field information to the type information.
        /// @param name The name of the field.
        /// @param type The type ID of the field (see BuiltinType).
        /// @param offset The memory offset of the field (use `offsetof(ComponentType, Field)`).
        /// @param readOnly Whether the field is read-only.
        void AddField(const char* name, BuiltinType type, size_t offset, bool readOnly = false);
        /// @brief Add field information to the type information.
        /// @param name The name of the field.
        /// @param type The type ID of the field (see BuiltinType).
        /// @param offset The memory offset of the field (use `offsetof(ComponentType, Field)`).
        /// @param readOnly Whether the field is read-only.
        void AddField(const char* name, uint32_t type, size_t offset, bool readOnly = false);

        /// @brief Get the ID of the type.
        /// @return
        uint32_t GetID() const;

        /// @brief The size of the type in bytes.
        /// @return
        size_t GetSize() const;

        /// @brief The name of the type.
        const char* GetName() const;

        /// @brief The number of fields in the type.
        /// @return
        size_t FieldCount() const;
        /// @brief Get a field of the type by its index.
        /// @param index The index of the field.
        /// @return
        Field GetField(size_t index) const;
        /// @brief Get a list of all fields of the type.
        /// @return
        std::vector<Field> GetFields() const;

        bool operator==(const TypeInfo& other) const;

        const void* CorePtr() const { return corePtr; }

      private:
        // Core instance pointer
        void* const corePtr = nullptr;
    };

    /// @brief Field information for fields in TypeInfo.
    class Field
    {
      public:
        Field() = delete;
        /// @brief Construct a Field around the core instance.
        /// @param ptr The pointer to the core instance.
        Field(const void* ptr);

        /// @brief The byte offset of the field.
        /// @return
        size_t GetOffset() const;
        /// @brief The type of the field.
        /// @return
        TypeInfo GetTypeInfo() const;
        /// @brief The name of the field.
        /// @return
        const char* GetName() const;
        /// @brief Whether the field is read-only.
        /// @return
        bool IsReadOnly() const;

        const void* CorePtr() const { return corePtr; }

      private:
        // Core instance pointer
        const void* const corePtr = nullptr;
    };

    class TypeRegistry
    {
      public:
        TypeRegistry()                               = delete;
        TypeRegistry(const TypeRegistry&)            = delete;
        TypeRegistry(TypeRegistry&&)                 = delete;
        TypeRegistry& operator=(const TypeRegistry&) = delete;
        TypeRegistry& operator=(TypeRegistry&&)      = delete;
        ~TypeRegistry()                              = delete;

        /// @brief Register the type information of a struct.
        /// @param name The name of the type.
        /// @return A TypeInfo object, which can be used to add fields.
        static TypeInfo* RegisterStruct(const char* name);

        /// @brief Get a TypeInfo by its type ID (via BuiltinType).
        /// @param type The type ID (via BuiltinType).
        /// @return
        static TypeInfo GetTypeInfo(BuiltinType type);
        /// @brief Get a TypeInfo by its type ID.
        /// @param type The type ID.
        /// @return The TypeInfo when found, nullptr when not found.
        static const TypeInfo* GetTypeInfo(uint32_t typeId);
        /// @brief Get a TypeInfo by its name.
        /// @param typeName The name of the type.
        /// @return The TypeInfo when found, nullptr when not found.
        static const TypeInfo* GetTypeInfo(const char* typeName);
    };
} // namespace Ers
