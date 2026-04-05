#include <Arduino.h>
#include <random>
#ifdef F
#undef F
#endif

#include "app_runner.h"
#include "zz_platform.h"

#ifndef ZZ_ESP32_ENABLE_BENCHMARK
#define ZZ_ESP32_ENABLE_BENCHMARK 1
#endif

namespace config {
// Main ESP32 mode switch. In normal use, this is the only mode flag
// you should need to change here.
// Recommended release default: RunMode::FmcSolve
// Recommended FMC testing/demo: RunMode::FmcSolve
// Recommended deterministic benchmark run: RunMode::NormalBenchmark
// Recommended FMC validation across many scrambles: RunMode::FmcBenchmark
constexpr RunMode kRunMode = RunMode::FmcSolve;
constexpr PatternPreset kPatternPreset = PatternPreset::None;

// These affect only the one-shot NormalSolve path.
constexpr bool kPrintMode = true;
constexpr bool kPrintScramble = true;
constexpr bool kPrintSolution = true;
constexpr bool kVisualizeSolution = false;

// For reproducible testing on the board, keep seeded scramble enabled.
// For the recommended release-like random solve demo, keep this off.
constexpr bool kUseFixedScramble = false;
constexpr bool kUseSeededScramble = false;
constexpr int kRandomScrambleLength = 20;
constexpr unsigned int kScrambleSeed = 12345;

#if ZZ_ESP32_ENABLE_BENCHMARK
constexpr int kBenchmarkRunCount = 20;
constexpr unsigned int kBenchmarkStartSeed = 1;
constexpr int kBenchmarkPauseMsBetweenRuns = 10;
constexpr int kFmcBenchmarkRunCount = 10;
constexpr unsigned int kFmcBenchmarkStartSeed = 1;
constexpr int kFmcBenchmarkPauseMsBetweenRuns = 10;
#endif

constexpr const char* kFixedScramble[] = {
    "D2", "B2", "L2", "Di", "U", "F", "B", "Li", "R", "B",
    "Di", "U", "R", "B2", "Di", "R2", "U2", "F", "Bi", "Di"
};
constexpr int kFixedScrambleLength =
    static_cast<int>(sizeof(kFixedScramble) / sizeof(kFixedScramble[0]));
}

static void print_stats(const SolveStats& stats) {
    Serial.printf("Solved: %s\n", stats.solved ? "igen" : "nem");
    Serial.printf("Time: %.3f ms\n", static_cast<double>(stats.elapsed_us) / 1000.0);
    Serial.printf("Total moves: %d\n", stats.total_moves);
    Serial.printf("Face moves: %d\n", stats.face_moves);
    Serial.printf("Rotations: %s\n", stats.has_rotations ? "igen" : "nem");
    Serial.printf("Solver heap peak: %u bytes\n",
                  static_cast<unsigned>(stats.solver_heap_peak_bytes));
    Serial.printf("Free heap before: %u bytes\n",
                  static_cast<unsigned>(stats.free_heap_before_bytes));
    Serial.printf("Free heap after: %u bytes\n",
                  static_cast<unsigned>(stats.free_heap_after_bytes));
    Serial.printf("Min free heap: %u bytes\n",
                  static_cast<unsigned>(stats.min_free_heap_bytes));
}

static const uint8_t kInitialState[54] __attribute__((aligned(4))) = {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6
};

struct ScrambleMoveDef {
    void (*fn)(Cube*);
    char face;
    const char* text;
};

static const ScrambleMoveDef kAllMoves[] = {
    {U,  'U', "U"},  {Ui, 'U', "Ui"}, {U2, 'U', "U2"},
    {L,  'L', "L"},  {Li, 'L', "Li"}, {L2, 'L', "L2"},
    {F,  'F', "F"},  {Fi, 'F', "Fi"}, {F2, 'F', "F2"},
    {R,  'R', "R"},  {Ri, 'R', "Ri"}, {R2, 'R', "R2"},
    {B,  'B', "B"},  {Bi, 'B', "Bi"}, {B2, 'B', "B2"},
    {D,  'D', "D"},  {Di, 'D', "Di"}, {D2, 'D', "D2"}
};

