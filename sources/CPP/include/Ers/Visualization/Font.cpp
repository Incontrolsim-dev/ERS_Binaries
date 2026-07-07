#include "Font.h"

namespace Ers
{
    Font::Font(void* corePtr) :
        corePtr(corePtr)
    {
    }

    void* Font::CorePtr()
    {
        return corePtr;
    }

    const void* const Font::CorePtr() const
    {
        return corePtr;
    }
} // namespace Ers
