#pragma once

#include "NameComponent.h"
#include "RelationComponent.h"
#include "TransformComponent.h"

#include "Ers/Api.h"
#include "Ers/SubModel/ScriptBehaviorComponent.h"

namespace Ers
{
    using ComponentID                               = uint32_t;
    static constexpr ComponentID InvalidComponentID = UINT32_MAX;

    template <typename T> struct TypeToComponentID
    {
        inline static uint32_t ComponentTypeID = InvalidComponentID;
    };

    template <typename T> ComponentID GetComponentTypeID()
    {
        return TypeToComponentID<T>::ComponentTypeID;
    }

    template <typename T> constexpr bool IsScriptBehavior()
    {
        return std::is_base_of<ScriptBehaviorComponent, T>::value;
    }

    template <typename T> constexpr bool IsCoreComponent()
    {
        return std::is_base_of<CoreComponent, T>::value;
    }

    template <typename T> bool IsComponentTypeGloballyRegistered()
    {
        return TypeToComponentID<T>::ComponentTypeID != InvalidComponentID;
    }

    void SetupCoreComponentIDS();
    void CoreScriptBehaviorOnCreation(void* scriptBehaviorInstance);
    void CoreScriptBehaviorOnAwake(void* scriptBehaviorInstance);
    void CoreScriptBehaviorOnStart(void* scriptBehaviorInstance);
    void CoreScriptBehaviorOnUpdate(void* scriptBehaviorInstance);
    void CoreScriptBehaviorOnLateUpdate(void* scriptBehaviorInstance);
    void CoreScriptBehaviorOnDestroy(void* scriptBehaviorInstance);
    void CoreScriptBehaviorOnEntering(void* scriptBehaviorInstance, EntityID parent);
    void CoreScriptBehaviorOnEntered(void* scriptBehaviorInstance, EntityID child);
    void CoreScriptBehaviorOnExiting(void* scriptBehaviorInstance, EntityID parent);
    void CoreScriptBehaviorOnExited(void* scriptBehaviorInstance, EntityID child);
    void CoreScriptBehaviorSerialization(void* scriptBehaviorInstance, void* serializationNode);
    void CoreScriptBehaviorOnSubModelMove(void* scriptBehaviorInstance, EntityID newEntityId);

    template <typename T> static void RegisterGlobalScriptBehavior()
    {
        // clang-format off
        const char* name = typeid(T).name();
        ComponentID id   = ersAPIFunctionPointers.ERS_GlobalComponentRegistry_RegisterScriptBehavior(
            name, [](void* handle) -> void* { return new /*TODO use allocator for better memory placement*/ T(); }, nullptr,
            CoreScriptBehaviorOnCreation, 
            CoreScriptBehaviorOnAwake, 
            CoreScriptBehaviorOnStart, 
            CoreScriptBehaviorOnUpdate,
            CoreScriptBehaviorOnLateUpdate, 
            CoreScriptBehaviorOnDestroy, 
            CoreScriptBehaviorOnEntering, 
            CoreScriptBehaviorOnEntered, 
            CoreScriptBehaviorOnExiting, 
            CoreScriptBehaviorOnExited, 
            CoreScriptBehaviorSerialization,
            CoreScriptBehaviorOnSubModelMove);
        TypeToComponentID<T>::ComponentTypeID = id;
        // clang-format on
    }

    template <typename T> static void RegisterGlobalComponentType()
    {
        assert(!IsComponentTypeGloballyRegistered<T>());

        if constexpr (std::is_base_of<ScriptBehaviorComponent, T>::value)
        {
            RegisterGlobalScriptBehavior<T>();
            return;
        }

        const char* name = typeid(T).name();
        size_t size      = sizeof(T);

        ComponentID id                        = ersAPIFunctionPointers.ERS_GlobalComponentRegistry_RegisterComponent(name, size);
        TypeToComponentID<T>::ComponentTypeID = id;
    }

} // namespace Ers
