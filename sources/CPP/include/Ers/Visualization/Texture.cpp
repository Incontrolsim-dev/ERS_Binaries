#include "Texture.h"

#include "Ers/Api.h"

namespace Ers::Visualization
{
    Texture::Texture()
    {
        coreInstance = ersAPIFunctionPointers.ERS_Texture_Create();
    }

    Texture::Texture(const std::string& path)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Texture_Create();
        ersAPIFunctionPointers.ERS_Texture_Load(coreInstance, path.c_str());
    }

    void Texture::Destroy()
    {
        ersAPIFunctionPointers.ERS_Texture_Release(Data());
    }

    void* Texture::Data()
    {
        return coreInstance;
    }

    const void* const Texture::Data() const
    {
        return coreInstance;
    }
} // namespace Ers::Visualization
