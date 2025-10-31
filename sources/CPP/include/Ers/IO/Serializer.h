#pragma once

#include <map>
#include <queue>
#include <stdint.h>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include <Ers/Api.h>

namespace Ers
{
    class ModelContainer; // Forward declaration
    class Serializer;     // Forward declaration

    class Serializer
    {
      public:
        // Helper to check if type has Serialization method at compile time
        template <typename T, typename = void> struct HasCustomSerializationImpl : std::false_type
        {
        };

        template <typename T>
        struct HasCustomSerializationImpl<T, std::void_t<decltype(std::declval<T&>().Serialization(std::declval<Serializer&>()))>>
            : std::true_type
        {
        };

        template <typename T> static constexpr bool HasCustomSerialization = HasCustomSerializationImpl<T>::value;

      public:
        Serializer(void* handle);
        Serializer(const Serializer&)            = delete;
        Serializer(Serializer&&)                 = delete;
        Serializer& operator=(const Serializer&) = delete;
        Serializer& operator=(Serializer&&)      = delete;

        bool IsWriting() const;

        int Size() const;

        Serializer operator[](const std::string_view& key);

        Serializer operator[](const std::string& key);

        Serializer operator[](const char* key);

        Serializer operator[](int index);

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

        // Helper methods that take key and value together (more convenient API)
        void Serialize(const std::string& key, uint32_t& value);
        void Serialize(const std::string& key, int32_t& value);
        void Serialize(const std::string& key, uint64_t& value);
        void Serialize(const std::string& key, int64_t& value);
        void Serialize(const std::string& key, double& value);
        void Serialize(const std::string& key, float& value);
        void Serialize(const std::string& key, bool& value);
        void Serialize(const std::string& key, std::string& value);

        /// <summary>
        /// Get the size of the current array in the serialization context.
        /// </summary>
        int GetArraySize();

        /// <summary>
        /// Push a named object onto the serialization stack.
        /// </summary>
        void PushObject(const std::string& key);

        /// <summary>
        /// Pop an object from the serialization stack.
        /// </summary>
        void PopObject();

        /// <summary>
        /// Push a named array onto the serialization stack.
        /// When writing, size should be set to the array size before calling.
        /// When reading, size will be set to the loaded array size after calling.
        /// </summary>
        void PushArray(const std::string& key, int& size);

        /// <summary>
        /// Push a named array onto the serialization stack.
        /// When writing, size should be set to the array size before calling.
        /// When reading, size will be set to the loaded array size after calling.
        /// </summary>
        void PushArray(const std::string& key, size_t& size);

        /// <summary>
        /// Pop an array from the serialization stack.
        /// </summary>
        void PopArray();

        /// <summary>
        /// Set the current array element by index.
        /// </summary>
        void SetObject(int index);

        // Serialization - Folder (Separate files for each simulator)
        /// @brief Save the model container to a folder with separate files for each simulator
        /// @param folderPath Path to the folder where the model will be saved
        static void SaveToFolder(Ers::ModelContainer& model, const std::string& folderPath);

        /// @brief Load a model container from a folder with separate files
        /// @param folderPath Path to the folder to load from
        /// @return A new ModelContainer instance loaded from the folder
        static ModelContainer LoadFromFolder(const std::string& folderPath);

        // Serialization - Compressed Archive files
        /// @brief Save the model container to a compressed archive file
        /// @param archivePath Path to the archive file
        /// @param compressionLevel Zstd compression level (1-22, default 3)
        static void SaveToArchive(Ers::ModelContainer& model, const std::string& archivePath, int compressionLevel = 3);

        /// @brief Load a model container from a compressed archive file
        /// @param archivePath Path to the archive file to load from
        /// @param useCache If true, cache decompressed files for faster repeated loading (useful for parallel loading)
        /// @return A new ModelContainer instance loaded from the archive
        static ModelContainer LoadFromArchive(const std::string& archivePath, bool useCache = false);

        /// @brief Clear the cached decompressed files for an archive
        /// @param archivePath Path to the archive file whose cache should be cleared
        static void ClearArchiveCache(const std::string& archivePath);

        // Template helper functions for standard containers
        // These support recursive serialization of nested collections (e.g. vector<queue<map<int, list<float>>>>)
        // Template resolution automatically picks the correct overload at compile time

