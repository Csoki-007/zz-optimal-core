#ifndef APP_RUNNER_H
#define APP_RUNNER_H

#include "ZZOptimalCore.h"
#include "pattern_presets.h"
#include <cstddef>
#include <cstdint>

enum class SolverMode {
    Normal,
    Fmc
};

enum class RunMode {
    NormalSolve,
    FmcSolve,
    NormalBenchmark,
    FmcBenchmark
};

struct AppRunConfig {
    SolverMode solver_mode;
    PatternPreset pattern_preset;
    bool print_mode;
    bool print_scramble;
    bool print_solution;
    bool visualize_solution;
    bool use_fixed_scramble;
    bool use_seeded_scramble;
    int random_scramble_length;
    unsigned int scramble_seed;
    const char* const* fixed_scramble;
    int fixed_scramble_length;
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

struct DirectSolveConfig {
    SolverMode solver_mode;
    PatternPreset pattern_preset;
    bool print_mode;
    bool print_solution;
    bool visualize_solution;
};

struct BenchmarkConfig {
    SolverMode solver_mode;
    int random_scramble_length;
    int run_count;
    unsigned int start_seed;
    int print_progress_every;
    bool print_failures;
    bool write_csv;
    const char* csv_path;
};

struct BenchmarkSummary {
    int success_count;
    int failure_count;
    int rotation_solution_count;
    uint32_t cpu_freq_mhz;

    double avg_total_moves;
    int min_total_moves;
    int max_total_moves;
    int p50_total_moves;
    int p90_total_moves;
    int p95_total_moves;
    int p99_total_moves;

    double avg_face_moves;
    int min_face_moves;
    int max_face_moves;
    int p50_face_moves;
    int p90_face_moves;
    int p95_face_moves;
    int p99_face_moves;

    double avg_time_ms;
    double min_time_ms;
    double max_time_ms;

    double avg_solver_heap_peak_bytes;
    size_t min_solver_heap_peak_bytes;
    size_t max_solver_heap_peak_bytes;

    double avg_free_heap_before_bytes;
    size_t min_free_heap_before_bytes;
    size_t max_free_heap_before_bytes;

    double avg_free_heap_after_bytes;
    size_t min_free_heap_after_bytes;
    size_t max_free_heap_after_bytes;

    double avg_min_free_heap_bytes;
    size_t min_min_free_heap_bytes;
    size_t max_min_free_heap_bytes;
};

extern char scramble_moves[256];

SolverMode solver_mode_from_run_mode(RunMode mode);
bool run_mode_is_benchmark(RunMode mode);
bool run_mode_is_fmc(RunMode mode);
const char* run_mode_label(RunMode mode);
const char* pattern_preset_name(PatternPreset preset);
const uint8_t* pattern_preset_state(PatternPreset preset);
bool has_pattern_preset(PatternPreset preset);

AppRunConfig make_run_config(SolverMode solver_mode,
                             PatternPreset pattern_preset,
                             bool print_mode,
                             bool print_scramble,
                             bool print_solution,
                             bool visualize_solution,
                             bool use_fixed_scramble,
                             bool use_seeded_scramble,
                             int random_scramble_length,
                             unsigned int scramble_seed,
                             const char* const* fixed_scramble,
                             int fixed_scramble_length);

BenchmarkConfig make_benchmark_config(SolverMode solver_mode,
                                      int random_scramble_length,
                                      int run_count,
                                      unsigned int start_seed,
                                      int print_progress_every,
                                      bool print_failures,
                                      bool write_csv,
                                      const char* csv_path);
DirectSolveConfig make_direct_solve_config(SolverMode solver_mode,
                                           PatternPreset pattern_preset,
                                           bool print_mode,
                                           bool print_solution,
                                           bool visualize_solution);

void app_clear_move_buffers();
bool app_run_solve(const AppRunConfig& config, SolveStats* stats);
bool app_run_solve_from_state(const uint8_t* state, const DirectSolveConfig& config, SolveStats* stats);
bool app_run_fmc_benchmark(const BenchmarkConfig& config, BenchmarkSummary* summary);
void app_print_benchmark_summary(const BenchmarkSummary& summary);

#endif
