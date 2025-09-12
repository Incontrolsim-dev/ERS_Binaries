#pragma once

namespace Ers
{
    class VirtualFileSystem
    {
      public:
        static bool MountDirectory(const char* path, const char* directoryName);
    };
} // namespace Ers
