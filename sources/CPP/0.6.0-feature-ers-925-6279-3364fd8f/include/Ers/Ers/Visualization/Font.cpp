#include "Font.h"

namespace Ers::Visualization
{
    Font::Font(void* coreInstance) :
        coreInstance(coreInstance)
    {
    }

    void* Font::Data()
    {
        return coreInstance;
    }

    const void* const Font::Data() const
    {
        return coreInstance;
    }
} // namespace Ers::Visualization
