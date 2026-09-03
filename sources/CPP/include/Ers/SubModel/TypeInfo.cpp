#include "TypeInfo.h"

#include "Ers/Api.h"

namespace Ers
{
    // TypeInfo

    TypeInfo::TypeInfo(void* corePtr_) :
        corePtr(corePtr_)
    {
    }

    void TypeInfo::AddField(const char* name, BuiltinType type, size_t offset, bool readOnly)
    {
        Ers::Engine::ERS_TypeInfo_AddField(corePtr, name, static_cast<uint32_t>(type), offset, readOnly);
    }

    void TypeInfo::AddField(const char* name, uint32_t type, size_t offset, bool readOnly)
    {
        Ers::Engine::ERS_TypeInfo_AddField(corePtr, name, type, offset, readOnly);
    }

    uint32_t TypeInfo::GetID() const
    {
        return Ers::Engine::ERS_TypeInfo_Get_ID(corePtr);
    }

    size_t TypeInfo::GetSize() const
    {
        return Ers::Engine::ERS_TypeInfo_Get_Size(corePtr);
    }

    const char* TypeInfo::GetName() const
    {
        return Ers::Engine::ERS_TypeInfo_Get_Name(corePtr);
    }

    size_t TypeInfo::FieldCount() const
    {
        return Ers::Engine::ERS_TypeInfo_Fields_Count(corePtr);
    }

    Field TypeInfo::GetField(size_t index) const
    {
        return Field(Ers::Engine::ERS_TypeInfo_Get_Field(corePtr, index));
    }

    std::vector<Field> TypeInfo::GetFields() const
    {
        std::vector<Ers::Field> fields;
        const size_t count = FieldCount();
        fields.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            fields.emplace_back(Ers::Field(Ers::Engine::ERS_TypeInfo_Get_Field(corePtr, i)));
        }
        return fields;
    }

    bool TypeInfo::operator==(const TypeInfo& other) const
    {
        return corePtr == other.corePtr;
    }

    // Field

    Field::Field(const void* ptr) :
        corePtr(ptr)
    {
    }

    size_t Field::GetOffset() const
    {
        return Ers::Engine::ERS_TypeInfo_Field_Get_Offset(corePtr);
    }

    TypeInfo Field::GetTypeInfo() const
    {
        const void* const ptr = Ers::Engine::ERS_TypeInfo_Field_Get_TypeInfo(corePtr);
        return TypeInfo(const_cast<void*>(ptr));
    }

    const char* Field::GetName() const
    {
        return Ers::Engine::ERS_TypeInfo_Field_Get_Name(corePtr);
    }

    bool Field::IsReadOnly() const
    {
        return Ers::Engine::ERS_TypeInfo_Field_Get_ReadOnly(corePtr);
    }

    // TypeRegistry

    TypeInfo* TypeRegistry::RegisterStruct(const char* name)
    {
        void* ptr = Ers::Engine::ERS_TypeRegistry_RegisterStruct(name);
        return new TypeInfo(ptr);
    }

    TypeInfo TypeRegistry::GetTypeInfo(BuiltinType type)
    {
        const void* const ptr = Ers::Engine::ERS_TypeRegistry_GetTypeById(static_cast<uint32_t>(type));
        return TypeInfo(const_cast<void* const>(ptr));
    }

    const TypeInfo* TypeRegistry::GetTypeInfo(uint32_t typeId)
    {
        const void* const ptr = Ers::Engine::ERS_TypeRegistry_GetTypeById(typeId);
        if (ptr == nullptr)
            return nullptr;

        return new TypeInfo(const_cast<void* const>(ptr));
    }

    const TypeInfo* TypeRegistry::GetTypeInfo(const char* typeName)
    {
        const void* const ptr = Ers::Engine::ERS_TypeRegistry_GetTypeByName(typeName);
        if (ptr == nullptr)
            return nullptr;
        return new TypeInfo(const_cast<void*>(ptr));
    }
} // namespace Ers
