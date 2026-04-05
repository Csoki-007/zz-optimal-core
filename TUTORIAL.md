# ZZOptimalCore Tutorial

This document explains how to use `ZZOptimalCore` as a solver library from your own project on:

- Windows
- Linux
- ESP32 / Arduino

The main goal is to make integration simple: pass in a cube state or let the library generate a scramble, choose the solve mode, and read back the solution string.

## What This Project Can Do

The solver currently supports:

- `Normal` solve
- `FMC` solve
- reverse `FMC` search
  - direct routes + inverse-state routes
  - total search space: `384` routes
- pattern solve
  - checkerboard
  - anaconda
  - cube in cube in cube
  - cube in cube
  - vertical stripes
  - python
  - 4 centers
  - 6 centers
  - superflip

## Main Entry Points

The easiest public entry points are in:

- [include/app_runner.h](include/app_runner.h)
- [src/app_runner.cpp](src/app_runner.cpp)

The two main integration styles are:

1. Solve from a generated or fixed scramble
2. Solve directly from a full `54`-sticker cube state

## Quick Start

If you want the smallest working example, open:

- [examples/direct_solve_example.cpp](examples/direct_solve_example.cpp)

That example:

- works as a normal desktop `main()`
- also works as an Arduino / ESP32 `setup()/loop()` example
- calls the shared library API
- prints the solution with `printf` or `Serial.printf`

## Cube State Format

When you use the direct-state API, you pass a `54`-element array of `uint8_t`.

Face block order:

- `0..8` = `U`
- `9..17` = `L`
- `18..26` = `F`
- `27..35` = `R`
- `36..44` = `B`
- `45..53` = `D`

This is the solved-state layout used by the project:

```cpp
const uint8_t solved[54] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6
};
```

Important:

- the exact numbers are internal color IDs
- what matters is consistency
- your cube state must use the same face-center color IDs as the solver

## API 1: Solve From a Full Cube State

This is the most useful API when another external project already knows the cube state.

Use:

- [include/app_runner.h](include/app_runner.h)

Relevant types:

```cpp
struct DirectSolveConfig {
    SolverMode solver_mode;
    PatternPreset pattern_preset;
    bool print_mode;
    bool print_solution;
    bool visualize_solution;
};

struct SolveStats {
    bool solved;
    bool has_rotations;
    int total_moves;
    int face_moves;
    uint64_t elapsed_us;
    size_t solver_heap_peak_bytes;
    size_t free_heap_before_bytes;
    size_t free_heap_after_bytes;
    size_t min_free_heap_bytes;
    char scramble[256];
    char solution[256];
};

DirectSolveConfig make_direct_solve_config(...);
bool app_run_solve_from_state(const uint8_t* state,
                              const DirectSolveConfig& config,
                              SolveStats* stats);
```

Minimal desktop example:

```cpp
#include "app_runner.h"
#include <cstdio>

int main() {
    const uint8_t cube_state[54] = {
        6, 1, 1, 1, 6, 6, 4, 6, 1,
        4, 4, 1, 2, 1, 5, 1, 3, 2,
        3, 3, 3, 3, 2, 2, 3, 6, 3,
        2, 5, 5, 4, 4, 4, 6, 2, 4,
        2, 2, 5, 1, 4, 4, 6, 1, 5,
        2, 5, 5, 3, 3, 5, 5, 6, 6
    };

    DirectSolveConfig config = make_direct_solve_config(
        SolverMode::Fmc,
        PatternPreset::None,
        false,
        false,
        false);

    SolveStats stats = {};
    bool ok = app_run_solve_from_state(cube_state, config, &stats);

    std::printf("Solved: %s\n", ok ? "yes" : "no");
    std::printf("Solution: %s\n", stats.solution);
    return ok ? 0 : 1;
}
```

## API 2: Solve From a Generated or Fixed Scramble

Use this if you want the library to:

- generate a random scramble
- generate a seeded scramble
- use a fixed scramble you already have

Relevant API:

```cpp
AppRunConfig make_run_config(...);
bool app_run_solve(const AppRunConfig& config, SolveStats* stats);
```

This path is used by:

- [src/main.cpp](src/main.cpp)
- [src/esp32_main.cpp](src/esp32_main.cpp)

Typical use:

```cpp
const char* fixed_scramble[] = {"R", "U", "Ri", "Ui"};

AppRunConfig config = make_run_config(
    SolverMode::Fmc,
    PatternPreset::None,
    true,
    true,
    true,
    false,
    true,
    false,
    20,
    12345,
    fixed_scramble,
    4);

SolveStats stats = {};
app_run_solve(config, &stats);
```

