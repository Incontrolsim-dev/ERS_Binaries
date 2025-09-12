#include "LibraryCollection.h"

#include "Ers/Api.h"

Ers::LibraryCollection::LibraryCollection(void* instance) :
    libraryCoreInstance(instance)
{
    // Nothing to do here
}

bool Ers::LibraryCollection::OpenLibrary(const std::string& libraryPath) const
{
    return ersAPIFunctionPointers.ERS_LibraryCollection_OpenLibrary(libraryCoreInstance, libraryPath.c_str());
}

bool Ers::LibraryCollection::IsLibraryOpen(const std::string& libraryPath) const
{
    return ersAPIFunctionPointers.ERS_LibraryCollection_IsLibraryOpen(libraryCoreInstance, libraryPath.c_str());
}

void* Ers::LibraryCollection::GetFunctionRaw(const std::string& libraryPath, const std::string& functionName) const
{
    return ersAPIFunctionPointers.ERS_LibraryCollection_GetFunctionFromLibrary(
        libraryCoreInstance, libraryPath.c_str(), functionName.c_str());
}

void* Ers::LibraryCollection::GetLibraryHandle(const std::string& libraryPath) const
{
    return ersAPIFunctionPointers.ERS_LibraryCollection_GetLibraryHandle(libraryCoreInstance, libraryPath.c_str());
}