static void apply_scramble_move_local(Cube* cube, const char* move) {
    if (strcmp(move, "U") == 0) U(cube);
    else if (strcmp(move, "Ui") == 0) Ui(cube);
    else if (strcmp(move, "U2") == 0) U2(cube);
    else if (strcmp(move, "L") == 0) L(cube);
    else if (strcmp(move, "Li") == 0) Li(cube);
    else if (strcmp(move, "L2") == 0) L2(cube);
    else if (strcmp(move, "F") == 0) F(cube);
    else if (strcmp(move, "Fi") == 0) Fi(cube);
    else if (strcmp(move, "F2") == 0) F2(cube);
    else if (strcmp(move, "R") == 0) R(cube);
    else if (strcmp(move, "Ri") == 0) Ri(cube);
    else if (strcmp(move, "R2") == 0) R2(cube);
    else if (strcmp(move, "B") == 0) B(cube);
    else if (strcmp(move, "Bi") == 0) Bi(cube);
    else if (strcmp(move, "B2") == 0) B2(cube);
    else if (strcmp(move, "D") == 0) D(cube);
    else if (strcmp(move, "Di") == 0) Di(cube);
    else if (strcmp(move, "D2") == 0) D2(cube);
}

static void apply_seeded_scramble_local(Cube* cube, int length, unsigned int seed) {
    std::mt19937 rng(seed);
    const char faces[6] = {'U', 'D', 'F', 'B', 'R', 'L'};
    char last_moves[2] = {'\0', '\0'};

    for (int i = 0; i < length; ++i) {
        char face_char;
        int dir_index;
        do {
            face_char = faces[rng() % 6];
            dir_index = rng() % 3;
        } while ((i > 0 && face_char == last_moves[0]) ||
                 (i > 1 && face_char == last_moves[1]));

        last_moves[1] = last_moves[0];
        last_moves[0] = face_char;

        int face_index = 0;
        switch (face_char) {
            case 'U': face_index = 0; break;
            case 'L': face_index = 1; break;
            case 'F': face_index = 2; break;
            case 'R': face_index = 3; break;
            case 'B': face_index = 4; break;
            case 'D': face_index = 5; break;
            default: face_index = 0; break;
        }

        const ScrambleMoveDef& move = kAllMoves[face_index * 3 + dir_index];
        move.fn(cube);
        strcat(scramble_moves, move.text);
        strcat(scramble_moves, " ");
    }

    reset_moves(temporary_moves, sizeof(temporary_moves));
}

static void prepare_scrambled_cube(Cube* cube, unsigned int seed_override, bool use_seed_override) {
    app_clear_move_buffers();
    cube_init(cube, kInitialState);

    if (config::kUseFixedScramble) {
        for (int i = 0; i < config::kFixedScrambleLength; ++i) {
            apply_scramble_move_local(cube, config::kFixedScramble[i]);
            strcat(scramble_moves, config::kFixedScramble[i]);
            strcat(scramble_moves, " ");
        }
        reset_moves(temporary_moves, sizeof(temporary_moves));
    } else if (config::kUseSeededScramble) {
        const unsigned int seed = use_seed_override ? seed_override : config::kScrambleSeed;
        apply_seeded_scramble_local(cube, config::kRandomScrambleLength, seed);
    } else {
        scramble_cube(cube, config::kRandomScrambleLength);
        catenate_moves(scramble_moves, temporary_moves);
        reset_moves(temporary_moves, sizeof(temporary_moves));
    }

    cube_set_initial_state(cube, cube_get_current_state(cube));
}

struct Esp32FmcState {
    bool active;
    bool printed_summary;
    Cube scrambled;
    Cube inverse_scrambled;
    bool has_reverse;
    int route_index;
    int total_routes;
    int best_move_count;
    char best_moves[256];
    uint64_t started_us;
    size_t free_heap_before_bytes;
};

static Esp32FmcState g_fmc = {};

