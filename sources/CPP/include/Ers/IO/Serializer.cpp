#include "Serializer.h"
#include "Ers/Api.h"

#include "Ers/Model/ModelContainer.h"

Ers::Serializer::Serializer(void* handle) :
    coreHandle(handle)
{
}

bool Ers::Serializer::IsWriting() const
{
    return ersAPIFunctionPointers.ERS_Serializer_IsWriting(coreHandle);
}

int Ers::Serializer::Size() const
{
    return ersAPIFunctionPointers.ERS_Serializer_GetArraySize(coreHandle);
}

Ers::Serializer Ers::Serializer::operator[](const std::string_view& key)
{
    ersAPIFunctionPointers.ERS_Serializer_PushObject(coreHandle, std::string(key).c_str());
    return Serializer(coreHandle);
}

Ers::Serializer Ers::Serializer::operator[](const std::string& key)
{
    ersAPIFunctionPointers.ERS_Serializer_PushObject(coreHandle, key.c_str());
    return Serializer(coreHandle);
}

Ers::Serializer Ers::Serializer::operator[](const char* key)
{
    ersAPIFunctionPointers.ERS_Serializer_PushObject(coreHandle, key);
    return Serializer(coreHandle);
}

Ers::Serializer Ers::Serializer::operator[](int index)
{
    ersAPIFunctionPointers.ERS_Serializer_SetObject(coreHandle, index);
    return Serializer(coreHandle);
}

void Ers::Serializer::ArrayCreate(int fixedSize)
{
    // Note: This is a no-op for now since arrays are created automatically when pushing
}

void Ers::Serializer::UInt32(uint32_t& value)
{
    Serialize("value", value);
}

void Ers::Serializer::Int32(int32_t& value)
{
    Serialize("value", value);
}

void Ers::Serializer::Double(double& value)
{
    Serialize("value", value);
}

void Ers::Serializer::UInt64(uint64_t& value)
{
    Serialize("value", value);
}

void Ers::Serializer::Int64(int64_t& value)
{
    Serialize("value", value);
}

void Ers::Serializer::Bool(bool& value)
{
    Serialize("value", value);
}

void Ers::Serializer::String(std::string& value)
{
    Serialize("value", value);
}

void Ers::Serializer::Null()
{
    // No-op for now
}

// Helper methods for direct key-value serialization
void Ers::Serializer::Serialize(const std::string& key, uint32_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeUInt32(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, int32_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeInt32(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, uint64_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeUInt64(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, int64_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeInt64(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, double& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeDouble(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, float& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeFloat(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, bool& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeBool(coreHandle, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, std::string& value)
{
    char* str  = nullptr;
    int length = 0;

    if (IsWriting())
    {
        str = const_cast<char*>(value.c_str());
    }

    ersAPIFunctionPointers.ERS_Serializer_SerializeString(coreHandle, key.c_str(), &str, &length);

    if (!IsWriting())
    {
        if (str != nullptr)
        {
            value = std::string(str, length);
            ersAPIFunctionPointers.ERS_STRING_DISPOSE(str); // Free using the API's free function
        }
        else
        {
            value = "";
        }
    }
}

int Ers::Serializer::GetArraySize()
{
    return ersAPIFunctionPointers.ERS_Serializer_GetArraySize(coreHandle);
}

void Ers::Serializer::PushObject(const std::string& key)
{
    ersAPIFunctionPointers.ERS_Serializer_PushObject(coreHandle, key.c_str());
}

void Ers::Serializer::PopObject()
{
    ersAPIFunctionPointers.ERS_Serializer_PopObject(coreHandle);
}

void Ers::Serializer::PushArray(const std::string& key, int& size)
{
    ersAPIFunctionPointers.ERS_Serializer_PushArray(coreHandle, key.c_str(), &size);
}

void Ers::Serializer::PushArray(const std::string& key, size_t& size)
{

    int sizeInt = size;
    PushArray(key, sizeInt);
    size = sizeInt;
}

void Ers::Serializer::PopArray()
{
    ersAPIFunctionPointers.ERS_Serializer_PopArray(coreHandle);
}

void Ers::Serializer::SetObject(int index)
{
    ersAPIFunctionPointers.ERS_Serializer_SetObject(coreHandle, index);
}

// Serialization - Folder (Separate files for each simulator)
void Ers::Serializer::SaveToFolder(Ers::ModelContainer& model, const std::string& folderPath)
{
    ersAPIFunctionPointers.ERS_Serializer_SaveToFolder(model.Data(), folderPath.c_str());
}

Ers::ModelContainer Ers::Serializer::LoadFromFolder(const std::string& folderPath)
{
    void* ptr = ersAPIFunctionPointers.ERS_Serializer_LoadFromFolder(folderPath.c_str());
    ModelContainer container(ptr);
    ersAPIFunctionPointers.ERS_ModelContainer_Release(ptr);
    return container;
}

// Serialization - Compressed Archive
void Ers::Serializer::SaveToArchive(Ers::ModelContainer& model, const std::string& archivePath, int compressionLevel)
{
    ersAPIFunctionPointers.ERS_Serializer_SaveToArchive(model.Data(), archivePath.c_str(), compressionLevel);
}

Ers::ModelContainer Ers::Serializer::LoadFromArchive(const std::string& archivePath, bool useCache)
{
    void* ptr = ersAPIFunctionPointers.ERS_Serializer_LoadFromArchive(archivePath.c_str(), useCache);
    ModelContainer container(ptr);
    ersAPIFunctionPointers.ERS_ModelContainer_Release(ptr);
    return container;
}

void Ers::Serializer::ClearArchiveCache(const std::string& archivePath)
{
    ersAPIFunctionPointers.ERS_Serializer_ClearArchiveCache(archivePath.c_str());
}

// Serialize implementations for primitive types (keyless serialization for array elements)
void Ers::Serializer::Serialize(size_t index, uint64_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueUInt64(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, int64_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueInt64(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, uint32_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueUInt32(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, int32_t& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueInt32(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, double& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueDouble(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, float& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueFloat(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, bool& value)
{
    ersAPIFunctionPointers.ERS_Serializer_SerializeValueBool(coreHandle, index, &value);
}

void Ers::Serializer::Serialize(size_t index, std::string& value)
{
    char* str  = nullptr;
    int length = 0;

    if (IsWriting())
    {
        str = const_cast<char*>(value.c_str());
    }

    ersAPIFunctionPointers.ERS_Serializer_SerializeValueString(coreHandle, index, &str, &length);

    if (!IsWriting())
    {
        if (str != nullptr)
        {
            value = std::string(str, length);
            ersAPIFunctionPointers.ERS_STRING_DISPOSE(str); // Free using the API's free function
        }
        else
        {
            value = "";
        }
    }
}