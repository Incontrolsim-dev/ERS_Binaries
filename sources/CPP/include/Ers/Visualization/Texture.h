#pragma once

#include <string>

namespace Ers
{
    class Texture
    {
      public:
        Texture();
        Texture(const std::string& path);
        Texture(const Texture&)            = delete;
        Texture(Texture&&)                 = delete;
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&)      = delete;
        ~Texture()                         = default;

        void Destroy();

        void* CorePtr();
        const void* const CorePtr() const;

      private:
        void* corePtr;
    };
} // namespace Ers