#if ZZ_ESP32_ENABLE_BENCHMARK
struct Esp32FmcBenchmarkState {
    bool active;
    bool printed_summary;
    int current_run;
    int route_index;
    int total_routes;
    int success_count;
    int failure_count;
    int best_move_count;
    uint64_t run_started_us;
    Cube scrambled;
    Cube inverse_scrambled;
    bool has_reverse;
    char best_moves[256];
    int best_move_counts[config::kFmcBenchmarkRunCount];
    uint32_t time_us[config::kFmcBenchmarkRunCount];
    size_t free_heap_before_bytes[config::kFmcBenchmarkRunCount];
    size_t free_heap_after_bytes[config::kFmcBenchmarkRunCount];
    size_t min_free_heap_bytes[config::kFmcBenchmarkRunCount];
};

static Esp32FmcBenchmarkState g_fmc_benchmark = {};

static void sort_ints(int* values, int count);
static void print_int_summary(const char* label, const int* values, int count);
static void print_size_summary(const char* label, const size_t* values, int count);
static void print_time_summary(const uint32_t* values, int count);
#endif

static void run_fmc_step() {
    if (!g_fmc.active || g_fmc.route_index >= g_fmc.total_routes) {
        return;
    }

    char candidate[256] = {};
    int move_count = -1;
    const bool reverse_phase = g_fmc.route_index >= static_cast<int>(kFmcRoutes.size());
    const int route_slot = reverse_phase
        ? g_fmc.route_index - static_cast<int>(kFmcRoutes.size())
        : g_fmc.route_index;
    const FmcRoute& route = kFmcRoutes[route_slot];

    bool solved = false;
    if (reverse_phase) {
        char reverse_route_solution[256] = {};
        int reverse_route_move_count = -1;
        if (solve_fmc_route(&g_fmc.inverse_scrambled, route, reverse_route_solution, sizeof(reverse_route_solution), &reverse_route_move_count) &&
            reverse_route_move_count <= g_fmc.best_move_count) {
            solved = invert_solution_string(reverse_route_solution, candidate, sizeof(candidate));
            move_count = reverse_route_move_count;
        }
    } else {
        solved = solve_fmc_route(&g_fmc.scrambled, route, candidate, sizeof(candidate), &move_count);
    }

    if (solved && move_count >= 0 && move_count <= g_fmc.best_move_count) {
        g_fmc.best_move_count = move_count;
        strncpy(g_fmc.best_moves, candidate, sizeof(g_fmc.best_moves) - 1);
        g_fmc.best_moves[sizeof(g_fmc.best_moves) - 1] = '\0';

        if (!reverse_phase && !g_fmc.has_reverse &&
            build_inverse_scramble_state_from_solution(candidate, &g_fmc.inverse_scrambled)) {
            g_fmc.has_reverse = true;
            g_fmc.total_routes = static_cast<int>(kFmcRoutes.size()) * 2;
        }

        Serial.printf("FMC best update: route=%d/%d%s | moves=%d | solution=%s\n",
                      g_fmc.route_index + 1,
                      g_fmc.total_routes,
                      reverse_phase ? " (reverse)" : "",
                      move_count,
                      g_fmc.best_moves);
    } else if (((g_fmc.route_index + 1) % 16) == 0) {
        Serial.printf("FMC progress: route=%d/%d | current_best=%d\n",
                      g_fmc.route_index + 1,
                      g_fmc.total_routes,
                      g_fmc.best_move_count >= 1000000 ? -1 : g_fmc.best_move_count);
    }

    g_fmc.route_index++;

    if (g_fmc.route_index >= g_fmc.total_routes && !g_fmc.printed_summary) {
        g_fmc.active = false;
        g_fmc.printed_summary = true;

        const uint64_t elapsed_us = zz_platform_now_us() - g_fmc.started_us;
        const size_t free_heap_after = zz_platform_free_heap_bytes();
        const size_t min_free_heap = zz_platform_min_free_heap_bytes();

        Serial.println("FMC kesz");
        if (g_fmc.best_move_count < 1000000) {
            Serial.printf("FMC best solution: %s\n", g_fmc.best_moves);
            Serial.printf("FMC best moves: %d\n", g_fmc.best_move_count);
        } else {
            Serial.println("FMC best solution: nincs ervenyes megoldas");
        }
        Serial.printf("FMC routes processed: %d\n", g_fmc.total_routes);
        Serial.printf("FMC time: %.3f ms\n", static_cast<double>(elapsed_us) / 1000.0);
        Serial.printf("FMC free heap before: %u bytes\n", static_cast<unsigned>(g_fmc.free_heap_before_bytes));
        Serial.printf("FMC free heap after: %u bytes\n", static_cast<unsigned>(free_heap_after));
        Serial.printf("FMC min free heap: %u bytes\n", static_cast<unsigned>(min_free_heap));
    }
}

