#include "License.h"
#include "Ers/Api.h"

bool Ers::License::HasFeature(const char* featureCode)
{
    return Ers::Engine::ERS_License_HasFeature(featureCode);
}

std::string Ers::License::EditionName()
{
    char* heapAllocatedName = Ers::Engine::ERS_License_EditionName();
    std::string edition(heapAllocatedName);
    Ers::Engine::ERS_String_Destroy(heapAllocatedName);

    return edition;
}

int Ers::License::MaxJobSystemCores()
{
    return Ers::Engine::ERS_License_GetLimits_MaxJobSystemCores();
}

int Ers::License::MaxComponentTypes()
{
    return Ers::Engine::ERS_License_GetLimits_MaxComponentTypes();
}
