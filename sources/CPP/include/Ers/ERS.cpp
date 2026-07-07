#include "ERS.h"
#include "Ers/Api.h"

uint32_t Ers::MajorVersion()
{
    return Ers::Engine::ERS_GetMajorVersion();
}

uint32_t Ers::MinorVersion()
{
    return Ers::Engine::ERS_GetMinorVersion();
}

uint32_t Ers::PatchVersion()
{
    return Ers::Engine::ERS_GetPatchVersion();
}

bool Ers::IsDebugBuild()
{
    return Ers::Engine::ERS_IsDebugBuild();
}
