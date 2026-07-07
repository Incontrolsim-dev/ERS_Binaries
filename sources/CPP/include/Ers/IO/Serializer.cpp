#include "Serializer.h"
#include "Ers/Api.h"

#include "Ers/Model/ModelContainer.h"

Ers::Serializer::Serializer(void* _corePtr) :
    corePtr(_corePtr)
{
}

bool Ers::Serializer::IsWriting() const
{
    return Ers::Engine::ERS_Serializer_IsWriting(corePtr);
}

int Ers::Serializer::Size() const
{
    return Ers::Engine::ERS_Serializer_GetArraySize(corePtr);
}

Ers::Serializer Ers::Serializer::operator[](const std::string_view& key)
{
    Ers::Engine::ERS_Serializer_PushObject(corePtr, std::string(key).c_str());
    return Serializer(corePtr);
}

Ers::Serializer Ers::Serializer::operator[](const std::string& key)
{
    Ers::Engine::ERS_Serializer_PushObject(corePtr, key.c_str());
    return Serializer(corePtr);
}

Ers::Serializer Ers::Serializer::operator[](const char* key)
{
    Ers::Engine::ERS_Serializer_PushObject(corePtr, key);
    return Serializer(corePtr);
}

Ers::Serializer Ers::Serializer::operator[](int index)
{
    Ers::Engine::ERS_Serializer_SetObject(corePtr, index);
    return Serializer(corePtr);
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
    Ers::Engine::ERS_Serializer_SerializeUInt32(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, int32_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeInt32(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, uint64_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeUInt64(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, int64_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeInt64(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, double& value)
{
    Ers::Engine::ERS_Serializer_SerializeDouble(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, float& value)
{
    Ers::Engine::ERS_Serializer_SerializeFloat(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, bool& value)
{
    Ers::Engine::ERS_Serializer_SerializeBool(corePtr, key.c_str(), &value);
}

void Ers::Serializer::Serialize(const std::string& key, std::string& value)
{
    char* str  = nullptr;
    int length = 0;

    if (IsWriting())
    {
        str = const_cast<char*>(value.c_str());
    }

    Ers::Engine::ERS_Serializer_SerializeString(corePtr, key.c_str(), &str, &length);

    if (!IsWriting())
    {
        if (str != nullptr)
        {
            value = std::string(str, length);
            Ers::Engine::ERS_String_Destroy(str); // Free using the API's free function
        }
        else
        {
            value = "";
        }
    }
}

int Ers::Serializer::GetArraySize()
{
    return Ers::Engine::ERS_Serializer_GetArraySize(corePtr);
}

void Ers::Serializer::PushObject(const std::string& key)
{
    Ers::Engine::ERS_Serializer_PushObject(corePtr, key.c_str());
}

void Ers::Serializer::PopObject()
{
    Ers::Engine::ERS_Serializer_PopObject(corePtr);
}

void Ers::Serializer::PushArray(const std::string& key, int& size)
{
    Ers::Engine::ERS_Serializer_PushArray(corePtr, key.c_str(), &size);
}

void Ers::Serializer::PushArray(const std::string& key, size_t& size)
{

    int sizeInt = size;
    PushArray(key, sizeInt);
    size = sizeInt;
}

void Ers::Serializer::PopArray()
{
    Ers::Engine::ERS_Serializer_PopArray(corePtr);
}

void Ers::Serializer::SetObject(int index)
{
    Ers::Engine::ERS_Serializer_SetObject(corePtr, index);
}

// Serialization - Folder (Separate files for each simulator)
void Ers::Serializer::SaveToFolder(Ers::ModelContainer& model, const std::string& folderPath)
{
    Ers::Engine::ERS_Serializer_SaveToFolder(model.CorePtr(), folderPath.c_str());
}

Ers::ModelContainer Ers::Serializer::LoadFromFolder(const std::string& folderPath)
{
    void* ptr = Ers::Engine::ERS_Serializer_LoadFromFolder(folderPath.c_str());
    ModelContainer container(ptr);
    Ers::Engine::ERS_ModelContainer_Release(ptr);
    return container;
}

// Serialization - Compressed Archive
void Ers::Serializer::SaveToArchive(Ers::ModelContainer& model, const std::string& archivePath, int compressionLevel)
{
    Ers::Engine::ERS_Serializer_SaveToArchive(model.CorePtr(), archivePath.c_str(), compressionLevel);
}

Ers::ModelContainer Ers::Serializer::LoadFromArchive(const std::string& archivePath, bool useCache)
{
    void* ptr = Ers::Engine::ERS_Serializer_LoadFromArchive(archivePath.c_str(), useCache);
    ModelContainer container(ptr);
    Ers::Engine::ERS_ModelContainer_Release(ptr);
    return container;
}

void Ers::Serializer::ClearArchiveCache(const std::string& archivePath)
{
    Ers::Engine::ERS_Serializer_ClearArchiveCache(archivePath.c_str());
}

// Serialize implementations for primitive types (keyless serialization for array elements)
void Ers::Serializer::Serialize(size_t index, uint64_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueUInt64(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, int64_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueInt64(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, uint32_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueUInt32(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, int32_t& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueInt32(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, double& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueDouble(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, float& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueFloat(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, bool& value)
{
    Ers::Engine::ERS_Serializer_SerializeValueBool(corePtr, index, &value);
}

void Ers::Serializer::Serialize(size_t index, std::string& value)
{
    char* str  = nullptr;
    int length = 0;

    if (IsWriting())
    {
        str = const_cast<char*>(value.c_str());
    }

    Ers::Engine::ERS_Serializer_SerializeValueString(corePtr, index, &str, &length);

    if (!IsWriting())
    {
        if (str != nullptr)
        {
            value = std::string(str, length);
            Ers::Engine::ERS_String_Destroy(str); // Free using the API's free function
        }
        else
        {
            value = "";
        }
    }
}
