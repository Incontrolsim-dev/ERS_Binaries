#include "TypeInfo.h"

#include "Ers/Api.h"

namespace Ers
{
    TypeInfo* TypeInfo::RegisterStruct(const char* name)
    {
        void* ptr = ersAPIFunctionPointers.ERS_TypeInfo_RegisterStruct(name);
        return static_cast<TypeInfo*>(ptr);
    }

    void TypeInfo::AddField(const char* name, FieldType type, size_t offset, bool readOnly)
    {
        ersAPIFunctionPointers.ERS_TypeInfo_AddField(this, name, static_cast<uint32_t>(type), offset, readOnly);
    }

    void TypeInfo::AddField(const char* name, uint32_t type, size_t offset, bool readOnly)
    {
        ersAPIFunctionPointers.ERS_TypeInfo_AddField(this, name, type, offset, readOnly);
    }

    const char* TypeInfo::GetName()
    {
        return ersAPIFunctionPointers.ERS_TypeInfo_GetName(this);
    }
} // namespace Ers
