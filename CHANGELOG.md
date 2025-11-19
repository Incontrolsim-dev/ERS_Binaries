# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.6.0 UTU 2025-11-20

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
  - Licensing manager to Activate new licenses, View current license or deactivate the license.
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

