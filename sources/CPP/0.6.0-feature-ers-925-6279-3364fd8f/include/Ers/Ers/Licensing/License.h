#pragma once

#include <string>

namespace Ers
{
    struct License
    {
        static bool HasFeature(const char* featureCode);
        static std::string EditionName();
        static int MaxJobSystemCores();
        static int MaxComponentTypes();
    };
} // namespace Ers