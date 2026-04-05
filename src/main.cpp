#include "app_runner.h"
#include "zz_profiler.h"

namespace config {
constexpr RunMode kRunMode = RunMode::FmcSolve;
constexpr PatternPreset kPatternPreset = PatternPreset::None;

constexpr bool kPrintMode = true;
constexpr bool kPrintScramble = true;
constexpr bool kPrintSolution = true;
constexpr bool kVisualizeSolution = true;

constexpr bool kUseFixedScramble = false;
constexpr bool kUseSeededScramble = false;
constexpr int kRandomScrambleLength = 20;
constexpr unsigned int kScrambleSeed = 12345;

constexpr int kBenchmarkRunCount = 1000;
constexpr unsigned int kBenchmarkStartSeed = 1;
constexpr int kBenchmarkPrintProgressEvery = 100;
constexpr bool kBenchmarkPrintFailures = true;
constexpr bool kBenchmarkWriteCsv = true;
constexpr const char* kBenchmarkCsvPath = "build/fmc_benchmark.csv";

constexpr const char* kFixedScramble[] = {
    "D2", "B2", "L2", "Di", "U", "F", "B", "Li", "R", "B",
    "Di", "U", "R", "B2", "Di", "R2", "U2", "F", "Bi", "Di"
};
constexpr int kFixedScrambleLength =
    static_cast<int>(sizeof(kFixedScramble) / sizeof(kFixedScramble[0]));
}

int main() {
#if !defined(ARDUINO) && !defined(ESP_PLATFORM)
    system("chcp 65001");
#endif

    zz_profiler_reset();

    if (run_mode_is_benchmark(config::kRunMode)) {
        printf("Mod: %s\n", run_mode_label(config::kRunMode));
        BenchmarkConfig benchmark_config = make_benchmark_config(
            solver_mode_from_run_mode(config::kRunMode),
            config::kRandomScrambleLength,
            config::kBenchmarkRunCount,
            config::kBenchmarkStartSeed,
            config::kBenchmarkPrintProgressEvery,
            config::kBenchmarkPrintFailures,
            config::kBenchmarkWriteCsv,
            config::kBenchmarkCsvPath);

        BenchmarkSummary summary = {};
        app_run_fmc_benchmark(benchmark_config, &summary);
        app_print_benchmark_summary(summary);
        zz_profiler_print(stdout);

#if !defined(ARDUINO) && !defined(ESP_PLATFORM)
        if (config::kBenchmarkWriteCsv) {
            printf("Benchmark CSV: %s\n", config::kBenchmarkCsvPath);
        }
#endif
        return 0;
    }

    AppRunConfig run_config = make_run_config(
        solver_mode_from_run_mode(config::kRunMode),
        config::kPatternPreset,
        config::kPrintMode,
        config::kPrintScramble,
        config::kPrintSolution,
        config::kVisualizeSolution,
        config::kUseFixedScramble,
        config::kUseSeededScramble,
        config::kRandomScrambleLength,
        config::kScrambleSeed,
        config::kFixedScramble,
        config::kFixedScrambleLength);

    SolveStats stats = {};
    app_run_solve(run_config, &stats);
    zz_profiler_print(stdout);
    return 0;
}
