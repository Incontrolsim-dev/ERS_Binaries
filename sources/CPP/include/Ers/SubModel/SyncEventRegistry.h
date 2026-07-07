#pragma once

#include <stdint.h>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include "Ers/Api.h"
#include "Ers/IO/Serializer.h"
#include "Ers/Logger.h"
#include "SyncEvent.h"

namespace Ers
{
    // Concept to ensure required static methods exist for SyncEvent
    template <typename T>
    concept SyncEventConcept = requires(T t) {
        { T::GetName() } -> std::convertible_to<const char*>;
        { t.OnSenderSide() } -> std::same_as<void>;
        { t.OnTargetSide() } -> std::same_as<void>;
    };

    template <typename T>
    concept SyncEventCombinedConcept = requires(T t) {
        { T::GetName() } -> std::convertible_to<const char*>;
        { t.OnSyncEvent() } -> std::same_as<void>;
    };

    // Concept to check if GetEventSourceLocation exists (optional, provided by ERS_EVENT macro)
    template <typename T>
    concept HasEventSourceLocation = requires {
        { T::GetEventSourceLocation().File } -> std::convertible_to<const char*>;
        { T::GetEventSourceLocation().Line } -> std::convertible_to<int>;
    };

    // Helper to get the source library name from a function pointer at runtime
    inline const char* GetLibraryNameFromFunctionPointer(void* functionPtr)
    {
#ifdef _WIN32
        // Windows: Use GetModuleHandleEx to find which DLL contains this function
        HMODULE hModule = nullptr;
        if (GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)functionPtr, &hModule))
        {
            static char moduleName[MAX_PATH];
            if (GetModuleFileNameA(hModule, moduleName, MAX_PATH) > 0)
            {
                // Extract just the filename without path
                const char* filename = strrchr(moduleName, '\\');
                return filename ? filename + 1 : moduleName;
            }
        }
        return "UnknownModule";
#else
        // Linux/Unix: Use dladdr to find which shared library contains this function
        Dl_info info;
        if (dladdr(functionPtr, &info) && info.dli_fname)
        {
            // Extract just the filename without path
            const char* filename = strrchr(info.dli_fname, '/');
            return filename ? filename + 1 : info.dli_fname;
        }
        return "UnknownModule";
#endif
    }

    // Serialization function template for SyncEvent data
    template <typename T> static void SyncEventDataSerialize(void* dataContext, void* serializerHandle)
    {
        T* data = static_cast<T*>(dataContext);
        Serializer serializer(serializerHandle);

        // Check if T has Serialization method
        if constexpr (Serializer::HasCustomSerialization<T>)
        {
            data->Serialization(serializer);
        }
        else
        {
            // Log warning for non-serializable types
            Ers::Logger::Warning(
                "SyncEvent data type does not provide Serialization(Ers::Serializer&) method - serialization will be incomplete");
        }
    }

    /// @brief Static registration of sync event type - templated per event type
    /// Each unique sync event struct gets its own registration with type-specific callbacks
    template <typename EventType> class SyncEventRegistry
    {
      public:
        static void* EventHandle()
        {
            // Static local - initialized once per EventType, thread-safe (C++11 magic statics)
            static void* handle = []()
            {
                // Type identifier for this specific EventType
                uint64_t eventTypeIdentifier = SyncEvent::TypeIdentifier<EventType>();

                // Sender and target side callbacks
                void (*senderSide)() = EventType::OnSenderSidePlain;
                void (*targetSide)() = EventType::OnTargetSidePlain;

                // Serialization callback
                void (*serializeDataPtr)(void*, void*) = &SyncEventDataSerialize<EventType>;

                // Event name and source library
                const char* eventName     = EventType::GetName();
                const char* sourceLibrary = GetLibraryNameFromFunctionPointer((void*)senderSide);

                // Data block size for automatic allocation
                uint32_t dataBlockSize = sizeof(EventType);

                // Location information for debugging - extract from ERS_EVENT macro's GetEventSourceLocation if available
                const char* filePath = "";
                int lineNumber       = 0;
                if constexpr (HasEventSourceLocation<EventType>)
                {
                    auto loc   = EventType::GetEventSourceLocation();
                    filePath   = loc.File;
                    lineNumber = loc.Line;
                }

                return Ers::Engine::ERS_EventScheduler_RegisterSyncEventType(
                    eventTypeIdentifier, senderSide, targetSide, serializeDataPtr, dataBlockSize, eventName, sourceLibrary, filePath,
                    lineNumber);
            }();

            return handle;
        }

        /// @brief Register a sync event type explicitly before simulation creation
        /// ensures all types are known before simulation model creation.
        /// Registration is idempotent - calling multiple times is safe and results in a no-op.
        static void Register()
        {
            // Simply accessing EventHandle() triggers registration via static initialization
            (void)EventHandle();
        }
    };

} // namespace Ers
