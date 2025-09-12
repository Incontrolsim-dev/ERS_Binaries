#pragma once

#include <string>
#include <stdint.h>

namespace Ers
{
    class SerializationNode
    {
      public:
        SerializationNode(void* handle);
        SerializationNode(const SerializationNode&) = delete;
        SerializationNode(SerializationNode&&)      = delete;
        SerializationNode& operator=(const SerializationNode&) = delete;
        SerializationNode& operator=(SerializationNode&&)      = delete;

        bool IsWriting() const;

        int Size() const;

        SerializationNode operator[](const std::string_view& key);

        SerializationNode operator[](const std::string& key);

        SerializationNode operator[](const char* key);

        SerializationNode operator[](int index);

        // Preallocates an array
        void ArrayCreate(int fixedSize);

        void UInt32(uint32_t& value);

        void Int32(int32_t& value);

        void Double(double& value);

        void UInt64(uint64_t& value);

        void Int64(int64_t& value);

        void Bool(bool& value);

        void String(std::string& value);

        void Null();

      private:
        void* coreHandle;


    };
}