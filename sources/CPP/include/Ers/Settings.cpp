#include "Settings.h"

#include "Ers/Api.h"

#include <stdexcept>

namespace Ers
{

    std::string Settings::GetSetting(const std::string& section, const std::string& setting, const std::string& defaultValue)
    {
        char* returnedSetting = ersAPIFunctionPointers.ERS_Settings_GetSetting(section.c_str(), setting.c_str(), defaultValue.c_str());
        const std::string output{returnedSetting};
        free(returnedSetting); // Free the output string allocated inside ERS lib
        return output;
    }

    void Settings::SetSetting(const std::string& section, const std::string& setting, const std::string& value)
    {
        ersAPIFunctionPointers.ERS_Settings_SetSetting(section.c_str(), setting.c_str(), value.c_str());
    }
} // namespace Ers