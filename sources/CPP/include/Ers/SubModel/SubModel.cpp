#include "SubModel.h"
#include "Ers/Api.h"

#include "Ers/Model/Simulator/Simulator.h"

namespace Ers
{
    void* SubModel::CorePtr()
    {
        return this;
    }

    const void* const SubModel::CorePtr() const
    {
        return this;
    }

    Entity SubModel::CreateEntity()
    {
        return Ers::Engine::ERS_SubModel_Entity_Create(CorePtr());
    }

    Entity SubModel::CreateEntity(std::string_view name)
    {
        return Ers::Engine::ERS_SubModel_Entity_Create_Name(CorePtr(), name.data());
    }

    Entity SubModel::CreateEntity(EntityID parentEntity)
    {
        return Ers::Engine::ERS_SubModel_Entity_Create_Name_Parent(CorePtr(), nullptr, parentEntity);
    }

    Entity SubModel::CreateEntity(EntityID parentEntity, std::string_view name)
    {
        const char* nameData = name.empty() ? nullptr : name.data();
        return Ers::Engine::ERS_SubModel_Entity_Create_Name_Parent(CorePtr(), nameData, parentEntity);
    }

    bool SubModel::EntityExists(Entity entity) const
    {
        return Ers::Engine::ERS_SubModel_Entity_Exists(CorePtr(), entity);
    }

    void SubModel::DestroyEntity(Entity entity)
    {
        Ers::Engine::ERS_SubModel_Entity_Destroy(CorePtr(), entity);
    }

    void SubModel::UpdateParentOnEntity(Entity entity, Entity parent)
    {
        Ers::Engine::ERS_SubModel_Entity_Relation_Update_Parent(CorePtr(), entity, parent.Id);
    }

    /// @brief Finds the entity with given entity name among the entities associated with the given submodel instance and return its
    /// EntityID. If no Entity is found with the given name InvalidEntity 0 is returned.
    /// @param submodelInstance The given instance of the SubModel with the entities to find.
    /// @param entityName The given name of the entity to find.
    /// @return Returns the EntityID of the found entity.
    Entity SubModel::FindEntity(const std::string_view& entityName)
    {
        return Ers::Engine::ERS_SubModel_FindEntity(CorePtr(), entityName.data());
    }

    Entity SubModel::FindEntity(const std::string_view& entityName, Entity parentEntity)
    {
        return Ers::Engine::ERS_SubModel_FindEntity_Parent(CorePtr(), entityName.data(), parentEntity);
    }

    SubModel& SubModel::Get()
    {
        return *static_cast<SubModel*>(Ers::Engine::ERS_ThreadLocal_GetSubModel());
    }

    SubModel* GetSubModelOrNull()
    {
        return static_cast<SubModel*>(Ers::Engine::ERS_ThreadLocal_GetSubModelOrNull());
    }

    Ers::Simulator SubModel::GetSimulator()
    {
        return Ers::Simulator(Ers::Engine::ERS_SubModel_GetSimulator(CorePtr()));
    }

    SentEntity SubModel::SendEntity(uint32_t simulatorId, Entity entity)
    {
        SentEntity sent = {Ers::Engine::ERS_SubModel_SendEntityTo(CorePtr(), simulatorId, entity)};
        return sent;
    }

    Entity SubModel::ReceiveEntity(uint32_t simulatorId, SentEntity sent)
    {
        Entity received = Ers::Engine::ERS_SubModel_ReceiveEntityFrom(CorePtr(), simulatorId, sent.id);
        return received;
    }

    SubModelRandomProperties& SubModel::GetRandomProperties()
    {
        return *static_cast<SubModelRandomProperties*>(CorePtr());
    }

    EntityID SubModel::RootEntityID() const
    {
        return Ers::Engine::ERS_SubModel_RootEntityID(CorePtr());
    }

    void SubModel::ResetRandomGenerator()
    {
        GetRandomProperties().GetRandomNumberGenerator().Reset();
    }

    void SubModel::SetRandomGeneratorSeed(size_t seed)
    {
        GetRandomProperties().GetRandomNumberGenerator().SetSeed(seed);
    }

    double SubModel::SampleRandomGenerator()
    {
        return GetRandomProperties().GetRandomNumberGenerator().Sample();
    }

    uint64_t SubModel::GetModelPrecision()
    {
        return Ers::Engine::ERS_SubModel_GetModelPrecision(CorePtr());
    }

    SimulationTime SubModel::ApplyModelPrecision(SimulationTime simTime)
    {
        return simTime * Ers::Engine::ERS_SubModel_GetModelPrecision(CorePtr());
    }
} // namespace Ers
