# ZZOptimalCore

High-performance C/C++ Rubik's Cube solver core with:

- normal solve mode
- FMC solve mode
- reverse FMC search (`384` routes total)
- pattern solve mode
- desktop support
- ESP32 support

## What Is This?

`ZZOptimalCore` is a Rubik's Cube solver core written in C/C++.

It focuses on:

- solving a cube from a full sticker state
- generating short solutions with ZZ-based solving
- deeper FMC-style search
- reverse FMC search for better move quality
- desktop and ESP32 compatibility

In short: this project is the solver engine behind a larger Rubik's Cube automation goal.

## Why Am I Building It?

This project is not just a small code experiment.

It is being built as one important part of a future diploma project:

- a Rubik's Cube solving robot

In that bigger system, this repository is the algorithmic core that decides how the cube should be solved.

So the long-term goal is not only to have a good standalone software solver, but to have a solver that can later be embedded into a real hardware system.

## Where Is It Heading?

The long-term direction of the project is:

- diploma-work integration
- robot-friendly solver behavior
- stable cross-platform operation
- practical integration into a larger control system

That means this repository is being developed with real future use in mind:

- reusable API
- deterministic behavior
- measurable performance
- embedded compatibility

## What Problem Does It Solve?

At the software level, this project solves a very practical problem:

- given a Rubik's Cube state, find a valid solution sequence

But in practice it addresses a bigger engineering problem too:

- how to turn cube state data into a reliable, short, machine-usable solution

That matters because a robot does not need only "a" solution.
It benefits from a solution that is:

- correct
- short
- repeatable
- fast enough to compute
- easy to integrate into other software

This repository is meant to bridge that gap between raw cube state input and a real system that can physically solve the cube.

If you want to use this project from another application, start here:

- full integration tutorial: [TUTORIAL.md](TUTORIAL.md)
- smallest direct API example: [examples/direct_solve_example.cpp](examples/direct_solve_example.cpp)

## Features

- solve from a full `54`-sticker cube state
- solve from a generated, seeded, or fixed scramble
- normal solve mode
- FMC solve mode
- reverse FMC search
  - total search space: `384` routes
- pattern solve presets
- shared integration API for desktop and ESP32

## Quick Start

If you want to embed the solver into another project, the main public API is:

- [include/app_runner.h](include/app_runner.h)

The smallest integration path is:

1. prepare a `54`-element cube state
2. create a `DirectSolveConfig`
3. call `app_run_solve_from_state(...)`
4. read back `SolveStats::solution`

## Project Structure

- [include/](include) public headers and solver-facing declarations
- [src/](src) core implementation, desktop entry point, ESP32 entry point
- [examples/](examples) minimal usage examples
- [docs/](docs) benchmark, ESP32, FMC, and performance notes
- [TESZT_UNITS/](TESZT_UNITS) development test assets and solver-side validation helpers
- [TUTORIAL.md](TUTORIAL.md) full integration tutorial

## Platform Support

- Windows desktop
- Linux desktop
- ESP32 / Arduino

## Public Integration API

Main entry points:

- `app_run_solve(...)`
- `app_run_solve_from_state(...)`
- `make_run_config(...)`
- `make_direct_solve_config(...)`

Main output type:

- `SolveStats`

## Limitations

- the project currently focuses on the ZZ-based solver pipeline implemented in this repository
- direct-state integration expects the same internal face/color layout used by the solver
- ESP32 benchmarking and development helpers are intentionally separate from the release-like default firmware mode

Additional project notes:

- ESP32 benchmark results: [docs/esp32_benchmark_results.md](docs/esp32_benchmark_results.md)
- ESP32 FMC results: [docs/esp32_fmc_results.md](docs/esp32_fmc_results.md)
- performance optimization summary: [docs/performance_optimization_results.md](docs/performance_optimization_results.md)

## License

This project is currently published under the [MIT License](LICENSE).