        /// @brief Serialize a std::vector using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections.
        /// If the vector is empty during writing, nothing is written.
        template <typename T> void Serialize(const std::string& key, std::vector<T>& vec)
        {
            size_t size = vec.size();

            // Skip writing empty vectors
            if (IsWriting() && size == 0)
            {
                return;
            }

            PushArray(key, size);

            if (!IsWriting())
            {
                vec.clear();
                vec.reserve(size);
            }

            for (size_t i = 0; i < size; i++)
            {
                IsWriting() ? vec[i] : vec.emplace_back();
                Serialize(i, vec[i]);
            }

            PopArray();
        }

      private:
        // Helper method for serializing values directly to arrays without keys
        template <typename T> void Serialize(size_t index, T& value)
        {
            SetObject(index);

            // Check if type has Serialization method - if so, call it directly
            if constexpr (HasCustomSerialization<T>)
            {
                value.Serialization(*this);
            }
            else
            {
                // For non-primitive types, fall back to key-based serialization with "value" key
                Serialize("value", value);
            }

            PopObject();
        }

        // Specializations for primitive types that use keyless serialization
        void Serialize(size_t index, uint64_t& value);
        void Serialize(size_t index, int64_t& value);
        void Serialize(size_t index, uint32_t& value);
        void Serialize(size_t index, int32_t& value);
        void Serialize(size_t index, double& value);
        void Serialize(size_t index, float& value);
        void Serialize(size_t index, bool& value);
        void Serialize(size_t index, std::string& value);

        // Specializations for collection types that serialize directly without "value" wrapper
        template <typename T> void Serialize(size_t index, std::vector<T>& vec)
        {
            size_t size = vec.size();
            // Always push array element when in nested context (even if empty) to maintain structure
            ersAPIFunctionPointers.ERS_Serializer_PushArrayElement(coreHandle, index, reinterpret_cast<int*>(&size));

            if (!IsWriting())
            {
                vec.clear();
                vec.reserve(size);
            }

            for (size_t i = 0; i < size; i++)
            {
                T value = IsWriting() ? vec[i] : T{};
                Serialize(i, value);
                if (!IsWriting())
                {
                    vec.push_back(value);
                }
            }

            PopArray();
        }

        template <typename T> void Serialize(size_t index, std::queue<T>& queue)
        {
            size_t size = queue.size();
            // Always push array element when in nested context (even if empty) to maintain structure
            ersAPIFunctionPointers.ERS_Serializer_PushArrayElement(coreHandle, index, reinterpret_cast<int*>(&size));

            if (IsWriting())
            {
                std::queue<T> queueCopy = queue;
                for (size_t i = 0; i < size; i++)
                {
                    T value = queueCopy.front();
                    queueCopy.pop();
                    Serialize(i, value);
                }
            }
            else
            {
                while (!queue.empty())
                {
                    queue.pop();
                }

                for (size_t i = 0; i < size; i++)
                {
                    T value{};
                    Serialize(i, value);
                    queue.push(value);
                }
            }

            PopArray();
        }

        template <typename TKey, typename TValue> void Serialize(size_t index, std::map<TKey, TValue>& map)
        {
            size_t size = map.size();
            // Always push array element when in nested context (even if empty) to maintain structure
            ersAPIFunctionPointers.ERS_Serializer_PushArrayElement(coreHandle, index, reinterpret_cast<int*>(&size));

            if (IsWriting())
            {
                size_t i = 0;
                for (auto& kvp : map)
                {
                    ersAPIFunctionPointers.ERS_Serializer_PushObjectElement(coreHandle, i);
                    TKey k   = kvp.first;
                    TValue v = kvp.second;
                    Serialize("key", k);
                    Serialize("value", v);
                    PopObject();
                    i++;
                }
            }
            else
            {
                map.clear();
                for (size_t i = 0; i < size; i++)
                {
                    ersAPIFunctionPointers.ERS_Serializer_PushObjectElement(coreHandle, i);
                    TKey k{};
                    TValue v{};
                    Serialize("key", k);
                    Serialize("value", v);
                    map[k] = v;
                    PopObject();
                }
            }

            PopArray();
        }

