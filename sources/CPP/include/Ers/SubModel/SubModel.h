#pragma once

#include <string>
#include <string_view>
#include <tuple>

#include "Ers/Utility/Util.h"

#include "CoreComponent.h"
#include "Event/SubModelSignals.h"
#include "ScriptBehaviorComponent.h"

#include "Ers/Utility/HelperFunctions.h"

#include "Entity.h"
#include "SubModelRandomProperties.h"
#include "View.h"

#include "Ers/SubModel/GlobalSubmodelContext.h"

namespace Ers
{
    class Simulator; // Forward declaration
}

namespace Ers
{

    // Wrapper for sent entities. Entity ids in submodel pipes.
    struct SentEntity
    {
        EntityID id{Ers::Entity::InvalidEntity};
    };

    struct SubModel; // Forward declaration

    SubModel& GetSubModel();
    SubModel* GetSubModelOrNull();

    struct SubModel
    {
      public:
        SubModel()                           = delete;
        SubModel(SubModel&&)                 = delete;
        SubModel(const SubModel&)            = delete;
        SubModel& operator=(const SubModel&) = delete;
        SubModel& operator=(SubModel&&)      = delete;
        ~SubModel()                          = delete;

        [[nodiscard]] Entity CreateEntity();
        [[nodiscard]] Entity CreateEntity(std::string_view name);
        [[nodiscard]] Entity CreateEntity(EntityID parentEntity);
        [[nodiscard]] Entity CreateEntity(EntityID parentEntity, std::string_view name);

        /// @brief Checks if the given entity exists
        /// @param entity
        /// @return
        [[nodiscard]] bool EntityExists(Entity entity) const;

        /// @brief Destroys an entity and all of its children recursively.
        /// @param entity
        void DestroyEntity(Entity entity);

        /// @brief Modify the parent of an entity
        /// @param entity
        /// @param parent
        void UpdateParentOnEntity(Entity entity, Entity parent);

        Entity FindEntity(const std::string_view& entityName);

        template <typename T> T& AddSubModelContext();

        template <typename T> T& GetSubModelContext();

        /// @brief Gets component from entity.
        /// @tparam T Type of component
        /// @param entity
        /// @return T=component pointer reference
        template <typename T> [[nodiscard]] T* GetComponent(Entity entity);

        /// @brief Checks if the component exists on the entity
        /// @tparam T Type of component
        /// @param entity
        /// @return
        template <typename T> [[nodiscard]] bool HasComponent(Entity entity);

        /// @brief Sent meta data about component to core to setup support.
        /// @tparam T Type of component
        template <typename T> void AddComponentType();

        /// @brief Add a component of provided type to an entity
        /// @tparam T Type of component
        /// @param entity
        /// @return T=component pointer reference
        template <typename T> T* AddComponent(Entity entity);

        void CreateInterpreter();
        void RunSimpleString(const std::string& code);
        void LoadModuleFromFile(const std::string& filePath);

        /// @brief Remove a component of type T from the entity
        /// @tparam T Data component or Core component
        /// @param entity
        template <typename T> void RemoveComponent(Entity entity);

        template <typename... IncludedTypes, typename... Excluded> View<IncludedTypes...> GetView(ExcludedTypes<Excluded...> excluded_ = {})
        {
            return View<IncludedTypes...>(this, GetComponentArray<Excluded...>().data(), GetComponentArray<Excluded...>().size());
        }

        SubModelRandomProperties& GetRandomProperties();

        void* Data();
        const void* const Data() const;

        SubModelSignals& Events();

        Ers::Simulator GetSimulator();

        SentEntity SendEntity(uint32_t simulatorId, Entity entity);
        Entity ReceiveEntity(uint32_t simulatorId, SentEntity entity);

        EntityID RootEntityID() const;

        void ResetRandomGenerator();
        void SetRandomGeneratorSeed(size_t seed);
        double SampleRandomGenerator();

        uint64_t GetModelPrecision();
        SimulationTime ApplyModelPrecision(SimulationTime simTime);
    };

    /// @brief Get a component from an entity
    /// @tparam T
    /// @param entity
    /// @return
    template <class T> T* Entity::GetComponent() const
    {
        auto& submodel = Ers::GetSubModel();

        // Ensure that the type has already been added. This step only exists for user convenience, and adds some overhead
        submodel.AddComponentType<T>();

        return submodel.GetComponent<T>(Id);
    }

