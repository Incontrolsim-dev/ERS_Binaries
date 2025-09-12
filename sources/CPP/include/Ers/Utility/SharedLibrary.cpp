#include "SharedLibrary.h"

#include "HelperFunctions.h"

#include <filesystem>
#include <iostream>

#if defined(_WIN32)

#include <strsafe.h>

namespace Ers::Utility
{
    std::string SharedLibrary::GetPlatformSpecificName(const std::string& baseName)
    {
        return baseName + ".dll";
    }

    std::string SharedLibrary::GetLastNativeError()
    {
        // Retrieve the last error code
        DWORD errorCode = ::GetLastError();

        // Allocate a buffer for the error message
        LPVOID messageBuffer;
        DWORD formatMessageFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        // Random comment

        FormatMessage(
            formatMessageFlags,
            NULL,                                                 // source
            errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // language
            reinterpret_cast<LPTSTR>(&messageBuffer),
            0,   // buffer size
            NULL // No arguments to pass for formatting message inserts
        );

        // Calculate the buffer size for the formatted error message
        const size_t messageLength              = lstrlen(static_cast<LPCTSTR>(messageBuffer));
        const size_t additionalCharacters       = 40; // Additional space for formatting
        const size_t formattedMessageBufferSize = (messageLength + additionalCharacters) * sizeof(TCHAR);

        // Create a buffer for the formatted error message
        LPVOID displayBuffer = static_cast<LPVOID>(::LocalAlloc(LMEM_ZEROINIT, formattedMessageBufferSize));

        // Format the error message string
        const size_t displayBufferSize = LocalSize(displayBuffer) / sizeof(TCHAR);
        TCHAR errorFormat[]            = TEXT("Failed with error %d: %s");

        StringCchPrintf(
            static_cast<LPTSTR>(displayBuffer), displayBufferSize, errorFormat,
            errorCode,    // error code
            messageBuffer // original message
        );

        // Convert the error message to an std::string
        const std::string errorMessage(static_cast<LPCTSTR>(displayBuffer));

        // Clean up allocated buffers
        LocalFree(messageBuffer);
        LocalFree(displayBuffer);

        return errorMessage;
    }

    SharedLibraryHandle SharedLibrary::OpenLibraryAndGetNativeHandle(const std::string& path)
    {
        if (path == executable_name())
            return static_cast<SharedLibraryHandle>(GetModuleHandle(NULL));
        else
            return static_cast<SharedLibraryHandle>(LoadLibrary(path.c_str()));
    }

    bool SharedLibrary::CloseLibraryWithNativeHandle(SharedLibraryHandle handle)
    {
        // FreeLibrary returns 0 on error>
        const bool closeResult = FreeLibrary(handle);
        return closeResult;
    }

    void* SharedLibrary::GetFunctionPointerFromNativeHandle(SharedLibraryHandle handle, bool isMainExecutable, const std::string& functionName)
    {
        // isMainExecutable should not be used on Windows, since windows can still find symbols on the provided handle

        return GetProcAddress(handle, functionName.c_str());
    }
} // namespace Ers::Utility

#elif defined(__linux__) || defined(__APPLE__)

namespace Ers::Utility
{

    std::string SharedLibrary::GetPlatformSpecificName(const std::string& baseName)
    {
#if defined(__linux__)
        return "lib" + baseName + ".so";
#else
        return "lib" + baseName + ".dylib";
#endif
    }

    std::string SharedLibrary::GetLastNativeError()
    {
        return std::string(dlerror());
    }

    SharedLibraryHandle SharedLibrary::OpenLibraryAndGetNativeHandle(const std::string& path)
    {
        void* handle = dlopen(path.c_str(), RTLD_LAZY);

        return static_cast<SharedLibraryHandle>(handle);
    }

    bool SharedLibrary::CloseLibraryWithNativeHandle(SharedLibraryHandle handle)
    {
        // dlclose returns 0 on success.
        const bool closeResult = !dlclose(handle);
        return closeResult;
    }

    void* SharedLibrary::GetFunctionPointerFromNativeHandle(SharedLibraryHandle handle, bool isMainExecutable, const std::string& functionName)
    {
        if(isMainExecutable){
            return dlsym(RTLD_DEFAULT, functionName.c_str());
        }

        void* functionPointer = dlsym(handle, functionName.c_str());
        return functionPointer;
    }
} // namespace Ers::Utility

#else
#error "Platform not supported for DLL loading"
#endif

// Platform independent implementation

namespace Ers::Utility
{
    SharedLibraryHandle SharedLibrary::Handle() const
    {
        return handle;
    }

    std::string SharedLibrary::GetLastError() const
    {
        return lastError;
    }

    bool SharedLibrary::UnLoad()
    {
        if(isMain)
            return true; // When the library to close contains the entrypoint we can skip unloading it

        if (handle == nullptr)
        {
            lastError = "Handle is already closed";
            return false;
        }


        bool success = CloseLibraryWithNativeHandle(handle);
        if (!success)
        {
            lastError = GetLastNativeError();
            return false;
        }

        handle = nullptr;

        return true;
    }

    bool SharedLibrary::IsLoaded() const
    {
        return (handle != nullptr);
    }

    void* SharedLibrary::GetFunctionRaw(const std::string& name) const
    {
        void* function = GetFunctionPointerFromNativeHandle(handle, isMain, name);
        if (function == nullptr)
        {
            lastError = GetLastNativeError();
        }
        return function;
    }

    SharedLibrary SharedLibrary::LoadFromPath(const std::string& path)
    {
        SharedLibraryHandle handle = OpenLibraryAndGetNativeHandle(path);


        // When we try to open the current executable that contains the entry point
        if (path == executable_name())
        {
            return SharedLibrary(handle, true);
        }

        if (handle == nullptr)
        {
            std::string error = GetLastNativeError();
            return SharedLibrary(handle, false, error);
        }
        else{
            return SharedLibrary(handle, false);
        }
    }

    SharedLibrary SharedLibrary::Load(const std::string& baseName)
    {
        std::filesystem::path libraryPath;
        if (!std::filesystem::exists(baseName))
        {
            libraryPath = GetPlatformSpecificName(baseName);
        }
        else
        {
            // In case we're already referencing an absolute file
            libraryPath = baseName;
        }

        // This should not be necessary.
        if (!libraryPath.is_absolute())
        {
            libraryPath = std::filesystem::absolute(libraryPath);
        }

        return LoadFromPath(libraryPath.string());
    }
} // namespace Ers::Utility