#if ZZ_ESP32_ENABLE_BENCHMARK
static void run_fmc_benchmark_step() {
    if (!g_fmc_benchmark.active || g_fmc_benchmark.current_run >= config::kFmcBenchmarkRunCount) {
        return;
    }

    char candidate[256] = {};
    int move_count = -1;
    const bool reverse_phase = g_fmc_benchmark.route_index >= static_cast<int>(kFmcRoutes.size());
    const int route_slot = reverse_phase
        ? g_fmc_benchmark.route_index - static_cast<int>(kFmcRoutes.size())
        : g_fmc_benchmark.route_index;
    const FmcRoute& route = kFmcRoutes[route_slot];

    bool solved = false;
    if (reverse_phase) {
        char reverse_route_solution[256] = {};
        int reverse_route_move_count = -1;
        if (solve_fmc_route(&g_fmc_benchmark.inverse_scrambled, route, reverse_route_solution, sizeof(reverse_route_solution), &reverse_route_move_count) &&
            reverse_route_move_count <= g_fmc_benchmark.best_move_count) {
            solved = invert_solution_string(reverse_route_solution, candidate, sizeof(candidate));
            move_count = reverse_route_move_count;
        }
    } else {
        solved = solve_fmc_route(&g_fmc_benchmark.scrambled, route, candidate, sizeof(candidate), &move_count);
    }

    if (solved && move_count >= 0 && move_count <= g_fmc_benchmark.best_move_count) {
        g_fmc_benchmark.best_move_count = move_count;
        strncpy(g_fmc_benchmark.best_moves, candidate, sizeof(g_fmc_benchmark.best_moves) - 1);
        g_fmc_benchmark.best_moves[sizeof(g_fmc_benchmark.best_moves) - 1] = '\0';

        if (!reverse_phase && !g_fmc_benchmark.has_reverse &&
            build_inverse_scramble_state_from_solution(candidate, &g_fmc_benchmark.inverse_scrambled)) {
            g_fmc_benchmark.has_reverse = true;
            g_fmc_benchmark.total_routes = static_cast<int>(kFmcRoutes.size()) * 2;
        }
    }

    g_fmc_benchmark.route_index++;

    if (g_fmc_benchmark.route_index >= g_fmc_benchmark.total_routes) {
        const int idx = g_fmc_benchmark.current_run;
        const uint64_t elapsed_us = zz_platform_now_us() - g_fmc_benchmark.run_started_us;
        g_fmc_benchmark.time_us[idx] = static_cast<uint32_t>(elapsed_us);
        g_fmc_benchmark.free_heap_after_bytes[idx] = zz_platform_free_heap_bytes();
        g_fmc_benchmark.min_free_heap_bytes[idx] = zz_platform_min_free_heap_bytes();
        g_fmc_benchmark.best_move_counts[idx] =
            g_fmc_benchmark.best_move_count >= 1000000 ? -1 : g_fmc_benchmark.best_move_count;

        if (g_fmc_benchmark.best_move_count >= 1000000) {
            g_fmc_benchmark.failure_count++;
        } else {
            g_fmc_benchmark.success_count++;
        }

        Serial.printf("FMC benchmark run %d / %d | seed=%u | solved=%s | best_moves=%d | time=%.3f ms | free_heap=%u\n",
                      idx + 1,
                      config::kFmcBenchmarkRunCount,
                      config::kFmcBenchmarkStartSeed + idx,
                      g_fmc_benchmark.best_move_count >= 1000000 ? "nem" : "igen",
                      g_fmc_benchmark.best_move_count >= 1000000 ? -1 : g_fmc_benchmark.best_move_count,
                      static_cast<double>(elapsed_us) / 1000.0,
                      static_cast<unsigned>(g_fmc_benchmark.free_heap_after_bytes[idx]));

        g_fmc_benchmark.current_run++;
        if (g_fmc_benchmark.current_run >= config::kFmcBenchmarkRunCount) {
            g_fmc_benchmark.active = false;
            g_fmc_benchmark.printed_summary = true;

            Serial.println("FMC benchmark kesz");
            Serial.printf("FMC benchmark success/fail: %d / %d\n",
                          g_fmc_benchmark.success_count,
                          g_fmc_benchmark.failure_count);
            print_int_summary("FMC best moves",
                              g_fmc_benchmark.best_move_counts,
                              config::kFmcBenchmarkRunCount);
            print_time_summary(g_fmc_benchmark.time_us, config::kFmcBenchmarkRunCount);
            print_size_summary("FMC free heap before (bytes)",
                               g_fmc_benchmark.free_heap_before_bytes,
                               config::kFmcBenchmarkRunCount);
            print_size_summary("FMC free heap after (bytes)",
                               g_fmc_benchmark.free_heap_after_bytes,
                               config::kFmcBenchmarkRunCount);
            print_size_summary("FMC min free heap (bytes)",
                               g_fmc_benchmark.min_free_heap_bytes,
                               config::kFmcBenchmarkRunCount);
            return;
        }

        const unsigned int next_seed = config::kFmcBenchmarkStartSeed + g_fmc_benchmark.current_run;
        prepare_scrambled_cube(&g_fmc_benchmark.scrambled, next_seed, true);
        g_fmc_benchmark.has_reverse = false;
        g_fmc_benchmark.route_index = 0;
        g_fmc_benchmark.total_routes = static_cast<int>(kFmcRoutes.size());
        g_fmc_benchmark.best_move_count = 1000000;
        g_fmc_benchmark.best_moves[0] = '\0';
        g_fmc_benchmark.run_started_us = zz_platform_now_us();
        g_fmc_benchmark.free_heap_before_bytes[g_fmc_benchmark.current_run] = zz_platform_free_heap_bytes();
    } else if ((g_fmc_benchmark.route_index % 32) == 0) {
        Serial.printf("FMC benchmark progress: run=%d/%d route=%d/%d current_best=%d\n",
                      g_fmc_benchmark.current_run + 1,
                      config::kFmcBenchmarkRunCount,
                      g_fmc_benchmark.route_index,
                      g_fmc_benchmark.total_routes,
                      g_fmc_benchmark.best_move_count >= 1000000 ? -1 : g_fmc_benchmark.best_move_count);
    }
}
#endif

