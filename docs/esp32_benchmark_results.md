# ESP32 Benchmark Results

## Scope

These measurements were collected on:

- board: `ESP32-WROOM-32D`
- firmware mode: `Normal` solver
- benchmark mode: incremental ESP32 benchmark
- solver path: current stable non-FMC path

The benchmark is currently driven from:

- [src/esp32_main.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\esp32_main.cpp)

The shared runtime and statistics layer lives in:

- [src/app_runner.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\app_runner.cpp)
- [src/zz_platform.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\zz_platform.cpp)

## Current Status

The normal ZZ solver is now running stably on `ESP32-WROOM-32D`.

Confirmed:

- successful PlatformIO build
- successful firmware upload
- successful serial execution
- stable repeated benchmark runs
- no watchdog reset in the incremental normal benchmark mode

See also:

- [docs/esp32_fmc_results.md](C:\Users\Dani\Desktop\ZZOptimalCore\docs\esp32_fmc_results.md)

## Firmware Footprint

From the successful PlatformIO build:

- RAM: `9.1%` used
- RAM bytes: `29928 / 327680`
- Flash: `53.2%` used
- Flash bytes: `1672281 / 3145728`

This build uses the larger app partition configuration from:

- [platformio.ini](C:\Users\Dani\Desktop\ZZOptimalCore\platformio.ini)

## Benchmark Configuration

Current ESP32 benchmark settings:

- mode: `Benchmark`
- solver mode: `Normal`
- run count: `20`
- seeded deterministic scrambles
- benchmark executed incrementally from `loop()`

Important implementation note:

The benchmark was changed from a blocking one-shot execution to an incremental per-loop execution, because the earlier blocking version triggered:

- `TG1WDT_SYS_RESET`

The current incremental benchmark is watchdog-safe for the tested configuration.

## Observed Results

Across repeated runs, the benchmark output remained stable.

Representative result:

- success/fail: `20 / 0`
- rotation solutions: `0`
- total moves avg/min/max: `47.300 / 39 / 57`
- total moves p50/p90/p95/p99: `47 / 52 / 52 / 52`
- face moves avg/min/max: `47.300 / 39 / 57`
- face moves p50/p90/p95/p99: `47 / 52 / 52 / 52`
- time avg/min/max: `0.533 / 0.469 / 0.905 ms`
- solver heap peak avg/min/max: `0 / 0 / 0 bytes`
- free heap before avg/min/max: `334442 / 334424 / 334784 bytes`
- free heap after avg/min/max: `334442 / 334424 / 334784 bytes`
- min free heap avg/min/max: `328849.2 / 328824 / 329292 bytes`

## Interpretation

### Stability

The benchmark result `20 / 0` across repeated runs indicates that the current normal solver path is stable on the target ESP32 board.

### Memory

The runtime heap values are stable and show no meaningful drift during the benchmark.

This suggests:

- no obvious heap leak during the benchmark loop
- good memory headroom for the current normal solver path

### Runtime

The measured runtime is very low and consistent for the tested normal solver route.

This is expected after removing the expensive benchmark logging noise:

- detailed stage-by-stage solver logs
- colored cube printing

### Dynamic Solver Heap

The solver-owned peak heap is `0` bytes in this benchmark mode.

That is currently acceptable, because the measured normal solve path does not materially depend on the tracked dynamic allocation path.
The heap tracking is expected to become more relevant again when FMC is revisited.

## Known Limits

These results currently apply to:

- the stable `Normal` ESP32 solver path

They do not describe the FMC path directly.
FMC now has its own dedicated document:

- [docs/esp32_fmc_results.md](C:\Users\Dani\Desktop\ZZOptimalCore\docs\esp32_fmc_results.md)

## Practical Conclusion

The project has reached an important milestone:

- the C/C++ ZZ solver is now working on `ESP32-WROOM-32D`
- the normal solve path is benchmarked
- the benchmark output is deterministic and reusable

This remains the baseline reference for the non-FMC ESP32 path.

## Suggested Next Step

Use this benchmark baseline as the reference point, then continue with:

1. ESP32-compatible FMC execution model
2. FMC-specific timing and memory measurements
3. comparison of `Normal` vs `FMC` behavior on the same board
