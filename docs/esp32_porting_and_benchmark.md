# ESP32 Porting And Benchmark Notes

## Current Goal

The project now runs reliably on desktop and has a built-in FMC benchmark mode.
The next target is running on ESP32 boards, especially `ESP32-WROOM-32D`.

## PlatformIO Project

The repo now contains a root-level PlatformIO project file:

- [platformio.ini](C:\Users\Dani\Desktop\ZZOptimalCore\platformio.ini)

and a dedicated ESP32 entrypoint:

- [src/esp32_main.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\esp32_main.cpp)

This is configured for:

- `framework = arduino`
- `platform = espressif32`
- `board = esp32dev`

For an `ESP32-WROOM-32D`, `esp32dev` is the usual safe starting board target in PlatformIO.

## What Is Already Friendly For ESP32

- Core solving logic is plain C/C++.
- No STL-heavy containers are used in `main.cpp`.
- FMC benchmark can generate deterministic scrambles from a fixed seed.
- Solver-owned dynamic allocation is now tracked.
- Windows-only `chcp` call is disabled automatically on `ARDUINO` / `ESP_PLATFORM`.
- FMC routes are embedded in [include/fmc_routes.h](C:\Users\Dani\Desktop\ZZOptimalCore\include\fmc_routes.h), so no filesystem is needed.
- The app runner is separated into [include/app_runner.h](C:\Users\Dani\Desktop\ZZOptimalCore\include\app_runner.h) and [src/app_runner.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\app_runner.cpp).
- Platform timing and heap queries are abstracted in [include/zz_platform.h](C:\Users\Dani\Desktop\ZZOptimalCore\include\zz_platform.h) and [src/zz_platform.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\zz_platform.cpp).

## Current Desktop Benchmark Outputs

When `AppMode::FmcBenchmark` is enabled in `src/main.cpp`, the benchmark prints:

- success / fail count
- move-count statistics
- wall-clock time statistics
- solver-owned peak heap statistics
- static buffer sizes
- optional CSV path

It also writes CSV rows like:

```csv
seed,success,total_moves,face_moves,has_rotations,time_ms,heap_peak_bytes
1,1,37,37,0,12.34,1024
```

Default CSV output:

- `build/fmc_benchmark.csv`

## What The Memory Numbers Mean

Current benchmark reports two memory categories:

1. Static sizes
- `sizeof(Cube)`
- `sizeof(scramble_moves)`
- `sizeof(moves)`
- `sizeof(temporary_moves)`

2. Solver-owned dynamic heap peak
- currently this tracks allocations made by `first_translate()`
- it is useful for regression tracking
- it is **not** total process RAM

## What Still Blocks A Clean ESP32 Port

### 1. Console output is still `printf`-centric

This is fine for ESP32 serial logging, but it should eventually be wrapped behind a small platform logger macro if we want:

- Serial on Arduino
- `ESP_LOGI` on ESP-IDF
- `printf` on desktop

### 2. Some benchmark features are still desktop-oriented

CSV writing to `build/fmc_benchmark.csv` is still desktop-only.
On ESP32 this should be changed to one of:

- serial CSV output
- LittleFS / SPIFFS CSV file
- streaming to host over UART / Wi-Fi

## Recommended Next Steps For ESP32

1. Add a tiny logger abstraction:
- `printf` on desktop
- `Serial.printf` or UART on Arduino
- `ESP_LOGI` on ESP-IDF
2. Add ESP-specific runtime metrics:
- free heap before solve
- free heap after solve
- minimum free heap during benchmark loop
3. Add an Arduino / ESP-IDF entrypoint variant while keeping desktop `main.cpp`.
4. Decide whether benchmark data leaves the board through serial CSV or filesystem.

## New Runtime Metrics

The shared app runner now measures:

- solve time in microseconds
- solver-owned dynamic heap peak
- free heap before solve
- free heap after solve
- minimum free heap reported by platform
- CPU frequency in MHz when the platform exposes it

On desktop, heap and CPU frequency values may remain `0`.
On ESP32, these should be populated automatically through the platform layer.

## New Shared Entry Layer

Desktop `main` now only configures and calls the shared runner.
The same runner can be called from ESP32 code through:

- [include/app_runner.h](C:\Users\Dani\Desktop\ZZOptimalCore\include\app_runner.h)