#if ZZ_ESP32_ENABLE_BENCHMARK
struct Esp32BenchmarkState {
    bool active;
    bool printed_summary;
    int current_run;
    int success_count;
    int failure_count;
    int rotation_solution_count;
    int total_moves[config::kBenchmarkRunCount];
    int face_moves[config::kBenchmarkRunCount];
    uint32_t time_us[config::kBenchmarkRunCount];
    size_t heap_peak_bytes[config::kBenchmarkRunCount];
    size_t free_heap_before_bytes[config::kBenchmarkRunCount];
    size_t free_heap_after_bytes[config::kBenchmarkRunCount];
    size_t min_free_heap_bytes[config::kBenchmarkRunCount];
};

static Esp32BenchmarkState g_benchmark = {};

static void sort_ints(int* values, int count) {
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (values[j] < values[i]) {
                const int tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;
            }
        }
    }
}

static void print_int_summary(const char* label, const int* values, int count) {
    if (count <= 0) {
        return;
    }

    long long sum = 0;
    int sorted[config::kBenchmarkRunCount];
    for (int i = 0; i < count; ++i) {
        sum += values[i];
        sorted[i] = values[i];
    }
    sort_ints(sorted, count);

    const int p50 = sorted[(count - 1) * 50 / 100];
    const int p90 = sorted[(count - 1) * 90 / 100];
    const int p95 = sorted[(count - 1) * 95 / 100];
    const int p99 = sorted[(count - 1) * 99 / 100];

    Serial.printf("%s avg/min/max: %.3f / %d / %d\n",
                  label,
                  static_cast<double>(sum) / count,
                  sorted[0],
                  sorted[count - 1]);
    Serial.printf("%s p50/p90/p95/p99: %d / %d / %d / %d\n",
                  label, p50, p90, p95, p99);
}

