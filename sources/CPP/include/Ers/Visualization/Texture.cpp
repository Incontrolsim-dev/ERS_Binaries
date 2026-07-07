#include "Texture.h"

#include "Ers/Api.h"

namespace Ers
{
    Texture::Texture()
    {
        corePtr = Ers::Engine::ERS_Texture_Create();
    }

    Texture::Texture(const std::string& path)
    {
        corePtr = Ers::Engine::ERS_Texture_Create();
        Ers::Engine::ERS_Texture_Load(corePtr, path.c_str());
    }

    void Texture::Destroy()
    {
        Ers::Engine::ERS_Texture_Release(CorePtr());
    }

    void* Texture::CorePtr()
    {
        return corePtr;
    }

    const void* const Texture::CorePtr() const
    {
        return corePtr;
    }
} // namespace Ers
