#include "SubModelSignals.h"

void* Ers::SubModelSignals::Data()
{
    return this;
}

const void* const Ers::SubModelSignals::Data() const
{
    return this;
}

Ers::RelationEvents& Ers::SubModelSignals::Relation()
{
    return *static_cast<RelationEvents*>(Data());
}