static void print_size_summary(const char* label, const size_t* values, int count) {
    if (count <= 0) {
        return;
    }

    unsigned long long sum = 0;
    size_t min_value = values[0];
    size_t max_value = values[0];
    for (int i = 0; i < count; ++i) {
        sum += values[i];
        if (values[i] < min_value) min_value = values[i];
        if (values[i] > max_value) max_value = values[i];
    }

    Serial.printf("%s avg/min/max: %.3f / %u / %u\n",
                  label,
                  static_cast<double>(sum) / count,
                  static_cast<unsigned>(min_value),
                  static_cast<unsigned>(max_value));
}

static void print_time_summary(const uint32_t* values, int count) {
    if (count <= 0) {
        return;
    }

    unsigned long long sum = 0;
    uint32_t min_value = values[0];
    uint32_t max_value = values[0];
    for (int i = 0; i < count; ++i) {
        sum += values[i];
        if (values[i] < min_value) min_value = values[i];
        if (values[i] > max_value) max_value = values[i];
    }

    Serial.printf("Time avg/min/max (ms): %.3f / %.3f / %.3f\n",
                  static_cast<double>(sum) / count / 1000.0,
                  static_cast<double>(min_value) / 1000.0,
                  static_cast<double>(max_value) / 1000.0);
}

static void run_benchmark_step() {
    if (!g_benchmark.active || g_benchmark.current_run >= config::kBenchmarkRunCount) {
        return;
    }

    AppRunConfig run_config = make_run_config(
        SolverMode::Normal,
        PatternPreset::None,
        false,
        false,
        false,
        false,
        false,
        true,
        config::kRandomScrambleLength,
        config::kBenchmarkStartSeed + g_benchmark.current_run,
        config::kFixedScramble,
        config::kFixedScrambleLength);

    SolveStats stats = {};
    const bool solved = app_run_solve(run_config, &stats);

    const int idx = g_benchmark.current_run;
    g_benchmark.total_moves[idx] = stats.total_moves;
    g_benchmark.face_moves[idx] = stats.face_moves;
    g_benchmark.time_us[idx] = static_cast<uint32_t>(stats.elapsed_us);
    g_benchmark.heap_peak_bytes[idx] = stats.solver_heap_peak_bytes;
    g_benchmark.free_heap_before_bytes[idx] = stats.free_heap_before_bytes;
    g_benchmark.free_heap_after_bytes[idx] = stats.free_heap_after_bytes;
    g_benchmark.min_free_heap_bytes[idx] = stats.min_free_heap_bytes;

    if (solved) {
        g_benchmark.success_count++;
    } else {
        g_benchmark.failure_count++;
        Serial.printf("Benchmark fail run=%d seed=%u solution=%s\n",
                      idx + 1,
                      run_config.scramble_seed,
                      stats.solution);
    }
    if (stats.has_rotations) {
        g_benchmark.rotation_solution_count++;
    }

    Serial.printf("Benchmark progress: %d / %d | solved=%s | time=%.3f ms | moves=%d | free_heap=%u\n",
                  idx + 1,
                  config::kBenchmarkRunCount,
                  solved ? "igen" : "nem",
                  static_cast<double>(stats.elapsed_us) / 1000.0,
                  stats.total_moves,
                  static_cast<unsigned>(stats.free_heap_after_bytes));

    g_benchmark.current_run++;

    if (g_benchmark.current_run >= config::kBenchmarkRunCount && !g_benchmark.printed_summary) {
        g_benchmark.active = false;
        g_benchmark.printed_summary = true;

        Serial.println("Benchmark kesz");
        Serial.printf("Benchmark success/fail: %d / %d\n",
                      g_benchmark.success_count,
                      g_benchmark.failure_count);
        Serial.printf("Benchmark rotation solutions: %d\n",
                      g_benchmark.rotation_solution_count);
        print_int_summary("Total", g_benchmark.total_moves, config::kBenchmarkRunCount);
        print_int_summary("Face", g_benchmark.face_moves, config::kBenchmarkRunCount);
        print_time_summary(g_benchmark.time_us, config::kBenchmarkRunCount);
        print_size_summary("Solver heap peak (bytes)",
                           g_benchmark.heap_peak_bytes,
                           config::kBenchmarkRunCount);
        print_size_summary("Free heap before (bytes)",
                           g_benchmark.free_heap_before_bytes,
                           config::kBenchmarkRunCount);
        print_size_summary("Free heap after (bytes)",
                           g_benchmark.free_heap_after_bytes,
                           config::kBenchmarkRunCount);
        print_size_summary("Min free heap (bytes)",
                           g_benchmark.min_free_heap_bytes,
                           config::kBenchmarkRunCount);
    }
}
#endif

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("ZZOptimalCore ESP32-WROOM-32D demo indul");

