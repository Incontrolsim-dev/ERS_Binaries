#pragma once

#include "Ers/Api.h"
#include <stdint.h>

namespace Ers
{
    using SubModelContextTypeIndex                                            = uint32_t;
    static constexpr SubModelContextTypeIndex InvalidSubModelContextTypeIndex = UINT32_MAX;

    inline SubModelContextTypeIndex SubModelContextTypeCounter = 0;

    template <typename T> struct RegisteredSubModelContext
    {
        inline static SubModelContextTypeIndex Index = InvalidSubModelContextTypeIndex;
    };

    template <typename T> static SubModelContextTypeIndex GetSubModelContextTypeIndex()
    {
        SubModelContextTypeIndex idx = RegisteredSubModelContext<T>::Index;
        return idx;
    }

    template <typename T> static SubModelContextTypeIndex RegisterSubModelContextTypeIndex()
    {
        // Only register if it wasn't registed before
        if (RegisteredSubModelContext<T>::Index == InvalidSubModelContextTypeIndex)
        {
            RegisteredSubModelContext<T>::Index = Ers::ersAPIFunctionPointers.ERS_SubModel_RegisterSubModelContext();
        }
        return RegisteredSubModelContext<T>::Index;
    }
} // namespace Ers