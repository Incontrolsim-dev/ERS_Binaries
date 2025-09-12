#include "Image.h"

#include "Ers/Api.h"

namespace Ers::Visualization
{
    Image::Image(void* coreInstance) :
        coreInstance(coreInstance)
    {
    }

    void* Image::Data()
    {
        return coreInstance;
    }

    const void* const Image::Data() const
    {
        return coreInstance;
    }
} // namespace Ers::Visualization
