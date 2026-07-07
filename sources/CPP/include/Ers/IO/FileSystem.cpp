#include "FileSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    bool VirtualFileSystem::MountDirectory(const char* path, const char* directoryName)
    {
        return Ers::Engine::ERS_VirtualFileSystem_MountDirectory(path, directoryName);
    }
} // namespace Ers