#if ZZ_ESP32_ENABLE_BENCHMARK
    if (config::kRunMode == RunMode::NormalBenchmark) {
        Serial.printf("Mod: %s\n", run_mode_label(config::kRunMode));
        g_benchmark.active = true;
        g_benchmark.printed_summary = false;
        g_benchmark.current_run = 0;
        g_benchmark.success_count = 0;
        g_benchmark.failure_count = 0;
        g_benchmark.rotation_solution_count = 0;
        return;
    }

    if (config::kRunMode == RunMode::FmcBenchmark) {
        Serial.printf("Mod: %s\n", run_mode_label(config::kRunMode));
        g_fmc_benchmark.active = true;
        g_fmc_benchmark.printed_summary = false;
        g_fmc_benchmark.current_run = 0;
        g_fmc_benchmark.route_index = 0;
        g_fmc_benchmark.success_count = 0;
        g_fmc_benchmark.failure_count = 0;
        g_fmc_benchmark.best_move_count = 1000000;
        g_fmc_benchmark.best_moves[0] = '\0';
        prepare_scrambled_cube(&g_fmc_benchmark.scrambled, config::kFmcBenchmarkStartSeed, true);
        g_fmc_benchmark.has_reverse = false;
        g_fmc_benchmark.total_routes = static_cast<int>(kFmcRoutes.size());
        g_fmc_benchmark.run_started_us = zz_platform_now_us();
        g_fmc_benchmark.free_heap_before_bytes[0] = zz_platform_free_heap_bytes();
        return;
    }
#endif

    if (config::kRunMode == RunMode::FmcSolve) {
        Serial.printf("Mod: %s\n", run_mode_label(config::kRunMode));
        prepare_scrambled_cube(&g_fmc.scrambled, 0, false);
        Serial.printf("Keveres: %s (%d lepesbol)\n", scramble_moves, count_moves(scramble_moves));
        g_fmc.active = true;
        g_fmc.printed_summary = false;
        g_fmc.route_index = 0;
        g_fmc.has_reverse = false;
        g_fmc.total_routes = static_cast<int>(kFmcRoutes.size());
        g_fmc.best_move_count = 1000000;
        g_fmc.best_moves[0] = '\0';
        g_fmc.started_us = zz_platform_now_us();
        g_fmc.free_heap_before_bytes = zz_platform_free_heap_bytes();
        return;
    }

    Serial.printf("Mod: %s\n", run_mode_label(config::kRunMode));
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
    print_stats(stats);
}

void loop() {
#if ZZ_ESP32_ENABLE_BENCHMARK
    if (config::kRunMode == RunMode::NormalBenchmark && g_benchmark.active) {
        run_benchmark_step();
        delay(config::kBenchmarkPauseMsBetweenRuns);
        return;
    }

    if (config::kRunMode == RunMode::FmcBenchmark && g_fmc_benchmark.active) {
        run_fmc_benchmark_step();
        delay(config::kFmcBenchmarkPauseMsBetweenRuns);
        return;
    }
#endif

    if (config::kRunMode == RunMode::FmcSolve && g_fmc.active) {
        run_fmc_step();
        delay(1);
        return;
    }

    delay(1000);
}
