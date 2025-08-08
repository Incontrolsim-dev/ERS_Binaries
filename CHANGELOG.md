# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.5.2 - 2025-07-03

### Added

- Parallelization of models running in the ModelManager, greatly improving load distribution.

### Changed

- Some visualization log messages are now set to Debug level instead of Info level.
- Updated the Internal CPU load balancer to keep threads alive for `ModelContainer.Update()` and scale threadcount up or down base on the workload for Models running on the ModelManager.
  - For `ModelContainer.Update` this results in no studdering in visualisation when rendering takes time.
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
