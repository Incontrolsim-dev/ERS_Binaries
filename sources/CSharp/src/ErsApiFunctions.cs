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
        public static extern void ERS_Debugger_Destroy(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Debugger_WantsRestart(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Debugger_ShowBackgroundGrid(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Debugger_SetModelContainer(IntPtr ptr, IntPtr modelContainerPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_GetRenderContext(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Debugger_Is3DMode(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Debugger_GetSelectedSimulator(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Debugger_GetSelectedEntity(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Debugger_Update(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Platform_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Platform_Destroy(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Platform_BeginFrame(IntPtr ptr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Platform_EndFrame(IntPtr ptr);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Platform_WantsClose(IntPtr ptr);

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
        public static extern unsafe void ERS_Serializer_SerializeBool(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeFloat(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeString(IntPtr serializerHandle, /* ASCII String */ byte* key, /* ASCII String */ byte* value, IntPtr length);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_PushObject(IntPtr serializerHandle, /* ASCII String */ byte* key);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PopObject(IntPtr serializerHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SetObject(IntPtr serializerHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_PushArray(IntPtr serializerHandle, /* ASCII String */ byte* key, IntPtr size);

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
        public static extern void ERS_Serializer_SerializeValueBool(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_SerializeValueFloat(IntPtr serializerHandle, nuint index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Serializer_SerializeValueString(IntPtr serializerHandle, nuint index, /* ASCII String */ byte* value, IntPtr length);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PushArrayElement(IntPtr serializerHandle, nuint index, IntPtr size);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Serializer_PushObjectElement(IntPtr serializerHandle, nuint index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_CreateInterpreter(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SubModel_RunSimpleString(IntPtr subModelHandle, /* ASCII String */ byte* code);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SubModel_LoadPythonModuleFromFile(IntPtr subModelHandle, /* ASCII String */ byte* filePath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SubModel_LoadPythonPackage(IntPtr subModelHandle, /* ASCII String */ byte* packageFolderPath);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_AddInterpreterScriptComponentType(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_AddInterpreterScriptComponent(IntPtr subModelHandle, Entity entity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetInterpreterScriptComponent(IntPtr subModelHandle, Entity entity);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_SubModel_HasInterpreterScriptComponent(IntPtr subModelHandle, Entity entity);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_BeginInterpreterRenderContext(IntPtr subModelHandle, IntPtr renderContextHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_EndInterpreterRenderContext(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_GetInterpreterRenderContext(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_PrintInterpreterGCStats(IntPtr subModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Interpreter_RegisterFunction(/* ASCII String */ byte* functionName, IntPtr userData, delegate* unmanaged[Cdecl]<IntPtr, IntPtr, IntPtr> callback, /* ASCII String */ byte* docs);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterArgs_GetStringArgument(IntPtr interpreterArgsHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern double ERS_InterpreterArgs_GetDoubleArgument(IntPtr interpreterArgsHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_InterpreterArgs_GetEntityArgument(IntPtr interpreterArgsHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_InterpreterArgs_GetUInt64Argument(IntPtr interpreterArgsHandle, int index);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_InterpreterArgs_GetBoolArgument(IntPtr interpreterArgsHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern double ERS_InterpreterArgs_GetArgCount(IntPtr interpreterArgsHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterArgs_Create(int sz);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InterpreterArgs_Destruct(IntPtr interpreterArgsHandle);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_InterpreterArgs_HasAttribute(IntPtr interpreterArgsHandle, IntPtr interpreterObject, /* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_InterpreterArgs_DynamicInvoke(IntPtr interpreterArgsHandle, IntPtr interpreterObject, /* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InterpreterArgs_SetArgument(IntPtr interpreterArgsHandle, int index, IntPtr value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterComponent_UpdateEnabled(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterComponent_Render2DEnabled(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterVariable_None();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterVariable_CreateBool([MarshalAs(UnmanagedType.I1)] bool value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterVariable_CreateUInt64(UInt64 value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_InterpreterVariable_CreateString(/* ASCII String */ byte* value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterVariable_CreateDouble(double value);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InterpreterVariable_CreateEntity(Entity entityId);

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
        public static extern void ERS_PathSegment_GetPointAlongPath(IntPtr instance, float t, IntPtr vec3out);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathSegment_GetRotationAlongPath(IntPtr instance, float t, IntPtr vec3out);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Random_Generator_MersenneTwister_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Random_Generator_WichmannHill_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Random_Generator_Destroy(IntPtr generator);

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
        public static extern void ERS_STRING_DISPOSE(IntPtr str);

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
        public static extern IntPtr ERS_ModelContainer_CreateModelContainer();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Release(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Increase(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ModelContainer_Dispose(IntPtr instance);

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
        public static extern UInt32 ERS_BasicRenderComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BasicRenderComponent_CreateCallback();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BasicRenderComponent_GetColor(IntPtr instance, IntPtr r, IntPtr g, IntPtr b, IntPtr a);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BasicRenderComponent_SetColor(IntPtr instance, float r, float g, float b, float a);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BasicRenderComponent_SetInstancedModel(IntPtr instance, IntPtr instancedModel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BasicRenderComponent_GetInstancedModel(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_BoxComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_CreateCallback();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_Min_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_Min_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_Min_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_Max_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_Max_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_BoxComponent_Max_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BoxComponent_Center(IntPtr instance, IntPtr outCenterX, IntPtr outCenterY, IntPtr outCenterZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BoxComponent_Dimensions(IntPtr instance, IntPtr outDimX, IntPtr outDimY, IntPtr outDimZ);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_BoxComponent_InCollision_Point2D(IntPtr instance, float pointX, float pointY);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_BoxComponent_InCollision_Ray(IntPtr instance, float posX, float posY, float posZ, float dirX, float dirY, float dirZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_ChannelComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ChannelComponent_CreateCallback();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ChannelComponent_RegisterType(IntPtr submodelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_ChannelComponent_GetType(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_ChannelComponent_GetConnectedTo(IntPtr instance);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_ChannelComponent_IsOpen(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_ChannelComponent_GetlongitudinalPosition(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_ChannelComponent_SetlongitudinalPosition(IntPtr instance, float position);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_Send(Entity channelFrom, Entity child);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_Open(Entity channel);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_Channel_IsReady(Entity channel);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Channel_Connect(Entity channelA, Entity channelB);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe UInt32 ERS_GlobalComponentRegistry_RegisterScriptBehavior(/* ASCII String */ byte* name, delegate* unmanaged[Cdecl]<IntPtr, IntPtr> CreateInstance, IntPtr handle, delegate* unmanaged[Cdecl]<IntPtr, void> OnCreation, delegate* unmanaged[Cdecl]<IntPtr, void> OnAwake, delegate* unmanaged[Cdecl]<IntPtr, void> OnStart, delegate* unmanaged[Cdecl]<IntPtr, void> OnUpdate, delegate* unmanaged[Cdecl]<IntPtr, void> OnLateUpdate, delegate* unmanaged[Cdecl]<IntPtr, void> OnDestroy, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnEntering, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnEntered, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnExiting, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnExited, delegate* unmanaged[Cdecl]<IntPtr, IntPtr, void> Serialization, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnSubModelMove);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe UInt32 ERS_GlobalComponentRegistry_RegisterResourceComponent(UInt32 componentIDValue, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnOutputChannelReady, delegate* unmanaged[Cdecl]<IntPtr, Entity, void> OnInputChannelReady, delegate* unmanaged[Cdecl]<IntPtr, Entity, Entity, void> OnReceive);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe UInt32 ERS_GlobalComponentRegistry_RegisterComponent(/* ASCII String */ byte* name, nuint sz, IntPtr typeInfoPtr, IntPtr customSerialize);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ERS_GlobalComponentRegistry_IsRegistered(UInt32 componentID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_NameComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_NameComponent_CreateCallback();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_NameComponent_GetName(IntPtr nameComponentPointer);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_NameComponent_SetName(IntPtr nameComponentPointer, /* ASCII String */ byte* newName, int newNameSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_OutlineComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_OutlineComponent_CreateCallback();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_OutlineComponent_Center_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_OutlineComponent_Center_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_OutlineComponent_Center_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Dimensions_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Dimensions_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_OutlineComponent_Dimensions_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_OutlineComponent_SetDimensions(IntPtr instance, float dimsX, float dimsY, float dimsZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_PathComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_PathComponent_CreateCallback();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_PathComponent_GetSegment(IntPtr instance, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ERS_PathComponent_GetNumSegments(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathComponent_AddStraight(IntPtr instance, float fromX, float fromY, float fromZ, float toX, float toY, float toZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathComponent_AddHelical(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ);

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
        public static extern UInt32 ERS_ResourceComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_ResourceComponent_CreateCallback();

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
        public static extern UInt32 ERS_TransformComponent_TypeId();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_TransformComponent_CreateCallback();

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
        public static extern unsafe UInt64 ERS_EventScheduler_ScheduleLocalEvent(int priority, UInt64 delay, IntPtr dataPtr, delegate* unmanaged[Cdecl]<IntPtr, void> callback, delegate* unmanaged[Cdecl]<IntPtr, void> destructor);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_CancelEvent(UInt64 eventKey);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_SetPromise(UInt64 promise, Int32 outgoingDependencyID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_EventScheduler_LastScheduledSyncEvent();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt64 ERS_EventScheduler_GetPromise(Int32 outgoingDependencyID);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_EventScheduler_ScheduleSyncEvent(UInt64 delay, Int32 targetSimulatorId, UInt64 eventTypeIdentifier, delegate* unmanaged[Cdecl]<void> onSenderSideCallback, delegate* unmanaged[Cdecl]<void> onTargetSideCallback);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_EventScheduler_SyncEvent_GetData(UInt16 dataContextIdx, IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_EventScheduler_ExchangeSyncEventForEventID(IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_EventScheduler_DelayEvent(UInt64 key, UInt64 delayAmount);

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
        public static extern void ERS_SubModel_AddComponentType(IntPtr subModelHandle, UInt32 componentID);

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
        public static extern unsafe void ERS_TypeInfo_AddField(IntPtr componentTypeInfoPtr, /* ASCII String */ byte* name, UInt32 fieldType, nuint offset);

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
        public static extern IntPtr ERS_Submodel_View_GetComponents(IntPtr viewHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern Entity ERS_Submodel_View_GetEntity(IntPtr viewHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Submodel_View_Dispose(IntPtr view);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SubModel_Events_Disconnect(IntPtr connectionObjectPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnAwake();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnAwake_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnStart();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnStart_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnCreate();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnCreate_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnDestroy();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnDestroy_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnEntering();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnEntering_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnEntered();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnEntered_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnExiting();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnExiting_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnExited();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SubModel_RelationEvents_OnExited_Connect(IntPtr signalHandle, IntPtr signalFunction, IntPtr obj);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SyncEvent_GetSyncEventMetaData(IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_SyncEvent_SetSyncEventMetaData(IntPtr syncEvent, IntPtr dataPtr, byte index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_SyncEvent_SetSyncEventName(IntPtr syncEvent, /* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 ERS_SyncEvent_GetSyncEventUID(IntPtr syncEvent);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt16 ERS_SyncEvent_GetOrRegisterDataContext(IntPtr syncEvent, UInt64 identifier, UInt32 blockSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_SyncEvent_GetData(IntPtr syncEvent, UInt16 dataContextIdx);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BasicRenderSystem_Render2D(IntPtr subModelInstance, IntPtr renderContextInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_BasicRenderSystem_Render3D(IntPtr subModelInstance, IntPtr renderContextInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_CollisionSystem_UpdateBoundingBoxes(IntPtr subModelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InterpreterRenderSystem_Render2D();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InterpreterRenderSystem_BuildMesh3D(IntPtr meshPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathAnimationSystem_Update(SimulationTime currentTime);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_PathAnimationSystem_Animate(Entity toAnimate, SimulationTime startTime, SimulationTime endTime, float fromValue, float toValue, Entity entityContainingPath, int pathIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_TransformSystem_UpdateGlobals(IntPtr subModelInstance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_UpdateTransform(IntPtr instance, int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera2D_PositionX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera2D_PositionY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera2D_Zoom(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ERS_Camera2D_SizePerPixel(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2D_GetWorldPos(IntPtr instance, int screenWidth, int screenHeight, float screenPosX, float screenPosY, IntPtr resultX, IntPtr resultY);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera2DController_Create(IntPtr camera2DPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Camera2DController_Destroy(IntPtr coreInstance);

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
        public static extern IntPtr ERS_Camera3D_PositionX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_PositionY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_PositionZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_LookAtX(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_LookAtY(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_LookAtZ(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_FovInTurns(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_ZNear(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Camera3D_ZFar(IntPtr instance);

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
        public static extern IntPtr ERS_Camera3DController_HeadBobbingIntensity(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe IntPtr ERS_InputHandler_GetAction(/* ASCII String */ byte* name);

        [return: MarshalAs(UnmanagedType.I1)]
        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe bool ERS_InputHandler_ExistsAction(/* ASCII String */ byte* name);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputHandler_Cycle();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InputHandler_UpdateMousePos(int x, int y);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InputAction_Triggered(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InputAction_Released(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InputAction_Strength(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_InstancedModel_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_Release(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_PushInstance(IntPtr instance, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_SetMesh(IntPtr instance, IntPtr meshPtr);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_InstancedModel_Clear(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Material_Copy_Shallow(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Material_Color_X(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Material_Color_Y(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Material_Color_Z(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Mesh_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Release(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Increase(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Dispose(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_SetDefaultMaterial(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_Clear(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushVertex3D(IntPtr instance, float x, float y, float z, float nx, float ny, float nz, float u, float v, float colorR, float colorG, float colorB);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushIndex(IntPtr instance, UInt32 index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushQuad(IntPtr instance, float pos0X, float pos0Y, float pos0Z, float uv0X, float uv0Y, float pos1X, float pos1Y, float pos1Z, float uv1X, float uv1Y, float pos2X, float pos2Y, float pos2Z, float uv2X, float uv2Y, float pos3X, float pos3Y, float pos3Z, float uv3X, float uv3Y, float colorR, float colorG, float colorB, float normX, float normY, float normZ);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushCube(IntPtr instance, float posX, float posY, float posZ, float dimsX, float dimsY, float dimsZ, float colorR, float colorG, float colorB);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushBeam(IntPtr instance, float fromX, float fromY, float fromZ, float toX, float toY, float toZ, float upX, float upY, float upZ, float width, float height, float colorR, float colorG, float colorB);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3D(IntPtr instance, IntPtr fontInstance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3DAligned(IntPtr instance, IntPtr fontInstance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpx, float worldUpy, float worldUpz, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushTextBillboard(IntPtr instance, IntPtr fontInstance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float cameraX, float cameraY, float cameraZ, float worldUpX, float worldUpY, float worldUpZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Mesh_PushText3DDefault(IntPtr instance, /* ASCII String */ byte* text, float posX, float posY, float posZ, float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float scale, UInt32 color);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushVerticalHelicalStrip(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float stripHeight, float colorR, float colorG, float colorB, int segments, [MarshalAs(UnmanagedType.I1)] bool normalsInward);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushHorizontalHelicalStrip(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float stripLength, float colorR, float colorG, float colorB, int segments, [MarshalAs(UnmanagedType.I1)] bool normalUp);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Mesh_PushHelicalBeam(IntPtr instance, float centerX, float centerY, float centerZ, float radius, float beginAngle, float endAngle, float endZ, float beamWidth, float beamHeight, float colorR, float colorG, float colorB, int segments);

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
        public static extern void ERS_Mesh_SetColor(IntPtr instance, float colorR, float colorG, float colorB);

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
        public static extern int ERS_Model3D_GetMeshCount(IntPtr modelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Model3D_SetTransform(IntPtr modelHandle, float x, float y, float z, float xRotAxis, float yRotAxis, float zRotAxis, float turns, float xScale, float yScale, float zScale);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Model3D_GetTransform(IntPtr modelHandle, IntPtr transformOut);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Model3D_GetMesh(IntPtr modelHandle, int index);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderContext_Create(int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Dispose(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_RenderContext_GetCamera2D(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_SetViewport(IntPtr instance, int width, int height);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_SetBackgroundColor(IntPtr instance, float r, float g, float b, float a);

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
        public static extern void ERS_RenderContext_DrawQuad2D(IntPtr instance, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawRect2D(IntPtr instance, float x, float y, float sizeX, float sizeY, float angle, float colorR, float colorG, float colorB, float colorA, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawScreenLine2D(IntPtr instance, float x0, float y0, float x1, float y1, float thickness, float colorR, float colorG, float colorB, float colorA, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawScreenLineRect2D(IntPtr instance, float x, float y, float sizeX, float sizeY, float angle, float thickness, float colorR, float colorG, float colorB, float colorA, Int64 zIndex);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_DrawTextBillboard(IntPtr instance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float scale, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_DrawText2D(IntPtr instance, /* ASCII String */ byte* text, float x, float y, float scale, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawTexture2D(IntPtr instance, IntPtr textureHandle, float x, float y, float width, float height, float uvMinX, float uvMinY, float uvMaxX, float uvMaxY, float angle, float r, float g, float b, float a);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawCube3D(IntPtr instance, float x, float y, float z, float xRotation, float yRotation, float zRotation, float xScale, float yScale, float zScale, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawInfiniteGrid2D(IntPtr instance, float colorR, float colorG, float colorB, float lineThickness, float armLength, float targetPixelSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawInfiniteGrid3D(IntPtr instance, float colorR, float colorG, float colorB, float lineThickness, float targetPixelSize);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_RenderContext_DrawText3D(IntPtr instance, /* ASCII String */ byte* text, float centerX, float centerY, float centerZ, float normalX, float normalY, float normalZ, float worldUpX, float worldUpY, float worldUpZ, float scale, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_SetLightDirection(IntPtr instance, float x, float y, float z);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawLine2D(IntPtr instance, float x0, float y0, float x1, float y1, float thickness, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawTriangle2D(IntPtr instance, float x0, float y0, float x1, float y1, float x2, float y2, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawTriangle2D_Box(IntPtr instance, float centerX, float centerY, float sizeX, float sizeY, float angle, float colorR, float colorG, float colorB, float colorA);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawInstancedModel3DWithMesh(IntPtr renderContextHandle, IntPtr meshHandle, IntPtr instancedModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_Present(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawInstancedModel3D(IntPtr renderContextHandle, IntPtr instancedModelHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_RenderContext_DrawArc2D(IntPtr renderContextHandle, float x, float y, float radius, float width, float beginAngle, float endAngle, int segments, float colorR, float colorG, float colorB, float colorA);

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
        public static extern IntPtr ERS_Texture_Create();

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern unsafe void ERS_Texture_Load(IntPtr instance, /* ASCII String */ byte* path);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Texture_Release(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ERS_Window_Create(IntPtr windowHandle, IntPtr displayHandle, int screenWidth, int screenHeight);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_Present(IntPtr instance);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_DrawRenderContext(IntPtr instance, IntPtr renderContextHandle);

        [DllImport("ers-engine", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ERS_Window_Destroy(IntPtr instance);

    }
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
}
