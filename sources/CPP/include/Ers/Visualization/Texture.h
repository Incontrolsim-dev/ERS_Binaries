#pragma once

#include <string>

namespace Ers::Visualization
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

        void* Data();
        const void* const Data() const;

      private:
        void* coreInstance;
    };
} // namespace Ers::Visualization
