#include "License.h"
#include "Ers/Api.h"

bool Ers::License::HasFeature(const char* featureCode)
{
    return Ers::ersAPIFunctionPointers.ERS_License_HasFeature(featureCode);
}

std::string Ers::License::EditionName()
{
    char* heapAllocatedName = Ers::ersAPIFunctionPointers.ERS_License_EditionName();
    std::string edition(heapAllocatedName);
    Ers::ersAPIFunctionPointers.ERS_STRING_DISPOSE(heapAllocatedName);

    return edition;
}

int Ers::License::MaxJobSystemCores()
{
    return Ers::ersAPIFunctionPointers.ERS_License_GetLimits_MaxJobSystemCores();
}

int Ers::License::MaxComponentTypes()
{
    return Ers::ersAPIFunctionPointers.ERS_License_GetLimits_MaxComponentTypes();
}
