#pragma once

#include <string>

namespace Ers
{
    class Settings
    {
      public:
        static std::string GetSetting(const std::string& section, const std::string& setting, const std::string& defaultValue);

        static void SetSetting(const std::string& section, const std::string& setting, const std::string& value);

        static void ClearSettings();
    };
} // namespace Ers
