# Changelog

## Unreleased

- added shared direct-state solver API via `app_run_solve_from_state(...)`
- added universal direct integration example for desktop and ESP32
- added pattern preset support through the shared runner API
- completed reverse FMC support with `384` total routes
- validated direct + reverse FMC on ESP32-WROOM-32D
- added benchmark and profiling infrastructure
- optimized major hotspots in:
  - `apply_solution_string`
  - `first_translate`
  - repeated F2L piece lookups
- added integration tutorial and publish-ready project documentation
