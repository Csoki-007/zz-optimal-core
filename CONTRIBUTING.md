# Contributing

Thanks for your interest in improving `zz-optimal-core`.

## Before You Start

- open an issue or start a discussion before large changes
- keep behavior-preserving refactors separate from feature changes
- prefer small, reviewable pull requests

## Development Guidelines

- keep the solver behavior correct and deterministic
- avoid changing move semantics unless the change is explicitly intended
- prefer measured optimization over speculative optimization
- preserve cross-platform support for:
  - desktop C++
  - ESP32 / Arduino

## Recommended Workflow

1. make the smallest correct change
2. verify desktop build
3. verify ESP32 build if the change affects embedded code
4. update documentation when behavior or public API changes
5. include benchmark or profiling evidence for performance-related changes

## Code Style

- keep changes consistent with the existing codebase
- prefer clear names over clever micro-optimizations
- avoid unnecessary dynamic allocation in hot paths
- keep platform-specific code isolated where possible

## Performance Changes

For performance pull requests, include:

- what was slow
- how it was measured
- before/after numbers
- any tradeoffs in readability or complexity

## Public API Changes

If you modify any integration-facing API, check:

- [include/app_runner.h](include/app_runner.h)
- [examples/direct_solve_example.cpp](examples/direct_solve_example.cpp)
- [TUTORIAL.md](TUTORIAL.md)

## Bug Reports

Useful bug reports should include:

- platform
- input cube state or scramble
- selected solve mode
- expected result
- actual result

## License

By contributing, you agree that your contributions will be released under the
same license as this repository.
