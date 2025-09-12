#pragma once

#include "Ers/Utility/SharedLibrary.h"
#include "Ers/Utility/Util.h"
#include "ErsApiFunctions.h"

namespace Ers
{

    extern ErsAPIFunctionPointers ersAPIFunctionPointers;

    bool Initialize();
    void Uninitialize();

    constexpr std::string_view GetErsEngineModuleName();

} // namespace Ers
