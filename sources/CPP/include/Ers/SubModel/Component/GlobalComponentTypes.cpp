#include "GlobalComponentTypes.h"

namespace Ers
{
    void CoreScriptBehaviorOnCreation(void* scriptBehaviorInstance)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnCreation();
    }

    void CoreScriptBehaviorOnAwake(void* scriptBehaviorInstance)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnAwake();
    }

    void CoreScriptBehaviorOnStart(void* scriptBehaviorInstance)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnStart();
    }

    void CoreScriptBehaviorOnUpdate(void* scriptBehaviorInstance)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnUpdate();
    }

    void CoreScriptBehaviorOnLateUpdate(void* scriptBehaviorInstance)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnLateUpdate();
    }

    void CoreScriptBehaviorOnDestroy(void* scriptBehaviorInstance)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnDestroy();
    }

    void CoreScriptBehaviorOnEntering(void* scriptBehaviorInstance, EntityID parent)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnEntering(parent);
    }

    void CoreScriptBehaviorOnEntered(void* scriptBehaviorInstance, EntityID child)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnEntered(child);
    }

    void CoreScriptBehaviorOnExiting(void* scriptBehaviorInstance, EntityID parent)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnExiting(parent);
    }

    void CoreScriptBehaviorOnExited(void* scriptBehaviorInstance, EntityID child)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->OnExited(child);
    }

    void CoreScriptBehaviorSerialization(void* scriptBehaviorInstance, void* serializationNode)
    {
        auto* script = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->Serialization(Ers::Serializer(serializationNode));
    }

    void CoreScriptBehaviorOnSubModelMove(void* scriptBehaviorInstance, EntityID newEntityId)
    {
        auto* script            = static_cast<ScriptBehaviorComponent*>(scriptBehaviorInstance);
        script->ConnectedEntity = newEntityId;
        script->OnSubModelMove(newEntityId);
    }

    void SetupCoreComponentIDS()
    {
        TypeToComponentID<Ers::NameComponent>::ComponentTypeID      = ersAPIFunctionPointers.ERS_NameComponent_TypeId();
        TypeToComponentID<Ers::RelationComponent>::ComponentTypeID  = ersAPIFunctionPointers.ERS_RelationComponent_TypeId();
        TypeToComponentID<Ers::TransformComponent>::ComponentTypeID = ersAPIFunctionPointers.ERS_TransformComponent_TypeId();
    }

} // namespace Ers