        template <typename TKey, typename TValue> void Serialize(size_t index, std::unordered_map<TKey, TValue>& map)
        {
            size_t size = map.size();
            // Always push array element when in nested context (even if empty) to maintain structure
            ersAPIFunctionPointers.ERS_Serializer_PushArrayElement(coreHandle, index, reinterpret_cast<int*>(&size));

            if (IsWriting())
            {
                size_t i = 0;
                for (auto& kvp : map)
                {
                    ersAPIFunctionPointers.ERS_Serializer_PushObjectElement(coreHandle, i);
                    TKey k   = kvp.first;
                    TValue v = kvp.second;
                    Serialize("key", k);
                    Serialize("value", v);
                    PopObject();
                    i++;
                }
            }
            else
            {
                map.clear();
                for (size_t i = 0; i < size; i++)
                {
                    ersAPIFunctionPointers.ERS_Serializer_PushObjectElement(coreHandle, i);
                    TKey k{};
                    TValue v{};
                    Serialize("key", k);
                    Serialize("value", v);
                    map[k] = v;
                    PopObject();
                }
            }

            PopArray();
        }

      public:
        /// @brief Serialize a std::queue using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections.
        /// If the queue is empty during writing, nothing is written.
        template <typename T> void Serialize(const std::string& key, std::queue<T>& queue)
        {
            size_t size = queue.size();

            // Skip writing empty queues
            if (IsWriting() && size == 0)
            {
                return;
            }

            PushArray(key, size);

            if (IsWriting())
            {
                std::queue<T> queueCopy = queue;
                for (size_t i = 0; i < size; i++)
                {
                    T value = queueCopy.front();
                    queueCopy.pop();
                    Serialize(i, value);
                }
            }
            else
            {
                // Clear existing queue
                while (!queue.empty())
                {
                    queue.pop();
                }

                for (size_t i = 0; i < size; i++)
                {
                    T value{};
                    Serialize(i, value);
                    queue.push(value);
                }
            }

            PopArray();
        }

        /// @brief Serialize a std::map using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections as keys or values.
        /// If the map is empty during writing, nothing is written.
        template <typename TKey, typename TValue> void Serialize(const std::string& key, std::map<TKey, TValue>& map)
        {
            size_t size = map.size();

            // Skip writing empty maps
            if (IsWriting() && size == 0)
            {
                return;
            }

            PushArray(key, size);

            if (IsWriting())
            {
                size_t i = 0;
                for (auto& kvp : map)
                {
                    SetObject(i);
                    TKey k   = kvp.first;
                    TValue v = kvp.second;
                    Serialize("key", k);
                    Serialize("value", v);
                    PopObject();
                    i++;
                }
            }
            else
            {
                map.clear();
                for (size_t i = 0; i < size; i++)
                {
                    SetObject(i);
                    TKey k{};
                    TValue v{};
                    Serialize("key", k);
                    Serialize("value", v);
                    map[k] = v;
                    PopObject();
                }
            }

            PopArray();
        }

        /// @brief Serialize a std::unordered_map using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections as keys or values.
        /// If the map is empty during writing, nothing is written.
        template <typename TKey, typename TValue> void Serialize(const std::string& key, std::unordered_map<TKey, TValue>& map)
        {
            size_t size = map.size();

            // Skip writing empty maps
            if (IsWriting() && size == 0)
            {
                return;
            }

            PushArray(key, size);

            if (IsWriting())
            {
                size_t i = 0;
                for (auto& kvp : map)
                {
                    SetObject(i);
                    TKey k   = kvp.first;
                    TValue v = kvp.second;
                    Serialize("key", k);
                    Serialize("value", v);
                    PopObject();
                    i++;
                }
            }
            else
            {
                map.clear();
                for (size_t i = 0; i < size; i++)
                {
                    SetObject(i);
                    TKey k{};
                    TValue v{};
                    Serialize("key", k);
                    Serialize("value", v);
                    map[k] = v;
                    PopObject();
                }
            }

            PopArray();
        }

        /// @brief Generic template for custom types with Serialization method
        /// This will be selected for any type that has a public Serialization(Serializer&) method
        template <typename T> void Serialize(const std::string& key, T& value)
        {
            if constexpr (HasCustomSerialization<T>)
            {
                PushObject(key);
                value.Serialization(*this);
                PopObject();
            }
        }

      private:
        void* coreHandle;
    };
} // namespace Ers