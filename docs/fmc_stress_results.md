# FMC Stress Test Results

## Scope

This stress test was collected on the current desktop machine using the optimized reverse-FMC implementation.

Measured solver mode:

- desktop FMC
- reverse FMC enabled
- effective search space: `384` route candidates
- scramble source: seeded random scrambles
- scramble length: `20`
- duration target: about `10 minutes`

The timed stress benchmark executable was built from:

- [build/fmc_stress_timed.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\build\fmc_stress_timed.cpp)

Core solver files involved:

- [src/ZZOptimalCore.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\ZZOptimalCore.cpp)
- [src/app_runner.cpp](C:\Users\Dani\Desktop\ZZOptimalCore\src\app_runner.cpp)

## Run Summary

Observed result:

- target runtime: `600` seconds
- actual runtime: `600004 ms`
- completed solves: `107021`
- failed solves: `0`
- rotation solutions: `0`

Throughput:

- about `178.4` solves / second
- about `5.60 ms` average per solve

## Move Count Statistics

- average move count: `34.204`
- median move count: `34`
- minimum move count: `14`
- maximum move count: `41`

Interpretation:

- the optimized reverse FMC stays very stable around the low-`34` range on average
- the median matches the average closely, which suggests a fairly tight distribution
- no failures occurred across more than `107k` solves

## Time Statistics

- average solve time: `5.587 ms`
- median solve time: `5.536 ms`
- minimum solve time: `4.015 ms`
- maximum solve time: `12.606 ms`

Interpretation:

- average and median are very close, which indicates stable runtime behavior
- the worst-case tail is still modest relative to the average
- the runtime profile is consistent with the earlier shorter A/B benchmark after reverse-FMC optimization

## Practical Conclusion

The current optimized reverse FMC implementation appears stable under sustained load.

Confirmed by this run:

- no crashes
- no failed solves
- no rotation-based output
- consistent runtime over roughly `10` minutes
- consistent move-count quality over more than `100k` scrambles

This is a strong validation that the current reverse-FMC desktop implementation is ready for near-final use.