    template <class T> [[nodiscard]] bool Entity::HasComponent() const
    {
        auto& submodel = Ers::GetSubModel();

        // Ensure that the type has already been added. This step only exists for user convenience, and adds some overhead
        submodel.AddComponentType<T>();

        return submodel.HasComponent<T>(Id);
    }

    template <typename T> T* SubModel::GetComponent(Entity entity)
    {
        uint32_t componentType = GetComponentTypeID<T>();
        if constexpr (IsScriptBehavior<T>())
        {
            void* scriptBehaviorPtr = ersAPIFunctionPointers.ERS_SubModel_GetScriptBehavior(this, entity, componentType);
            auto* sb                = static_cast<T*>(scriptBehaviorPtr);
            sb->ConnectedEntity     = entity;
            return sb;
        }
        return static_cast<T*>(ersAPIFunctionPointers.ERS_SubModel_GetComponent(this, entity, componentType));
    }

    template <typename T> bool SubModel::HasComponent(Entity entity)
    {
        uint32_t componentType = GetComponentTypeID<T>();
        return ersAPIFunctionPointers.ERS_SubModel_HasComponent(this, entity, componentType);
    }

    template <typename T> void SubModel::AddComponentType()
    {
        if (!IsComponentTypeGloballyRegistered<T>())
        {
            RegisterGlobalComponentType<T>();
        }

        uint32_t componentType = GetComponentTypeID<T>();
        return ersAPIFunctionPointers.ERS_SubModel_AddComponentType(this, componentType);
    }

    template <typename T> T* SubModel::AddComponent(Entity entity)
    {
        uint32_t componentType = GetComponentTypeID<T>();

        if constexpr (IsScriptBehavior<T>())
        {
            T* scriptBehavior               = new T();
            scriptBehavior->ConnectedEntity = entity;
            ersAPIFunctionPointers.ERS_SubModel_AddScriptBehavior(this, entity, componentType, scriptBehavior);
            return scriptBehavior;
        }

        void* componentPtr = ersAPIFunctionPointers.ERS_SubModel_AddDataComponent(this, entity, componentType);

        // Constructor is also called for core components but this does not matter since they are empty.
        T* component = new (componentPtr) T();

        return component;
    }

    template <typename T> void SubModel::RemoveComponent(Entity entity)
    {
        ComponentID componentType = GetComponentTypeID<T>();
        if constexpr (IsScriptBehavior<T>())
        {
            auto* script = static_cast<ScriptBehaviorComponent*>(
                ersAPIFunctionPointers.ERS_SubModel_RemoveScriptBehavior(this, entity, componentType));
            delete script;
            return;
        }
        else
        {
        }
        return ersAPIFunctionPointers.ERS_SubModel_RemoveDataComponent(this, entity, componentType);
    }

    template <class T> T* Entity::AddComponent() const
    {
        auto& submodel = Ers::GetSubModel();

        // Ensure that the type has already been added. This step only exists for user convenience, and adds a lot of overhead
        submodel.AddComponentType<T>();

        return submodel.AddComponent<T>(Id);
    }

    template <class T> void Entity::RemoveComponent() const
    {
        auto& submodel = Ers::GetSubModel();

        // Ensure that the type has already been added. This step only exists for user convenience, and adds a lot of overhead
        submodel.AddComponentType<T>();
        return submodel.RemoveComponent<T>(Id);
    }

    template <typename T> T& SubModel::AddSubModelContext()
    {
        // Ensure it is registered
        RegisterSubModelContextTypeIndex<T>();

        T* value = new T();
        ersAPIFunctionPointers.ERS_SubModel_AddSubModelContext(
            Data(), GetSubModelContextTypeIndex<T>(), typeid(T).name(), value, [](void* data) { delete static_cast<T*>(data); });
        return *value;
    }

    template <typename T> T& SubModel::GetSubModelContext()
    {
        void* ptr = ersAPIFunctionPointers.ERS_SubModel_GetContext(Data(), GetSubModelContextTypeIndex<T>());
        T* value  = static_cast<T*>(ptr);
        return *value;
    }
} // namespace Ers
