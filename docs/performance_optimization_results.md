# Performance Optimization Results

## Scope

This document summarizes the measured desktop optimization work that was done after the profiling framework was added.

Primary measurement target:

- reverse FMC benchmark
- `1000` seeded runs
- profiling enabled
- focus on self-time hotspots

Main profiling helper:

- [include/zz_profiler.h](C:\Users\Dani\Desktop\ZZOptimalCore\include\zz_profiler.h)
- [src/zz_profiler.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\zz_profiler.cpp)

## Baseline

Initial measured reverse-FMC benchmark result:

- average time: `8.989 ms`

Main hotspots at the start:

- `apply_solution_string`
- `first_translate`
- `solve_fmc_route`
- `find_edge`
- `solve_ZBLL`
- `find_corner`

## Implemented Optimizations

### 1. Faster solution application

File:

- [src/ZZOptimalCore.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\ZZOptimalCore.cpp)

Changes:

- removed the old `strtok` + long `strcmp` dispatch chain from `apply_solution_string`
- added a lightweight token parser
- applied parsed moves directly without the old string-heavy path

Effect:

- large reduction in `apply_solution_string` self time

### 2. Faster translation path

File:

- [src/ZZOptimalCore.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\ZZOptimalCore.cpp)

Changes:

- reduced copying inside `first_translate`
- switched to a more direct parsing flow
- removed heavy `strcat`-style building in the hot path
- later moved route-level translation to a stack-buffer path

Effect:

- large reduction in translation overhead
- route-level heap usage dropped to zero during benchmark

### 3. F2L repeated lookup cleanup

File:

- [src/f2l_solver.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\f2l_solver.cpp)

Changes:

- removed repeated `find_edge` / `find_corner` calls inside the same route functions
- reused locally computed values instead

Effect:

- lower `find_edge` / `find_corner` call counts
- noticeable end-to-end speedup

### 4. Safe cleanup passes

Files:

- [src/f2l_solver.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\f2l_solver.cpp)
- [src/zbll_solver.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\zbll_solver.cpp)

Changes:

- removed stray duplicate include lines left behind during profiling instrumentation work
- kept only the optimizations that measured as beneficial
- reverted experiments that caused regressions

## Measured Progress

### Step 1: after string-path optimization

- average time improved from `8.989 ms`
- to `6.449 ms`

Approximate gain:

- about `28.3%`

### Step 2: after local F2L lookup reuse

- average time improved from `6.449 ms`
- to `4.873 ms`

Approximate gain:

- about `24.4%` relative to the previous step

### Best measured state from the optimization cycle

- average time: `4.476 ms`

Compared to the original profiling baseline:

- original: `8.989 ms`
- optimized best: `4.476 ms`
- total improvement: about `50.2%`

## Practical Conclusion

The low-risk, high-value optimization work is now largely complete.

What was achieved:

- the biggest string-processing bottlenecks were reduced substantially
- repeated F2L piece-lookup waste was reduced
- reverse FMC stayed correct and stable
- the code remained maintainable and did not require risky algorithm changes

What was intentionally **not** forced further:

- some later micro-optimizations did not consistently improve runtime
- those were reverted instead of leaving fragile or misleading code in the project

This leaves the project in a strong state:

- profiling infrastructure exists
- the main easy wins were captured
- future optimization work can now focus only on deeper hotspots like:
  - `solve_fmc_route`
  - `solve_ZBLL`
  - broader token-based move pipelines

## Reference Profiling Outputs

Collected benchmark/profile outputs:

- [build/profile_reverse_fmc_output.txt](C:\Users\Dani\Desktop\ZZOptimalCore\build\profile_reverse_fmc_output.txt)
- [build/profile_reverse_fmc_output_after_opt.txt](C:\Users\Dani\Desktop\ZZOptimalCore\build\profile_reverse_fmc_output_after_opt.txt)
- [build/profile_reverse_fmc_output_after_local_cache.txt](C:\Users\Dani\Desktop\ZZOptimalCore\build\profile_reverse_fmc_output_after_local_cache.txt)
- [build/profile_reverse_fmc_output_after_route_zbll_opt.txt](C:\Users\Dani\Desktop\ZZOptimalCore\build\profile_reverse_fmc_output_after_route_zbll_opt.txt)
- [build/profile_reverse_fmc_output_reverted_best.txt](C:\Users\Dani\Desktop\ZZOptimalCore\build\profile_reverse_fmc_output_reverted_best.txt)