Example Arduino sketch:

- [examples/esp32_wroom32d/esp32_wroom32d.ino](C:\Users\Dani\Desktop\ZZOptimalCore\examples\esp32_wroom32d\esp32_wroom32d.ino)

## How To Build For ESP32 Later

Once PlatformIO is installed locally, the expected flow will be:

1. `pio run -e esp32-wroom-32d`
2. `pio run -e esp32-wroom-32d -t upload`
3. `pio device monitor -b 115200`

The current environment in this session did not have `pio` / `platformio` installed, so the project layout was prepared but not end-to-end validated with the actual ESP32 toolchain here.

Update:

The PlatformIO workflow has since been validated by building and uploading to an actual `ESP32-WROOM-32D`, and the normal solver benchmark has been executed successfully on-device.

Benchmark summary document:

- [docs/esp32_benchmark_results.md](C:\Users\Dani\Desktop\ZZOptimalCore\docs\esp32_benchmark_results.md)

FMC summary document:

- [docs/esp32_fmc_results.md](C:\Users\Dani\Desktop\ZZOptimalCore\docs\esp32_fmc_results.md)

## Recommended ESP32 Release Configuration

For everyday flashing on `ESP32-WROOM-32D`, the recommended release setup is:

- in [platformio.ini](C:\Users\Dani\Desktop\ZZOptimalCore\platformio.ini):
  - `-DZZ_ESP32_ENABLE_BENCHMARK=0`
- in [src/esp32_main.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\esp32_main.cpp):
  - `constexpr RunMode kRunMode = RunMode::FmcSolve;`
  - `constexpr bool kUseSeededScramble = false;`
  - `constexpr bool kPrintScramble = true;`
  - `constexpr bool kPrintSolution = true;`
  - `constexpr bool kVisualizeSolution = false;`

This gives:

- no benchmark-only code in the image
- straightforward serial output
- FMC solve behavior suitable for final validation and shortest-solution usage
- reverse FMC enabled by default through the shared solver core

For validation or measurement builds:

- `NormalBenchmark`
  - set `ZZ_ESP32_ENABLE_BENCHMARK=1`
  - set `kRunMode = Esp32RunMode::NormalBenchmark`
- `FmcSolve`
  - keep `ZZ_ESP32_ENABLE_BENCHMARK` at either `0` or `1`
  - set `kRunMode = Esp32RunMode::FmcSolve`
- `FmcBenchmark`
  - set `ZZ_ESP32_ENABLE_BENCHMARK=1`
  - set `kRunMode = Esp32RunMode::FmcBenchmark`

Latest validated FMC benchmark result on real hardware:

- `10 / 0` success / fail
- all `192` routes processed per run
- best moves avg / min / max: `35.600 / 29 / 37`
- time avg / min / max: `2119.553 / 2110.150 / 2123.150 ms`

Latest classic-vs-reverse FMC comparison:

- classic search space: `192` routes
- reverse FMC search space: `384` routes
- classic average best solution: `35.600`
- reverse average best solution: `34.230`
- average improvement: `1.370` moves
- reverse better in `46 / 100` cases
- reverse never worse in the measured `100`-seed sample
- average runtime factor after optimization: `2.061x`

Latest optimization summary:

- reverse FMC profiling and cleanup reduced the benchmark average from `8.989 ms`
- to a best measured `4.476 ms`
- total desktop-side speedup from the measured baseline: about `50.2%`

Detailed optimization notes:

- [docs/performance_optimization_results.md](C:\Users\Dani\Desktop\ZZOptimalCore\docs\performance_optimization_results.md)

## Suggested Visualizations Later

With the benchmark CSV, useful charts will be:

1. Histogram of `total_moves`
2. Histogram of `time_ms`
3. Scatter plot: `time_ms` vs `total_moves`
4. Line chart of `heap_peak_bytes` by seed
5. Pass/fail summary per firmware revision

## Important Interpretation Note

`solver_heap_peak_bytes` is still **solver-owned dynamic allocation peak**, not total board RAM usage.
For ESP32 documentation, the more board-realistic numbers are now:

- total free heap before solve
- total free heap after solve
- minimum free heap during run

Optional later additions:

- stack high-water marks per task
- solve time histogram exported over serial
- board-specific comparison charts (`WROOM-32D`, `S3`, `C3`, etc.)
