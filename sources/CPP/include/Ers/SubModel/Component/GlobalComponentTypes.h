#pragma once

#include "NameComponent.h"
#include "RelationComponent.h"
#include "TransformComponent.h"

#include "Ers/Api.h"
#include "Ers/IO/Serializer.h"
#include "Ers/SubModel/DataComponent.h"
#include "Ers/SubModel/ScriptBehaviorComponent.h"
#include "Ers/SubModel/TypeInfo.h"

#include <type_traits>

// Forward declaration for Serializer
namespace Ers
{
    class Serializer;
}

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

    // Custom serialization callback for DataComponents with Serialization methods
    template <typename T> static void DataComponentSerializationCallback(void* componentHandle, void* serializerHandle)
    {
        T* component          = static_cast<T*>(componentHandle);
        Serializer serializer = Serializer(serializerHandle);
        component->Serialization(serializer);
    }

    template <typename T> static void RegisterGlobalComponentType(TypeInfo* typeInfo)
    {
        assert(!IsComponentTypeGloballyRegistered<T>());

        if constexpr (std::is_base_of<ScriptBehaviorComponent, T>::value)
        {
            RegisterGlobalScriptBehavior<T>();
            return;
        }

        const char* name = typeInfo ? typeInfo->GetName() : typeid(T).name();
        size_t size      = sizeof(T);

        // Determine if this DataComponent has a custom Serialization method
        // Custom serialization takes precedence over TypeInfo when present
        void* customSerialize = nullptr;
        if constexpr (std::is_base_of<DataComponent, T>::value && Serializer::HasCustomSerialization<T>)
        {
            // Cast function pointer to void* for API compatibility
            customSerialize = reinterpret_cast<void*>(DataComponentSerializationCallback<T>);
        }

        // When custom serialization is present, pass nullptr for typeInfo to ensure it takes precedence
        TypeInfo* finalTypeInfo = customSerialize ? nullptr : typeInfo;

        ComponentID id = ersAPIFunctionPointers.ERS_GlobalComponentRegistry_RegisterComponent(name, size, finalTypeInfo, customSerialize);
        TypeToComponentID<T>::ComponentTypeID = id;
    }

} // namespace Ers
