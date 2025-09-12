#pragma once

#include <memory>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOMINMAX
#include <Windows.h>
namespace Ers::Utility
{
    // This is burried in 4 layers of abstraction but in the end just void*. Thank you Windows.h.
    using SharedLibraryHandle = HMODULE;
} // namespace Ers::Utility
#elif __APPLE__ || __linux__
#include <dlfcn.h>
namespace Ers::Utility
{
    using SharedLibraryHandle = void*;
}
#else
#error "Unsupported platform"
#endif

namespace Ers::Utility
{
    /// @brief Shared library utility. IMPORTANT: unloading a library needs to be done
    /// manually. Is not done automatically when the SharedLibrary is deleted.
    class SharedLibrary
    {

      public:
        /// @brief Returns a platform specific handle to the loaded library.
        SharedLibraryHandle Handle() const;

        /// @brief Get the last error from the current platform.
        std::string GetLastError() const;

        /// @brief Unloads this shared library and releases resources. Updates lastError
        /// if unloading is unsuccesful.
        /// @return  True if unloading succesfully false otherwise
        [[nodiscard]] bool UnLoad();

        /// @return  True if this library is loaded succesfully
        bool IsLoaded() const;

        /// @brief Returns the function pointer to an exported function in this shared library.
        /// @param name The name of the function to load.
        /// @return  nullptr on failure, call GetLastError() for failure reason
        void* GetFunctionRaw(const std::string& name) const;

        /// @brief Returns the function pointer to an exported function in this shared library.
        /// <tparam name="FunctionSignature">The function signature of the function to return.</param>
        /// @param functionName The name of the function to load.
        /// @return  nullptr on failure, call GetLastError() to investigate the cause.
        template <typename FunctionSignature> FunctionSignature* GetFunction(const std::string& name) const
        {
            return reinterpret_cast<FunctionSignature*>(GetFunctionRaw(name));
        }

        /// @brief Loads a shared library from the specified path. Requires a call to UnLoad() to unload.
        /// Library resources are not automatically released.
        /// @param path  Relative of full path to the shared library.
        /// @return Returns an instance of SharedLibrary after loading the library at the given path.
        [[nodiscard]] static SharedLibrary LoadFromPath(const std::string& path);

        /// @brief Loads a library with a given base name. Constructs a local path
        /// based on the platform.  updates lastError if something went
        /// wrong which can be checked by calling IsLoaded afterwards.
        /// Always call UnLoad for unloading this library.
        /// @param baseName Base name of the sharedlibrary without the extension or the prefix.
        ///  E.g. for a library with a name: mylibrary.dll or libmylibrary.so, baseName is 'mylibrary'.
        /// @return Returns an instance of SharedLibrary after loading the library with given base name.
        [[nodiscard]] static SharedLibrary Load(const std::string& baseName);

        SharedLibrary() = default;

      private:
        SharedLibraryHandle handle = nullptr;
        bool isMain;
        mutable std::string lastError;

        /// @brief Reconstructs the platform dependent name of a shared library with a given base name.
        /// @param baseName Base name of the sharedlibrary without the extension or the prefix.
        ///  E.g. for a library with a name: mylibrary.dll or libmylibrary.so, baseName is 'mylibrary'.
        /// @return Returns the full name of a shared library after adding an appropriate prefix
        /// and/or a suffix for the given platform.
        static std::string GetPlatformSpecificName(const std::string& baseName);

        /// @return Gets the last platform specific error.
        static std::string GetLastNativeError();

        /// @brief Calls platform specific function to open a shared library at the given path.
        /// @param path The given path of the shared library to open.
        /// @return The platform dependent handle to the opened library or nullptr if in case of failure to open the library.
        /// Call GetLastError() for more details to invetigate the failure.
        static SharedLibraryHandle OpenLibraryAndGetNativeHandle(const std::string& path);

        /// @brief Calls the platform dependent function to close the shared library with a given handle.
        /// @param handle Handle to an open shared library.
        /// @return  false on failure, true on success
        [[nodiscard]] static bool CloseLibraryWithNativeHandle(SharedLibraryHandle handle);

        /// @brief Returns the function pointer to an exported function in the given shared library.
        /// @param handle The handle to the loaded shared library.
        /// @param functionName The name of the function to load.
        /// @return  nullptr on failure, call GetLastError() for failure reason
        static void* GetFunctionPointerFromNativeHandle(SharedLibraryHandle handle, bool isMainExecutable, const std::string& functionName);

        /// @param handle The handle of the shared library.
        /// @param lastErrorMessage The error message in case of failure.
        /// @return  nullptr on failure, call GetLastError() for failure reason
        explicit SharedLibrary(SharedLibraryHandle handle, bool isMain = false, const std::string& lastErrorMessage = "") :
            handle(handle),
            lastError(lastErrorMessage),
            isMain(isMain)
        {
            // Nothing to do here.
        }
    };
} // namespace Ers::Utility