## Choosing the Solve Mode

The main solve modes are:

```cpp
enum class SolverMode {
    Normal,
    Fmc
};
```

### `SolverMode::Normal`

Use this when:

- you want a fast solve
- you do not need FMC-style deeper search
- you want the lowest runtime overhead

### `SolverMode::Fmc`

Use this when:

- you want shorter solutions
- you want the direct + reverse FMC route search
- runtime is less important than move count quality

Current FMC behavior:

- direct FMC routes: `192`
- reverse FMC routes: `192`
- total: `384`

## Using Pattern Presets

Pattern solving is also available from the same public API:

```cpp
enum class PatternPreset {
    None,
    Checkerboard,
    Anaconda,
    CubeInCubeInCube,
    CubeInCube,
    VerticalStripes,
    Python,
    FourCenters,
    SixCenters,
    SuperFlip
};
```

Example:

```cpp
DirectSolveConfig config = make_direct_solve_config(
    SolverMode::Fmc,
    PatternPreset::Checkerboard,
    false,
    false,
    false);
```

This means:

- start from the given cube state
- solve into the selected pattern instead of the fully solved cube

## Universal Desktop + ESP32 Integration

If you want one source file that works in both environments, follow the pattern used in:

- [examples/direct_solve_example.cpp](examples/direct_solve_example.cpp)

The idea is:

- use `#if defined(ARDUINO)` for `Serial`
- otherwise use normal `main()` and `printf`
- keep all actual solver calls shared

Basic structure:

```cpp
#if defined(ARDUINO)
void setup() {
    Serial.begin(115200);
    // call shared solve function here
}

void loop() {
    delay(1000);
}
#else
int main() {
    // call the same shared solve function here
}
#endif
```

## Building on Desktop

Example `g++` build command for the direct example:

```powershell
g++ -O2 -Iinclude examples/direct_solve_example.cpp `
    src/ZZOptimalCore.cpp `
    src/app_runner.cpp `
    src/eo_solver.cpp `
    src/f2l_solver.cpp `
    src/line_solver.cpp `
    src/zbll_solver.cpp `
    src/zz_platform.cpp `
    src/zz_profiler.cpp `
    -o build/direct_solve_example.exe
```

Then run:

```powershell
build/direct_solve_example.exe
```

## Building on ESP32

The ESP32 project is already set up for PlatformIO:

- [platformio.ini](platformio.ini)

Main firmware entry:

- [src/esp32_main.cpp](src/esp32_main.cpp)

Build:

```powershell
pio run -e esp32-wroom-32d
```

Upload:

```powershell
pio run -e esp32-wroom-32d -t upload
```

Monitor:

```powershell
pio device monitor -b 115200 --port COM5
```

## Recommended Integration Strategy

If another project is going to call this solver most of the time, the cleanest strategy is:

1. Keep your external project responsible for obtaining the cube state
2. Pass the `54`-byte state into `app_run_solve_from_state(...)`
3. Choose:
   - `SolverMode::Normal` for speed
   - `SolverMode::Fmc` for better move quality
4. Read the result from:
   - `stats.solution`
   - `stats.total_moves`
   - `stats.elapsed_us`

This is usually better than editing [src/main.cpp](src/main.cpp) every time.

## Recommended Release Defaults

At the moment, the project defaults are set up for final FMC usage:

- desktop default mode: `FmcSolve`
- ESP32 default mode: `FmcSolve`
- reverse FMC enabled
- ESP32 benchmark code disabled in release-like firmware

Relevant files:

- [src/main.cpp](src/main.cpp)
- [src/esp32_main.cpp](src/esp32_main.cpp)
- [platformio.ini](platformio.ini)

## What To Use First

If you are new to the project, start in this order:

1. Open [examples/direct_solve_example.cpp](examples/direct_solve_example.cpp)
2. Replace `kCubeState` with your own cube state
3. Choose:
   - `SolverMode::Normal`
   - or `SolverMode::Fmc`
4. Optional:
   - set a `PatternPreset`
5. Read back `stats.solution`

## Notes

- `SolveStats::scramble` is meaningful in scramble-generated mode
- for direct-state solve, `SolveStats::scramble` is empty by design
- `SolveStats::solution` always contains the final move sequence if solve succeeded
- `visualize_solution` is mostly useful for desktop demos, not for library-style integration

## Further Reading

- direct example: [examples/direct_solve_example.cpp](examples/direct_solve_example.cpp)
- ESP32 FMC results: [docs/esp32_fmc_results.md](docs/esp32_fmc_results.md)
- optimization summary: [docs/performance_optimization_results.md](docs/performance_optimization_results.md)
