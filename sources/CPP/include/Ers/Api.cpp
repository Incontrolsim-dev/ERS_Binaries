#include "Api.h"
#include "Ers/Logger.h"
#include "Ers/SubModel/APILocalEvent.h"
#include "Ers/SubModel/Component/GlobalComponentTypes.h"
#include "Ers/Utility/HelperMacros.h"

// This macro is used to enable the definition of API function names in ErsApiFunctions.h
#define ERS_API_FUNCTIONS_IMPLEMENTATION
#include "ErsApiFunctions.h"

#include <iostream>
#include <string>

/// @brief Default name of the shared library wrapping the ers-core for external users.
constexpr static const std::string_view coreModuleName{"ers-engine"};

namespace Ers
{
    ErsAPIFunctionPointers ersAPIFunctionPointers = {0};

    constexpr std::string_view GetErsEngineModuleName(void)
    {
        return coreModuleName;
    }

    /// @brief Loads all exposed functions of ERS core and initializes the global ersAPIFunctionPointers struct array elements.
    /// @return True on success, false on error.
    bool LoadApiFunctions()
    {
        // Load library and never unload
        Ers::Utility::SharedLibrary library = Ers::Utility::SharedLibrary::Load(std::string(coreModuleName));
        if (!library.IsLoaded())
        {
            // TODO Log when logging is available independent from the ers-engine DLL,
            // logging is not available at this point yet
            // Ers::Logger::Error("Error loading ERS shared object: " + ERSCore.GetLastError());
            auto error = library.GetLastError();
            std::cout << error << "\n";
            return false;
        }

        for (int i = 0; i < ERS_N_FUNCTIONS; i++)
        {
            const char* functionName = ersFunctionNames[i];
            void* functionPointer    = library.GetFunctionRaw(functionName);

            if (!functionPointer)
            {
                // TODO Log when logging is available independent from the ers-engine DLL,
                // logging might not be available at this point yet
                // Ers::Logger::Error("Could not load function " + std::string(functionName));
                return false;
            }
            ersAPIFunctionPointers.functions[i] = functionPointer;
        }

        ersAPIFunctionPointers.ERS_SetBindingType("C++");
        ersAPIFunctionPointers.ERS_Initialize();
        return true;
    }

    /// @brief Checks if the major and minor version of the loaded ers-engine library match the expected version in ErsApiFunctions.h.
    /// @return True, if the API major and minor version do not exceed the major and minor version number
    /// of the loaded library, otherwise returns false.
    bool ValidateAPIVersion()
    {
        // Check major version and warn for minor version
        uint32_t majorVersion = ersAPIFunctionPointers.ERS_GetMajorVersion();
        uint32_t minorVersion = ersAPIFunctionPointers.ERS_GetMinorVersion();
        if (majorVersion != ERS_API_FUNCTION_HEADER_MAJOR_VERSION)
        {
            Ers::Logger::Error(
                "Error loading ERS API, library has major version " + std::to_string(majorVersion) + " while header has major version " +
                std::to_string(ERS_API_FUNCTION_HEADER_MAJOR_VERSION));
            return false;
        }
        if (minorVersion < ERS_API_FUNCTION_HEADER_MINOR_VERSION)
        {
            Ers::Logger::Warning(
                "Warning: ERS API library has minor version " + std::to_string(minorVersion) +
                " which is older than header's minor version " + std::to_string(ERS_API_FUNCTION_HEADER_MINOR_VERSION));
            return false;
        }
        return true;
    }

    /// @brief Loads and initializes the ers-engine exported functions.
    /// @return True, if the functions are successfully loaded and the API version is valid, otherwise returns false.
    bool Initialize()
    {
        bool result = LoadApiFunctions();
        if (!result)
            return false;
        result = ValidateAPIVersion();

        return result;
    }

    /// @brief Uninitialize ERS.
    void Uninitialize()
    {
        ersAPIFunctionPointers.ERS_Uninitialize();
    }
} // namespace Ers
