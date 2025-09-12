#include "RelationEvents.h"

#include "Ers/SubModel/SubModel.h"

#include "Ers/Api.h"

void* Ers::RelationEvents::Data()
{
    return this;
}

const void* const Ers::RelationEvents::Data() const
{
    return this;
}

Ers::EventSignal<Ers::Entity> Ers::RelationEvents::OnAwake()
{

    return Ers::EventSignal<Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnAwake(), ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnAwake_Connect);
}

Ers::EventSignal<Ers::Entity> Ers::RelationEvents::OnStart()
{
    return Ers::EventSignal<Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnStart(), ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnStart_Connect);
}

Ers::EventSignal<Ers::Entity> Ers::RelationEvents::OnCreate()
{
    return Ers::EventSignal<Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnCreate(), ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnCreate_Connect);
}

Ers::EventSignal<Ers::Entity> Ers::RelationEvents::OnDestroy()
{
    return Ers::EventSignal<Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnDestroy(),
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnDestroy_Connect);
}

Ers::EventSignal<Ers::Entity, Ers::Entity> Ers::RelationEvents::OnEntering()
{
    return Ers::EventSignal<Entity, Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnEntering(),
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnEntering_Connect);
}

Ers::EventSignal<Ers::Entity, Ers::Entity> Ers::RelationEvents::OnEntered()
{
    return Ers::EventSignal<Entity, Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnEntered(),
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnEntered_Connect);
}

Ers::EventSignal<Ers::Entity, Ers::Entity> Ers::RelationEvents::OnExiting()
{
    return Ers::EventSignal<Entity, Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnExiting(),
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnExiting_Connect);
}

Ers::EventSignal<Ers::Entity, Ers::Entity> Ers::RelationEvents::OnExited()
{
    return Ers::EventSignal<Entity, Entity>(
        ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnExited(), ersAPIFunctionPointers.ERS_SubModel_RelationEvents_OnExited_Connect);
}
