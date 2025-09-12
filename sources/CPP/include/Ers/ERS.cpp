#include "ERS.h"
#include "Ers/Api.h"

void Ers::Platform::Initialize()
{
    ersAPIFunctionPointers.ERS_Initialize();
}

void Ers::Platform::Uninitialize()
{
    ersAPIFunctionPointers.ERS_Uninitialize();
}

uint32_t Ers::Platform::MajorVersion()
{
    return ersAPIFunctionPointers.ERS_GetMajorVersion();
}

uint32_t Ers::Platform::MinorVersion()
{
    return ersAPIFunctionPointers.ERS_GetMinorVersion();
}

uint32_t Ers::Platform::PatchVersion()
{
    return ersAPIFunctionPointers.ERS_GetPatchVersion();
}

bool Ers::Platform::IsDebugBuild()
{
    return ersAPIFunctionPointers.ERS_IsDebugBuild();
}
