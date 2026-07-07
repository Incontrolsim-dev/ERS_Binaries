# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.7.0 Nanna - 2026-07-07

### Added

- Added pre-defined point, rectangle, circle and triangle shapes to `RenderComponent`.
- Added 2D texture to `RenderComponent`.
- Added z-index parameter to set the layering of 2D rendering for:
  - `DrawLine2D`
  - `DrawTriangle2D`
  - `DrawQuad2D`
  - `DrawTexture2D`
  - `DrawText2D`  
- Added `DrawArc2D` to the C++ bindings.
- Added `ERS_RenderContext_DrawCircle2D` API function.
- Added `RenderContext::DrawArc2D` to the C++ bindings.
- Added various Mesh API functions:
  - `ERS_Mesh_Material`
  - `ERS_Mesh_PushSphere`
  - `ERS_Mesh_PushPyramid`
- Added working directory to the model container, which is used to load scripts and assets related to the model.
  - Added `ERS_ModelContainer_GetWorkingDir` API function.
  - Added `ERS_ModelContainer_SetWorkingDir` API function.
- Expanded event information visible in the Debugger
- Added event types for all events, Local and Sync events now have an event type.
  - Local events are defined by implementing `ILocalEvent<T>` (C#) or using the `ERS_EVENT` macro with an `OnEvent()` method (C++).
  - Sync events are defined by implementing `ISyncEvent<T>` (C#) or inheriting from `ISyncEvent<T>` (C++) with `GetName()`, `OnSenderSide()`, and `OnTargetSide()` methods.
  - Event types can be explicitly registered before simulation creation using `EventScheduler.RegisterLocalEvent<T>()` and `EventScheduler.RegisterSyncEvent<T>()`.
  - Events support automatic serialization: C# uses reflection-based field serialization by default; C++ uses the `ERS_EVENT(field1, field2, ...)` macro.
- Added functionality to the Debugger.Run function in the C# and C++ bindings to draw over multiple submodels.
  - The `Render2D` and `Render3D` callbacks now require a second `Simulator` parameter. This simulator is the currently iterated one.
- Added the `PushTriangle` function to `Mesh`.
- Added `GetAttachedModelContainer` (C++) and `AttachedModelContainer` (C#) to `Simulator`.
- Added a constructor for `Window` (previously `Platform`) to set the window title.
- Added `SetWindowTitle` function to set the title of a `Window`.
  - Added `ERS_Window_SetWindowTitle` to the API.
- Added `SetWindowIcon` function to set the icon of a `Window`.
  - Added `ERS_Window_SetWindowIcon` to the API.
- Added a static variant of `IsOpen` to `ChannelComponent` to make it consistent with the other channel functions.
- Added `GetAttachedModelContainer` (C++) and `AttachedModelContainer` (C#) to `Simulator`.
- Added option to the run controls speed pop-up to run as fast as possible.
- Added ImGui 1.92.8
- Added ImPlot 0.7
- Added ERS ImGui widgets to the C++ and C# bindings:
  - Entity Inspector Widget: inspect and edit an entity and its attached components.
  - Event Inspector Widget: inspect the data of an event.
  - Event Timeline Widget: shows a timeline of events.
  - Inspector Widget: inspector wrapper for all other inspector widgets.
  - Licensing Widget: license activation and management.
  - Log Widget: show the ERS log.
  - ModelContainer Inspector Widget: inspect and modify a model container's state.
  - Model Hierarchy Widget: shows the hierarchy of a model container with all simulators and entities.
  - Model Progression Widget: show the simulation progress of the simulators in a model.
  - Model Structure Widget: shows the structure of a model (simulator dependencies).
  - Run Controls Widget: controls the execution of a model container.
  - Simulator Inspector Widget: inspect and modify a simulator's state.
  - Speedup Widget: shows the speedup over realtime of a model container.
  - Visualization Widget: shows the visualization of a model.
  - SwitchButton: switch button (toggle).
  - DragVectorXYZ: input widget for a `Vector3`, consisting of three `DragFloat` widgets with color-coded XYZ labels.

### Changed

- All components must now be registered using ComponentRegistry<MyComponent>.Register() before creating a ModelContainer in which they are used.
  - This will break all existing `submodel.AddComponentType<MyComponent>` this must be refactored to the new method.
- Selecting an entity inside the Debugger is now done by left mouse instead of right mouse button.
- The step button inside the debugger now continues executing to the next event inside the simulation model. Inside the non-blocking mode the button is now disabled.
- The `CancelEvent` function can now cancel any event is scheduled at the same time, but still in queue. (But not the currently executing event)
- Renamed `ModelManager::GetModelManager()` to `ModelManager::Get()`.
- Renamed `SubModel::GetSubModel()` to `SubModel::Get()`.
- Renamed `BasicRenderSystem` to `RenderSystem` (a.k.a. standard render system).
- Renamed `BasicRenderComponent` to `RenderComponent`.
- The standard render system now uses the transform's scale in addition to the `BoxComponent` for the size of the visualized objects.
- Split various `BoxComponent` API functions into separate getters and setters:
  - Getters now have separate functions for the XYZ values:
    - `ERS_BoxComponent_Min_X` -> `ERS_BoxComponent_Get_Min_X`
    - `ERS_BoxComponent_Min_Y` -> `ERS_BoxComponent_Get_Min_Y`
    - `ERS_BoxComponent_Min_Z` -> `ERS_BoxComponent_Get_Min_Z`
    - `ERS_BoxComponent_Max_X` -> `ERS_BoxComponent_Get_Max_X`
    - `ERS_BoxComponent_Max_Y` -> `ERS_BoxComponent_Get_Max_Y`
    - `ERS_BoxComponent_Max_Z` -> `ERS_BoxComponent_Get_Max_Z`
    - `ERS_BoxComponent_Dimension_X` -> `ERS_BoxComponent_Get_Dimensions_X`
    - `ERS_BoxComponent_Dimension_Y` -> `ERS_BoxComponent_Get_Dimensions_Y`
    - `ERS_BoxComponent_Dimension_Z` -> `ERS_BoxComponent_Get_Dimensions_Z`
  - Setters
    - All min values are now set with a single function: `ERS_BoxComponent_Set_Min`.
    - All max values are now set with a single function: `ERS_BoxComponent_Set_Max`.
    - All dimension values are now set with a single function: `ERS_BoxComponent_Set_Dimensions`.
- `PushBeam` now takes a Vector2 instead of separate width and height parameters.
- Various functions in the C# bindings have been made properties:
  - `Parent`, `First`, `Last`, `Previous`, `Next`, and `ChildCount` on `RelationComponent`.
  - `GetNumInputChannels()` and `GetNumOutputChannels()` on `ResourceComponent`, and renamed them to `NumInputChannels` and `NumOutputChannels`.
  - `GetNumSegments` on `PathComponent`, and rename it to `NumSegments`.
  - `IsStarted`, `SimulatorCount`, `Precision`, and `Seed` on `ModelContainer`.
  - `GetCurrentTime`, `GetSeed`, and `TimeStep` on `Simulator`.
  - `EditionName` on `License`.
  - `GetSelectedSimulator`, `GetSelectedEntity`, `GetRenderContext`, `WantsRestart`, `Is3DMode`, and `ShowBackgroundGrid` on `Debugger`.
  - `WantsClose` on `Platform`.
  - `GetRandomGeneratorType` on `RandomGenerator`.
  - `InInsideSyncEvent`, `GetTargetSimulatorId`, `GetSenderSimulatorId` on `SyncEvent`.
  - `NumMeshes` on `Model3D`, renamed to `MeshCount`.
  - `IsTriggered` and `IsReleased` on `InputAction`.
  - `CountModelContainers` on `ModelManager`, renamed to `Count`.
- Rename `ModelManager::GetModelManager()` to `ModelManager::Get()`.
- Rename `SubModel::GetSubModel()` to `SubModel::Get()`.
- Rename `ModelContainer::CreateModelContainer()` to `ModelContainer::Create()`.
- Rename API function `ERS_ModelContainer_CreateModelContainer` to `ERS_ModelContainer_Create`.
- Split various API function to be separate getter and setter functions instead of using a pointer:
  - `ERS_Camera2D_PositionX`
  - `ERS_Camera2D_PositionY`
  - `ERS_Camera2D_Zoom`
  - `ERS_Camera3D_PositionX`
  - `ERS_Camera3D_PositionY`
  - `ERS_Camera3D_PositionZ`
  - `ERS_Camera3D_LookAtX`
  - `ERS_Camera3D_LookAtY`
  - `ERS_Camera3D_LookAtZ`
  - `ERS_Camera3D_FovInTurns`
  - `ERS_Camera3D_ZNear`
  - `ERS_Camera3D_ZFar`
  - `ERS_Camera3DController_HeadBobbingIntensity`
  - `ERS_InputAction_Triggered`
  - `ERS_InputAction_Released`
  - `ERS_InputAction_Strength`
  - `ERS_OutlineComponent_Center_X`
  - `ERS_OutlineComponent_Center_Y`
  - `ERS_OutlineComponent_Center_Z`
  - `ERS_OutlineComponent_Dimensions_X` (Getter only)
  - `ERS_OutlineComponent_Dimensions_Y` (Getter only)
  - `ERS_OutlineComponent_Dimensions_Z` (Getter only)
- API functions `ERS_Material_Color_X`, `ERS_Material_Color_Y`, `ERS_Material_Color_Z` have been merged into `ERS_Material_GetDiffuseColor` and `ERS_Material_SetDiffuseColor`.
- API function `ERS_OutlineComponent_SetDimensions` has been renamed to `ERS_OutlineComponent_Set_Dimensions` for more consistency.
- Use references in the C++ bindings where nullptr should not be allowed:
  - `RenderComponent::SetTexture2D` now takes a const reference parameter instead of a non-const pointer.
  - `RenderComponent::SetInstancedModel` now takes a const reference parameter instead of a non-const pointer.
  - `Mesh::PushMesh` now takes a const reference parameter instead of a non-const pointer.
- The `RenderContext` is now responsible for drawing the background grid.
  - Added `BackgroundColor` and `BackgroundGridColor` to `RenderContext` to make them configurable.
- Rename `Window` to `RenderFramework`. This included the related API functions:
  - Renamed `ERS_Window_Create` to `ERS_RenderFramework_Create`.
  - Renamed `ERS_Window_Destroy` to `ERS_RenderFramework_Destroy`.
  - Renamed `ERS_Window_Present` to `ERS_RenderFramework_Present`.
  - Renamed `ERS_Window_DrawRenderContext` to `ERS_RenderFramework_DrawRenderContext`.
- Renamed `Platform` to `Window`. This includes the related API functions:
  - Renamed `ERS_Platform_Create` to `ERS_Window_Create`.
  - Renamed `ERS_Platform_Destroy` to `ERS_Window_Destroy`.
  - Renamed `ERS_Platform_BeginFrame` to `ERS_Window_BeginFrame`.
  - Renamed `ERS_Platform_EndFrame` to `ERS_Window_EndFrame`.
  - Renamed `ERS_Platform_WantsClose` to `ERS_Window_WantsClose`.
- Updated dependencies:
  - Upgraded `assimp` from 6.0.1 to 6.0.2#1
  - Upgraded `catch2` from 3.8.1 to 3.11.0
  - Upgraded `cli11` from 2.5.0 to 2.6.1
  - Upgraded `curl` from 8.14.1 to 8.17.0
  - Upgraded `fmt` from 11.0.2#1 to 12.1.0
  - Upgraded `openssl` from 3.5.0#1 to 3.6.0#3
  - Upgraded `sdl2` from 2.32.8 to 2.32.10
  - Upgraded `spdlog` from 1.15.3 to 1.16.0
  - Upgraded `yyjson` from 0.11.1 to 0.12.0

### Removed

- Removed ERS Editor application.
- Removed Python scripting support while we redesign the feature.
- Removed `RandomGeneratorOwned` class in the C++ and C# bindings, which gave users the ability to create and manage owned random generators through the Ers platform.
- Removed `RenderContext::Present` function, because it no longer did anything.
- Removed `GetCurrentTime()` from ModelContainer in the C# bindings (the `CurrentTime` property remains).
- Removed `ERS_SyncEvent_SetSyncEventName` from the API, this was used to set names of SyncEvents but is replaced by new EventTypes
- Removed `ERS_EventScheduler_SyncEvent_GetData` Not needed anymore for scheduling
- Removed `ERS_SyncEvent_SetSyncEventMetaData` not needed anymore for scheduling sync events in all binding languages supported.
- Removed `ERS_SyncEvent_GetSyncEventMetaData` not needed anymore for scheduling sync events in all binding languages supported.
- Removed `ERS_SubModel_AddComponentType` Not needed anymore, components are now all registered globally before a model is created through the bindings.
- Removed `DrawInfiniteGrid2D` and `DrawInfiniteGrid3D` from `RenderContext` in all bindings.
- Removed `ERS_RenderContext_DrawInfiniteGrid2D` from the API.
- Removed `ERS_RenderContext_DrawInfiniteGrid3D` from the API.
- Removed `WantsRestart` variable from the `Debugger`.
- Removed `ERS_ModelContainer_Destroy` API function (`ERS_ModelContainer_Release` should be used instead).
- Removed old 4DScript files from `Ers/Common` in the C++ bindings.

### Fixed

- Fixed a bug where adding multiple submodel contexts resulted in all but the last one becoming unusable / throwing an exception when retrieved.
- The Views on submodels that are requested with components not registered on a submodel using `submodel.AddComponentType<MyComponent>` caused a crash, now we return `false` in the `view.Next()` method. preventing doing a loop an impossible combination.
- Consistently use `Vector2` or `Vector3` instead of `const Vector2&` or `const Vector3&` in the C++ bindings.
- `Material` in C# now uses the `Color` type for its color instead of a `Vector3`.
- Fix 3D meshes using the error material instead of the default material when no material is explicitly set (they now default to the default white material).
- Fix some functions missing from `InstancedModel` in the C++ bindings:
  - The constructor with a `Mesh` as its parameter.
  - `SetMesh`
- Fix some functions missing from `Mesh` in the C++ bindings:
  - `PushVertex`
  - `PushIndex`
  - `PushQuad`
- Fix `ResourceComponent` callbacks not firing.
- Fix `OnDestroy` being called on script behaviors when moving an entity between submodels. It will no longer be called.
- Fix an "InvalidOperationException" occurring in certain cases when using sync-events in C#.
- Fix Model Structure widget crashes on Linux and in some models.
- Fix `ModelContainer`'s speedup factor calculation not working with model precisions other than 1.000.000.

## 0.6.0 Utu - 2025-11-20

### Added

- ERS Editor as a C# application.
  - Editing components by field in the ERS Editor.
  - RunControls with live switching between blocking and non-blocking updates.
    - Live simulation speed indicator, with graph over last 60 seconds on hover.
    - Blocking
      - Speed slider to easily select desired simulation speed.
    - Non-blocking
      - Worker time budget slider, to alter update behavior and find performance bottlenecks in the model.
      - Maximum events execution budget slider, to alter update behavior and find performance bottlenecks in the model.
  - Visualization window included into the Ers Editor.
  - Licensing manager to Activate new licenses, view current license or deactivate the license.
- Adding types and components at runtime and through scripting.
- Added Saving & Loading functionality to C# and C++ bindings (Experimental)
  - New `Serialization` function in both DataComponents and ScriptBehaviors.
  - New Serializer class to serialize and deserialize the entire ModelContainer and data types on DataComponents and ScriptBehaviors.
  - Zstd compression to save ModelContainer including assets in 1 .ersmodel file.
  - With this release the saved model format is not finalized without notifying it might change in the next few releases.
- Resource Component: specialized component for material handling.
- Channel Component: Handling connections between resources for material handling.
- Added a lot more Python functions.
- Added 2D visualization through Python.
  - Default Render component.
- An increased grace period, and offline capabilities.
  - Add a 5 day period between online license checks.
  - Add 'ERS_License_ForceOnlineFetch()' to allow manually forcing an online license check.
- Creating a FORCEERSCHECK file inside the license directory forces ERS to contact the license platform on startup to receive license updates.
- Added error log messages when:
  - A component is not registered when using `AddComponent`, `GetComponent`, or `HasComponent`.
  - Scheduling a sync-event without defining a dependency between simulators.
  - Setting a promise when simulators do not have a dependency.
- `CalculateTextSize` function to pre-calculate the size of text before rendering.
- Added `Run` method on the Debugger to be able to run the ERS Debugger with one line of code.
- Added `ClearSettings` function to the Settings class, this deletes the erssettings.ini file created when ERS starts.
- Added `Color` struct to C++ and C# bindings.
- Added `Vector2`, `Vector3` and `Vector4` structs to C++ bindings.

### Changed

- Removed the `Ers::Model` namespace. All items under this namespace are now under the `Ers` namespace.
- Removed the `Ers::Debugging` namespace. All items under this namespace are now under the `Ers` namespace.
- Removed the `Ers::Platform` namespace. All items under this namespace are now under the `Ers` namespace.
- 2D text is now rendered from the top-left of the first character instead of the baseline of the first character.
- Renamed some ERS engine functions for more consistent naming:
  - `ERS_STRING_DISPOSE` -> `ERS_String_Destroy`
  - `ERS_SubModel_View_Dispose` -> `ERS_SubModel_View_Destroy`
  - `ERS_InstancedModel_Release` -> `ERS_InstancedModel_Destroy`
  - `ERS_ModelContainer_Dispose` -> `ERS_ModelContainer_Destroy`
  - `ERS_Mesh_Dispose` -> `ERS_Mesh_Destroy`
  - `ERS_RenderContext_Dispose` -> `ERS_RenderContext_Destroy`

### Deprecated

- ErsWinForms nuget package

### Removed

- Removed the `ERS_ThreadLocal_IsSyncEventInSenderSide` function from the API.
- Removed `ISyncEventCombined` from C# and C++ bindings. The exact original behavior can be replicated in a few lines of code by adding a function to a SyncEvent Struct.
- Ers.Math, Ers.Visualization, Ers.Model namespaces removed.

### Fixed

- Fix visualization not able to render `!` and `"` characters.
- Fix JobSystem worker count not always set correctly when using an Enterprise License

## 0.5.2 - 2025-07-03

### Added

- Parallelization of models running in the ModelManager, greatly improving load distribution.

### Changed

- Some visualization log messages are now set to Debug level instead of Info level.
- Updated the Internal CPU load balancer to keep threads alive for `ModelContainer.Update()` and scale thread count up or down base on the workload for Models running on the ModelManager.
  - For `ModelContainer.Update` this results in no stuttering in visualization when rendering takes time.
  - For ModelManager this results in lower overall CPU utilization, for equivalent simulation speed.

### Fixed

- Fix no constructor existing for Texture to load an image file in C#.
- Fix font size not being correctly calculated.

## 0.5.1 - 2025-06-25

### Added

- Added CHANGELOG file.
- Added notice of all used libraries and their licenses.
- Added `GetModelPrecision` function on SubModel.
- Added functions to check active license limits.
- Added function to get active license edition name.
- New visualization functionality:
  - Added default colors to the C++ bindings.
  - Added color helper functions to the C++ bindings.
  - Added text billboards.

### Changed

- Python: it is no longer required to have a specific Python version installed.
- Remove `EditingSubModel`, moving entering and exiting to the simulator.
- Rename all bindings initialize and uninitialize functions to `Initialize` and `Uninitialize`,
  making them consistent across all bindings.
- Replace `ApplyModelPrecision` functions with a version that does not take a reference.
- Changes to visualization:
  - Meshes now have a transform and a material. A Model3D now only consists of multiple meshes.
  - InstancedModel is now more flexible, allowing the mesh to be replaced with a single `SetMesh` function call.
  - Improved the look and clarity of the infinite 3D grid.
  - The infinite 2D grid now has configurable line lengths, allowing the grid to be visualized ranging from just its corners to full tiles.

### Removed

- Ability to execute sync events functions as part of another sync event
  - Removed because it slowed down all sync events, increased complexity and didn't see much use for models, since the same behavior could be achieved by simpler means.

### Fixed

- Fix ERS not exiting after first license activation.
- Fixed Linux NuGet package not including the ers-engine.so file.

## 0.4.0 - 2025-05-16

### Added

- Added licensing via LicenseSpring.
- Added dedicated `DrawInfiniteGrid3D`.
- Show simulation speed in model manager's progress bar.
- Added gamepad camera control support to ErsWinForms via the new input actions.

### Changed

- Refactor sync-events to use classes instead of separate callback functions.
- Refactor the InputHandler. It no longer requires all character inputs, instead it uses `InputAction`s.
  Input actions are more flexible and cross-platform, allowing multiple inputs to be mapped to certain behavior.
