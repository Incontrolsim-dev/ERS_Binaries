#ifndef ERS_API_FUNCTIONS_DEFINITION
#define ERS_API_FUNCTIONS_DEFINITION

#define ERS_API_FUNCTION_HEADER_MAJOR_VERSION 0
#define ERS_API_FUNCTION_HEADER_MINOR_VERSION 0

#include <stddef.h>

#include <stdint.h>

#define ERS_N_FUNCTIONS 529

// Temporary typedef until we found a good place for shared information.
typedef uint64_t EntityID; typedef uint64_t SimulationTime;

typedef void* (*ERS_Debugger_CreateSignature)(void* modelContainerPtr);
typedef void (*ERS_Debugger_DestroySignature)(void* ptr);
typedef bool (*ERS_Debugger_WantsRestartSignature)(void* ptr);
typedef bool (*ERS_Debugger_ShowBackgroundGridSignature)(void* ptr);
typedef void (*ERS_Debugger_SetModelContainerSignature)(void* ptr, void* modelContainerPtr);
typedef void* (*ERS_Debugger_GetRenderContextSignature)(void* ptr);
typedef bool (*ERS_Debugger_Is3DModeSignature)(void* ptr);
typedef void* (*ERS_Debugger_GetSelectedSimulatorSignature)(void* ptr);
typedef EntityID (*ERS_Debugger_GetSelectedEntitySignature)(void* ptr);
typedef bool (*ERS_Debugger_UpdateSignature)(void* ptr);
typedef void* (*ERS_Platform_CreateSignature)();
typedef void (*ERS_Platform_DestroySignature)(void* ptr);
typedef void (*ERS_Platform_BeginFrameSignature)(void* ptr);
typedef void (*ERS_Platform_EndFrameSignature)(void* ptr);
typedef bool (*ERS_Platform_WantsCloseSignature)(void* ptr);
typedef void (*ERS_RunWithProgressBarSignature)();
typedef void (*ERS_SetBindingTypeSignature)(const char* bindingType);
typedef void (*ERS_License_ForceOnlineFetchSignature)();
typedef void (*ERS_InitializeSignature)();
typedef void (*ERS_UninitializeSignature)();
typedef uint32_t (*ERS_GetMajorVersionSignature)();
typedef uint32_t (*ERS_GetMinorVersionSignature)();
typedef uint32_t (*ERS_GetPatchVersionSignature)();
typedef bool (*ERS_IsDebugBuildSignature)();
typedef bool (*ERS_License_CheckSignature)();
typedef void (*ERS_License_ActivateSignature)(int licenseType);
typedef void (*ERS_License_DeactivateSignature)();
typedef uint32_t (*ERS_License_Info_DaysRemainingSignature)();
typedef int (*ERS_License_Info_LicenseTypeSignature)();
typedef bool (*ERS_License_HasFeatureSignature)(const char* featureCode);
typedef int (*ERS_License_GetLimits_MaxJobSystemCoresSignature)();
typedef int (*ERS_License_GetLimits_MaxComponentTypesSignature)();
typedef char* (*ERS_License_EditionNameSignature)();
typedef void (*ERS_Logger_TraceSignature)(const char* message);
typedef void (*ERS_Logger_DebugSignature)(const char* message);
typedef void (*ERS_Logger_WarningSignature)(const char* message);
typedef void (*ERS_Logger_InfoSignature)(const char* message);
typedef void (*ERS_Logger_ErrorSignature)(const char* message);
typedef void (*ERS_Logger_CriticalSignature)(const char* message);
typedef void (*ERS_Logger_SetLogLevelSignature)(int logLevel);
typedef void (*ERS_Logger_AddCallbackSignature)(void(*logCallback)(int level, const char* message, void* callbackData), void* callbackData);
typedef char* (*ERS_Settings_GetSettingSignature)(const char* section, const char* message, const char* defaultValue);
typedef void (*ERS_Settings_SetSettingSignature)(const char* section, const char* message, const char* value);
typedef bool (*ERS_VirtualFileSystem_MountDirectorySignature)(const char* path, const char* directoryName);
typedef bool (*ERS_Serializer_IsWritingSignature)(void* serializerHandle);
typedef void (*ERS_Serializer_SerializeUInt64Signature)(void* serializerHandle, const char* key, uint64_t* value);
typedef void (*ERS_Serializer_SerializeInt64Signature)(void* serializerHandle, const char* key, int64_t* value);
typedef void (*ERS_Serializer_SerializeUInt32Signature)(void* serializerHandle, const char* key, uint32_t* value);
typedef void (*ERS_Serializer_SerializeInt32Signature)(void* serializerHandle, const char* key, int32_t* value);
typedef void (*ERS_Serializer_SerializeDoubleSignature)(void* serializerHandle, const char* key, double* value);
typedef void (*ERS_Serializer_SerializeBoolSignature)(void* serializerHandle, const char* key, bool* value);
typedef void (*ERS_Serializer_SerializeFloatSignature)(void* serializerHandle, const char* key, float* value);
typedef void (*ERS_Serializer_SerializeStringSignature)(void* serializerHandle, const char* key, char** value, int* length);
typedef void (*ERS_Serializer_PushObjectSignature)(void* serializerHandle, const char* key);
typedef void (*ERS_Serializer_PopObjectSignature)(void* serializerHandle);
typedef void (*ERS_Serializer_SetObjectSignature)(void* serializerHandle, int index);
typedef void (*ERS_Serializer_PushArraySignature)(void* serializerHandle, const char* key, int* size);
typedef void (*ERS_Serializer_PopArraySignature)(void* serializerHandle);
typedef int (*ERS_Serializer_GetArraySizeSignature)(void* serializerHandle);
typedef void (*ERS_Serializer_SaveToFolderSignature)(void* modelContainerInstance, const char* folderPath);
typedef void* (*ERS_Serializer_LoadFromFolderSignature)(const char* folderPath);
typedef void (*ERS_Serializer_SaveToArchiveSignature)(void* modelContainerInstance, const char* archivePath, int compressionLevel);
typedef void* (*ERS_Serializer_LoadFromArchiveSignature)(const char* archivePath, bool useCache);
typedef void (*ERS_Serializer_ClearArchiveCacheSignature)(const char* archivePath);
typedef void (*ERS_Serializer_SerializeValueUInt64Signature)(void* serializerHandle, size_t index, uint64_t* value);
typedef void (*ERS_Serializer_SerializeValueInt64Signature)(void* serializerHandle, size_t index, int64_t* value);
typedef void (*ERS_Serializer_SerializeValueUInt32Signature)(void* serializerHandle, size_t index, uint32_t* value);
typedef void (*ERS_Serializer_SerializeValueInt32Signature)(void* serializerHandle, size_t index, int32_t* value);
typedef void (*ERS_Serializer_SerializeValueDoubleSignature)(void* serializerHandle, size_t index, double* value);
typedef void (*ERS_Serializer_SerializeValueBoolSignature)(void* serializerHandle, size_t index, bool* value);
typedef void (*ERS_Serializer_SerializeValueFloatSignature)(void* serializerHandle, size_t index, float* value);
typedef void (*ERS_Serializer_SerializeValueStringSignature)(void* serializerHandle, size_t index, char** value, int* length);
typedef void (*ERS_Serializer_PushArrayElementSignature)(void* serializerHandle, size_t index, int* size);
typedef void (*ERS_Serializer_PushObjectElementSignature)(void* serializerHandle, size_t index);
typedef void (*ERS_SubModel_CreateInterpreterSignature)(void* subModelHandle);
typedef void (*ERS_SubModel_RunSimpleStringSignature)(void* subModelHandle, const char* code);
typedef void (*ERS_SubModel_LoadPythonModuleFromFileSignature)(void* subModelHandle, const char* filePath);
typedef void (*ERS_SubModel_LoadPythonPackageSignature)(void* subModelHandle, const char* packageFolderPath);
typedef void (*ERS_SubModel_AddInterpreterScriptComponentTypeSignature)(void* subModelHandle);
typedef void* (*ERS_SubModel_AddInterpreterScriptComponentSignature)(void* subModelHandle, EntityID entity);
typedef void* (*ERS_SubModel_GetInterpreterScriptComponentSignature)(void* subModelHandle, EntityID entity);
typedef bool (*ERS_SubModel_HasInterpreterScriptComponentSignature)(void* subModelHandle, EntityID entity);
typedef void (*ERS_SubModel_BeginInterpreterRenderContextSignature)(void* subModelHandle, void* renderContextHandle);
typedef void (*ERS_SubModel_EndInterpreterRenderContextSignature)(void* subModelHandle);
typedef void* (*ERS_SubModel_GetInterpreterRenderContextSignature)(void* subModelHandle);
typedef void (*ERS_SubModel_PrintInterpreterGCStatsSignature)(void* subModelHandle);
typedef void (*ERS_Interpreter_RegisterFunctionSignature)(const char* functionName, void* userData, void*(*callback)(void* userData, void* interpreterArgs), char* docs);
typedef const char* (*ERS_InterpreterArgs_GetStringArgumentSignature)(void* interpreterArgsHandle, int index);
typedef double (*ERS_InterpreterArgs_GetDoubleArgumentSignature)(void* interpreterArgsHandle, int index);
typedef EntityID (*ERS_InterpreterArgs_GetEntityArgumentSignature)(void* interpreterArgsHandle, int index);
typedef uint64_t (*ERS_InterpreterArgs_GetUInt64ArgumentSignature)(void* interpreterArgsHandle, int index);
typedef bool (*ERS_InterpreterArgs_GetBoolArgumentSignature)(void* interpreterArgsHandle, int index);
typedef double (*ERS_InterpreterArgs_GetArgCountSignature)(void* interpreterArgsHandle);
typedef void* (*ERS_InterpreterArgs_CreateSignature)(int sz);
typedef void (*ERS_InterpreterArgs_DestructSignature)(void* interpreterArgsHandle);
typedef bool (*ERS_InterpreterArgs_HasAttributeSignature)(void* interpreterArgsHandle, void* interpreterObject, const char* name);
typedef void* (*ERS_InterpreterArgs_DynamicInvokeSignature)(void* interpreterArgsHandle, void* interpreterObject, const char* name);
typedef void (*ERS_InterpreterArgs_SetArgumentSignature)(void* interpreterArgsHandle, int index, void* value);
typedef bool* (*ERS_InterpreterComponent_UpdateEnabledSignature)(void* instance);
typedef bool* (*ERS_InterpreterComponent_Render2DEnabledSignature)(void* instance);
typedef void* (*ERS_InterpreterVariable_NoneSignature)();
typedef void* (*ERS_InterpreterVariable_CreateBoolSignature)(bool value);
typedef void* (*ERS_InterpreterVariable_CreateUInt64Signature)(uint64_t value);
typedef void* (*ERS_InterpreterVariable_CreateStringSignature)(const char* value);
typedef void* (*ERS_InterpreterVariable_CreateDoubleSignature)(double value);
typedef void* (*ERS_InterpreterVariable_CreateEntitySignature)(EntityID entityId);
typedef int (*ERS_PathSegment_GetTypeSignature)(void* instance);
typedef float (*ERS_PathSegment_GetFromXSignature)(void* instance);
typedef float (*ERS_PathSegment_GetFromYSignature)(void* instance);
typedef float (*ERS_PathSegment_GetFromZSignature)(void* instance);
typedef float (*ERS_PathSegment_GetToXSignature)(void* instance);
typedef float (*ERS_PathSegment_GetToYSignature)(void* instance);
typedef float (*ERS_PathSegment_GetToZSignature)(void* instance);
typedef float (*ERS_PathSegment_GetCenterXSignature)(void* instance);
typedef float (*ERS_PathSegment_GetCenterYSignature)(void* instance);
typedef float (*ERS_PathSegment_GetCenterZSignature)(void* instance);
typedef float (*ERS_PathSegment_GetRadiusSignature)(void* instance);
typedef float (*ERS_PathSegment_GetBeginAngleSignature)(void* instance);
typedef float (*ERS_PathSegment_GetEndAngleSignature)(void* instance);
typedef float (*ERS_PathSegment_GetEndZSignature)(void* instance);
typedef void (*ERS_PathSegment_GetPointAlongPathSignature)(void* instance, float t, float* vec3out);
typedef void (*ERS_PathSegment_GetRotationAlongPathSignature)(void* instance, float t, float* vec3out);
typedef void* (*ERS_Random_Generator_MersenneTwister_CreateSignature)();
typedef void* (*ERS_Random_Generator_WichmannHill_CreateSignature)();
typedef void (*ERS_Random_Generator_DestroySignature)(void* generator);
typedef void (*ERS_Random_Generator_Set_SeedSignature)(void* generator, size_t seed);
typedef double (*ERS_Random_Generator_SampleSignature)(void* generator);
typedef void (*ERS_Random_Generator_ResetSignature)(void* generator);
typedef int (*ERS_Random_Generator_GetTypeSignature)(void* generator);
typedef void (*ERS_Profiler_StartSessionSignature)();
typedef void (*ERS_Profiler_PrintResultsSignature)();
typedef void (*ERS_STRING_DISPOSESignature)(void* str);
typedef void* (*ERS_ThreadLocal_GetSubModelSignature)();
typedef void* (*ERS_ThreadLocal_GetSubModelOrNullSignature)();
typedef bool (*ERS_ThreadLocal_InsideSubModelSignature)();
typedef void (*ERS_ThreadLocal_EnterSubModelSignature)(void* submodel);
typedef void (*ERS_ThreadLocal_ExitSubModelSignature)();
typedef void* (*ERS_ThreadLocal_GetCurrentSyncEventSignature)();
typedef bool (*ERS_ThreadLocal_IsInsideSyncEventSignature)();
typedef int32_t (*ERS_ThreadLocal_GetSyncEventTargetSignature)();
typedef int32_t (*ERS_ThreadLocal_GetSyncEventSenderSignature)();
typedef void* (*ERS_ModelContainer_CreateModelContainerSignature)();
typedef void (*ERS_ModelContainer_ReleaseSignature)(void* instance);
typedef void (*ERS_ModelContainer_IncreaseSignature)(void* instance);
typedef void (*ERS_ModelContainer_DisposeSignature)(void* instance);
typedef size_t (*ERS_ModelContainer_GetSimulatorsCountSignature)(const void* modelContainerInstance);
typedef void* (*ERS_ModelContainer_GetSimulatorSignature)(void* modelContainerInstance, int index);
typedef void* (*ERS_ModelContainer_GetSimulatorByIdSignature)(void* modelContainerInstance, const int32_t simulatorId);
typedef void* (*ERS_ModelContainer_AddSimulatorSignature)(void* modelContainerInstance, const char* tag, const uint8_t simulatorType);
typedef void (*ERS_ModelContainer_RemoveSimulatorSignature)(void* modelContainerInstance, void* coreSimulator);
typedef SimulationTime (*ERS_ModelContainer_CurrentTimeSignature)(const void* modelContainerInstance);
typedef void (*ERS_ModelContainer_Update_BlockingSignature)(void* modelContainerInstance, SimulationTime timeStep);
typedef double (*ERS_ModelContainer_SimulationSpeedOverRealtimeSignature)(void* modelContainerInstance);
typedef void (*ERS_ModelContainer_SetModelPrecisionSignature)(void* modelContainerInstance, uint64_t newPrecision);
typedef uint64_t (*ERS_ModelContainer_GetModelPrecisionSignature)(void* modelContainerInstance);
typedef bool (*ERS_ModelContainer_IsStartedSignature)(const void* modelContainerInstance);
typedef void (*ERS_ModelContainer_SetSeedSignature)(void* modelContainerInstance, size_t seed);
typedef void (*ERS_ModelContainer_GenerateRandomSeedSignature)(void* modelContainerInstance);
typedef size_t (*ERS_ModelContainer_SeedSignature)(void* modelContainerInstance);
typedef void* (*ERS_ModelContainer_FindSimulatorByIdSignature)(void* modelContainerInstance, const int32_t id);
typedef void* (*ERS_ModelContainer_FindSimulatorByTagSignature)(void* modelContainerInstance, const char* tag);
typedef void (*ERS_ModelContainer_AddSimulatorDependencySignature)(void* modelContainerInstance, void* fromSharedPtr, void* toSimulatorSharedPtr);
typedef void (*ERS_ModelContainer_RemoveSimulatorDependencySignature)(void* modelContainerInstance, void* fromSimulatorSharedPtr, void* toSimulatorSharedPtr);
typedef void (*ERS_ModelContainer_StartSignature)(void* modelContainerInstance);
typedef void* (*ERS_ModelManager_GetModelManagerSignature)();
typedef void (*ERS_ModelManager_AddModelContainerSignature)(void* modelManager, void* modelContainer, uint64_t releaseTime);
typedef void (*ERS_ModelManager_RemoveModelContainerSignature)(void* modelManager, void* modelContainer);
typedef size_t (*ERS_ModelManager_CountModelContainersSignature)(const void* modelManager);
typedef void* (*ERS_ModelManager_GetModelContainerAtSignature)(void* modelManager, const size_t index);
typedef bool (*ERS_ModelManager_HasModelContainerSignature)(const void* modelManager, const void* modelContainer);
typedef void (*ERS_ModelManager_UpdateSignature)(void* updateManager);
typedef bool (*ERS_LibraryCollection_OpenLibrarySignature)(void* instance, const char* libraryPath);
typedef bool (*ERS_LibraryCollection_IsLibraryOpenSignature)(const void* instance, const char* libraryPath);
typedef void* (*ERS_LibraryCollection_GetFunctionFromLibrarySignature)(const void* instance, const char* libraryPath, const char* functionName);
typedef void* (*ERS_LibraryCollection_GetLibraryHandleSignature)(const void* instance, const char* libraryPath);
typedef void* (*ERS_Simulator_GetLibraryCollectionSignature)(void* instance);
typedef void* (*ERS_Simulator_GetSubModelSignature)(void* instance);
typedef bool (*ERS_Simulator_IsRunTogetherSignature)(void* instance, int32_t otherSimulatorId);
typedef bool (*ERS_Simulator_IsBiDirectionalSignature)(void* instance, int32_t otherSimulatorId);
typedef char* (*ERS_Simulator_GetNameSignature)(const void* instance);
typedef uint64_t (*ERS_Simulator_GetTimeStepSignature)(const void* instance);
typedef void (*ERS_Simulator_SetTimeStepSignature)(void* instance, uint64_t newTimeStep);
typedef int32_t (*ERS_Simulator_GetIDSignature)(const void* instance);
typedef uint8_t (*ERS_Simulator_GetSimulatorTypeSignature)(const void* instance);
typedef void* (*ERS_Simulator_GetAttachedModelContainerSignature)(void* instance);
typedef size_t (*ERS_Simulator_GetDependenciesAmountSignature)(const void* instance);
typedef char* (*ERS_Simulator_GetDependencyNameSignature)(const void* instance, size_t index);
typedef void* (*ERS_Simulator_FindDependencyByIdSignature)(void* instance, int32_t simulatorId);
typedef void* (*ERS_Simulator_FindDependencyByNameSignature)(void* instance, const char* nameTag, int nameSize);
typedef void* (*ERS_Simulator_FindOutgoingDependencyByIdSignature)(void* instance, int32_t id);
typedef void* (*ERS_Simulator_FindOutgoingDependencyByNameSignature)(void* instance, const char* nameTag, int nameSize);
typedef SimulationTime (*ERS_Simulator_GetCurrentTimeSignature)(const void* simulatorInstance);
typedef uint32_t (*ERS_BasicRenderComponent_TypeIdSignature)();
typedef void* (*ERS_BasicRenderComponent_CreateCallbackSignature)();
typedef void (*ERS_BasicRenderComponent_GetColorSignature)(void* instance, float* r, float* g, float* b, float* a);
typedef void (*ERS_BasicRenderComponent_SetColorSignature)(void* instance, float r, float g, float b, float a);
typedef void (*ERS_BasicRenderComponent_SetInstancedModelSignature)(void* instance, void* instancedModel);
typedef void* (*ERS_BasicRenderComponent_GetInstancedModelSignature)(void* instance);
typedef uint32_t (*ERS_BoxComponent_TypeIdSignature)();
typedef void* (*ERS_BoxComponent_CreateCallbackSignature)();
typedef float* (*ERS_BoxComponent_Min_XSignature)(void* instance);
typedef float* (*ERS_BoxComponent_Min_YSignature)(void* instance);
typedef float* (*ERS_BoxComponent_Min_ZSignature)(void* instance);
typedef float* (*ERS_BoxComponent_Max_XSignature)(void* instance);
typedef float* (*ERS_BoxComponent_Max_YSignature)(void* instance);
typedef float* (*ERS_BoxComponent_Max_ZSignature)(void* instance);
typedef void (*ERS_BoxComponent_CenterSignature)(void* instance, float* outCenterX, float* outCenterY, float* outCenterZ);
typedef void (*ERS_BoxComponent_DimensionsSignature)(void* instance, float* outDimX, float* outDimY, float* outDimZ);
typedef bool (*ERS_BoxComponent_InCollision_Point2DSignature)(void* instance, float pointX, float pointY);
typedef bool (*ERS_BoxComponent_InCollision_RaySignature)(void* instance, float posX, float posY, float posZ, float dirX, float dirY, float dirZ);
typedef uint32_t (*ERS_ChannelComponent_TypeIdSignature)();
typedef void* (*ERS_ChannelComponent_CreateCallbackSignature)();
typedef void (*ERS_ChannelComponent_RegisterTypeSignature)(void* submodelInstance);
typedef int (*ERS_ChannelComponent_GetTypeSignature)(void* instance);
typedef EntityID (*ERS_ChannelComponent_GetConnectedToSignature)(void* instance);
typedef bool (*ERS_ChannelComponent_IsOpenSignature)(void* instance);
typedef float (*ERS_ChannelComponent_GetlongitudinalPositionSignature)(void* instance);
typedef void (*ERS_ChannelComponent_SetlongitudinalPositionSignature)(void* instance, float position);
typedef void (*ERS_Channel_SendSignature)(EntityID channelFrom, EntityID child);
typedef void (*ERS_Channel_OpenSignature)(EntityID channel);
typedef bool (*ERS_Channel_IsReadySignature)(EntityID channel);
typedef void (*ERS_Channel_ConnectSignature)(EntityID channelA, EntityID channelB);
typedef uint32_t (*ERS_GlobalComponentRegistry_RegisterScriptBehaviorSignature)(const char* name, void*(*CreateInstance)(void* handle), void* handle, void(*OnCreation)(void* scriptBehaviorInstance), void(*OnAwake)(void* scriptBehaviorInstance), void(*OnStart)(void* scriptBehaviorInstance), void(*OnUpdate)(void* scriptBehaviorInstance), void(*OnLateUpdate)(void* scriptBehaviorInstance), void(*OnDestroy)(void* scriptBehaviorInstance), void(*OnEntering)(void* scriptBehaviorInstance, EntityID child), void(*OnEntered)(void* scriptBehaviorInstance, EntityID child), void(*OnExiting)(void* scriptBehaviorInstance, EntityID child), void(*OnExited)(void* scriptBehaviorInstance, EntityID child), void(*Serialization)(void* scriptBehaviorInstance, void* serializer), void(*OnSubModelMove)(void* scriptBehaviorInstance, EntityID newConnectedEntity));
typedef uint32_t (*ERS_GlobalComponentRegistry_RegisterResourceComponentSignature)(uint32_t componentIDValue, void(*OnOutputChannelReady)(void* handle, EntityID channel), void(*OnInputChannelReady)(void* handle, EntityID channel), void(*OnReceive)(void* handle, EntityID channel, EntityID child));
typedef uint32_t (*ERS_GlobalComponentRegistry_RegisterComponentSignature)(const char* name, size_t sz, void* typeInfoPtr, void* customSerialize);
typedef bool (*ERS_GlobalComponentRegistry_IsRegisteredSignature)(uint32_t componentID);
typedef uint32_t (*ERS_NameComponent_TypeIdSignature)();
typedef void* (*ERS_NameComponent_CreateCallbackSignature)();
typedef const char* (*ERS_NameComponent_GetNameSignature)(void* nameComponentPointer);
typedef void (*ERS_NameComponent_SetNameSignature)(void* nameComponentPointer, const char* newName, int newNameSize);
typedef uint32_t (*ERS_OutlineComponent_TypeIdSignature)();
typedef void* (*ERS_OutlineComponent_CreateCallbackSignature)();
typedef float* (*ERS_OutlineComponent_Center_XSignature)(void* instance);
typedef float* (*ERS_OutlineComponent_Center_YSignature)(void* instance);
typedef float* (*ERS_OutlineComponent_Center_ZSignature)(void* instance);
typedef float (*ERS_OutlineComponent_Dimensions_XSignature)(void* instance);
typedef float (*ERS_OutlineComponent_Dimensions_YSignature)(void* instance);
typedef float (*ERS_OutlineComponent_Dimensions_ZSignature)(void* instance);
typedef void (*ERS_OutlineComponent_SetDimensionsSignature)(void* instance, float dimsX, float dimsY, float dimsZ);
typedef uint32_t (*ERS_PathComponent_TypeIdSignature)();
typedef void* (*ERS_PathComponent_CreateCallbackSignature)();
typedef void* (*ERS_PathComponent_GetSegmentSignature)(void* instance, int index);
typedef int (*ERS_PathComponent_GetNumSegmentsSignature)(void* instance);
typedef void (*ERS_PathComponent_AddStraightSignature)(void* instance, float fromX, float fromY, float fromZ, float toX, float toY, float toZ);
typedef void (*ERS_PathComponent_AddHelicalSignature)(void* instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ);
typedef uint32_t (*ERS_RelationComponent_TypeIdSignature)();
typedef void (*ERS_RelationComponent_RegisterTypeSignature)(void* submodelInstance);
typedef EntityID (*ERS_RelationComponent_GetParentSignature)(void* relationComponent);
typedef EntityID (*ERS_RelationComponent_GetFirstSignature)(void* relationComponent);
typedef EntityID (*ERS_RelationComponent_GetLastSignature)(void* relationComponent);
typedef EntityID (*ERS_RelationComponent_GetPreviousSignature)(void* relationComponent);
typedef EntityID (*ERS_RelationComponent_GetNextSignature)(void* relationComponent);
typedef uint32_t (*ERS_RelationComponent_GetChildCountSignature)(void* relationComponent);
typedef uint32_t (*ERS_ResourceComponent_TypeIdSignature)();
typedef void* (*ERS_ResourceComponent_CreateCallbackSignature)();
typedef void (*ERS_ResourceComponent_RegisterTypeSignature)(void* submodelInstance);
typedef size_t (*ERS_ResourceComponent_GetNumInputChannelsSignature)(void* instance);
typedef size_t (*ERS_ResourceComponent_GetNumOutputChannelsSignature)(void* instance);
typedef EntityID (*ERS_ResourceComponent_GetInputChannelSignature)(void* instance, size_t index);
typedef EntityID (*ERS_ResourceComponent_GetOutputChannelSignature)(void* instance, size_t index);
typedef uint32_t (*ERS_TransformComponent_TypeIdSignature)();
typedef void* (*ERS_TransformComponent_CreateCallbackSignature)();
typedef void (*ERS_TransformComponent_RegisterTypeSignature)(void* submodelInstance);
typedef float (*ERS_TransformComponent_Position_XSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetPosition_XSignature)(void* instance, float x);
typedef float (*ERS_TransformComponent_Position_YSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetPosition_YSignature)(void* instance, float y);
typedef float (*ERS_TransformComponent_Position_ZSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetPosition_ZSignature)(void* instance, float z);
typedef void (*ERS_TransformComponent_SetPositionSignature)(void* instance, float x, float y, float z);
typedef float (*ERS_TransformComponent_Scale_XSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetScale_XSignature)(void* instance, float x);
typedef float (*ERS_TransformComponent_Scale_YSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetScale_YSignature)(void* instance, float y);
typedef float (*ERS_TransformComponent_Scale_ZSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetScale_ZSignature)(void* instance, float z);
typedef void (*ERS_TransformComponent_SetScaleSignature)(void* instance, float x, float y, float z);
typedef float (*ERS_TransformComponent_Rotation_XSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetRotation_XSignature)(void* instance, float x);
typedef float (*ERS_TransformComponent_Rotation_YSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetRotation_YSignature)(void* instance, float y);
typedef float (*ERS_TransformComponent_Rotation_ZSignature)(void* instance);
typedef void (*ERS_TransformComponent_SetRotation_ZSignature)(void* instance, float z);
typedef void (*ERS_TransformComponent_Rotate_XSignature)(void* instance, float angle);
typedef void (*ERS_TransformComponent_Rotate_YSignature)(void* instance, float angle);
typedef void (*ERS_TransformComponent_Rotate_ZSignature)(void* instance, float angle);
typedef void (*ERS_TransformComponent_SetRotationEulerSignature)(void* instance, float x, float y, float z);
typedef void (*ERS_TransformComponent_SetQuaternionSignature)(void* instance, float x, float y, float z, float w);
typedef float (*ERS_TransformComponent_GlobalPosition_XSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalPosition_YSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalPosition_ZSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalScale_XSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalScale_YSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalScale_ZSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalRotation_XSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalRotation_YSignature)(const void* instance);
typedef float (*ERS_TransformComponent_GlobalRotation_ZSignature)(const void* instance);
typedef EntityID (*ERS_Entity_InvalidSignature)();
typedef EntityID (*ERS_Entity_GetParentSignature)(EntityID currentEntity);
typedef uint64_t (*ERS_Entity_GetChildCountSignature)(EntityID currentEntity);
typedef EntityID (*ERS_Entity_GetFirstChildSignature)(EntityID currentEntity);
typedef EntityID (*ERS_Entity_GetLastChildSignature)(EntityID currentEntity);
typedef EntityID (*ERS_Entity_GetPreviousSiblingSignature)(EntityID currentEntity);
typedef EntityID (*ERS_Entity_GetNextSiblingSignature)(EntityID currentEntity);
typedef bool (*ERS_Entity_IsValidSignature)(EntityID currentEntity);
typedef uint64_t (*ERS_EventScheduler_ScheduleLocalEventSignature)(int priority, uint64_t delay, void* dataPtr, void(*callback)(void* data), void(*destructor)(void* data));
typedef void (*ERS_EventScheduler_CancelEventSignature)(uint64_t eventKey);
typedef void (*ERS_EventScheduler_SetPromiseSignature)(uint64_t promise, int32_t outgoingDependencyID);
typedef void* (*ERS_EventScheduler_LastScheduledSyncEventSignature)();
typedef uint64_t (*ERS_EventScheduler_GetPromiseSignature)(int32_t outgoingDependencyID);
typedef void* (*ERS_EventScheduler_ScheduleSyncEventSignature)(uint64_t delay, int32_t targetSimulatorId, uint64_t eventTypeIdentifier, void(*onSenderSideCallback)(), void(*onTargetSideCallback)());
typedef void* (*ERS_EventScheduler_SyncEvent_GetDataSignature)(uint16_t dataContextIdx, void* syncEvent);
typedef uint32_t (*ERS_EventScheduler_ExchangeSyncEventForEventIDSignature)(void* syncEvent);
typedef void (*ERS_EventScheduler_DelayEventSignature)(uint64_t key, uint64_t delayAmount);
typedef EntityID (*ERS_SubModel_Move_Entity_ToSignature)(void* targetSubModel, void* sourceSubModel, EntityID sourceEntity);
typedef EntityID (*ERS_SubModel_Entity_Create_Name_ParentSignature)(void* submodel, const char* entityName, EntityID parent);
typedef EntityID (*ERS_SubModel_Entity_CreateSignature)(void* subModelPtr);
typedef EntityID (*ERS_SubModel_Entity_Create_NameSignature)(void* subModelHandle, const char* entityName);
typedef EntityID (*ERS_SubModel_FindEntitySignature)(void* submodelInstance, const char* entityName);
typedef EntityID (*ERS_SubModel_FindEntity_ParentSignature)(void* subModelInstance, const char* entityName, EntityID root);
typedef bool (*ERS_SubModel_Entity_DestroySignature)(void* subModel, EntityID entity);
typedef bool (*ERS_SubModel_Entity_ExistsSignature)(const void* submodel, EntityID entityId);
typedef void (*ERS_SubModel_Entity_Relation_Update_ParentSignature)(void* subModelHandle, EntityID entityId, EntityID parentId);
typedef void (*ERS_SubModel_AddScriptBehaviorSignature)(void* subModelHandle, EntityID entityID, uint32_t componentID, void* managedHandle);
typedef void* (*ERS_SubModel_GetScriptBehaviorSignature)(void* subModelHandle, EntityID entityID, uint32_t componentID);
typedef void* (*ERS_SubModel_RemoveScriptBehaviorSignature)(void* subModelHandle, EntityID entity, uint32_t componentID);
typedef void* (*ERS_SubModel_GetComponentSignature)(void* subModelHandle, EntityID entity, uint32_t componentID);
typedef void* (*ERS_SubModel_AddDataComponentSignature)(void* subModelHandle, EntityID entity, uint32_t componentID);
typedef void* (*ERS_SubModel_GetSimulatorSignature)(void* subModelHandle);
typedef void (*ERS_SubModel_RemoveDataComponentSignature)(void* subModelHandle, EntityID entity, uint32_t componentID);
typedef bool (*ERS_SubModel_HasComponentSignature)(const void* subModelHandle, EntityID entity, uint32_t componentID);
typedef void (*ERS_SubModel_AddComponentTypeSignature)(void* subModelHandle, uint32_t componentID);
typedef void* (*ERS_SubModel_GetRandomPropertiesSignature)(void* subModelHandle);
typedef EntityID (*ERS_SubModel_SendEntityToSignature)(void* subModelInstance, int32_t toSimulator, EntityID entity);
typedef EntityID (*ERS_SubModel_ReceiveEntityFromSignature)(void* subModelInstance, int32_t fromSimulator, EntityID pipeEntity);
typedef EntityID (*ERS_SubModel_RootEntityIDSignature)(const void* subModelHandle);
typedef double (*ERS_SubModel_GenerateRandomDoubleSignature)(void* subModelHandle, double min, double max);
typedef uint64_t (*ERS_SubModel_GetModelPrecisionSignature)(void* subModelInstance);
typedef uint32_t (*ERS_SubModel_RegisterSubModelContextSignature)();
typedef void (*ERS_SubModel_AddSubModelContextSignature)(void* subModelHandle, uint32_t SubModelContextTypeIdx, const char* name, void* SubModelContextPtr, void(*destructor)(void* contextHandle));
typedef void* (*ERS_SubModel_GetContextSignature)(void* subModelHandle, uint32_t SubModelContextTypeIdx);
typedef void* (*ERS_SubModelRandomProperties_CreateSignature)();
typedef void (*ERS_SubModelRandomProperties_DestroySignature)(void* properties);
typedef void (*ERS_SubModelRandomProperties_SetRandomGenerator_TypeSignature)(void* submodel, int randomNumberGeneratorType);
typedef void (*ERS_SubModelRandomProperties_SetRepetitiveSignature)(void* submodel, bool value);
typedef void (*ERS_SubModelRandomProperties_SetAntitheticalSignature)(void* submodel, bool value);
typedef void (*ERS_SubModelRandomProperties_SetSeedSignature)(void* submodel, size_t seed);
typedef bool (*ERS_SubModelRandomProperties_IsRepetitiveSignature)(void* submodel);
typedef bool (*ERS_SubModelRandomProperties_IsAntitheticalSignature)(void* submodel);
typedef const size_t (*ERS_SubModelRandomProperties_GetOriginalSeedSignature)(const void* submodel);
typedef void* (*ERS_SubModelRandomProperties_GetRandomNumberGeneratorSignature)(void* submodel);
typedef void* (*ERS_TypeInfo_RegisterStructSignature)(const char* name);
typedef void (*ERS_TypeInfo_AddFieldSignature)(void* componentTypeInfoPtr, const char* name, uint32_t fieldType, size_t offset);
typedef const char* (*ERS_TypeInfo_GetNameSignature)(void* componentTypeInfoPtr);
typedef void* (*ERS_Submodel_View_CreateSignature)(void* subModelHandle, uint32_t* includedTypeIdArray_, uint32_t includedTypeArraySize, uint32_t* excludedTypeIdArray_, uint32_t excludedTypeArraySize);
typedef bool (*ERS_Submodel_View_NextSignature)(void* viewHandle);
typedef void* (*ERS_Submodel_View_GetComponentSignature)(void* viewHandle, size_t typeIndex);
typedef void** (*ERS_Submodel_View_GetComponentsSignature)(void* viewHandle);
typedef EntityID (*ERS_Submodel_View_GetEntitySignature)(void* viewHandle);
typedef void (*ERS_Submodel_View_DisposeSignature)(void* view);
typedef void (*ERS_SubModel_Events_DisconnectSignature)(void* connectionObjectPtr);
typedef void* (*ERS_SubModel_RelationEvents_OnAwakeSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnAwake_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnStartSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnStart_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnCreateSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnCreate_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnDestroySignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnDestroy_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnEnteringSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnEntering_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnEnteredSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnEntered_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnExitingSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnExiting_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void* (*ERS_SubModel_RelationEvents_OnExitedSignature)();
typedef void* (*ERS_SubModel_RelationEvents_OnExited_ConnectSignature)(void* signalHandle, void* signalFunction, void* obj);
typedef void** (*ERS_SyncEvent_GetSyncEventMetaDataSignature)(void* syncEvent);
typedef void (*ERS_SyncEvent_SetSyncEventMetaDataSignature)(void* syncEvent, void* dataPtr, uint8_t index);
typedef void (*ERS_SyncEvent_SetSyncEventNameSignature)(void* syncEvent, const char* name);
typedef uint32_t (*ERS_SyncEvent_GetSyncEventUIDSignature)(void* syncEvent);
typedef uint16_t (*ERS_SyncEvent_GetOrRegisterDataContextSignature)(void* syncEvent, uint64_t identifier, uint32_t blockSize);
typedef void* (*ERS_SyncEvent_GetDataSignature)(void* syncEvent, uint16_t dataContextIdx);
typedef void (*ERS_BasicRenderSystem_Render2DSignature)(void* subModelInstance, void* renderContextInstance);
typedef void (*ERS_BasicRenderSystem_Render3DSignature)(void* subModelInstance, void* renderContextInstance);
typedef void (*ERS_CollisionSystem_UpdateBoundingBoxesSignature)(void* subModelInstance);
typedef void (*ERS_InterpreterRenderSystem_Render2DSignature)();
typedef void (*ERS_InterpreterRenderSystem_BuildMesh3DSignature)(void* meshPtr);
typedef void (*ERS_PathAnimationSystem_UpdateSignature)(SimulationTime currentTime);
typedef void (*ERS_PathAnimationSystem_AnimateSignature)(EntityID toAnimate, SimulationTime startTime, SimulationTime endTime, float fromValue, float toValue, EntityID entityContainingPath, int pathIndex);
typedef void (*ERS_TransformSystem_UpdateGlobalsSignature)(void* subModelInstance);
typedef void (*ERS_Camera2D_UpdateTransformSignature)(void* instance, int screenWidth, int screenHeight);
typedef float* (*ERS_Camera2D_PositionXSignature)(void* instance);
typedef float* (*ERS_Camera2D_PositionYSignature)(void* instance);
typedef float* (*ERS_Camera2D_ZoomSignature)(void* instance);
typedef float (*ERS_Camera2D_SizePerPixelSignature)(void* instance);
typedef void (*ERS_Camera2D_GetWorldPosSignature)(void* instance, int screenWidth, int screenHeight, float screenPosX, float screenPosY, float* resultX, float* resultY);
typedef void* (*ERS_Camera2DController_CreateSignature)(void* camera2DPtr);
typedef void (*ERS_Camera2DController_DestroySignature)(void* coreInstance);
typedef void (*ERS_Camera2DController_ControlCameraSignature)(void* instance, int screenWidth, int screenHeight);
typedef void (*ERS_Camera2DController_SetScreenSizeSignature)(void* instance, int width, int height);
typedef void (*ERS_Camera2DController_UpdateSignature)(void* instance, float mouseX, float mouseY);
typedef void (*ERS_Camera2DController_StartDraggingSignature)(void* instance, float mouseX, float mouseY);
typedef void (*ERS_Camera2DController_StopDraggingSignature)(void* instance);
typedef void (*ERS_Camera2DController_ZoomSignature)(void* instance, float baseF, float power);
typedef float* (*ERS_Camera3D_PositionXSignature)(void* instance);
typedef float* (*ERS_Camera3D_PositionYSignature)(void* instance);
typedef float* (*ERS_Camera3D_PositionZSignature)(void* instance);
typedef float* (*ERS_Camera3D_LookAtXSignature)(void* instance);
typedef float* (*ERS_Camera3D_LookAtYSignature)(void* instance);
typedef float* (*ERS_Camera3D_LookAtZSignature)(void* instance);
typedef float* (*ERS_Camera3D_FovInTurnsSignature)(void* instance);
typedef float* (*ERS_Camera3D_ZNearSignature)(void* instance);
typedef float* (*ERS_Camera3D_ZFarSignature)(void* instance);
typedef void (*ERS_Camera3D_SetLookAtSignature)(void* instance, float x, float y, float z);
typedef void (*ERS_Camera3D_UpdateTransformSignature)(void* instance, int screenWidth, int screenHeight);
typedef void (*ERS_Camera3D_GetPickRaySignature)(void* instance, int screenWidth, int screenHeight, int screenPosX, int screenPosY, float* outPosX, float* outPosY, float* outPosZ, float* outDirX, float* outDirY, float* outDirZ);
typedef void* (*ERS_Camera3DController_CreateSignature)(void* camera3DPtr);
typedef void (*ERS_Camera3DController_DestroySignature)(void* instance);
typedef void (*ERS_Camera3DController_ControlCameraSignature)(void* instance, int screenWidth, int screenHeight, float deltaTime, float lookAtZ);
typedef void (*ERS_Camera3DController_UpdateSignature)(void* instance, float deltaTime);
typedef void (*ERS_Camera3DController_SwitchCameraModeSignature)(void* instance, int mode);
typedef int (*ERS_Camera3DController_GetCameraModeSignature)(void* instance);
typedef float* (*ERS_Camera3DController_HeadBobbingIntensitySignature)(void* instance);
typedef void* (*ERS_InputHandler_GetActionSignature)(const char* name);
typedef bool (*ERS_InputHandler_ExistsActionSignature)(const char* name);
typedef void (*ERS_InputHandler_CycleSignature)();
typedef void (*ERS_InputHandler_UpdateMousePosSignature)(int x, int y);
typedef bool* (*ERS_InputAction_TriggeredSignature)(void* instance);
typedef bool* (*ERS_InputAction_ReleasedSignature)(void* instance);
typedef float* (*ERS_InputAction_StrengthSignature)(void* instance);
typedef void* (*ERS_InstancedModel_CreateSignature)();
typedef void (*ERS_InstancedModel_ReleaseSignature)(void* instance);
typedef void (*ERS_InstancedModel_PushInstanceSignature)(void* instance, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
typedef void (*ERS_InstancedModel_SetMeshSignature)(void* instance, void* meshPtr);
typedef void (*ERS_InstancedModel_ClearSignature)(void* instance);
typedef void* (*ERS_Material_Copy_ShallowSignature)(void* instance);
typedef float* (*ERS_Material_Color_XSignature)(void* instance);
typedef float* (*ERS_Material_Color_YSignature)(void* instance);
typedef float* (*ERS_Material_Color_ZSignature)(void* instance);
typedef void* (*ERS_Mesh_CreateSignature)();
typedef void (*ERS_Mesh_ReleaseSignature)(void* instance);
typedef void (*ERS_Mesh_IncreaseSignature)(void* instance);
typedef void (*ERS_Mesh_DisposeSignature)(void* instance);
typedef void (*ERS_Mesh_SetDefaultMaterialSignature)(void* instance);
typedef void (*ERS_Mesh_ClearSignature)(void* instance);
typedef void (*ERS_Mesh_PushVertex3DSignature)(void* instance, float x, float y, float z, float nx, float ny, float nz, float u, float v, float colorR, float colorG, float colorB);
typedef void (*ERS_Mesh_PushIndexSignature)(void* instance, uint32_t index);
typedef void (*ERS_Mesh_PushQuadSignature)(void* instance, float pos0X, float pos0Y, float pos0Z, float uv0X, float uv0Y, float pos1X, float pos1Y, float pos1Z, float uv1X, float uv1Y, float pos2X, float pos2Y, float pos2Z, float uv2X, float uv2Y, float pos3X, float pos3Y, float pos3Z, float uv3X, float uv3Y, float colorR, float colorG, float colorB, float normX, float normY, float normZ);
typedef void (*ERS_Mesh_PushCubeSignature)(void* instance, float posX, float posY, float posZ, float dimsX, float dimsY, float dimsZ, float colorR, float colorG, float colorB);
typedef void (*ERS_Mesh_PushBeamSignature)(void* instance, float fromX, float fromY, float fromZ, float toX, float toY, float toZ, float upX, float upY, float upZ, float width, float height, float colorR, float colorG, float colorB);
typedef void (*ERS_Mesh_PushText3DSignature)(void* instance, void* fontInstance, const char* text, float posX, float posY, float posZ, float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float scale, uint32_t color);
typedef void (*ERS_Mesh_PushText3DAlignedSignature)(void* instance, void* fontInstance, const char* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpx, float worldUpy, float worldUpz, float scale, uint32_t color);
typedef void (*ERS_Mesh_PushTextBillboardSignature)(void* instance, void* fontInstance, const char* text, float posX, float posY, float posZ, float cameraX, float cameraY, float cameraZ, float worldUpX, float worldUpY, float worldUpZ, float scale, uint32_t color);
typedef void (*ERS_Mesh_PushText3DDefaultSignature)(void* instance, const char* text, float posX, float posY, float posZ, float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float scale, uint32_t color);
typedef void (*ERS_Mesh_PushVerticalHelicalStripSignature)(void* instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float stripHeight, float colorR, float colorG, float colorB, int segments, bool normalsInward);
typedef void (*ERS_Mesh_PushHorizontalHelicalStripSignature)(void* instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float stripLength, float colorR, float colorG, float colorB, int segments, bool normalUp);
typedef void (*ERS_Mesh_PushHelicalBeamSignature)(void* instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float beamWidth, float beamHeight, float colorR, float colorG, float colorB, int segments);
typedef void (*ERS_Mesh_PushText3DAlignedDefaultSignature)(void* instance, const char* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpx, float worldUpy, float worldUpz, float scale, uint32_t color);
typedef void (*ERS_Mesh_PushTextBillboardDefaultSignature)(void* instance, const char* text, float posX, float posY, float posZ, float cameraX, float cameraY, float cameraZ, float worldUpx, float worldUpy, float worldUpz, float scale, uint32_t color);
typedef bool (*ERS_Mesh_CreateBuffersSignature)(void* instance);
typedef void (*ERS_Mesh_DeleteBuffersSignature)(void* instance);
typedef void (*ERS_Mesh_UpdateBuffersSignature)(void* instance);
typedef void (*ERS_Mesh_DrawSignature)(void* instance, void* shaderInstance);
typedef size_t (*ERS_Mesh_GetVertexCountSignature)(void* instance);
typedef size_t (*ERS_Mesh_GetIndexCountSignature)(void* instance);
typedef bool (*ERS_Mesh_HasBuffersSignature)(void* instance);
typedef uint32_t (*ERS_Mesh_GetVAOSignature)(void* instance);
typedef void (*ERS_Mesh_TransformVertices2Signature)(void* instance, float translationX, float translationY, float translationZ, float axisX, float axisY, float axisZ, float turns, float scaleX, float scaleY, float scaleZ);
typedef void (*ERS_Mesh_TransformVerticesSignature)(void* instance, float* transform16);
typedef void (*ERS_Mesh_TransformVerticesRangeSignature)(void* instance, float* transform16, uint32_t startIdx, uint32_t endIdx);
typedef void (*ERS_Mesh_CenterAtOriginSignature)(void* instance);
typedef void (*ERS_Mesh_TranslateToFloorSignature)(void* instance);
typedef void (*ERS_Mesh_SetColorSignature)(void* instance, float colorR, float colorG, float colorB);
typedef void (*ERS_Mesh_NormalizeSignature)(void* instance);
typedef void (*ERS_Mesh_GetMaxSignature)(void* instance, float* outX, float* outY, float* outZ);
typedef void (*ERS_Mesh_GetMinSignature)(void* instance, float* outX, float* outY, float* outZ);
typedef void (*ERS_Mesh_SetTransformSignature)(void* instance, float* transform16);
typedef void (*ERS_Mesh_PushMeshSignature)(void* instance, void* otherInstance, float posX, float posY, float posZ, float axisX, float axisY, float axisZ, float turns, float scaleX, float scaleY, float scaleZ);
typedef void (*ERS_Mesh_GetTransformSignature)(void* instance, float* outTransform16);
typedef void* (*ERS_Model3D_CreateSignature)();
typedef void (*ERS_Model3D_DestroySignature)(void* model);
typedef bool (*ERS_Model3D_LoadSignature)(void* modelHandle, const char* path);
typedef int (*ERS_Model3D_GetMeshCountSignature)(void* modelHandle);
typedef void (*ERS_Model3D_SetTransformSignature)(void* modelHandle, float x, float y, float z, float xRotAxis, float yRotAxis, float zRotAxis, float turns, float xScale, float yScale, float zScale);
typedef void (*ERS_Model3D_GetTransformSignature)(void* modelHandle, float* transformOut);
typedef void* (*ERS_Model3D_GetMeshSignature)(void* modelHandle, int index);
typedef void* (*ERS_RenderContext_CreateSignature)(int screenWidth, int screenHeight);
typedef void (*ERS_RenderContext_DisposeSignature)(void* instance);
typedef void* (*ERS_RenderContext_GetCamera2DSignature)(void* instance);
typedef void (*ERS_RenderContext_SetViewportSignature)(void* instance, int width, int height);
typedef void (*ERS_RenderContext_SetBackgroundColorSignature)(void* instance, float r, float g, float b, float a);
typedef void* (*ERS_RenderContext_GetCamera3DSignature)(void* instance);
typedef void (*ERS_RenderContext_ClearScreenSignature)(void* instance);
typedef void (*ERS_RenderContext_Begin2DSignature)(void* instance);
typedef void (*ERS_RenderContext_End2DSignature)(void* instance);
typedef void (*ERS_RenderContext_Begin3DSignature)(void* instance);
typedef void (*ERS_RenderContext_End3DSignature)(void* instance);
typedef void (*ERS_RenderContext_DrawQuad2DSignature)(void* instance, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawRect2DSignature)(void* instance, float x, float y, float sizeX, float sizeY, float angle, float colorR, float colorG, float colorB, float colorA, int64_t zIndex);
typedef void (*ERS_RenderContext_DrawScreenLine2DSignature)(void* instance, float x0, float y0, float x1, float y1, float thickness, float colorR, float colorG, float colorB, float colorA, int64_t zIndex);
typedef void (*ERS_RenderContext_DrawScreenLineRect2DSignature)(void* instance, float x, float y, float sizeX, float sizeY, float angle, float thickness, float colorR, float colorG, float colorB, float colorA, int64_t zIndex);
typedef void (*ERS_RenderContext_DrawTextBillboardSignature)(void* instance, const char* text, float centerX, float centerY, float centerZ, float scale, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawText2DSignature)(void* instance, const char* text, float x, float y, float scale, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawTexture2DSignature)(void* instance, void* textureHandle, float x, float y, float width, float height, float uvMinX, float uvMinY, float uvMaxX, float uvMaxY, float angle, float r, float g, float b, float a);
typedef void (*ERS_RenderContext_DrawCube3DSignature)(void* instance, float x, float y, float z, float xRotation, float yRotation, float zRotation, float xScale, float yScale, float zScale, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawInfiniteGrid2DSignature)(void* instance, float colorR, float colorG, float colorB, float lineThickness, float armLength, float targetPixelSize);
typedef void (*ERS_RenderContext_DrawInfiniteGrid3DSignature)(void* instance, float colorR, float colorG, float colorB, float lineThickness, float targetPixelSize);
typedef void (*ERS_RenderContext_DrawText3DSignature)(void* instance, const char* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpX, float worldUpY, float worldUpZ, float scale, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_SetLightDirectionSignature)(void* instance, float x, float y, float z);
typedef void (*ERS_RenderContext_DrawLine2DSignature)(void* instance, float x0, float y0, float x1, float y1, float thickness, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawTriangle2DSignature)(void* instance, float x0, float y0, float x1, float y1, float x2, float y2, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawTriangle2D_BoxSignature)(void* instance, float centerX, float centerY, float sizeX, float sizeY, float angle, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawInstancedModel3DWithMeshSignature)(void* renderContextHandle, void* meshHandle, void* instancedModelHandle);
typedef void (*ERS_RenderContext_PresentSignature)(void* instance);
typedef void (*ERS_RenderContext_DrawInstancedModel3DSignature)(void* renderContextHandle, void* instancedModelHandle);
typedef void (*ERS_RenderContext_DrawArc2DSignature)(void* renderContextHandle, float x, float y, float radius, float width, float beginAngle, float endAngle, int segments, float colorR, float colorG, float colorB, float colorA);
typedef void (*ERS_RenderContext_DrawModel3DSignature)(void* instanceHandle, void* modelHandle);
typedef void (*ERS_RenderContext_DrawMeshSignature)(void* instance, void* meshHandle);
typedef void (*ERS_RenderContext_CalculateTextSizeSignature)(void* instance, const char* text, float scale, float* width, float* height);
typedef bool (*ERS_RenderContext_IsOpenGLInitializedSignature)();
typedef bool (*ERS_RenderContext_InitializeOpenGLSignature)(void* windowHandle, void* displayHandle);
typedef void* (*ERS_Texture_CreateSignature)();
typedef void (*ERS_Texture_LoadSignature)(void* instance, const char* path);
typedef void (*ERS_Texture_ReleaseSignature)(void* instance);
typedef void* (*ERS_Window_CreateSignature)(void* windowHandle, void* displayHandle, int screenWidth, int screenHeight);
typedef void (*ERS_Window_PresentSignature)(void* instance);
typedef void (*ERS_Window_DrawRenderContextSignature)(void* instance, void* renderContextHandle);
typedef void (*ERS_Window_DestroySignature)(void* instance);

union ErsAPIFunctionPointers {
    struct {
        ERS_Debugger_CreateSignature ERS_Debugger_Create;
        ERS_Debugger_DestroySignature ERS_Debugger_Destroy;
        ERS_Debugger_WantsRestartSignature ERS_Debugger_WantsRestart;
        ERS_Debugger_ShowBackgroundGridSignature ERS_Debugger_ShowBackgroundGrid;
        ERS_Debugger_SetModelContainerSignature ERS_Debugger_SetModelContainer;
        ERS_Debugger_GetRenderContextSignature ERS_Debugger_GetRenderContext;
        ERS_Debugger_Is3DModeSignature ERS_Debugger_Is3DMode;
        ERS_Debugger_GetSelectedSimulatorSignature ERS_Debugger_GetSelectedSimulator;
        ERS_Debugger_GetSelectedEntitySignature ERS_Debugger_GetSelectedEntity;
        ERS_Debugger_UpdateSignature ERS_Debugger_Update;
        ERS_Platform_CreateSignature ERS_Platform_Create;
        ERS_Platform_DestroySignature ERS_Platform_Destroy;
        ERS_Platform_BeginFrameSignature ERS_Platform_BeginFrame;
        ERS_Platform_EndFrameSignature ERS_Platform_EndFrame;
        ERS_Platform_WantsCloseSignature ERS_Platform_WantsClose;
        ERS_RunWithProgressBarSignature ERS_RunWithProgressBar;
        ERS_SetBindingTypeSignature ERS_SetBindingType;
        ERS_License_ForceOnlineFetchSignature ERS_License_ForceOnlineFetch;
        ERS_InitializeSignature ERS_Initialize;
        ERS_UninitializeSignature ERS_Uninitialize;
        ERS_GetMajorVersionSignature ERS_GetMajorVersion;
        ERS_GetMinorVersionSignature ERS_GetMinorVersion;
        ERS_GetPatchVersionSignature ERS_GetPatchVersion;
        ERS_IsDebugBuildSignature ERS_IsDebugBuild;
        ERS_License_CheckSignature ERS_License_Check;
        ERS_License_ActivateSignature ERS_License_Activate;
        ERS_License_DeactivateSignature ERS_License_Deactivate;
        ERS_License_Info_DaysRemainingSignature ERS_License_Info_DaysRemaining;
        ERS_License_Info_LicenseTypeSignature ERS_License_Info_LicenseType;
        ERS_License_HasFeatureSignature ERS_License_HasFeature;
        ERS_License_GetLimits_MaxJobSystemCoresSignature ERS_License_GetLimits_MaxJobSystemCores;
        ERS_License_GetLimits_MaxComponentTypesSignature ERS_License_GetLimits_MaxComponentTypes;
        ERS_License_EditionNameSignature ERS_License_EditionName;
        ERS_Logger_TraceSignature ERS_Logger_Trace;
        ERS_Logger_DebugSignature ERS_Logger_Debug;
        ERS_Logger_WarningSignature ERS_Logger_Warning;
        ERS_Logger_InfoSignature ERS_Logger_Info;
        ERS_Logger_ErrorSignature ERS_Logger_Error;
        ERS_Logger_CriticalSignature ERS_Logger_Critical;
        ERS_Logger_SetLogLevelSignature ERS_Logger_SetLogLevel;
        ERS_Logger_AddCallbackSignature ERS_Logger_AddCallback;
        ERS_Settings_GetSettingSignature ERS_Settings_GetSetting;
        ERS_Settings_SetSettingSignature ERS_Settings_SetSetting;
        ERS_VirtualFileSystem_MountDirectorySignature ERS_VirtualFileSystem_MountDirectory;
        ERS_Serializer_IsWritingSignature ERS_Serializer_IsWriting;
        ERS_Serializer_SerializeUInt64Signature ERS_Serializer_SerializeUInt64;
        ERS_Serializer_SerializeInt64Signature ERS_Serializer_SerializeInt64;
        ERS_Serializer_SerializeUInt32Signature ERS_Serializer_SerializeUInt32;
        ERS_Serializer_SerializeInt32Signature ERS_Serializer_SerializeInt32;
        ERS_Serializer_SerializeDoubleSignature ERS_Serializer_SerializeDouble;
        ERS_Serializer_SerializeBoolSignature ERS_Serializer_SerializeBool;
        ERS_Serializer_SerializeFloatSignature ERS_Serializer_SerializeFloat;
        ERS_Serializer_SerializeStringSignature ERS_Serializer_SerializeString;
        ERS_Serializer_PushObjectSignature ERS_Serializer_PushObject;
        ERS_Serializer_PopObjectSignature ERS_Serializer_PopObject;
        ERS_Serializer_SetObjectSignature ERS_Serializer_SetObject;
        ERS_Serializer_PushArraySignature ERS_Serializer_PushArray;
        ERS_Serializer_PopArraySignature ERS_Serializer_PopArray;
        ERS_Serializer_GetArraySizeSignature ERS_Serializer_GetArraySize;
        ERS_Serializer_SaveToFolderSignature ERS_Serializer_SaveToFolder;
        ERS_Serializer_LoadFromFolderSignature ERS_Serializer_LoadFromFolder;
        ERS_Serializer_SaveToArchiveSignature ERS_Serializer_SaveToArchive;
        ERS_Serializer_LoadFromArchiveSignature ERS_Serializer_LoadFromArchive;
        ERS_Serializer_ClearArchiveCacheSignature ERS_Serializer_ClearArchiveCache;
        ERS_Serializer_SerializeValueUInt64Signature ERS_Serializer_SerializeValueUInt64;
        ERS_Serializer_SerializeValueInt64Signature ERS_Serializer_SerializeValueInt64;
        ERS_Serializer_SerializeValueUInt32Signature ERS_Serializer_SerializeValueUInt32;
        ERS_Serializer_SerializeValueInt32Signature ERS_Serializer_SerializeValueInt32;
        ERS_Serializer_SerializeValueDoubleSignature ERS_Serializer_SerializeValueDouble;
        ERS_Serializer_SerializeValueBoolSignature ERS_Serializer_SerializeValueBool;
        ERS_Serializer_SerializeValueFloatSignature ERS_Serializer_SerializeValueFloat;
        ERS_Serializer_SerializeValueStringSignature ERS_Serializer_SerializeValueString;
        ERS_Serializer_PushArrayElementSignature ERS_Serializer_PushArrayElement;
        ERS_Serializer_PushObjectElementSignature ERS_Serializer_PushObjectElement;
        ERS_SubModel_CreateInterpreterSignature ERS_SubModel_CreateInterpreter;
        ERS_SubModel_RunSimpleStringSignature ERS_SubModel_RunSimpleString;
        ERS_SubModel_LoadPythonModuleFromFileSignature ERS_SubModel_LoadPythonModuleFromFile;
        ERS_SubModel_LoadPythonPackageSignature ERS_SubModel_LoadPythonPackage;
        ERS_SubModel_AddInterpreterScriptComponentTypeSignature ERS_SubModel_AddInterpreterScriptComponentType;
        ERS_SubModel_AddInterpreterScriptComponentSignature ERS_SubModel_AddInterpreterScriptComponent;
        ERS_SubModel_GetInterpreterScriptComponentSignature ERS_SubModel_GetInterpreterScriptComponent;
        ERS_SubModel_HasInterpreterScriptComponentSignature ERS_SubModel_HasInterpreterScriptComponent;
        ERS_SubModel_BeginInterpreterRenderContextSignature ERS_SubModel_BeginInterpreterRenderContext;
        ERS_SubModel_EndInterpreterRenderContextSignature ERS_SubModel_EndInterpreterRenderContext;
        ERS_SubModel_GetInterpreterRenderContextSignature ERS_SubModel_GetInterpreterRenderContext;
        ERS_SubModel_PrintInterpreterGCStatsSignature ERS_SubModel_PrintInterpreterGCStats;
        ERS_Interpreter_RegisterFunctionSignature ERS_Interpreter_RegisterFunction;
        ERS_InterpreterArgs_GetStringArgumentSignature ERS_InterpreterArgs_GetStringArgument;
        ERS_InterpreterArgs_GetDoubleArgumentSignature ERS_InterpreterArgs_GetDoubleArgument;
        ERS_InterpreterArgs_GetEntityArgumentSignature ERS_InterpreterArgs_GetEntityArgument;
        ERS_InterpreterArgs_GetUInt64ArgumentSignature ERS_InterpreterArgs_GetUInt64Argument;
        ERS_InterpreterArgs_GetBoolArgumentSignature ERS_InterpreterArgs_GetBoolArgument;
        ERS_InterpreterArgs_GetArgCountSignature ERS_InterpreterArgs_GetArgCount;
        ERS_InterpreterArgs_CreateSignature ERS_InterpreterArgs_Create;
        ERS_InterpreterArgs_DestructSignature ERS_InterpreterArgs_Destruct;
        ERS_InterpreterArgs_HasAttributeSignature ERS_InterpreterArgs_HasAttribute;
        ERS_InterpreterArgs_DynamicInvokeSignature ERS_InterpreterArgs_DynamicInvoke;
        ERS_InterpreterArgs_SetArgumentSignature ERS_InterpreterArgs_SetArgument;
        ERS_InterpreterComponent_UpdateEnabledSignature ERS_InterpreterComponent_UpdateEnabled;
        ERS_InterpreterComponent_Render2DEnabledSignature ERS_InterpreterComponent_Render2DEnabled;
        ERS_InterpreterVariable_NoneSignature ERS_InterpreterVariable_None;
        ERS_InterpreterVariable_CreateBoolSignature ERS_InterpreterVariable_CreateBool;
        ERS_InterpreterVariable_CreateUInt64Signature ERS_InterpreterVariable_CreateUInt64;
        ERS_InterpreterVariable_CreateStringSignature ERS_InterpreterVariable_CreateString;
        ERS_InterpreterVariable_CreateDoubleSignature ERS_InterpreterVariable_CreateDouble;
        ERS_InterpreterVariable_CreateEntitySignature ERS_InterpreterVariable_CreateEntity;
        ERS_PathSegment_GetTypeSignature ERS_PathSegment_GetType;
        ERS_PathSegment_GetFromXSignature ERS_PathSegment_GetFromX;
        ERS_PathSegment_GetFromYSignature ERS_PathSegment_GetFromY;
        ERS_PathSegment_GetFromZSignature ERS_PathSegment_GetFromZ;
        ERS_PathSegment_GetToXSignature ERS_PathSegment_GetToX;
        ERS_PathSegment_GetToYSignature ERS_PathSegment_GetToY;
        ERS_PathSegment_GetToZSignature ERS_PathSegment_GetToZ;
        ERS_PathSegment_GetCenterXSignature ERS_PathSegment_GetCenterX;
        ERS_PathSegment_GetCenterYSignature ERS_PathSegment_GetCenterY;
        ERS_PathSegment_GetCenterZSignature ERS_PathSegment_GetCenterZ;
        ERS_PathSegment_GetRadiusSignature ERS_PathSegment_GetRadius;
        ERS_PathSegment_GetBeginAngleSignature ERS_PathSegment_GetBeginAngle;
        ERS_PathSegment_GetEndAngleSignature ERS_PathSegment_GetEndAngle;
        ERS_PathSegment_GetEndZSignature ERS_PathSegment_GetEndZ;
        ERS_PathSegment_GetPointAlongPathSignature ERS_PathSegment_GetPointAlongPath;
        ERS_PathSegment_GetRotationAlongPathSignature ERS_PathSegment_GetRotationAlongPath;
        ERS_Random_Generator_MersenneTwister_CreateSignature ERS_Random_Generator_MersenneTwister_Create;
        ERS_Random_Generator_WichmannHill_CreateSignature ERS_Random_Generator_WichmannHill_Create;
        ERS_Random_Generator_DestroySignature ERS_Random_Generator_Destroy;
        ERS_Random_Generator_Set_SeedSignature ERS_Random_Generator_Set_Seed;
        ERS_Random_Generator_SampleSignature ERS_Random_Generator_Sample;
        ERS_Random_Generator_ResetSignature ERS_Random_Generator_Reset;
        ERS_Random_Generator_GetTypeSignature ERS_Random_Generator_GetType;
        ERS_Profiler_StartSessionSignature ERS_Profiler_StartSession;
        ERS_Profiler_PrintResultsSignature ERS_Profiler_PrintResults;
        ERS_STRING_DISPOSESignature ERS_STRING_DISPOSE;
        ERS_ThreadLocal_GetSubModelSignature ERS_ThreadLocal_GetSubModel;
        ERS_ThreadLocal_GetSubModelOrNullSignature ERS_ThreadLocal_GetSubModelOrNull;
        ERS_ThreadLocal_InsideSubModelSignature ERS_ThreadLocal_InsideSubModel;
        ERS_ThreadLocal_EnterSubModelSignature ERS_ThreadLocal_EnterSubModel;
        ERS_ThreadLocal_ExitSubModelSignature ERS_ThreadLocal_ExitSubModel;
        ERS_ThreadLocal_GetCurrentSyncEventSignature ERS_ThreadLocal_GetCurrentSyncEvent;
        ERS_ThreadLocal_IsInsideSyncEventSignature ERS_ThreadLocal_IsInsideSyncEvent;
        ERS_ThreadLocal_GetSyncEventTargetSignature ERS_ThreadLocal_GetSyncEventTarget;
        ERS_ThreadLocal_GetSyncEventSenderSignature ERS_ThreadLocal_GetSyncEventSender;
        ERS_ModelContainer_CreateModelContainerSignature ERS_ModelContainer_CreateModelContainer;
        ERS_ModelContainer_ReleaseSignature ERS_ModelContainer_Release;
        ERS_ModelContainer_IncreaseSignature ERS_ModelContainer_Increase;
        ERS_ModelContainer_DisposeSignature ERS_ModelContainer_Dispose;
        ERS_ModelContainer_GetSimulatorsCountSignature ERS_ModelContainer_GetSimulatorsCount;
        ERS_ModelContainer_GetSimulatorSignature ERS_ModelContainer_GetSimulator;
        ERS_ModelContainer_GetSimulatorByIdSignature ERS_ModelContainer_GetSimulatorById;
        ERS_ModelContainer_AddSimulatorSignature ERS_ModelContainer_AddSimulator;
        ERS_ModelContainer_RemoveSimulatorSignature ERS_ModelContainer_RemoveSimulator;
        ERS_ModelContainer_CurrentTimeSignature ERS_ModelContainer_CurrentTime;
        ERS_ModelContainer_Update_BlockingSignature ERS_ModelContainer_Update_Blocking;
        ERS_ModelContainer_SimulationSpeedOverRealtimeSignature ERS_ModelContainer_SimulationSpeedOverRealtime;
        ERS_ModelContainer_SetModelPrecisionSignature ERS_ModelContainer_SetModelPrecision;
        ERS_ModelContainer_GetModelPrecisionSignature ERS_ModelContainer_GetModelPrecision;
        ERS_ModelContainer_IsStartedSignature ERS_ModelContainer_IsStarted;
        ERS_ModelContainer_SetSeedSignature ERS_ModelContainer_SetSeed;
        ERS_ModelContainer_GenerateRandomSeedSignature ERS_ModelContainer_GenerateRandomSeed;
        ERS_ModelContainer_SeedSignature ERS_ModelContainer_Seed;
        ERS_ModelContainer_FindSimulatorByIdSignature ERS_ModelContainer_FindSimulatorById;
        ERS_ModelContainer_FindSimulatorByTagSignature ERS_ModelContainer_FindSimulatorByTag;
        ERS_ModelContainer_AddSimulatorDependencySignature ERS_ModelContainer_AddSimulatorDependency;
        ERS_ModelContainer_RemoveSimulatorDependencySignature ERS_ModelContainer_RemoveSimulatorDependency;
        ERS_ModelContainer_StartSignature ERS_ModelContainer_Start;
        ERS_ModelManager_GetModelManagerSignature ERS_ModelManager_GetModelManager;
        ERS_ModelManager_AddModelContainerSignature ERS_ModelManager_AddModelContainer;
        ERS_ModelManager_RemoveModelContainerSignature ERS_ModelManager_RemoveModelContainer;
        ERS_ModelManager_CountModelContainersSignature ERS_ModelManager_CountModelContainers;
        ERS_ModelManager_GetModelContainerAtSignature ERS_ModelManager_GetModelContainerAt;
        ERS_ModelManager_HasModelContainerSignature ERS_ModelManager_HasModelContainer;
        ERS_ModelManager_UpdateSignature ERS_ModelManager_Update;
        ERS_LibraryCollection_OpenLibrarySignature ERS_LibraryCollection_OpenLibrary;
        ERS_LibraryCollection_IsLibraryOpenSignature ERS_LibraryCollection_IsLibraryOpen;
        ERS_LibraryCollection_GetFunctionFromLibrarySignature ERS_LibraryCollection_GetFunctionFromLibrary;
        ERS_LibraryCollection_GetLibraryHandleSignature ERS_LibraryCollection_GetLibraryHandle;
        ERS_Simulator_GetLibraryCollectionSignature ERS_Simulator_GetLibraryCollection;
        ERS_Simulator_GetSubModelSignature ERS_Simulator_GetSubModel;
        ERS_Simulator_IsRunTogetherSignature ERS_Simulator_IsRunTogether;
        ERS_Simulator_IsBiDirectionalSignature ERS_Simulator_IsBiDirectional;
        ERS_Simulator_GetNameSignature ERS_Simulator_GetName;
        ERS_Simulator_GetTimeStepSignature ERS_Simulator_GetTimeStep;
        ERS_Simulator_SetTimeStepSignature ERS_Simulator_SetTimeStep;
        ERS_Simulator_GetIDSignature ERS_Simulator_GetID;
        ERS_Simulator_GetSimulatorTypeSignature ERS_Simulator_GetSimulatorType;
        ERS_Simulator_GetAttachedModelContainerSignature ERS_Simulator_GetAttachedModelContainer;
        ERS_Simulator_GetDependenciesAmountSignature ERS_Simulator_GetDependenciesAmount;
        ERS_Simulator_GetDependencyNameSignature ERS_Simulator_GetDependencyName;
        ERS_Simulator_FindDependencyByIdSignature ERS_Simulator_FindDependencyById;
        ERS_Simulator_FindDependencyByNameSignature ERS_Simulator_FindDependencyByName;
        ERS_Simulator_FindOutgoingDependencyByIdSignature ERS_Simulator_FindOutgoingDependencyById;
        ERS_Simulator_FindOutgoingDependencyByNameSignature ERS_Simulator_FindOutgoingDependencyByName;
        ERS_Simulator_GetCurrentTimeSignature ERS_Simulator_GetCurrentTime;
        ERS_BasicRenderComponent_TypeIdSignature ERS_BasicRenderComponent_TypeId;
        ERS_BasicRenderComponent_CreateCallbackSignature ERS_BasicRenderComponent_CreateCallback;
        ERS_BasicRenderComponent_GetColorSignature ERS_BasicRenderComponent_GetColor;
        ERS_BasicRenderComponent_SetColorSignature ERS_BasicRenderComponent_SetColor;
        ERS_BasicRenderComponent_SetInstancedModelSignature ERS_BasicRenderComponent_SetInstancedModel;
        ERS_BasicRenderComponent_GetInstancedModelSignature ERS_BasicRenderComponent_GetInstancedModel;
        ERS_BoxComponent_TypeIdSignature ERS_BoxComponent_TypeId;
        ERS_BoxComponent_CreateCallbackSignature ERS_BoxComponent_CreateCallback;
        ERS_BoxComponent_Min_XSignature ERS_BoxComponent_Min_X;
        ERS_BoxComponent_Min_YSignature ERS_BoxComponent_Min_Y;
        ERS_BoxComponent_Min_ZSignature ERS_BoxComponent_Min_Z;
        ERS_BoxComponent_Max_XSignature ERS_BoxComponent_Max_X;
        ERS_BoxComponent_Max_YSignature ERS_BoxComponent_Max_Y;
        ERS_BoxComponent_Max_ZSignature ERS_BoxComponent_Max_Z;
        ERS_BoxComponent_CenterSignature ERS_BoxComponent_Center;
        ERS_BoxComponent_DimensionsSignature ERS_BoxComponent_Dimensions;
        ERS_BoxComponent_InCollision_Point2DSignature ERS_BoxComponent_InCollision_Point2D;
        ERS_BoxComponent_InCollision_RaySignature ERS_BoxComponent_InCollision_Ray;
        ERS_ChannelComponent_TypeIdSignature ERS_ChannelComponent_TypeId;
        ERS_ChannelComponent_CreateCallbackSignature ERS_ChannelComponent_CreateCallback;
        ERS_ChannelComponent_RegisterTypeSignature ERS_ChannelComponent_RegisterType;
        ERS_ChannelComponent_GetTypeSignature ERS_ChannelComponent_GetType;
        ERS_ChannelComponent_GetConnectedToSignature ERS_ChannelComponent_GetConnectedTo;
        ERS_ChannelComponent_IsOpenSignature ERS_ChannelComponent_IsOpen;
        ERS_ChannelComponent_GetlongitudinalPositionSignature ERS_ChannelComponent_GetlongitudinalPosition;
        ERS_ChannelComponent_SetlongitudinalPositionSignature ERS_ChannelComponent_SetlongitudinalPosition;
        ERS_Channel_SendSignature ERS_Channel_Send;
        ERS_Channel_OpenSignature ERS_Channel_Open;
        ERS_Channel_IsReadySignature ERS_Channel_IsReady;
        ERS_Channel_ConnectSignature ERS_Channel_Connect;
        ERS_GlobalComponentRegistry_RegisterScriptBehaviorSignature ERS_GlobalComponentRegistry_RegisterScriptBehavior;
        ERS_GlobalComponentRegistry_RegisterResourceComponentSignature ERS_GlobalComponentRegistry_RegisterResourceComponent;
        ERS_GlobalComponentRegistry_RegisterComponentSignature ERS_GlobalComponentRegistry_RegisterComponent;
        ERS_GlobalComponentRegistry_IsRegisteredSignature ERS_GlobalComponentRegistry_IsRegistered;
        ERS_NameComponent_TypeIdSignature ERS_NameComponent_TypeId;
        ERS_NameComponent_CreateCallbackSignature ERS_NameComponent_CreateCallback;
        ERS_NameComponent_GetNameSignature ERS_NameComponent_GetName;
        ERS_NameComponent_SetNameSignature ERS_NameComponent_SetName;
        ERS_OutlineComponent_TypeIdSignature ERS_OutlineComponent_TypeId;
        ERS_OutlineComponent_CreateCallbackSignature ERS_OutlineComponent_CreateCallback;
        ERS_OutlineComponent_Center_XSignature ERS_OutlineComponent_Center_X;
        ERS_OutlineComponent_Center_YSignature ERS_OutlineComponent_Center_Y;
        ERS_OutlineComponent_Center_ZSignature ERS_OutlineComponent_Center_Z;
        ERS_OutlineComponent_Dimensions_XSignature ERS_OutlineComponent_Dimensions_X;
        ERS_OutlineComponent_Dimensions_YSignature ERS_OutlineComponent_Dimensions_Y;
        ERS_OutlineComponent_Dimensions_ZSignature ERS_OutlineComponent_Dimensions_Z;
        ERS_OutlineComponent_SetDimensionsSignature ERS_OutlineComponent_SetDimensions;
        ERS_PathComponent_TypeIdSignature ERS_PathComponent_TypeId;
        ERS_PathComponent_CreateCallbackSignature ERS_PathComponent_CreateCallback;
        ERS_PathComponent_GetSegmentSignature ERS_PathComponent_GetSegment;
        ERS_PathComponent_GetNumSegmentsSignature ERS_PathComponent_GetNumSegments;
        ERS_PathComponent_AddStraightSignature ERS_PathComponent_AddStraight;
        ERS_PathComponent_AddHelicalSignature ERS_PathComponent_AddHelical;
        ERS_RelationComponent_TypeIdSignature ERS_RelationComponent_TypeId;
        ERS_RelationComponent_RegisterTypeSignature ERS_RelationComponent_RegisterType;
        ERS_RelationComponent_GetParentSignature ERS_RelationComponent_GetParent;
        ERS_RelationComponent_GetFirstSignature ERS_RelationComponent_GetFirst;
        ERS_RelationComponent_GetLastSignature ERS_RelationComponent_GetLast;
        ERS_RelationComponent_GetPreviousSignature ERS_RelationComponent_GetPrevious;
        ERS_RelationComponent_GetNextSignature ERS_RelationComponent_GetNext;
        ERS_RelationComponent_GetChildCountSignature ERS_RelationComponent_GetChildCount;
        ERS_ResourceComponent_TypeIdSignature ERS_ResourceComponent_TypeId;
        ERS_ResourceComponent_CreateCallbackSignature ERS_ResourceComponent_CreateCallback;
        ERS_ResourceComponent_RegisterTypeSignature ERS_ResourceComponent_RegisterType;
        ERS_ResourceComponent_GetNumInputChannelsSignature ERS_ResourceComponent_GetNumInputChannels;
        ERS_ResourceComponent_GetNumOutputChannelsSignature ERS_ResourceComponent_GetNumOutputChannels;
        ERS_ResourceComponent_GetInputChannelSignature ERS_ResourceComponent_GetInputChannel;
        ERS_ResourceComponent_GetOutputChannelSignature ERS_ResourceComponent_GetOutputChannel;
        ERS_TransformComponent_TypeIdSignature ERS_TransformComponent_TypeId;
        ERS_TransformComponent_CreateCallbackSignature ERS_TransformComponent_CreateCallback;
        ERS_TransformComponent_RegisterTypeSignature ERS_TransformComponent_RegisterType;
        ERS_TransformComponent_Position_XSignature ERS_TransformComponent_Position_X;
        ERS_TransformComponent_SetPosition_XSignature ERS_TransformComponent_SetPosition_X;
        ERS_TransformComponent_Position_YSignature ERS_TransformComponent_Position_Y;
        ERS_TransformComponent_SetPosition_YSignature ERS_TransformComponent_SetPosition_Y;
        ERS_TransformComponent_Position_ZSignature ERS_TransformComponent_Position_Z;
        ERS_TransformComponent_SetPosition_ZSignature ERS_TransformComponent_SetPosition_Z;
        ERS_TransformComponent_SetPositionSignature ERS_TransformComponent_SetPosition;
        ERS_TransformComponent_Scale_XSignature ERS_TransformComponent_Scale_X;
        ERS_TransformComponent_SetScale_XSignature ERS_TransformComponent_SetScale_X;
        ERS_TransformComponent_Scale_YSignature ERS_TransformComponent_Scale_Y;
        ERS_TransformComponent_SetScale_YSignature ERS_TransformComponent_SetScale_Y;
        ERS_TransformComponent_Scale_ZSignature ERS_TransformComponent_Scale_Z;
        ERS_TransformComponent_SetScale_ZSignature ERS_TransformComponent_SetScale_Z;
        ERS_TransformComponent_SetScaleSignature ERS_TransformComponent_SetScale;
        ERS_TransformComponent_Rotation_XSignature ERS_TransformComponent_Rotation_X;
        ERS_TransformComponent_SetRotation_XSignature ERS_TransformComponent_SetRotation_X;
        ERS_TransformComponent_Rotation_YSignature ERS_TransformComponent_Rotation_Y;
        ERS_TransformComponent_SetRotation_YSignature ERS_TransformComponent_SetRotation_Y;
        ERS_TransformComponent_Rotation_ZSignature ERS_TransformComponent_Rotation_Z;
        ERS_TransformComponent_SetRotation_ZSignature ERS_TransformComponent_SetRotation_Z;
        ERS_TransformComponent_Rotate_XSignature ERS_TransformComponent_Rotate_X;
        ERS_TransformComponent_Rotate_YSignature ERS_TransformComponent_Rotate_Y;
        ERS_TransformComponent_Rotate_ZSignature ERS_TransformComponent_Rotate_Z;
        ERS_TransformComponent_SetRotationEulerSignature ERS_TransformComponent_SetRotationEuler;
        ERS_TransformComponent_SetQuaternionSignature ERS_TransformComponent_SetQuaternion;
        ERS_TransformComponent_GlobalPosition_XSignature ERS_TransformComponent_GlobalPosition_X;
        ERS_TransformComponent_GlobalPosition_YSignature ERS_TransformComponent_GlobalPosition_Y;
        ERS_TransformComponent_GlobalPosition_ZSignature ERS_TransformComponent_GlobalPosition_Z;
        ERS_TransformComponent_GlobalScale_XSignature ERS_TransformComponent_GlobalScale_X;
        ERS_TransformComponent_GlobalScale_YSignature ERS_TransformComponent_GlobalScale_Y;
        ERS_TransformComponent_GlobalScale_ZSignature ERS_TransformComponent_GlobalScale_Z;
        ERS_TransformComponent_GlobalRotation_XSignature ERS_TransformComponent_GlobalRotation_X;
        ERS_TransformComponent_GlobalRotation_YSignature ERS_TransformComponent_GlobalRotation_Y;
        ERS_TransformComponent_GlobalRotation_ZSignature ERS_TransformComponent_GlobalRotation_Z;
        ERS_Entity_InvalidSignature ERS_Entity_Invalid;
        ERS_Entity_GetParentSignature ERS_Entity_GetParent;
        ERS_Entity_GetChildCountSignature ERS_Entity_GetChildCount;
        ERS_Entity_GetFirstChildSignature ERS_Entity_GetFirstChild;
        ERS_Entity_GetLastChildSignature ERS_Entity_GetLastChild;
        ERS_Entity_GetPreviousSiblingSignature ERS_Entity_GetPreviousSibling;
        ERS_Entity_GetNextSiblingSignature ERS_Entity_GetNextSibling;
        ERS_Entity_IsValidSignature ERS_Entity_IsValid;
        ERS_EventScheduler_ScheduleLocalEventSignature ERS_EventScheduler_ScheduleLocalEvent;
        ERS_EventScheduler_CancelEventSignature ERS_EventScheduler_CancelEvent;
        ERS_EventScheduler_SetPromiseSignature ERS_EventScheduler_SetPromise;
        ERS_EventScheduler_LastScheduledSyncEventSignature ERS_EventScheduler_LastScheduledSyncEvent;
        ERS_EventScheduler_GetPromiseSignature ERS_EventScheduler_GetPromise;
        ERS_EventScheduler_ScheduleSyncEventSignature ERS_EventScheduler_ScheduleSyncEvent;
        ERS_EventScheduler_SyncEvent_GetDataSignature ERS_EventScheduler_SyncEvent_GetData;
        ERS_EventScheduler_ExchangeSyncEventForEventIDSignature ERS_EventScheduler_ExchangeSyncEventForEventID;
        ERS_EventScheduler_DelayEventSignature ERS_EventScheduler_DelayEvent;
        ERS_SubModel_Move_Entity_ToSignature ERS_SubModel_Move_Entity_To;
        ERS_SubModel_Entity_Create_Name_ParentSignature ERS_SubModel_Entity_Create_Name_Parent;
        ERS_SubModel_Entity_CreateSignature ERS_SubModel_Entity_Create;
        ERS_SubModel_Entity_Create_NameSignature ERS_SubModel_Entity_Create_Name;
        ERS_SubModel_FindEntitySignature ERS_SubModel_FindEntity;
        ERS_SubModel_FindEntity_ParentSignature ERS_SubModel_FindEntity_Parent;
        ERS_SubModel_Entity_DestroySignature ERS_SubModel_Entity_Destroy;
        ERS_SubModel_Entity_ExistsSignature ERS_SubModel_Entity_Exists;
        ERS_SubModel_Entity_Relation_Update_ParentSignature ERS_SubModel_Entity_Relation_Update_Parent;
        ERS_SubModel_AddScriptBehaviorSignature ERS_SubModel_AddScriptBehavior;
        ERS_SubModel_GetScriptBehaviorSignature ERS_SubModel_GetScriptBehavior;
        ERS_SubModel_RemoveScriptBehaviorSignature ERS_SubModel_RemoveScriptBehavior;
        ERS_SubModel_GetComponentSignature ERS_SubModel_GetComponent;
        ERS_SubModel_AddDataComponentSignature ERS_SubModel_AddDataComponent;
        ERS_SubModel_GetSimulatorSignature ERS_SubModel_GetSimulator;
        ERS_SubModel_RemoveDataComponentSignature ERS_SubModel_RemoveDataComponent;
        ERS_SubModel_HasComponentSignature ERS_SubModel_HasComponent;
        ERS_SubModel_AddComponentTypeSignature ERS_SubModel_AddComponentType;
        ERS_SubModel_GetRandomPropertiesSignature ERS_SubModel_GetRandomProperties;
        ERS_SubModel_SendEntityToSignature ERS_SubModel_SendEntityTo;
        ERS_SubModel_ReceiveEntityFromSignature ERS_SubModel_ReceiveEntityFrom;
        ERS_SubModel_RootEntityIDSignature ERS_SubModel_RootEntityID;
        ERS_SubModel_GenerateRandomDoubleSignature ERS_SubModel_GenerateRandomDouble;
        ERS_SubModel_GetModelPrecisionSignature ERS_SubModel_GetModelPrecision;
        ERS_SubModel_RegisterSubModelContextSignature ERS_SubModel_RegisterSubModelContext;
        ERS_SubModel_AddSubModelContextSignature ERS_SubModel_AddSubModelContext;
        ERS_SubModel_GetContextSignature ERS_SubModel_GetContext;
        ERS_SubModelRandomProperties_CreateSignature ERS_SubModelRandomProperties_Create;
        ERS_SubModelRandomProperties_DestroySignature ERS_SubModelRandomProperties_Destroy;
        ERS_SubModelRandomProperties_SetRandomGenerator_TypeSignature ERS_SubModelRandomProperties_SetRandomGenerator_Type;
        ERS_SubModelRandomProperties_SetRepetitiveSignature ERS_SubModelRandomProperties_SetRepetitive;
        ERS_SubModelRandomProperties_SetAntitheticalSignature ERS_SubModelRandomProperties_SetAntithetical;
        ERS_SubModelRandomProperties_SetSeedSignature ERS_SubModelRandomProperties_SetSeed;
        ERS_SubModelRandomProperties_IsRepetitiveSignature ERS_SubModelRandomProperties_IsRepetitive;
        ERS_SubModelRandomProperties_IsAntitheticalSignature ERS_SubModelRandomProperties_IsAntithetical;
        ERS_SubModelRandomProperties_GetOriginalSeedSignature ERS_SubModelRandomProperties_GetOriginalSeed;
        ERS_SubModelRandomProperties_GetRandomNumberGeneratorSignature ERS_SubModelRandomProperties_GetRandomNumberGenerator;
        ERS_TypeInfo_RegisterStructSignature ERS_TypeInfo_RegisterStruct;
        ERS_TypeInfo_AddFieldSignature ERS_TypeInfo_AddField;
        ERS_TypeInfo_GetNameSignature ERS_TypeInfo_GetName;
        ERS_Submodel_View_CreateSignature ERS_Submodel_View_Create;
        ERS_Submodel_View_NextSignature ERS_Submodel_View_Next;
        ERS_Submodel_View_GetComponentSignature ERS_Submodel_View_GetComponent;
        ERS_Submodel_View_GetComponentsSignature ERS_Submodel_View_GetComponents;
        ERS_Submodel_View_GetEntitySignature ERS_Submodel_View_GetEntity;
        ERS_Submodel_View_DisposeSignature ERS_Submodel_View_Dispose;
        ERS_SubModel_Events_DisconnectSignature ERS_SubModel_Events_Disconnect;
        ERS_SubModel_RelationEvents_OnAwakeSignature ERS_SubModel_RelationEvents_OnAwake;
        ERS_SubModel_RelationEvents_OnAwake_ConnectSignature ERS_SubModel_RelationEvents_OnAwake_Connect;
        ERS_SubModel_RelationEvents_OnStartSignature ERS_SubModel_RelationEvents_OnStart;
        ERS_SubModel_RelationEvents_OnStart_ConnectSignature ERS_SubModel_RelationEvents_OnStart_Connect;
        ERS_SubModel_RelationEvents_OnCreateSignature ERS_SubModel_RelationEvents_OnCreate;
        ERS_SubModel_RelationEvents_OnCreate_ConnectSignature ERS_SubModel_RelationEvents_OnCreate_Connect;
        ERS_SubModel_RelationEvents_OnDestroySignature ERS_SubModel_RelationEvents_OnDestroy;
        ERS_SubModel_RelationEvents_OnDestroy_ConnectSignature ERS_SubModel_RelationEvents_OnDestroy_Connect;
        ERS_SubModel_RelationEvents_OnEnteringSignature ERS_SubModel_RelationEvents_OnEntering;
        ERS_SubModel_RelationEvents_OnEntering_ConnectSignature ERS_SubModel_RelationEvents_OnEntering_Connect;
        ERS_SubModel_RelationEvents_OnEnteredSignature ERS_SubModel_RelationEvents_OnEntered;
        ERS_SubModel_RelationEvents_OnEntered_ConnectSignature ERS_SubModel_RelationEvents_OnEntered_Connect;
        ERS_SubModel_RelationEvents_OnExitingSignature ERS_SubModel_RelationEvents_OnExiting;
        ERS_SubModel_RelationEvents_OnExiting_ConnectSignature ERS_SubModel_RelationEvents_OnExiting_Connect;
        ERS_SubModel_RelationEvents_OnExitedSignature ERS_SubModel_RelationEvents_OnExited;
        ERS_SubModel_RelationEvents_OnExited_ConnectSignature ERS_SubModel_RelationEvents_OnExited_Connect;
        ERS_SyncEvent_GetSyncEventMetaDataSignature ERS_SyncEvent_GetSyncEventMetaData;
        ERS_SyncEvent_SetSyncEventMetaDataSignature ERS_SyncEvent_SetSyncEventMetaData;
        ERS_SyncEvent_SetSyncEventNameSignature ERS_SyncEvent_SetSyncEventName;
        ERS_SyncEvent_GetSyncEventUIDSignature ERS_SyncEvent_GetSyncEventUID;
        ERS_SyncEvent_GetOrRegisterDataContextSignature ERS_SyncEvent_GetOrRegisterDataContext;
        ERS_SyncEvent_GetDataSignature ERS_SyncEvent_GetData;
        ERS_BasicRenderSystem_Render2DSignature ERS_BasicRenderSystem_Render2D;
        ERS_BasicRenderSystem_Render3DSignature ERS_BasicRenderSystem_Render3D;
        ERS_CollisionSystem_UpdateBoundingBoxesSignature ERS_CollisionSystem_UpdateBoundingBoxes;
        ERS_InterpreterRenderSystem_Render2DSignature ERS_InterpreterRenderSystem_Render2D;
        ERS_InterpreterRenderSystem_BuildMesh3DSignature ERS_InterpreterRenderSystem_BuildMesh3D;
        ERS_PathAnimationSystem_UpdateSignature ERS_PathAnimationSystem_Update;
        ERS_PathAnimationSystem_AnimateSignature ERS_PathAnimationSystem_Animate;
        ERS_TransformSystem_UpdateGlobalsSignature ERS_TransformSystem_UpdateGlobals;
        ERS_Camera2D_UpdateTransformSignature ERS_Camera2D_UpdateTransform;
        ERS_Camera2D_PositionXSignature ERS_Camera2D_PositionX;
        ERS_Camera2D_PositionYSignature ERS_Camera2D_PositionY;
        ERS_Camera2D_ZoomSignature ERS_Camera2D_Zoom;
        ERS_Camera2D_SizePerPixelSignature ERS_Camera2D_SizePerPixel;
        ERS_Camera2D_GetWorldPosSignature ERS_Camera2D_GetWorldPos;
        ERS_Camera2DController_CreateSignature ERS_Camera2DController_Create;
        ERS_Camera2DController_DestroySignature ERS_Camera2DController_Destroy;
        ERS_Camera2DController_ControlCameraSignature ERS_Camera2DController_ControlCamera;
        ERS_Camera2DController_SetScreenSizeSignature ERS_Camera2DController_SetScreenSize;
        ERS_Camera2DController_UpdateSignature ERS_Camera2DController_Update;
        ERS_Camera2DController_StartDraggingSignature ERS_Camera2DController_StartDragging;
        ERS_Camera2DController_StopDraggingSignature ERS_Camera2DController_StopDragging;
        ERS_Camera2DController_ZoomSignature ERS_Camera2DController_Zoom;
        ERS_Camera3D_PositionXSignature ERS_Camera3D_PositionX;
        ERS_Camera3D_PositionYSignature ERS_Camera3D_PositionY;
        ERS_Camera3D_PositionZSignature ERS_Camera3D_PositionZ;
        ERS_Camera3D_LookAtXSignature ERS_Camera3D_LookAtX;
        ERS_Camera3D_LookAtYSignature ERS_Camera3D_LookAtY;
        ERS_Camera3D_LookAtZSignature ERS_Camera3D_LookAtZ;
        ERS_Camera3D_FovInTurnsSignature ERS_Camera3D_FovInTurns;
        ERS_Camera3D_ZNearSignature ERS_Camera3D_ZNear;
        ERS_Camera3D_ZFarSignature ERS_Camera3D_ZFar;
        ERS_Camera3D_SetLookAtSignature ERS_Camera3D_SetLookAt;
        ERS_Camera3D_UpdateTransformSignature ERS_Camera3D_UpdateTransform;
        ERS_Camera3D_GetPickRaySignature ERS_Camera3D_GetPickRay;
        ERS_Camera3DController_CreateSignature ERS_Camera3DController_Create;
        ERS_Camera3DController_DestroySignature ERS_Camera3DController_Destroy;
        ERS_Camera3DController_ControlCameraSignature ERS_Camera3DController_ControlCamera;
        ERS_Camera3DController_UpdateSignature ERS_Camera3DController_Update;
        ERS_Camera3DController_SwitchCameraModeSignature ERS_Camera3DController_SwitchCameraMode;
        ERS_Camera3DController_GetCameraModeSignature ERS_Camera3DController_GetCameraMode;
        ERS_Camera3DController_HeadBobbingIntensitySignature ERS_Camera3DController_HeadBobbingIntensity;
        ERS_InputHandler_GetActionSignature ERS_InputHandler_GetAction;
        ERS_InputHandler_ExistsActionSignature ERS_InputHandler_ExistsAction;
        ERS_InputHandler_CycleSignature ERS_InputHandler_Cycle;
        ERS_InputHandler_UpdateMousePosSignature ERS_InputHandler_UpdateMousePos;
        ERS_InputAction_TriggeredSignature ERS_InputAction_Triggered;
        ERS_InputAction_ReleasedSignature ERS_InputAction_Released;
        ERS_InputAction_StrengthSignature ERS_InputAction_Strength;
        ERS_InstancedModel_CreateSignature ERS_InstancedModel_Create;
        ERS_InstancedModel_ReleaseSignature ERS_InstancedModel_Release;
        ERS_InstancedModel_PushInstanceSignature ERS_InstancedModel_PushInstance;
        ERS_InstancedModel_SetMeshSignature ERS_InstancedModel_SetMesh;
        ERS_InstancedModel_ClearSignature ERS_InstancedModel_Clear;
        ERS_Material_Copy_ShallowSignature ERS_Material_Copy_Shallow;
        ERS_Material_Color_XSignature ERS_Material_Color_X;
        ERS_Material_Color_YSignature ERS_Material_Color_Y;
        ERS_Material_Color_ZSignature ERS_Material_Color_Z;
        ERS_Mesh_CreateSignature ERS_Mesh_Create;
        ERS_Mesh_ReleaseSignature ERS_Mesh_Release;
        ERS_Mesh_IncreaseSignature ERS_Mesh_Increase;
        ERS_Mesh_DisposeSignature ERS_Mesh_Dispose;
        ERS_Mesh_SetDefaultMaterialSignature ERS_Mesh_SetDefaultMaterial;
        ERS_Mesh_ClearSignature ERS_Mesh_Clear;
        ERS_Mesh_PushVertex3DSignature ERS_Mesh_PushVertex3D;
        ERS_Mesh_PushIndexSignature ERS_Mesh_PushIndex;
        ERS_Mesh_PushQuadSignature ERS_Mesh_PushQuad;
        ERS_Mesh_PushCubeSignature ERS_Mesh_PushCube;
        ERS_Mesh_PushBeamSignature ERS_Mesh_PushBeam;
        ERS_Mesh_PushText3DSignature ERS_Mesh_PushText3D;
        ERS_Mesh_PushText3DAlignedSignature ERS_Mesh_PushText3DAligned;
        ERS_Mesh_PushTextBillboardSignature ERS_Mesh_PushTextBillboard;
        ERS_Mesh_PushText3DDefaultSignature ERS_Mesh_PushText3DDefault;
        ERS_Mesh_PushVerticalHelicalStripSignature ERS_Mesh_PushVerticalHelicalStrip;
        ERS_Mesh_PushHorizontalHelicalStripSignature ERS_Mesh_PushHorizontalHelicalStrip;
        ERS_Mesh_PushHelicalBeamSignature ERS_Mesh_PushHelicalBeam;
        ERS_Mesh_PushText3DAlignedDefaultSignature ERS_Mesh_PushText3DAlignedDefault;
        ERS_Mesh_PushTextBillboardDefaultSignature ERS_Mesh_PushTextBillboardDefault;
        ERS_Mesh_CreateBuffersSignature ERS_Mesh_CreateBuffers;
        ERS_Mesh_DeleteBuffersSignature ERS_Mesh_DeleteBuffers;
        ERS_Mesh_UpdateBuffersSignature ERS_Mesh_UpdateBuffers;
        ERS_Mesh_DrawSignature ERS_Mesh_Draw;
        ERS_Mesh_GetVertexCountSignature ERS_Mesh_GetVertexCount;
        ERS_Mesh_GetIndexCountSignature ERS_Mesh_GetIndexCount;
        ERS_Mesh_HasBuffersSignature ERS_Mesh_HasBuffers;
        ERS_Mesh_GetVAOSignature ERS_Mesh_GetVAO;
        ERS_Mesh_TransformVertices2Signature ERS_Mesh_TransformVertices2;
        ERS_Mesh_TransformVerticesSignature ERS_Mesh_TransformVertices;
        ERS_Mesh_TransformVerticesRangeSignature ERS_Mesh_TransformVerticesRange;
        ERS_Mesh_CenterAtOriginSignature ERS_Mesh_CenterAtOrigin;
        ERS_Mesh_TranslateToFloorSignature ERS_Mesh_TranslateToFloor;
        ERS_Mesh_SetColorSignature ERS_Mesh_SetColor;
        ERS_Mesh_NormalizeSignature ERS_Mesh_Normalize;
        ERS_Mesh_GetMaxSignature ERS_Mesh_GetMax;
        ERS_Mesh_GetMinSignature ERS_Mesh_GetMin;
        ERS_Mesh_SetTransformSignature ERS_Mesh_SetTransform;
        ERS_Mesh_PushMeshSignature ERS_Mesh_PushMesh;
        ERS_Mesh_GetTransformSignature ERS_Mesh_GetTransform;
        ERS_Model3D_CreateSignature ERS_Model3D_Create;
        ERS_Model3D_DestroySignature ERS_Model3D_Destroy;
        ERS_Model3D_LoadSignature ERS_Model3D_Load;
        ERS_Model3D_GetMeshCountSignature ERS_Model3D_GetMeshCount;
        ERS_Model3D_SetTransformSignature ERS_Model3D_SetTransform;
        ERS_Model3D_GetTransformSignature ERS_Model3D_GetTransform;
        ERS_Model3D_GetMeshSignature ERS_Model3D_GetMesh;
        ERS_RenderContext_CreateSignature ERS_RenderContext_Create;
        ERS_RenderContext_DisposeSignature ERS_RenderContext_Dispose;
        ERS_RenderContext_GetCamera2DSignature ERS_RenderContext_GetCamera2D;
        ERS_RenderContext_SetViewportSignature ERS_RenderContext_SetViewport;
        ERS_RenderContext_SetBackgroundColorSignature ERS_RenderContext_SetBackgroundColor;
        ERS_RenderContext_GetCamera3DSignature ERS_RenderContext_GetCamera3D;
        ERS_RenderContext_ClearScreenSignature ERS_RenderContext_ClearScreen;
        ERS_RenderContext_Begin2DSignature ERS_RenderContext_Begin2D;
        ERS_RenderContext_End2DSignature ERS_RenderContext_End2D;
        ERS_RenderContext_Begin3DSignature ERS_RenderContext_Begin3D;
        ERS_RenderContext_End3DSignature ERS_RenderContext_End3D;
        ERS_RenderContext_DrawQuad2DSignature ERS_RenderContext_DrawQuad2D;
        ERS_RenderContext_DrawRect2DSignature ERS_RenderContext_DrawRect2D;
        ERS_RenderContext_DrawScreenLine2DSignature ERS_RenderContext_DrawScreenLine2D;
        ERS_RenderContext_DrawScreenLineRect2DSignature ERS_RenderContext_DrawScreenLineRect2D;
        ERS_RenderContext_DrawTextBillboardSignature ERS_RenderContext_DrawTextBillboard;
        ERS_RenderContext_DrawText2DSignature ERS_RenderContext_DrawText2D;
        ERS_RenderContext_DrawTexture2DSignature ERS_RenderContext_DrawTexture2D;
        ERS_RenderContext_DrawCube3DSignature ERS_RenderContext_DrawCube3D;
        ERS_RenderContext_DrawInfiniteGrid2DSignature ERS_RenderContext_DrawInfiniteGrid2D;
        ERS_RenderContext_DrawInfiniteGrid3DSignature ERS_RenderContext_DrawInfiniteGrid3D;
        ERS_RenderContext_DrawText3DSignature ERS_RenderContext_DrawText3D;
        ERS_RenderContext_SetLightDirectionSignature ERS_RenderContext_SetLightDirection;
        ERS_RenderContext_DrawLine2DSignature ERS_RenderContext_DrawLine2D;
        ERS_RenderContext_DrawTriangle2DSignature ERS_RenderContext_DrawTriangle2D;
        ERS_RenderContext_DrawTriangle2D_BoxSignature ERS_RenderContext_DrawTriangle2D_Box;
        ERS_RenderContext_DrawInstancedModel3DWithMeshSignature ERS_RenderContext_DrawInstancedModel3DWithMesh;
        ERS_RenderContext_PresentSignature ERS_RenderContext_Present;
        ERS_RenderContext_DrawInstancedModel3DSignature ERS_RenderContext_DrawInstancedModel3D;
        ERS_RenderContext_DrawArc2DSignature ERS_RenderContext_DrawArc2D;
        ERS_RenderContext_DrawModel3DSignature ERS_RenderContext_DrawModel3D;
        ERS_RenderContext_DrawMeshSignature ERS_RenderContext_DrawMesh;
        ERS_RenderContext_CalculateTextSizeSignature ERS_RenderContext_CalculateTextSize;
        ERS_RenderContext_IsOpenGLInitializedSignature ERS_RenderContext_IsOpenGLInitialized;
        ERS_RenderContext_InitializeOpenGLSignature ERS_RenderContext_InitializeOpenGL;
        ERS_Texture_CreateSignature ERS_Texture_Create;
        ERS_Texture_LoadSignature ERS_Texture_Load;
        ERS_Texture_ReleaseSignature ERS_Texture_Release;
        ERS_Window_CreateSignature ERS_Window_Create;
        ERS_Window_PresentSignature ERS_Window_Present;
        ERS_Window_DrawRenderContextSignature ERS_Window_DrawRenderContext;
        ERS_Window_DestroySignature ERS_Window_Destroy;
    };
    void* functions[ERS_N_FUNCTIONS];
};

#endif // ERS_API_FUNCTIONS_DEFINITION

#ifdef ERS_API_FUNCTIONS_IMPLEMENTATION
const char* ersFunctionNames[ERS_N_FUNCTIONS] = {
    "ERS_Debugger_Create",
    "ERS_Debugger_Destroy",
    "ERS_Debugger_WantsRestart",
    "ERS_Debugger_ShowBackgroundGrid",
    "ERS_Debugger_SetModelContainer",
    "ERS_Debugger_GetRenderContext",
    "ERS_Debugger_Is3DMode",
    "ERS_Debugger_GetSelectedSimulator",
    "ERS_Debugger_GetSelectedEntity",
    "ERS_Debugger_Update",
    "ERS_Platform_Create",
    "ERS_Platform_Destroy",
    "ERS_Platform_BeginFrame",
    "ERS_Platform_EndFrame",
    "ERS_Platform_WantsClose",
    "ERS_RunWithProgressBar",
    "ERS_SetBindingType",
    "ERS_License_ForceOnlineFetch",
    "ERS_Initialize",
    "ERS_Uninitialize",
    "ERS_GetMajorVersion",
    "ERS_GetMinorVersion",
    "ERS_GetPatchVersion",
    "ERS_IsDebugBuild",
    "ERS_License_Check",
    "ERS_License_Activate",
    "ERS_License_Deactivate",
    "ERS_License_Info_DaysRemaining",
    "ERS_License_Info_LicenseType",
    "ERS_License_HasFeature",
    "ERS_License_GetLimits_MaxJobSystemCores",
    "ERS_License_GetLimits_MaxComponentTypes",
    "ERS_License_EditionName",
    "ERS_Logger_Trace",
    "ERS_Logger_Debug",
    "ERS_Logger_Warning",
    "ERS_Logger_Info",
    "ERS_Logger_Error",
    "ERS_Logger_Critical",
    "ERS_Logger_SetLogLevel",
    "ERS_Logger_AddCallback",
    "ERS_Settings_GetSetting",
    "ERS_Settings_SetSetting",
    "ERS_VirtualFileSystem_MountDirectory",
    "ERS_Serializer_IsWriting",
    "ERS_Serializer_SerializeUInt64",
    "ERS_Serializer_SerializeInt64",
    "ERS_Serializer_SerializeUInt32",
    "ERS_Serializer_SerializeInt32",
    "ERS_Serializer_SerializeDouble",
    "ERS_Serializer_SerializeBool",
    "ERS_Serializer_SerializeFloat",
    "ERS_Serializer_SerializeString",
    "ERS_Serializer_PushObject",
    "ERS_Serializer_PopObject",
    "ERS_Serializer_SetObject",
    "ERS_Serializer_PushArray",
    "ERS_Serializer_PopArray",
    "ERS_Serializer_GetArraySize",
    "ERS_Serializer_SaveToFolder",
    "ERS_Serializer_LoadFromFolder",
    "ERS_Serializer_SaveToArchive",
    "ERS_Serializer_LoadFromArchive",
    "ERS_Serializer_ClearArchiveCache",
    "ERS_Serializer_SerializeValueUInt64",
    "ERS_Serializer_SerializeValueInt64",
    "ERS_Serializer_SerializeValueUInt32",
    "ERS_Serializer_SerializeValueInt32",
    "ERS_Serializer_SerializeValueDouble",
    "ERS_Serializer_SerializeValueBool",
    "ERS_Serializer_SerializeValueFloat",
    "ERS_Serializer_SerializeValueString",
    "ERS_Serializer_PushArrayElement",
    "ERS_Serializer_PushObjectElement",
    "ERS_SubModel_CreateInterpreter",
    "ERS_SubModel_RunSimpleString",
    "ERS_SubModel_LoadPythonModuleFromFile",
    "ERS_SubModel_LoadPythonPackage",
    "ERS_SubModel_AddInterpreterScriptComponentType",
    "ERS_SubModel_AddInterpreterScriptComponent",
    "ERS_SubModel_GetInterpreterScriptComponent",
    "ERS_SubModel_HasInterpreterScriptComponent",
    "ERS_SubModel_BeginInterpreterRenderContext",
    "ERS_SubModel_EndInterpreterRenderContext",
    "ERS_SubModel_GetInterpreterRenderContext",
    "ERS_SubModel_PrintInterpreterGCStats",
    "ERS_Interpreter_RegisterFunction",
    "ERS_InterpreterArgs_GetStringArgument",
    "ERS_InterpreterArgs_GetDoubleArgument",
    "ERS_InterpreterArgs_GetEntityArgument",
    "ERS_InterpreterArgs_GetUInt64Argument",
    "ERS_InterpreterArgs_GetBoolArgument",
    "ERS_InterpreterArgs_GetArgCount",
    "ERS_InterpreterArgs_Create",
    "ERS_InterpreterArgs_Destruct",
    "ERS_InterpreterArgs_HasAttribute",
    "ERS_InterpreterArgs_DynamicInvoke",
    "ERS_InterpreterArgs_SetArgument",
    "ERS_InterpreterComponent_UpdateEnabled",
    "ERS_InterpreterComponent_Render2DEnabled",
    "ERS_InterpreterVariable_None",
    "ERS_InterpreterVariable_CreateBool",
    "ERS_InterpreterVariable_CreateUInt64",
    "ERS_InterpreterVariable_CreateString",
    "ERS_InterpreterVariable_CreateDouble",
    "ERS_InterpreterVariable_CreateEntity",
    "ERS_PathSegment_GetType",
    "ERS_PathSegment_GetFromX",
    "ERS_PathSegment_GetFromY",
    "ERS_PathSegment_GetFromZ",
    "ERS_PathSegment_GetToX",
    "ERS_PathSegment_GetToY",
    "ERS_PathSegment_GetToZ",
    "ERS_PathSegment_GetCenterX",
    "ERS_PathSegment_GetCenterY",
    "ERS_PathSegment_GetCenterZ",
    "ERS_PathSegment_GetRadius",
    "ERS_PathSegment_GetBeginAngle",
    "ERS_PathSegment_GetEndAngle",
    "ERS_PathSegment_GetEndZ",
    "ERS_PathSegment_GetPointAlongPath",
    "ERS_PathSegment_GetRotationAlongPath",
    "ERS_Random_Generator_MersenneTwister_Create",
    "ERS_Random_Generator_WichmannHill_Create",
    "ERS_Random_Generator_Destroy",
    "ERS_Random_Generator_Set_Seed",
    "ERS_Random_Generator_Sample",
    "ERS_Random_Generator_Reset",
    "ERS_Random_Generator_GetType",
    "ERS_Profiler_StartSession",
    "ERS_Profiler_PrintResults",
    "ERS_STRING_DISPOSE",
    "ERS_ThreadLocal_GetSubModel",
    "ERS_ThreadLocal_GetSubModelOrNull",
    "ERS_ThreadLocal_InsideSubModel",
    "ERS_ThreadLocal_EnterSubModel",
    "ERS_ThreadLocal_ExitSubModel",
    "ERS_ThreadLocal_GetCurrentSyncEvent",
    "ERS_ThreadLocal_IsInsideSyncEvent",
    "ERS_ThreadLocal_GetSyncEventTarget",
    "ERS_ThreadLocal_GetSyncEventSender",
    "ERS_ModelContainer_CreateModelContainer",
    "ERS_ModelContainer_Release",
    "ERS_ModelContainer_Increase",
    "ERS_ModelContainer_Dispose",
    "ERS_ModelContainer_GetSimulatorsCount",
    "ERS_ModelContainer_GetSimulator",
    "ERS_ModelContainer_GetSimulatorById",
    "ERS_ModelContainer_AddSimulator",
    "ERS_ModelContainer_RemoveSimulator",
    "ERS_ModelContainer_CurrentTime",
    "ERS_ModelContainer_Update_Blocking",
    "ERS_ModelContainer_SimulationSpeedOverRealtime",
    "ERS_ModelContainer_SetModelPrecision",
    "ERS_ModelContainer_GetModelPrecision",
    "ERS_ModelContainer_IsStarted",
    "ERS_ModelContainer_SetSeed",
    "ERS_ModelContainer_GenerateRandomSeed",
    "ERS_ModelContainer_Seed",
    "ERS_ModelContainer_FindSimulatorById",
    "ERS_ModelContainer_FindSimulatorByTag",
    "ERS_ModelContainer_AddSimulatorDependency",
    "ERS_ModelContainer_RemoveSimulatorDependency",
    "ERS_ModelContainer_Start",
    "ERS_ModelManager_GetModelManager",
    "ERS_ModelManager_AddModelContainer",
    "ERS_ModelManager_RemoveModelContainer",
    "ERS_ModelManager_CountModelContainers",
    "ERS_ModelManager_GetModelContainerAt",
    "ERS_ModelManager_HasModelContainer",
    "ERS_ModelManager_Update",
    "ERS_LibraryCollection_OpenLibrary",
    "ERS_LibraryCollection_IsLibraryOpen",
    "ERS_LibraryCollection_GetFunctionFromLibrary",
    "ERS_LibraryCollection_GetLibraryHandle",
    "ERS_Simulator_GetLibraryCollection",
    "ERS_Simulator_GetSubModel",
    "ERS_Simulator_IsRunTogether",
    "ERS_Simulator_IsBiDirectional",
    "ERS_Simulator_GetName",
    "ERS_Simulator_GetTimeStep",
    "ERS_Simulator_SetTimeStep",
    "ERS_Simulator_GetID",
    "ERS_Simulator_GetSimulatorType",
    "ERS_Simulator_GetAttachedModelContainer",
    "ERS_Simulator_GetDependenciesAmount",
    "ERS_Simulator_GetDependencyName",
    "ERS_Simulator_FindDependencyById",
    "ERS_Simulator_FindDependencyByName",
    "ERS_Simulator_FindOutgoingDependencyById",
    "ERS_Simulator_FindOutgoingDependencyByName",
    "ERS_Simulator_GetCurrentTime",
    "ERS_BasicRenderComponent_TypeId",
    "ERS_BasicRenderComponent_CreateCallback",
    "ERS_BasicRenderComponent_GetColor",
    "ERS_BasicRenderComponent_SetColor",
    "ERS_BasicRenderComponent_SetInstancedModel",
    "ERS_BasicRenderComponent_GetInstancedModel",
    "ERS_BoxComponent_TypeId",
    "ERS_BoxComponent_CreateCallback",
    "ERS_BoxComponent_Min_X",
    "ERS_BoxComponent_Min_Y",
    "ERS_BoxComponent_Min_Z",
    "ERS_BoxComponent_Max_X",
    "ERS_BoxComponent_Max_Y",
    "ERS_BoxComponent_Max_Z",
    "ERS_BoxComponent_Center",
    "ERS_BoxComponent_Dimensions",
    "ERS_BoxComponent_InCollision_Point2D",
    "ERS_BoxComponent_InCollision_Ray",
    "ERS_ChannelComponent_TypeId",
    "ERS_ChannelComponent_CreateCallback",
    "ERS_ChannelComponent_RegisterType",
    "ERS_ChannelComponent_GetType",
    "ERS_ChannelComponent_GetConnectedTo",
    "ERS_ChannelComponent_IsOpen",
    "ERS_ChannelComponent_GetlongitudinalPosition",
    "ERS_ChannelComponent_SetlongitudinalPosition",
    "ERS_Channel_Send",
    "ERS_Channel_Open",
    "ERS_Channel_IsReady",
    "ERS_Channel_Connect",
    "ERS_GlobalComponentRegistry_RegisterScriptBehavior",
    "ERS_GlobalComponentRegistry_RegisterResourceComponent",
    "ERS_GlobalComponentRegistry_RegisterComponent",
    "ERS_GlobalComponentRegistry_IsRegistered",
    "ERS_NameComponent_TypeId",
    "ERS_NameComponent_CreateCallback",
    "ERS_NameComponent_GetName",
    "ERS_NameComponent_SetName",
    "ERS_OutlineComponent_TypeId",
    "ERS_OutlineComponent_CreateCallback",
    "ERS_OutlineComponent_Center_X",
    "ERS_OutlineComponent_Center_Y",
    "ERS_OutlineComponent_Center_Z",
    "ERS_OutlineComponent_Dimensions_X",
    "ERS_OutlineComponent_Dimensions_Y",
    "ERS_OutlineComponent_Dimensions_Z",
    "ERS_OutlineComponent_SetDimensions",
    "ERS_PathComponent_TypeId",
    "ERS_PathComponent_CreateCallback",
    "ERS_PathComponent_GetSegment",
    "ERS_PathComponent_GetNumSegments",
    "ERS_PathComponent_AddStraight",
    "ERS_PathComponent_AddHelical",
    "ERS_RelationComponent_TypeId",
    "ERS_RelationComponent_RegisterType",
    "ERS_RelationComponent_GetParent",
    "ERS_RelationComponent_GetFirst",
    "ERS_RelationComponent_GetLast",
    "ERS_RelationComponent_GetPrevious",
    "ERS_RelationComponent_GetNext",
    "ERS_RelationComponent_GetChildCount",
    "ERS_ResourceComponent_TypeId",
    "ERS_ResourceComponent_CreateCallback",
    "ERS_ResourceComponent_RegisterType",
    "ERS_ResourceComponent_GetNumInputChannels",
    "ERS_ResourceComponent_GetNumOutputChannels",
    "ERS_ResourceComponent_GetInputChannel",
    "ERS_ResourceComponent_GetOutputChannel",
    "ERS_TransformComponent_TypeId",
    "ERS_TransformComponent_CreateCallback",
    "ERS_TransformComponent_RegisterType",
    "ERS_TransformComponent_Position_X",
    "ERS_TransformComponent_SetPosition_X",
    "ERS_TransformComponent_Position_Y",
    "ERS_TransformComponent_SetPosition_Y",
    "ERS_TransformComponent_Position_Z",
    "ERS_TransformComponent_SetPosition_Z",
    "ERS_TransformComponent_SetPosition",
    "ERS_TransformComponent_Scale_X",
    "ERS_TransformComponent_SetScale_X",
    "ERS_TransformComponent_Scale_Y",
    "ERS_TransformComponent_SetScale_Y",
    "ERS_TransformComponent_Scale_Z",
    "ERS_TransformComponent_SetScale_Z",
    "ERS_TransformComponent_SetScale",
    "ERS_TransformComponent_Rotation_X",
    "ERS_TransformComponent_SetRotation_X",
    "ERS_TransformComponent_Rotation_Y",
    "ERS_TransformComponent_SetRotation_Y",
    "ERS_TransformComponent_Rotation_Z",
    "ERS_TransformComponent_SetRotation_Z",
    "ERS_TransformComponent_Rotate_X",
    "ERS_TransformComponent_Rotate_Y",
    "ERS_TransformComponent_Rotate_Z",
    "ERS_TransformComponent_SetRotationEuler",
    "ERS_TransformComponent_SetQuaternion",
    "ERS_TransformComponent_GlobalPosition_X",
    "ERS_TransformComponent_GlobalPosition_Y",
    "ERS_TransformComponent_GlobalPosition_Z",
    "ERS_TransformComponent_GlobalScale_X",
    "ERS_TransformComponent_GlobalScale_Y",
    "ERS_TransformComponent_GlobalScale_Z",
    "ERS_TransformComponent_GlobalRotation_X",
    "ERS_TransformComponent_GlobalRotation_Y",
    "ERS_TransformComponent_GlobalRotation_Z",
    "ERS_Entity_Invalid",
    "ERS_Entity_GetParent",
    "ERS_Entity_GetChildCount",
    "ERS_Entity_GetFirstChild",
    "ERS_Entity_GetLastChild",
    "ERS_Entity_GetPreviousSibling",
    "ERS_Entity_GetNextSibling",
    "ERS_Entity_IsValid",
    "ERS_EventScheduler_ScheduleLocalEvent",
    "ERS_EventScheduler_CancelEvent",
    "ERS_EventScheduler_SetPromise",
    "ERS_EventScheduler_LastScheduledSyncEvent",
    "ERS_EventScheduler_GetPromise",
    "ERS_EventScheduler_ScheduleSyncEvent",
    "ERS_EventScheduler_SyncEvent_GetData",
    "ERS_EventScheduler_ExchangeSyncEventForEventID",
    "ERS_EventScheduler_DelayEvent",
    "ERS_SubModel_Move_Entity_To",
    "ERS_SubModel_Entity_Create_Name_Parent",
    "ERS_SubModel_Entity_Create",
    "ERS_SubModel_Entity_Create_Name",
    "ERS_SubModel_FindEntity",
    "ERS_SubModel_FindEntity_Parent",
    "ERS_SubModel_Entity_Destroy",
    "ERS_SubModel_Entity_Exists",
    "ERS_SubModel_Entity_Relation_Update_Parent",
    "ERS_SubModel_AddScriptBehavior",
    "ERS_SubModel_GetScriptBehavior",
    "ERS_SubModel_RemoveScriptBehavior",
    "ERS_SubModel_GetComponent",
    "ERS_SubModel_AddDataComponent",
    "ERS_SubModel_GetSimulator",
    "ERS_SubModel_RemoveDataComponent",
    "ERS_SubModel_HasComponent",
    "ERS_SubModel_AddComponentType",
    "ERS_SubModel_GetRandomProperties",
    "ERS_SubModel_SendEntityTo",
    "ERS_SubModel_ReceiveEntityFrom",
    "ERS_SubModel_RootEntityID",
    "ERS_SubModel_GenerateRandomDouble",
    "ERS_SubModel_GetModelPrecision",
    "ERS_SubModel_RegisterSubModelContext",
    "ERS_SubModel_AddSubModelContext",
    "ERS_SubModel_GetContext",
    "ERS_SubModelRandomProperties_Create",
    "ERS_SubModelRandomProperties_Destroy",
    "ERS_SubModelRandomProperties_SetRandomGenerator_Type",
    "ERS_SubModelRandomProperties_SetRepetitive",
    "ERS_SubModelRandomProperties_SetAntithetical",
    "ERS_SubModelRandomProperties_SetSeed",
    "ERS_SubModelRandomProperties_IsRepetitive",
    "ERS_SubModelRandomProperties_IsAntithetical",
    "ERS_SubModelRandomProperties_GetOriginalSeed",
    "ERS_SubModelRandomProperties_GetRandomNumberGenerator",
    "ERS_TypeInfo_RegisterStruct",
    "ERS_TypeInfo_AddField",
    "ERS_TypeInfo_GetName",
    "ERS_Submodel_View_Create",
    "ERS_Submodel_View_Next",
    "ERS_Submodel_View_GetComponent",
    "ERS_Submodel_View_GetComponents",
    "ERS_Submodel_View_GetEntity",
    "ERS_Submodel_View_Dispose",
    "ERS_SubModel_Events_Disconnect",
    "ERS_SubModel_RelationEvents_OnAwake",
    "ERS_SubModel_RelationEvents_OnAwake_Connect",
    "ERS_SubModel_RelationEvents_OnStart",
    "ERS_SubModel_RelationEvents_OnStart_Connect",
    "ERS_SubModel_RelationEvents_OnCreate",
    "ERS_SubModel_RelationEvents_OnCreate_Connect",
    "ERS_SubModel_RelationEvents_OnDestroy",
    "ERS_SubModel_RelationEvents_OnDestroy_Connect",
    "ERS_SubModel_RelationEvents_OnEntering",
    "ERS_SubModel_RelationEvents_OnEntering_Connect",
    "ERS_SubModel_RelationEvents_OnEntered",
    "ERS_SubModel_RelationEvents_OnEntered_Connect",
    "ERS_SubModel_RelationEvents_OnExiting",
    "ERS_SubModel_RelationEvents_OnExiting_Connect",
    "ERS_SubModel_RelationEvents_OnExited",
    "ERS_SubModel_RelationEvents_OnExited_Connect",
    "ERS_SyncEvent_GetSyncEventMetaData",
    "ERS_SyncEvent_SetSyncEventMetaData",
    "ERS_SyncEvent_SetSyncEventName",
    "ERS_SyncEvent_GetSyncEventUID",
    "ERS_SyncEvent_GetOrRegisterDataContext",
    "ERS_SyncEvent_GetData",
    "ERS_BasicRenderSystem_Render2D",
    "ERS_BasicRenderSystem_Render3D",
    "ERS_CollisionSystem_UpdateBoundingBoxes",
    "ERS_InterpreterRenderSystem_Render2D",
    "ERS_InterpreterRenderSystem_BuildMesh3D",
    "ERS_PathAnimationSystem_Update",
    "ERS_PathAnimationSystem_Animate",
    "ERS_TransformSystem_UpdateGlobals",
    "ERS_Camera2D_UpdateTransform",
    "ERS_Camera2D_PositionX",
    "ERS_Camera2D_PositionY",
    "ERS_Camera2D_Zoom",
    "ERS_Camera2D_SizePerPixel",
    "ERS_Camera2D_GetWorldPos",
    "ERS_Camera2DController_Create",
    "ERS_Camera2DController_Destroy",
    "ERS_Camera2DController_ControlCamera",
    "ERS_Camera2DController_SetScreenSize",
    "ERS_Camera2DController_Update",
    "ERS_Camera2DController_StartDragging",
    "ERS_Camera2DController_StopDragging",
    "ERS_Camera2DController_Zoom",
    "ERS_Camera3D_PositionX",
    "ERS_Camera3D_PositionY",
    "ERS_Camera3D_PositionZ",
    "ERS_Camera3D_LookAtX",
    "ERS_Camera3D_LookAtY",
    "ERS_Camera3D_LookAtZ",
    "ERS_Camera3D_FovInTurns",
    "ERS_Camera3D_ZNear",
    "ERS_Camera3D_ZFar",
    "ERS_Camera3D_SetLookAt",
    "ERS_Camera3D_UpdateTransform",
    "ERS_Camera3D_GetPickRay",
    "ERS_Camera3DController_Create",
    "ERS_Camera3DController_Destroy",
    "ERS_Camera3DController_ControlCamera",
    "ERS_Camera3DController_Update",
    "ERS_Camera3DController_SwitchCameraMode",
    "ERS_Camera3DController_GetCameraMode",
    "ERS_Camera3DController_HeadBobbingIntensity",
    "ERS_InputHandler_GetAction",
    "ERS_InputHandler_ExistsAction",
    "ERS_InputHandler_Cycle",
    "ERS_InputHandler_UpdateMousePos",
    "ERS_InputAction_Triggered",
    "ERS_InputAction_Released",
    "ERS_InputAction_Strength",
    "ERS_InstancedModel_Create",
    "ERS_InstancedModel_Release",
    "ERS_InstancedModel_PushInstance",
    "ERS_InstancedModel_SetMesh",
    "ERS_InstancedModel_Clear",
    "ERS_Material_Copy_Shallow",
    "ERS_Material_Color_X",
    "ERS_Material_Color_Y",
    "ERS_Material_Color_Z",
    "ERS_Mesh_Create",
    "ERS_Mesh_Release",
    "ERS_Mesh_Increase",
    "ERS_Mesh_Dispose",
    "ERS_Mesh_SetDefaultMaterial",
    "ERS_Mesh_Clear",
    "ERS_Mesh_PushVertex3D",
    "ERS_Mesh_PushIndex",
    "ERS_Mesh_PushQuad",
    "ERS_Mesh_PushCube",
    "ERS_Mesh_PushBeam",
    "ERS_Mesh_PushText3D",
    "ERS_Mesh_PushText3DAligned",
    "ERS_Mesh_PushTextBillboard",
    "ERS_Mesh_PushText3DDefault",
    "ERS_Mesh_PushVerticalHelicalStrip",
    "ERS_Mesh_PushHorizontalHelicalStrip",
    "ERS_Mesh_PushHelicalBeam",
    "ERS_Mesh_PushText3DAlignedDefault",
    "ERS_Mesh_PushTextBillboardDefault",
    "ERS_Mesh_CreateBuffers",
    "ERS_Mesh_DeleteBuffers",
    "ERS_Mesh_UpdateBuffers",
    "ERS_Mesh_Draw",
    "ERS_Mesh_GetVertexCount",
    "ERS_Mesh_GetIndexCount",
    "ERS_Mesh_HasBuffers",
    "ERS_Mesh_GetVAO",
    "ERS_Mesh_TransformVertices2",
    "ERS_Mesh_TransformVertices",
    "ERS_Mesh_TransformVerticesRange",
    "ERS_Mesh_CenterAtOrigin",
    "ERS_Mesh_TranslateToFloor",
    "ERS_Mesh_SetColor",
    "ERS_Mesh_Normalize",
    "ERS_Mesh_GetMax",
    "ERS_Mesh_GetMin",
    "ERS_Mesh_SetTransform",
    "ERS_Mesh_PushMesh",
    "ERS_Mesh_GetTransform",
    "ERS_Model3D_Create",
    "ERS_Model3D_Destroy",
    "ERS_Model3D_Load",
    "ERS_Model3D_GetMeshCount",
    "ERS_Model3D_SetTransform",
    "ERS_Model3D_GetTransform",
    "ERS_Model3D_GetMesh",
    "ERS_RenderContext_Create",
    "ERS_RenderContext_Dispose",
    "ERS_RenderContext_GetCamera2D",
    "ERS_RenderContext_SetViewport",
    "ERS_RenderContext_SetBackgroundColor",
    "ERS_RenderContext_GetCamera3D",
    "ERS_RenderContext_ClearScreen",
    "ERS_RenderContext_Begin2D",
    "ERS_RenderContext_End2D",
    "ERS_RenderContext_Begin3D",
    "ERS_RenderContext_End3D",
    "ERS_RenderContext_DrawQuad2D",
    "ERS_RenderContext_DrawRect2D",
    "ERS_RenderContext_DrawScreenLine2D",
    "ERS_RenderContext_DrawScreenLineRect2D",
    "ERS_RenderContext_DrawTextBillboard",
    "ERS_RenderContext_DrawText2D",
    "ERS_RenderContext_DrawTexture2D",
    "ERS_RenderContext_DrawCube3D",
    "ERS_RenderContext_DrawInfiniteGrid2D",
    "ERS_RenderContext_DrawInfiniteGrid3D",
    "ERS_RenderContext_DrawText3D",
    "ERS_RenderContext_SetLightDirection",
    "ERS_RenderContext_DrawLine2D",
    "ERS_RenderContext_DrawTriangle2D",
    "ERS_RenderContext_DrawTriangle2D_Box",
    "ERS_RenderContext_DrawInstancedModel3DWithMesh",
    "ERS_RenderContext_Present",
    "ERS_RenderContext_DrawInstancedModel3D",
    "ERS_RenderContext_DrawArc2D",
    "ERS_RenderContext_DrawModel3D",
    "ERS_RenderContext_DrawMesh",
    "ERS_RenderContext_CalculateTextSize",
    "ERS_RenderContext_IsOpenGLInitialized",
    "ERS_RenderContext_InitializeOpenGL",
    "ERS_Texture_Create",
    "ERS_Texture_Load",
    "ERS_Texture_Release",
    "ERS_Window_Create",
    "ERS_Window_Present",
    "ERS_Window_DrawRenderContext",
    "ERS_Window_Destroy"
};
#endif // ERS_API_FUNCTIONS_IMPLEMENTATION

