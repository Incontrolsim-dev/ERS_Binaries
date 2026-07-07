#include "Api.h"
#include "Ers/Logger.h"
#include "Ers/SubModel/APILocalEvent.h"
#include "Ers/SubModel/Component/GlobalComponentTypes.h"
#include "Ers/Utility/HelperMacros.h"

#include "Ers/SubModel/EventScheduler.h"
#include "Ers/SubModel/SyncEvents/MoveEntity.h"

// This macro is used to enable the definition of API function names in ErsApiFunctions.h
#define ERS_API_FUNCTIONS_IMPLEMENTATION
#include "ErsApiFunctions.h"

#include <iostream>
#include <string>

namespace Ers
{
    /// @brief Checks if the major and minor version of the loaded ers-engine library match the expected version in ErsApiFunctions.h.
    /// @return True, if the API major and minor version do not exceed the major and minor version number
    /// of the loaded library, otherwise returns false.
    bool ValidateAPIVersion()
    {
        // Check major version and warn for minor version
        uint32_t majorVersion = Ers::Engine::ERS_GetMajorVersion();
        uint32_t minorVersion = Ers::Engine::ERS_GetMinorVersion();
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
        Ers::Engine::ERS_SetBindingType("C++");
        Ers::Engine::ERS_Initialize();

        Ers::EventScheduler::RegisterSyncEvent<Ers::MoveEntitySyncEvent>();
        return ValidateAPIVersion();
    }

    /// @brief Uninitialize ERS.
    void Uninitialize()
    {
        Ers::Engine::ERS_Uninitialize();
    }
} // namespace Ers
