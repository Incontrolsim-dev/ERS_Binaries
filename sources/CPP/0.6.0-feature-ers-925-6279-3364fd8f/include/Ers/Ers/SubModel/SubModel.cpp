#include "SubModel.h"
#include "Ers/Api.h"

#include "Ers/Model/Simulator/Simulator.h"

namespace Ers
{
    void* SubModel::Data()
    {
        return this;
    }

    const void* const SubModel::Data() const
    {
        return this;
    }

    SubModelSignals& SubModel::Events()
    {
        return *static_cast<SubModelSignals*>(Data());
    }

    Entity SubModel::CreateEntity()
    {
        return ersAPIFunctionPointers.ERS_SubModel_Entity_Create(Data());
    }

    Entity SubModel::CreateEntity(std::string_view name)
    {
        return ersAPIFunctionPointers.ERS_SubModel_Entity_Create_Name(Data(), name.data());
    }

    Entity SubModel::CreateEntity(EntityID parentEntity)
    {
        return ersAPIFunctionPointers.ERS_SubModel_Entity_Create_Name_Parent(Data(), nullptr, parentEntity);
    }

    Entity SubModel::CreateEntity(EntityID parentEntity, std::string_view name)
    {
        const char* nameData = name.empty() ? nullptr : name.data();
        return ersAPIFunctionPointers.ERS_SubModel_Entity_Create_Name_Parent(Data(), nameData, parentEntity);
    }

    bool SubModel::EntityExists(Entity entity) const
    {
        return ersAPIFunctionPointers.ERS_SubModel_Entity_Exists(Data(), entity);
    }

    void SubModel::DestroyEntity(Entity entity)
    {
        ersAPIFunctionPointers.ERS_SubModel_Entity_Destroy(Data(), entity);
    }

    void SubModel::UpdateParentOnEntity(Entity entity, Entity parent)
    {
        ersAPIFunctionPointers.ERS_SubModel_Entity_Relation_Update_Parent(Data(), entity, parent.Id);
    }

    /// @brief Finds the entity with given entity name among the entities associated with the given submodel instance and return its
    /// EntityID. If no Entity is found with the given name InvalidEntity 0 is returned.
    /// @param submodelInstance The given instance of the SubModel with the entities to find.
    /// @param entityName The given name of the entity to find.
    /// @return Returns the EntityID of the found entity.
    Entity SubModel::FindEntity(const std::string_view& entityName)
    {
        return ersAPIFunctionPointers.ERS_SubModel_FindEntity(Data(), entityName.data());
    }

    SubModel& GetSubModel()
    {
        return *static_cast<SubModel*>(ersAPIFunctionPointers.ERS_ThreadLocal_GetSubModel());
    }

    SubModel* GetSubModelOrNull()
    {
        return static_cast<SubModel*>(ersAPIFunctionPointers.ERS_ThreadLocal_GetSubModelOrNull());
    }

    Ers::Simulator SubModel::GetSimulator()
    {
        return Ers::Simulator(ersAPIFunctionPointers.ERS_SubModel_GetSimulator(Data()));
    }

    SentEntity SubModel::SendEntity(uint32_t simulatorId, Entity entity)
    {
        SentEntity sent = {ersAPIFunctionPointers.ERS_SubModel_SendEntityTo(Data(), simulatorId, entity)};
        return sent;
    }

    Entity SubModel::ReceiveEntity(uint32_t simulatorId, SentEntity sent)
    {
        Entity received = ersAPIFunctionPointers.ERS_SubModel_ReceiveEntityFrom(Data(), simulatorId, sent.id);
        return received;
    }

    SubModelRandomProperties& SubModel::GetRandomProperties()
    {
        return *static_cast<SubModelRandomProperties*>(Data());
    }

    EntityID SubModel::RootEntityID() const
    {
        return ersAPIFunctionPointers.ERS_SubModel_RootEntityID(Data());
    }

    void SubModel::CreateInterpreter()
    {
        ersAPIFunctionPointers.ERS_SubModel_CreateInterpreter(Data());
    }

    void SubModel::RunSimpleString(const std::string& code)
    {
        ersAPIFunctionPointers.ERS_SubModel_RunSimpleString(Data(), code.c_str());
    }

    void SubModel::LoadModuleFromFile(const std::string& filePath)
    {
        ersAPIFunctionPointers.ERS_SubModel_LoadModuleFromFile(Data(), filePath.c_str());
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
        return ersAPIFunctionPointers.ERS_SubModel_GetModelPrecision(Data());
    }

    SimulationTime SubModel::ApplyModelPrecision(SimulationTime simTime)
    {
        return simTime * ersAPIFunctionPointers.ERS_SubModel_GetModelPrecision(Data());
    }
} // namespace Ers
