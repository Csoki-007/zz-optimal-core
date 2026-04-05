# ESP32 FMC Results

## Scope

These FMC measurements were collected on:

- board: `ESP32-WROOM-32D`
- firmware mode: `FMC`
- route count: `192`
- execution model: incremental, watchdog-safe route processing

The active ESP32 entrypoint is:

- [src/esp32_main.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\esp32_main.cpp)

The FMC route table is:

- [include/fmc_routes.h](C:\Users\Dani\Desktop\ZZOptimalCore\include\fmc_routes.h)

The reusable route solver helper is:

- [src/ZZOptimalCore.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\ZZOptimalCore.cpp)

The recommended current release-like mode is:

- `RunMode::FmcSolve`
- benchmark code disabled in [platformio.ini](C:\Users\Dani\Desktop\ZZOptimalCore\platformio.ini)
- reverse FMC enabled by default in the shared solver core

## Current Status

FMC is now running successfully on `ESP32-WROOM-32D`.

Confirmed:

- successful ESP32 build
- successful ESP32 upload
- successful serial execution
- stable repeated FMC runs
- all `192` routes processed
- no watchdog reset during incremental FMC execution

## Why This Works

The original desktop-style FMC flow was too blocking when treated as one large solve pass on ESP32.

The working embedded approach is:

- prepare the scramble once
- evaluate one FMC route at a time
- yield between route steps
- keep the best solution seen so far
- print progress and final summary over serial

This keeps the watchdog satisfied while preserving the FMC search behavior.

## Observed Results

Across repeated runs, the FMC result remained deterministic for the tested seeded scramble.

Representative result:

- best move count: `34`
- routes processed: `192`
- total time: `471.888 ms`
- free heap before: `335388 bytes`
- free heap after: `335292 bytes`
- minimum free heap: `328756 bytes`

Representative best solution:

```text
Di Fi R F D2 Bi L2 Bi Ui B2 D B2 U Di B D B U B D B Di B2 D Bi D B2 U Bi Di B Ui D B
```

## FMC Benchmark Results

The full multi-seed FMC benchmark was also validated directly on `ESP32-WROOM-32D`.

Benchmark configuration:

- mode: `FMC Benchmark`
- run count: `10`
- seeds: `1..10`
- routes per run: `192`
- execution model: incremental, watchdog-safe

Observed summary:

- success / fail: `10 / 0`
- best moves avg / min / max: `35.600 / 29 / 37`
- best moves p50 / p90 / p95 / p99: `36 / 37 / 37 / 37`
- time avg / min / max: `2119.553 / 2110.150 / 2123.150 ms`
- free heap before avg / min / max: `334856.000 / 334820 / 335180 bytes`
- free heap after avg / min / max: `334846.400 / 334820 / 335084 bytes`
- min free heap avg / min / max: `328310.400 / 328284 / 328548 bytes`

Interpretation:

- all `10` benchmark scrambles completed successfully
- each run processed the full `192` route table
- no watchdog reset occurred during the benchmark
- heap usage stayed stable across runs

This is the strongest current validation that the embedded FMC flow is now working reliably across multiple scrambles, not just on a single fixed test case.

## Reverse FMC Expansion

The FMC search has now been extended with a reverse-search branch.

Instead of only exploring the original `192` route table on the original scramble, the solver can now:

- run the direct `192` FMC routes
- derive the inverse-scramble state from the best direct FMC solution
- run the same `192` FMC routes on that inverse-scramble state
- invert only competitive reverse candidates
- keep the shortest solution found across both halves

This brings the effective search space from:

- `192` route candidates

to:

- `384` route candidates

while avoiding the earlier extra full normal-solve cost.

In practical release terms, the ESP32 FMC path now means:

- direct FMC routes are explored
- reverse FMC routes are explored from the derived inverse state
- the best result across the full `384` candidate space is kept

## Direct vs Reverse FMC Comparison

A direct A/B benchmark was run on desktop using the same `100` seeded scrambles for both variants:

- classic FMC: direct `192` routes only
- reverse FMC: direct `192` + reverse `192` routes

Observed result:

- classic solved: `100 / 100`
- reverse solved: `100 / 100`
- compared scrambles: `100`

Move-count comparison:

- classic average: `35.600`
- reverse average: `34.230`
- average improvement: `1.370` moves
- median improvement: `0`
- maximum improvement: `11` moves

Win distribution:

- reverse better: `46`
- same result: `54`
- classic better: `0`

Improvement thresholds:

- at least `1` move better: `46` cases
- at least `2` moves better: `36` cases
- at least `3` moves better: `21` cases

Runtime comparison:

- classic average time: `2.942 ms`
- reverse average time: `6.063 ms`
- slowdown factor: `2.061x`

Interpretation:

- the reverse FMC extension improves average solution quality
- it never produced a worse result on the measured sample
- the runtime is now close to the expected `2x` cost of doubling the route count
- this is a strong tradeoff in favor of enabling reverse FMC when shortest solutions matter more than raw solve speed

## Optimization Follow-Up

After profiling and targeted cleanup on desktop, the reverse FMC path was further optimized.

Measured desktop profiling baseline:

- average reverse-FMC benchmark time: `8.989 ms`

Best measured optimized state:

- average reverse-FMC benchmark time: `4.476 ms`

This is about:

- `50.2%` faster than the initial measured profiling baseline

The largest wins came from:

- faster solution-string application
- faster translation handling
- reduced repeated F2L piece lookup work

Detailed notes:

- [docs/performance_optimization_results.md](C:\Users\Dani\Desktop\ZZOptimalCore\docs\performance_optimization_results.md)

## Interpretation

### Stability

Repeated runs produced the same best solution and did not trigger watchdog resets.

This indicates that the current incremental FMC execution model is stable on `ESP32-WROOM-32D` for the tested configuration.

### Runtime

A full FMC pass over all `192` routes completed in about:

- `472 ms`

This is a practical on-device runtime for the current implementation.

With reverse FMC enabled, the desktop A/B benchmark indicates that the extra search cost is now close to the theoretical `2x` expectation after optimization.

### Memory

Runtime heap values remained stable across the FMC run, suggesting:

- no obvious leak in incremental FMC execution
- healthy free-heap headroom for this mode on the tested board

## Practical Conclusion

The project has now reached another major milestone:

- the normal solver works on `ESP32-WROOM-32D`
- the normal benchmark works on `ESP32-WROOM-32D`
- the FMC solver also works on `ESP32-WROOM-32D`
- the FMC benchmark also works on `ESP32-WROOM-32D`

## Suggested Next Step

Use this FMC baseline for final polish:

1. keep a lean release configuration for everyday flashing
2. use `FmcSolve` or `FmcBenchmark` only when validation is needed
3. optionally add serial-friendly CSV export for later charting
