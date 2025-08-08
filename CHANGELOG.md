
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
