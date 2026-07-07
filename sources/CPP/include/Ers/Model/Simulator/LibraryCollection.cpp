#include "LibraryCollection.h"

#include "Ers/Api.h"

Ers::LibraryCollection::LibraryCollection(void* instance) :
    corePtr(instance)
{
    // Nothing to do here
}

bool Ers::LibraryCollection::OpenLibrary(const std::string& libraryPath) const
{
    return Ers::Engine::ERS_LibraryCollection_OpenLibrary(corePtr, libraryPath.c_str());
}

bool Ers::LibraryCollection::IsLibraryOpen(const std::string& libraryPath) const
{
    return Ers::Engine::ERS_LibraryCollection_IsLibraryOpen(corePtr, libraryPath.c_str());
}

void* Ers::LibraryCollection::GetFunctionRaw(const std::string& libraryPath, const std::string& functionName) const
{
    return Ers::Engine::ERS_LibraryCollection_GetFunctionFromLibrary(corePtr, libraryPath.c_str(), functionName.c_str());
}

void* Ers::LibraryCollection::GetLibraryHandle(const std::string& libraryPath) const
{
    return Ers::Engine::ERS_LibraryCollection_GetLibraryHandle(corePtr, libraryPath.c_str());
}
