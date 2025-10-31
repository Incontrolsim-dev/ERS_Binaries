#include "ERS.h"
#include "Ers/Api.h"

uint32_t Ers::MajorVersion()
{
    return ersAPIFunctionPointers.ERS_GetMajorVersion();
}

uint32_t Ers::MinorVersion()
{
    return ersAPIFunctionPointers.ERS_GetMinorVersion();
}

uint32_t Ers::PatchVersion()
{
    return ersAPIFunctionPointers.ERS_GetPatchVersion();
}

bool Ers::IsDebugBuild()
{
    return ersAPIFunctionPointers.ERS_IsDebugBuild();
}
