using System;
using System.Runtime.InteropServices;

namespace Ers.Engine
{
    /// <summary>
    /// Functions of the ERS engine shared library.
    /// </summary>
    public static class ErsEngine
    {
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_Create(IntPtr modelContainerPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_Create_Window(IntPtr modelContainerPtr, IntPtr windowPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Debugger_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Debugger_BeginUpdate(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Debugger_EndUpdate(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_GetWindow(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Debugger_Get_IsRunning(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Debugger_Set_IsRunning(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_GetRenderContext(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Debugger_Is3DMode(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_GetSelectedSimulator(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Debugger_GetSelectedEntity(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_TopBarDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_MainDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_LeftSidebarDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_CenterDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_RightSidebarDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_CenterMainDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Debugger_Get_CenterBottomDockID(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RunWithProgressBar();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SetBindingType(/* ASCII String */ byte* bindingType);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_License_ForceOnlineFetch();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Initialize();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Uninitialize();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_GetMajorVersion();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_GetMinorVersion();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_GetPatchVersion();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_IsDebugBuild();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_License_Check();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_License_Activate(int licenseType);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_License_Deactivate();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_License_Info_DaysRemaining();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_License_Info_LicenseType();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_License_HasFeature(/* ASCII String */ byte* featureCode);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_License_GetLimits_MaxJobSystemCores();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_License_GetLimits_MaxComponentTypes();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_License_EditionName();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_Trace(/* ASCII String */ byte* message);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_Debug(/* ASCII String */ byte* message);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_Warning(/* ASCII String */ byte* message);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_Info(/* ASCII String */ byte* message);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_Error(/* ASCII String */ byte* message);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_Critical(/* ASCII String */ byte* message);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Logger_SetLogLevel(int logLevel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Logger_AddCallback(delegate* unmanaged[Cdecl]<int, IntPtr, IntPtr, void> logCallback, IntPtr callbackData);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_Settings_GetSetting(/* ASCII String */ byte* section, /* ASCII String */ byte* message, /* ASCII String */ byte* defaultValue);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Settings_SetSetting(/* ASCII String */ byte* section, /* ASCII String */ byte* message, /* ASCII String */ byte* value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Settings_Clear();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_VirtualFileSystem_MountDirectory(/* ASCII String */ byte* path, /* ASCII String */ byte* directoryName);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Serializer_IsWriting(IntPtr serializerHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeUInt64(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeInt64(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeUInt32(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeInt32(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeDouble(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeBool(IntPtr serializerHandle, /* ASCII String */ byte* key, bool* value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeFloat(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeString(IntPtr serializerHandle, /* ASCII String */ byte* key, /* ASCII String */ byte* value, ref int length);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_PushObject(IntPtr serializerHandle, /* ASCII String */ byte* key);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PopObject(IntPtr serializerHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SetObject(IntPtr serializerHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_PushArray(IntPtr serializerHandle, /* ASCII String */ byte* key, ref int size);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PopArray(IntPtr serializerHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_Serializer_GetArraySize(IntPtr serializerHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SaveToFolder(IntPtr modelContainerInstance, /* ASCII String */ byte* folderPath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_Serializer_LoadFromFolder(/* ASCII String */ byte* folderPath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SaveToArchive(IntPtr modelContainerInstance, /* ASCII String */ byte* archivePath, int compressionLevel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_Serializer_LoadFromArchive(/* ASCII String */ byte* archivePath, [MarshalAs(UnmanagedType.I1)] bool useCache);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_ClearArchiveCache(/* ASCII String */ byte* archivePath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueUInt64(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueInt64(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueUInt32(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueInt32(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueDouble(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeValueBool(IntPtr serializerHandle, nuint index, bool* value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueFloat(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeValueString(IntPtr serializerHandle, nuint index, /* ASCII String */ byte* value, ref int length);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PushArrayElement(IntPtr serializerHandle, nuint index, ref int size);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PushObjectElement(IntPtr serializerHandle, nuint index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_PathSegment_GetType(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetFromX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetFromY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetFromZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetToX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetToY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetToZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetCenterX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetCenterY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetCenterZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetRadius(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetBeginAngle(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetEndAngle(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetEndZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP0X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP0Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP0Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP1X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP1Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP1Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP2X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP2Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP2Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP3X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP3Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_PathSegment_GetP3Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathSegment_GetPointAlongPath(IntPtr instance, float t, IntPtr vec3out);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathSegment_GetRotationAlongPath(IntPtr instance, float t, IntPtr vec3out);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Random_Generator_Set_Seed(IntPtr generator, nuint seed);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern double ERS_Random_Generator_Sample(IntPtr generator);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Random_Generator_Reset(IntPtr generator);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_Random_Generator_GetType(IntPtr generator);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Profiler_StartSession();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Profiler_PrintResults();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_String_Destroy(IntPtr str);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ThreadLocal_GetSubModel();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ThreadLocal_GetSubModelOrNull();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ThreadLocal_InsideSubModel();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ThreadLocal_EnterSubModel(IntPtr submodel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ThreadLocal_ExitSubModel();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ThreadLocal_GetCurrentSyncEvent();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ThreadLocal_IsInsideSyncEvent();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 ERS_ThreadLocal_GetSyncEventTarget();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 ERS_ThreadLocal_GetSyncEventSender();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelContainer_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Release(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Increase(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_ModelContainer_GetSimulatorsCount(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelContainer_GetSimulator(IntPtr modelContainerInstance, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelContainer_GetSimulatorById(IntPtr modelContainerInstance, Int32 simulatorId);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_ModelContainer_AddSimulator(IntPtr modelContainerInstance, /* ASCII String */ byte* tag, byte simulatorType);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_RemoveSimulator(IntPtr modelContainerInstance, IntPtr coreSimulator);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern SimulationTime ERS_ModelContainer_CurrentTime(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Update_Blocking(IntPtr modelContainerInstance, SimulationTime timeStep);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern double ERS_ModelContainer_SimulationSpeedOverRealtime(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_SetModelPrecision(IntPtr modelContainerInstance, UInt64 newPrecision);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_ModelContainer_GetModelPrecision(IntPtr modelContainerInstance);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ModelContainer_IsStarted(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_SetSeed(IntPtr modelContainerInstance, nuint seed);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_GenerateRandomSeed(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_ModelContainer_Seed(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelContainer_FindSimulatorById(IntPtr modelContainerInstance, Int32 id);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_ModelContainer_FindSimulatorByTag(IntPtr modelContainerInstance, /* ASCII String */ byte* tag);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_AddSimulatorDependency(IntPtr modelContainerInstance, IntPtr fromSharedPtr, IntPtr toSimulatorSharedPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_RemoveSimulatorDependency(IntPtr modelContainerInstance, IntPtr fromSimulatorSharedPtr, IntPtr toSimulatorSharedPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Start(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelContainer_GetWorkingDir(IntPtr modelContainerInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_ModelContainer_SetWorkingDir(IntPtr modelContainerInstance, /* ASCII String */ byte* path);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelManager_GetModelManager();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelManager_AddModelContainer(IntPtr modelManager, IntPtr modelContainer, UInt64 releaseTime);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelManager_RemoveModelContainer(IntPtr modelManager, IntPtr modelContainer);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_ModelManager_CountModelContainers(IntPtr modelManager);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelManager_GetModelContainerAt(IntPtr modelManager, nuint index);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ModelManager_HasModelContainer(IntPtr modelManager, IntPtr modelContainer);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelManager_Update(IntPtr updateManager);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_LibraryCollection_OpenLibrary(IntPtr instance, /* ASCII String */ byte* libraryPath);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_LibraryCollection_IsLibraryOpen(IntPtr instance, /* ASCII String */ byte* libraryPath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_LibraryCollection_GetFunctionFromLibrary(IntPtr instance, /* ASCII String */ byte* libraryPath, /* ASCII String */ byte* functionName);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_LibraryCollection_GetLibraryHandle(IntPtr instance, /* ASCII String */ byte* libraryPath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_PersistentEvent_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PersistentEvent_Release(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_PersistentEvent_IsEmpty(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_PersistentEvent_GetSimulator(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_PersistentEvent_GetSimEvent(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_SimEvent_Get_Time(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_SimEvent_Get_Priority(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SimEvent_IsSyncEvent(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_GetLibraryCollection(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_GetSubModel(IntPtr instance);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Simulator_IsRunTogether(IntPtr instance, Int32 otherSimulatorId);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Simulator_IsBiDirectional(IntPtr instance, Int32 otherSimulatorId);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_GetName(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_Simulator_GetTimeStep(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Simulator_SetTimeStep(IntPtr instance, UInt64 newTimeStep);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 ERS_Simulator_GetID(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern byte ERS_Simulator_GetSimulatorType(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_GetAttachedModelContainer(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_Simulator_GetDependenciesAmount(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_GetDependencyName(IntPtr instance, nuint index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_FindDependencyById(IntPtr instance, Int32 simulatorId);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_Simulator_FindDependencyByName(IntPtr instance, /* ASCII String */ byte* nameTag, int nameSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Simulator_FindOutgoingDependencyById(IntPtr instance, Int32 id);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_Simulator_FindOutgoingDependencyByName(IntPtr instance, /* ASCII String */ byte* nameTag, int nameSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern SimulationTime ERS_Simulator_GetCurrentTime(IntPtr simulatorInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_BoxComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Min_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Min_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Min_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Max_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Max_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Max_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BoxComponent_Set_Min(IntPtr instance, float minX, float minY, float minZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BoxComponent_Set_Max(IntPtr instance, float maxX, float maxY, float maxZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Dimensions_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Dimensions_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_BoxComponent_Get_Dimensions_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BoxComponent_Set_Dimensions(IntPtr instance, float dimsX, float dimsY, float dimsZ);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_BoxComponent_InCollision_Point2D(IntPtr instance, float pointX, float pointY);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_BoxComponent_InCollision_Ray(IntPtr instance, float posX, float posY, float posZ, float dirX, float dirY, float dirZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_ChannelComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ChannelComponent_RegisterType(IntPtr submodelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_ChannelComponent_GetType(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_ChannelComponent_GetConnectedTo(IntPtr instance);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ChannelComponent_IsOpen(IntPtr instance);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ChannelComponent_IsOpenStatic(Entity channel);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Channel_Send(Entity channelFrom, Entity child);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_Open(Entity channel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_Close(Entity channel);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Channel_IsReady(Entity channel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_Connect(Entity channelA, Entity channelB);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_AddChannelComponent(Entity channel, int type, Entity resource);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe UInt32 ERS_GlobalComponentRegistry_RegisterScriptBehavior(/* ASCII String */ byte* name, delegate* unmanaged[Cdecl]<IntPtr, IntPtr> CreateInstance, IntPtr handle, delegate* unmanaged[Cdecl]<IntPtr, void> OnCreation, delegate* unmanaged[Cdecl]<IntPtr, void> OnAwake, delegate* unmanaged[Cdecl]<IntPtr, void> OnStart, delegate* unmanaged[Cdecl]<IntPtr, void> OnUpdate, delegate* unmanaged[Cdecl]<IntPtr, void> OnLateUpdate, delegate* unmanaged[Cdecl]<IntPtr, void> OnDestroy, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnEntering, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnEntered, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnExiting, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnExited, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnInputChannelReady, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnOutputChannelReady, delegate* unmanaged[Cdecl]<IntPtr, Entity, Entity, void> OnReceive, delegate* unmanaged[Cdecl]<IntPtr, IntPtr, void> Serialization, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnSubModelMove);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe UInt32 ERS_GlobalComponentRegistry_RegisterComponent(/* ASCII String */ byte* name, nuint sz, IntPtr typeInfoPtr, IntPtr customSerialize);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_GlobalComponentRegistry_IsRegistered(UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_NameComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_NameComponent_GetName(IntPtr nameComponentPointer);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_NameComponent_SetName(IntPtr nameComponentPointer, /* ASCII String */ byte* newName, int newNameSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_OutlineComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Get_Center_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_OutlineComponent_Set_Center_X(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Get_Center_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_OutlineComponent_Set_Center_Y(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Get_Center_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_OutlineComponent_Set_Center_Z(IntPtr instance, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Get_Dimensions_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Get_Dimensions_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Get_Dimensions_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_OutlineComponent_Set_Dimensions(IntPtr instance, float dimsX, float dimsY, float dimsZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_PathComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_PathComponent_GetSegment(IntPtr instance, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_PathComponent_GetNumSegments(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathComponent_AddStraight(IntPtr instance, float fromX, float fromY, float fromZ, float toX, float toY, float toZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathComponent_AddHelical(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathComponent_AddCubicBezier(IntPtr instance, float p0X, float p0Y, float p0Z, float p1X, float p1Y, float p1Z, float p2X, float p2Y, float p2Z, float p3X, float p3Y, float p3Z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathComponent_AddCubicBezierFromDirections(IntPtr instance, float startX, float startY, float startZ, float startDirX, float startDirY, float startDirZ, float endX, float endY, float endZ, float endDirX, float endDirY, float endDirZ, float curvature);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_RelationComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RelationComponent_RegisterType(IntPtr submodelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_RelationComponent_GetParent(IntPtr relationComponent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_RelationComponent_GetFirst(IntPtr relationComponent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_RelationComponent_GetLast(IntPtr relationComponent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_RelationComponent_GetPrevious(IntPtr relationComponent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_RelationComponent_GetNext(IntPtr relationComponent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_RelationComponent_GetChildCount(IntPtr relationComponent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_RenderComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern byte ERS_RenderComponent_GetShape(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderComponent_SetShape(IntPtr instance, byte shape);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_RenderComponent_GetColor(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderComponent_SetColor(IntPtr instance, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderComponent_GetTexture2D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderComponent_SetTexture2D(IntPtr instance, IntPtr texturePtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderComponent_RemoveTexture2D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderComponent_SetInstancedModel(IntPtr instance, IntPtr instancedModel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderComponent_GetInstancedModel(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_ResourceComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ResourceComponent_RegisterType(IntPtr submodelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_ResourceComponent_GetNumInputChannels(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_ResourceComponent_GetNumOutputChannels(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_ResourceComponent_GetInputChannel(IntPtr instance, nuint index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_ResourceComponent_GetOutputChannel(IntPtr instance, nuint index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ResourceComponent_CloseAllInput(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ResourceComponent_OpenAllInput(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ResourceComponent_CloseAllOutput(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ResourceComponent_OpenAllOutput(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_TransformComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_RegisterType(IntPtr submodelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Position_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetPosition_X(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Position_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetPosition_Y(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Position_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetPosition_Z(IntPtr instance, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetPosition(IntPtr instance, float x, float y, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Scale_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetScale_X(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Scale_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetScale_Y(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Scale_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetScale_Z(IntPtr instance, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetScale(IntPtr instance, float x, float y, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Rotation_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetRotation_X(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Rotation_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetRotation_Y(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_Rotation_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetRotation_Z(IntPtr instance, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_Rotate_X(IntPtr instance, float angle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_Rotate_Y(IntPtr instance, float angle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_Rotate_Z(IntPtr instance, float angle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetRotationEuler(IntPtr instance, float x, float y, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformComponent_SetQuaternion(IntPtr instance, float x, float y, float z, float w);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalPosition_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalPosition_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalPosition_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalScale_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalScale_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalScale_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalRotation_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalRotation_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_TransformComponent_GlobalRotation_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Entity_Invalid();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Entity_GetParent(Entity currentEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_Entity_GetChildCount(Entity currentEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Entity_GetFirstChild(Entity currentEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Entity_GetLastChild(Entity currentEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Entity_GetPreviousSibling(Entity currentEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Entity_GetNextSibling(Entity currentEntity);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Entity_IsValid(Entity currentEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_EventScheduler_RegisterLocalEventType(UInt64 typeIdentifier, delegate* unmanaged[Cdecl]<IntPtr, void> callback, delegate* unmanaged[Cdecl]<IntPtr, void> destructor, delegate* unmanaged[Cdecl]<IntPtr, IntPtr, void> serialize, delegate* unmanaged[Cdecl]<IntPtr> allocator, /* ASCII String */ byte* uniqueName, /* ASCII String */ byte* sourceLibrary, nuint size, /* ASCII String */ byte* filePath, int lineNumber);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_EventScheduler_RegisterSyncEventType(UInt64 eventTypeIdentifier, delegate* unmanaged[Cdecl]<void> onSenderSideCallback, delegate* unmanaged[Cdecl]<void> onTargetSideCallback, delegate* unmanaged[Cdecl]<IntPtr, IntPtr, void> serializeData, UInt32 dataBlockSize, /* ASCII String */ byte* name, /* ASCII String */ byte* sourceLibrary, /* ASCII String */ byte* filePath, int lineNumber);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_EventScheduler_ScheduleLocalEvent(int priority, UInt64 delay, IntPtr dataPtr, IntPtr eventTypeInfo);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_CancelEvent(UInt64 eventKey);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_SetPromise(UInt64 promise, Int32 outgoingDependencyID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_EventScheduler_LastScheduledSyncEvent();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_EventScheduler_GetPromise(Int32 outgoingDependencyID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_EventScheduler_ScheduleSyncEvent(UInt64 delay, Int32 targetSimulatorId, IntPtr syncEventTypeInfo);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_EventScheduler_ExchangeSyncEventForEventID(IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_DelayEvent(UInt64 key, UInt64 delayAmount);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_EventScheduler_AllocLocalEvent(IntPtr eventTypeInfo);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_FreeLocalEvent(IntPtr dataPtr, IntPtr eventTypeInfo);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_SubModel_Move_Entity_To(IntPtr targetSubModel, IntPtr sourceSubModel, Entity sourceEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe Entity ERS_SubModel_Entity_Create_Name_Parent(IntPtr submodel, /* ASCII String */ byte* entityName, Entity parent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_SubModel_Entity_Create(IntPtr subModelPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe Entity ERS_SubModel_Entity_Create_Name(IntPtr subModelHandle, /* ASCII String */ byte* entityName);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe Entity ERS_SubModel_FindEntity(IntPtr submodelInstance, /* ASCII String */ byte* entityName);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe Entity ERS_SubModel_FindEntity_Parent(IntPtr subModelInstance, /* ASCII String */ byte* entityName, Entity root);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SubModel_Entity_Destroy(IntPtr subModel, Entity entity);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SubModel_Entity_Exists(IntPtr submodel, Entity entityId);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_Entity_Relation_Update_Parent(IntPtr subModelHandle, Entity entityId, Entity parentId);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_AddScriptBehavior(IntPtr subModelHandle, Entity entityID, UInt32 componentID, IntPtr managedHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetScriptBehavior(IntPtr subModelHandle, Entity entityID, UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RemoveScriptBehavior(IntPtr subModelHandle, Entity entity, UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetComponent(IntPtr subModelHandle, Entity entity, UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_AddDataComponent(IntPtr subModelHandle, Entity entity, UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetSimulator(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_RemoveDataComponent(IntPtr subModelHandle, Entity entity, UInt32 componentID);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SubModel_HasComponent(IntPtr subModelHandle, Entity entity, UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetRandomProperties(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_SubModel_SendEntityTo(IntPtr subModelInstance, Int32 toSimulator, Entity entity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_SubModel_ReceiveEntityFrom(IntPtr subModelInstance, Int32 fromSimulator, Entity pipeEntity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_SubModel_RootEntityID(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern double ERS_SubModel_GenerateRandomDouble(IntPtr subModelHandle, double min, double max);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_SubModel_GetModelPrecision(IntPtr subModelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_SubModel_RegisterSubModelContext();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SubModel_AddSubModelContext(IntPtr subModelHandle, UInt32 SubModelContextTypeIdx, /* ASCII String */ byte* name, IntPtr SubModelContextPtr, delegate* unmanaged[Cdecl]<IntPtr, void> destructor);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetContext(IntPtr subModelHandle, UInt32 SubModelContextTypeIdx);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModelRandomProperties_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModelRandomProperties_Destroy(IntPtr properties);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModelRandomProperties_SetRandomGenerator_Type(IntPtr submodel, int randomNumberGeneratorType);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModelRandomProperties_SetRepetitive(IntPtr submodel, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModelRandomProperties_SetAntithetical(IntPtr submodel, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModelRandomProperties_SetSeed(IntPtr submodel, nuint seed);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SubModelRandomProperties_IsRepetitive(IntPtr submodel);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SubModelRandomProperties_IsAntithetical(IntPtr submodel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_SubModelRandomProperties_GetOriginalSeed(IntPtr submodel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModelRandomProperties_GetRandomNumberGenerator(IntPtr submodel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_TypeInfo_RegisterStruct(/* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_TypeInfo_AddField(IntPtr componentTypeInfoPtr, /* ASCII String */ byte* name, UInt32 fieldType, nuint offset, [MarshalAs(UnmanagedType.I1)] bool readOnly);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_TypeInfo_GetName(IntPtr componentTypeInfoPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Submodel_View_Create(IntPtr subModelHandle, IntPtr includedTypeIdArray_, UInt32 includedTypeArraySize, IntPtr excludedTypeIdArray_, UInt32 excludedTypeArraySize);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Submodel_View_Next(IntPtr viewHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Submodel_View_GetComponent(IntPtr viewHandle, nuint typeIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern ref IntPtr ERS_Submodel_View_GetComponents(IntPtr viewHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Submodel_View_GetEntity(IntPtr viewHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Submodel_View_Destroy(IntPtr view);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_SyncEvent_GetSyncEventUID(IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SyncEvent_GetData(IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_CollisionSystem_UpdateBoundingBoxes(IntPtr subModelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathAnimationSystem_Update(SimulationTime currentTime);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathAnimationSystem_Animate(Entity toAnimate, SimulationTime startTime, SimulationTime endTime, float fromValue, float toValue, Entity entityContainingPath, int pathIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathAnimationSystem_AnimateStraightPath(Entity toAnimate, SimulationTime startTime, SimulationTime endTime, float fromX, float fromY, float fromZ, float toX, float toY, float toZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderSystem_Render2D(IntPtr subModelInstance, IntPtr renderContextInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderSystem_Render3D(IntPtr subModelInstance, IntPtr renderContextInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformSystem_UpdateGlobals(IntPtr subModelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ImGui_StyleColorsErsDark();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ImGui_StyleColorsErsLight();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_ImGui_SwitchButton(/* ASCII String */ byte* label, bool* value, int flags);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_ImGui_DragVectorXYZ(/* ASCII String */ byte* label, IntPtr x, IntPtr y, IntPtr z, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Window_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_Window_Create_Title(/* ASCII String */ byte* title);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_BeginFrame(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_EndFrame(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Window_BeginRootDockSpace(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_EndRootDockSpace(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Window_GetRootDockSpaceID(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Window_Get_WantsClose(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_Set_WantsClose(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Window_SetWindowTitle(IntPtr ptr, /* ASCII String */ byte* title);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_Window_SetWindowIcon(IntPtr ptr, /* ASCII String */ byte* path);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_EntityInspectorWidget_Window(IntPtr simulatorPtr, Entity entity, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EntityInspectorWidget_Widget(IntPtr simulatorPtr, Entity entity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EntityInspectorWidget_EntityData(IntPtr simulatorPtr, Entity entity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EntityInspectorWidget_ComponentData(IntPtr simulatorPtr, Entity entity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_EventInspectorWidget_Window(IntPtr persistentEventPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventInspectorWidget_Widget(IntPtr persistentEventPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventInspectorWidget_EventDetails(IntPtr persistentEventPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventInspectorWidget_SyncEventDetails(IntPtr persistentEventPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventInspectorWidget_LocalEventDetails(IntPtr persistentEventPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_EventTimelineWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventTimeLineWidget_Destroy(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_EventTimelineWidget_Window(IntPtr ptr, IntPtr modelContainerPtr, IntPtr persistentEventPtr, [MarshalAs(UnmanagedType.I1)] bool isRunning, /* ASCII String */ byte* name, bool* open, int flags);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_EventTimelineWidget_Widget(IntPtr ptr, IntPtr modelContainerPtr, IntPtr persistentEventPtr, [MarshalAs(UnmanagedType.I1)] bool isRunning);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_EventTimelineWidget_Get_ShowLocalEvents(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventTimelineWidget_Set_ShowLocalEvents(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_EventTimelineWidget_Get_ShowSyncEvents(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventTimelineWidget_Set_ShowSyncEvents(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_EventTimelineWidget_Get_AutoScroll(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventTimelineWidget_Set_AutoScroll(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_EventTimelineWidget_Get_MaxEvents(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventTimelineWidget_Set_MaxEvents(IntPtr ptr, nuint value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InspectorWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InspectorWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_InspectorWidget_Window(IntPtr ptr, byte selectedType, IntPtr modelContainerPtr, IntPtr simulatorPtr, IntPtr entitySimulatorPtr, Entity entity, IntPtr persistentEventPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InspectorWidget_Widget(IntPtr ptr, byte selectedType, IntPtr modelContainerPtr, IntPtr simulatorPtr, IntPtr entitySimulatorPtr, Entity entity, IntPtr persistentEventPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_LicensingWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_LicensingWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_LicensingWidget_Window(IntPtr ptr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_LicensingWidget_Widget(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_LogWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_LogWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_LogWidget_Window(IntPtr ptr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_LogWidget_Widget(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_LogWidget_Get_SelectedLogLevel(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_LogWidget_Set_SelectedLogLevel(IntPtr ptr, int logLevel);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_LogWidget_Get_AutoScroll(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_LogWidget_Set_AutoScroll(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool autoScroll);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_ModelContainerInspectorWidget_Window(IntPtr modelContainerPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainerInspectorWidget_Widget(IntPtr modelContainerPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelHierarchyWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelHierarchyWidget_Destroy(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_ModelHierarchyWidget_Window(IntPtr ptr, IntPtr modelContainerPtr, ref IntPtr selectedSimulatorPtr, ref IntPtr selectedEntitySimulatorPtr, ref Entity selectedEntity, ref byte selectedTypePtr, /* ASCII String */ byte* name, bool* open, int flags);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ModelHierarchyWidget_Widget(IntPtr modelContainerPtr, int treeNodeFlags, ref IntPtr selectedSimulatorPtr, ref IntPtr selectedEntitySimulatorPtr, ref Entity selectedEntity, ref byte selectedTypePtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelProgressionWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelProgressionWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_ModelProgressionWidget_Window(IntPtr ptr, IntPtr modelContainerPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelProgressionWidget_Widget(IntPtr ptr, IntPtr modelContainerPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelProgressionWidget_Reset(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ModelStructureWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_ModelStructureWidget_Window(IntPtr ptr, IntPtr modelContainerPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Widget(IntPtr ptr, IntPtr modelContainerPtr, int heatMapMode);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ModelStructureWidget_Get_ShowGrid(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Set_ShowGrid(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_ModelStructureWidget_Get_SelectedHeatMapMode(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Set_SelectedHeatMapMode(IntPtr ptr, int value);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ModelStructureWidget_Get_ShowSimulatorGroups(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Set_ShowSimulatorGroups(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ModelStructureWidget_Get_ShowSimulatorSuperGroups(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Set_ShowSimulatorSuperGroups(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_ModelStructureWidget_Get_SelectedGroupStyle(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelStructureWidget_Set_SelectedGroupStyle(IntPtr ptr, int value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RunControlsWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RunControlsWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RunControlsWidget_Window(IntPtr ptr, IntPtr modelContainerPtr, bool* isRunning, /* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RunControlsWidget_Widget(IntPtr ptr, IntPtr modelContainerPtr, bool* isRunning);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SimulatorInspectorWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SimulatorInspectorWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SimulatorInspectorWidget_Window(IntPtr ptr, IntPtr simulatorPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SimulatorInspectorWidget_Widget(IntPtr ptr, IntPtr simulatorPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SpeedupWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SpeedupWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SpeedupWidget_Window(IntPtr ptr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SpeedupWidget_Widget(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SpeedupWidget_Update(IntPtr ptr, IntPtr modelContainerPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_VisualizationWidget_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_VisualizationWidget_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_VisualizationWidget_Window(IntPtr ptr, IntPtr renderContextPtr, /* ASCII String */ byte* name, bool* open, int flags);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_VisualizationWidget_Widget(IntPtr ptr, IntPtr renderContextPtr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_VisualizationWidget_Get_Is3DMode(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_VisualizationWidget_Set_Is3DMode(IntPtr ptr, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_UpdateTransform(IntPtr instance, int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera2D_GetPositionX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_SetPositionX(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera2D_GetPositionY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_SetPositionY(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera2D_GetZoom(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_SetZoom(IntPtr instance, float zoom);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera2D_SizePerPixel(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_GetWorldPos(IntPtr instance, int screenWidth, int screenHeight, float screenPosX, float screenPosY, IntPtr resultX, IntPtr resultY);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera2DController_Create(IntPtr camera2DPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_Destroy(IntPtr corePtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_ControlCamera(IntPtr instance, int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_SetScreenSize(IntPtr instance, int width, int height);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_Update(IntPtr instance, float mouseX, float mouseY);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_StartDragging(IntPtr instance, float mouseX, float mouseY);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_StopDragging(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_Zoom(IntPtr instance, float baseF, float power);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetPositionX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetPositionX(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetPositionY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetPositionY(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetPositionZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetPositionZ(IntPtr instance, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetLookAtX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetLookAtX(IntPtr instance, float x);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetLookAtY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetLookAtY(IntPtr instance, float y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetLookAtZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetLookAtZ(IntPtr instance, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetFovInTurns(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetFovInTurns(IntPtr instance, float fov);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetZNear(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetZNear(IntPtr instance, float zNear);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3D_GetZFar(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetZFar(IntPtr instance, float zFar);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_SetLookAt(IntPtr instance, float x, float y, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_UpdateTransform(IntPtr instance, int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3D_GetPickRay(IntPtr instance, int screenWidth, int screenHeight, int screenPosX, int screenPosY, IntPtr outPosX, IntPtr outPosY, IntPtr outPosZ, IntPtr outDirX, IntPtr outDirY, IntPtr outDirZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3DController_Create(IntPtr camera3DPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3DController_Destroy(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3DController_ControlCamera(IntPtr instance, int screenWidth, int screenHeight, float deltaTime, float lookAtZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3DController_Update(IntPtr instance, float deltaTime);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3DController_SwitchCameraMode(IntPtr instance, int mode);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_Camera3DController_GetCameraMode(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera3DController_GetHeadBobbingIntensity(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera3DController_SetHeadBobbingIntensity(IntPtr instance, float intensity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_InputHandler_GetAction(/* ASCII String */ byte* name);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_InputHandler_ExistsAction(/* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputHandler_Cycle();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputHandler_UpdateMousePos(int x, int y);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_InputAction_GetTriggered(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputAction_SetTriggered(IntPtr instance, [MarshalAs(UnmanagedType.I1)] bool triggered);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_InputAction_GetReleased(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputAction_SetReleased(IntPtr instance, [MarshalAs(UnmanagedType.I1)] bool released);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_InputAction_GetStrength(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputAction_SetStrength(IntPtr instance, float strength);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InstancedModel_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_Destroy(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_PushInstance(IntPtr instance, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_SetMesh(IntPtr instance, IntPtr meshPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_Clear(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Material_Copy_Shallow(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Material_GetDiffuseColor(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Material_SetDiffuseColor(IntPtr instance, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Mesh_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Release(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Increase(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Destroy(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Mesh_Material(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_SetDefaultMaterial(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Clear(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushVertex3D(IntPtr instance, float x, float y, float z, float nx, float ny, float nz, float u, float v, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushIndex(IntPtr instance, UInt32 index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushTriangle(IntPtr instance, float pos0X, float pos0Y, float pos0Z, float uv0X, float uv0Y, float pos1X, float pos1Y, float pos1Z, float uv1X, float uv1Y, float pos2X, float pos2Y, float pos2Z, float uv2X, float uv2Y, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushQuad(IntPtr instance, float pos0X, float pos0Y, float pos0Z, float uv0X, float uv0Y, float pos1X, float pos1Y, float pos1Z, float uv1X, float uv1Y, float pos2X, float pos2Y, float pos2Z, float uv2X, float uv2Y, float pos3X, float pos3Y, float pos3Z, float uv3X, float uv3Y, UInt32 color, float normX, float normY, float normZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushCube(IntPtr instance, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushSphere(IntPtr instance, float centerX, float centerY, float centerZ, byte subdivisions, float radius, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushPyramid(IntPtr instance, float centerX, float centerY, float centerZ, float dimsX, float dimsY, float dimsZ, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushBeam(IntPtr instance, float fromX, float fromY, float fromZ, float toX, float toY, float toZ, float upX, float upY, float upZ, float width, float height, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3D(IntPtr instance, IntPtr fontInstance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3DAligned(IntPtr instance, IntPtr fontInstance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpx, float worldUpy, float worldUpz, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushTextBillboard(IntPtr instance, IntPtr fontInstance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float cameraX, float cameraY, float cameraZ, float worldUpX, float worldUpY, float worldUpZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3DDefault(IntPtr instance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushVerticalHelicalStrip(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float stripHeight, UInt32 color, int segments, [MarshalAs(UnmanagedType.I1)] bool normalsInward);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushHorizontalHelicalStrip(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float stripLength, UInt32 color, int segments, [MarshalAs(UnmanagedType.I1)] bool normalUp);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushHelicalBeam(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float beamWidth, float beamHeight, UInt32 color, int segments);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3DAlignedDefault(IntPtr instance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpx, float worldUpy, float worldUpz, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushTextBillboardDefault(IntPtr instance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float cameraX, float cameraY, float cameraZ, float worldUpx, float worldUpy, float worldUpz, float scale, UInt32 color);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Mesh_CreateBuffers(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_DeleteBuffers(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_UpdateBuffers(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Draw(IntPtr instance, IntPtr shaderInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_Mesh_GetVertexCount(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern nuint ERS_Mesh_GetIndexCount(IntPtr instance);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Mesh_HasBuffers(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Mesh_GetVAO(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_TransformVertices2(IntPtr instance, float translationX, float translationY, float translationZ, float axisX, float axisY, float axisZ, float turns, float scaleX, float scaleY, float scaleZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_TransformVertices(IntPtr instance, IntPtr transform16);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_TransformVerticesRange(IntPtr instance, IntPtr transform16, UInt32 startIdx, UInt32 endIdx);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_CenterAtOrigin(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_TranslateToFloor(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_SetColor(IntPtr instance, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Normalize(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_GetMax(IntPtr instance, IntPtr outX, IntPtr outY, IntPtr outZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_GetMin(IntPtr instance, IntPtr outX, IntPtr outY, IntPtr outZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_SetTransform(IntPtr instance, IntPtr transform16);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushMesh(IntPtr instance, IntPtr otherInstance, float posX, float posY, float posZ, float axisX, float axisY, float axisZ, float turns, float scaleX, float scaleY, float scaleZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_GetTransform(IntPtr instance, IntPtr outTransform16);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Model3D_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Model3D_Destroy(IntPtr model);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_Model3D_Load(IntPtr modelHandle, /* ASCII String */ byte* path);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_Model3D_GetMeshCount(IntPtr modelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Model3D_SetTransform(IntPtr modelHandle, float x, float y, float z, float xRotAxis, float yRotAxis, float zRotAxis, float turns, float xScale, float yScale, float zScale);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Model3D_GetTransform(IntPtr modelHandle, IntPtr transformOut);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Model3D_GetMesh(IntPtr modelHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderContext_Create(int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Destroy(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderContext_GetCamera2D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_SetViewport(IntPtr instance, int width, int height);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_RenderContext_Get_DrawBackgroundGrid(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Set_DrawBackgroundGrid(IntPtr instance, [MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_RenderContext_Get_BackgroundColor(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Set_BackgroundColor(IntPtr instance, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_RenderContext_Get_BackgroundGridColor(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Set_BackgroundGridColor(IntPtr instance, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderContext_GetCamera3D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_ClearScreen(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Begin2D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_End2D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Begin3D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_End3D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawQuad2D(IntPtr instance, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawRect2D(IntPtr instance, float x, float y, float sizeX, float sizeY, float angle, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawCircle2D(IntPtr instance, float centerX, float centerY, float sizeX, float sizeY, int segments, float angle, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawScreenLine2D(IntPtr instance, float x0, float y0, float x1, float y1, float thickness, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawScreenLineRect2D(IntPtr instance, float x, float y, float sizeX, float sizeY, float angle, float thickness, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_DrawTextBillboard(IntPtr instance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_DrawText2D(IntPtr instance, /* ASCII String */ byte* text, float x, float y, float scale, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawTexture2D(IntPtr instance, IntPtr textureHandle, float x, float y, float width, float height, float uvMinX, float uvMinY, float uvMaxX, float uvMaxY, float angle, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawCube3D(IntPtr instance, float x, float y, float z, float xRotation, float yRotation, float zRotation, float xScale, float yScale, float zScale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_DrawText3D(IntPtr instance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpX, float worldUpY, float worldUpZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_SetLightDirection(IntPtr instance, float x, float y, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawLine2D(IntPtr instance, float x0, float y0, float x1, float y1, float thickness, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawTriangle2D(IntPtr instance, float x0, float y0, float x1, float y1, float x2, float y2, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawTriangle2D_Box(IntPtr instance, float centerX, float centerY, float sizeX, float sizeY, float angle, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawInstancedModel3DWithMesh(IntPtr renderContextHandle, IntPtr meshHandle, IntPtr instancedModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawInstancedModel3D(IntPtr renderContextHandle, IntPtr instancedModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawArc2D(IntPtr renderContextHandle, float centerX, float centerY, float radius, float width, float beginAngle, float endAngle, int segments, UInt32 color, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawModel3D(IntPtr instanceHandle, IntPtr modelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawMesh(IntPtr instance, IntPtr meshHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_CalculateTextSize(IntPtr instance, /* ASCII String */ byte* text, float scale, IntPtr width, IntPtr height);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_RenderContext_IsOpenGLInitialized();

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_RenderContext_InitializeOpenGL(IntPtr windowHandle, IntPtr displayHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderFramework_Create(IntPtr windowHandle, IntPtr displayHandle, int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderFramework_Present(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderFramework_DrawRenderContext(IntPtr instance, IntPtr renderContextHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderFramework_Destroy(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Texture_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Texture_Load(IntPtr instance, /* ASCII String */ byte* path);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Texture_Release(IntPtr instance);

    }
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
}
