#pragma once
#include "Ers/Event/EventSignal.h"
#include "Ers/SubModel/Entity.h"
#include "Ers/Utility/Util.h"

namespace Ers
{
    class SubModel;

    struct RelationEvents
    {
      public:
        RelationEvents()                                 = delete;
        RelationEvents(const RelationEvents&)            = delete;
        RelationEvents(RelationEvents&&)                 = delete;
        RelationEvents& operator=(const RelationEvents&) = delete;
        RelationEvents& operator=(RelationEvents&&)      = delete;
        ~RelationEvents()                                = delete;

        void* Data();
        const void* const Data() const;

        // Default Events
        Ers::EventSignal<Entity /*entity*/> OnAwake();
        Ers::EventSignal<Entity /*entity*/> OnStart();

        Ers::EventSignal<Entity /*entity*/> OnCreate();
        Ers::EventSignal<Entity /*entity*/> OnDestroy();

        Ers::EventSignal<Entity /*parent*/, Entity /*entity*/> OnEntering();
        Ers::EventSignal<Entity /*parent*/, Entity /*newChild*/> OnEntered();

        Ers::EventSignal<Entity /*parent*/, Entity /*entity*/> OnExiting();
        Ers::EventSignal<Entity /*parent*/, Entity /*oldChild*/> OnExited();
    };
} // namespace Ers