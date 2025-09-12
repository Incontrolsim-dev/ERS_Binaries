#pragma once
#include "RelationEvents.h"

namespace Ers
{
    struct SubModel;

    struct SubModelSignals
    {
      public:
        SubModelSignals()                                  = delete;
        SubModelSignals(const SubModelSignals&)            = delete;
        SubModelSignals(SubModelSignals&&)                 = delete;
        SubModelSignals& operator=(const SubModelSignals&) = delete;
        SubModelSignals& operator=(SubModelSignals&&)      = delete;
        ~SubModelSignals()                                 = delete;

        void* Data();
        const void* const Data() const;

        RelationEvents& Relation();
    };
} // namespace Ers
