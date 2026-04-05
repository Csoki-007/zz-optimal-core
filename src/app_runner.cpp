#include "app_runner.h"
#include "zz_profiler.h"
#include "zz_platform.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>

#if !defined(ARDUINO) && !defined(ESP_PLATFORM)
#include <fstream>
#endif

static const uint8_t initial_state[54] __attribute__((aligned(4))) = {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6
};

char scramble_moves[256] = {};
char moves[256] = {};
char temporary_moves[256] = {};

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

static constexpr int kMaxBenchmarkSamples = 10000;
static const uint8_t kSolvedState[54] = {
    1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,
    4,4,4,4,4,4,4,4,4,
    5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6
};

static bool apply_solution(Cube* cube, const char* solution);
static const uint8_t* build_pattern_state_from_algorithm(const char* algorithm);

SolverMode solver_mode_from_run_mode(RunMode mode) {
    return (mode == RunMode::FmcSolve || mode == RunMode::FmcBenchmark)
        ? SolverMode::Fmc
        : SolverMode::Normal;
}

bool run_mode_is_benchmark(RunMode mode) {
    return mode == RunMode::NormalBenchmark || mode == RunMode::FmcBenchmark;
}

bool run_mode_is_fmc(RunMode mode) {
    return solver_mode_from_run_mode(mode) == SolverMode::Fmc;
}

const char* run_mode_label(RunMode mode) {
    switch (mode) {
        case RunMode::NormalSolve: return "Normal";
        case RunMode::FmcSolve: return "FMC";
        case RunMode::NormalBenchmark: return "Benchmark";
        case RunMode::FmcBenchmark: return "FMC Benchmark";
        default: return "Unknown";
    }
}

const char* pattern_preset_name(PatternPreset preset) {
    switch (preset) {
        case PatternPreset::None: return "None";
        case PatternPreset::Checkerboard: return "Checkerboard";
        case PatternPreset::Anaconda: return "Anaconda";
        case PatternPreset::CubeInCubeInCube: return "Cube in a cube in a cube";
        case PatternPreset::CubeInCube: return "Cube in cube";
        case PatternPreset::VerticalStripes: return "Vertical stripes";
        case PatternPreset::Python: return "Python";
        case PatternPreset::FourCenters: return "4 centers";
        case PatternPreset::SixCenters: return "6 centers";
        case PatternPreset::SuperFlip: return "SuperFlip";
        default: return "Unknown";
    }
}

const uint8_t* pattern_preset_state(PatternPreset preset) {
    switch (preset) {
        case PatternPreset::Checkerboard: return kCheckerboardPattern;
        case PatternPreset::Anaconda: return kAnacondaPattern;
        case PatternPreset::CubeInCubeInCube: return kCubeInCubeInCubePattern;
        case PatternPreset::CubeInCube:
            return build_pattern_state_from_algorithm("F L F Ui R U F2 L2 Ui Li B Di Bi L2 U");
        case PatternPreset::VerticalStripes:
            return build_pattern_state_from_algorithm("F U F R L2 B Di R D2 L Di B R2 L F U F");
        case PatternPreset::Python:
            return build_pattern_state_from_algorithm("F2 Ri Bi U Ri L Fi L Fi B Di R B L2");
        case PatternPreset::FourCenters:
            return build_pattern_state_from_algorithm("F2 B2 U Di R2 L2 U Di");
        case PatternPreset::SixCenters:
            return build_pattern_state_from_algorithm("U Di R Li F Bi U Di");
        case PatternPreset::SuperFlip:
            return build_pattern_state_from_algorithm("U R2 F B R B2 R U2 L B2 R Ui Di R2 F Ri L B2 U2 F2");
        case PatternPreset::None:
        default: return nullptr;
    }
}

bool has_pattern_preset(PatternPreset preset) {
    return pattern_preset_state(preset) != nullptr;
}

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
                             int fixed_scramble_length) {
    AppRunConfig config = {};
    config.solver_mode = solver_mode;
    config.pattern_preset = pattern_preset;
    config.print_mode = print_mode;
    config.print_scramble = print_scramble;
    config.print_solution = print_solution;
    config.visualize_solution = visualize_solution;
    config.use_fixed_scramble = use_fixed_scramble;
    config.use_seeded_scramble = use_seeded_scramble;
    config.random_scramble_length = random_scramble_length;
    config.scramble_seed = scramble_seed;
    config.fixed_scramble = fixed_scramble;
    config.fixed_scramble_length = fixed_scramble_length;
    return config;
}

BenchmarkConfig make_benchmark_config(SolverMode solver_mode,
                                      int random_scramble_length,
                                      int run_count,
                                      unsigned int start_seed,
                                      int print_progress_every,
                                      bool print_failures,
                                      bool write_csv,
                                      const char* csv_path) {
    BenchmarkConfig config = {};
    config.solver_mode = solver_mode;
    config.random_scramble_length = random_scramble_length;
    config.run_count = run_count;
    config.start_seed = start_seed;
    config.print_progress_every = print_progress_every;
    config.print_failures = print_failures;
    config.write_csv = write_csv;
    config.csv_path = csv_path;
    return config;
}

DirectSolveConfig make_direct_solve_config(SolverMode solver_mode,
                                           PatternPreset pattern_preset,
                                           bool print_mode,
                                           bool print_solution,
                                           bool visualize_solution) {
    DirectSolveConfig config = {};
    config.solver_mode = solver_mode;
    config.pattern_preset = pattern_preset;
    config.print_mode = print_mode;
    config.print_solution = print_solution;
    config.visualize_solution = visualize_solution;
    return config;
}

void app_clear_move_buffers() {
    reset_moves(scramble_moves, sizeof(scramble_moves));
    reset_moves(moves, sizeof(moves));
    reset_moves(temporary_moves, sizeof(temporary_moves));
}

static void apply_scramble_move(Cube* cube, const char* move) {
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

static void apply_seeded_scramble(Cube* cube, int length, unsigned int seed, bool record_scramble) {
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
        if (record_scramble) {
            strcat(scramble_moves, move.text);
            strcat(scramble_moves, " ");
        }
    }

    reset_moves(temporary_moves, sizeof(temporary_moves));
}

static bool cube_is_solved_local(const Cube* cube) {
    for (int face = 0; face < 6; ++face) {
        const int start = face * 9;
        const uint8_t color = cube->cube[start];
        for (int i = 1; i < 9; ++i) {
            if (cube->cube[start + i] != color) {
                return false;
            }
        }
    }
    return true;
}

static bool is_rotation_token(const char* token) {
    return strcmp(token, "x") == 0 || strcmp(token, "X") == 0 ||
           strcmp(token, "xi") == 0 || strcmp(token, "Xi") == 0 ||
           strcmp(token, "x2") == 0 || strcmp(token, "X2") == 0 ||
           strcmp(token, "y") == 0 || strcmp(token, "Y") == 0 ||
           strcmp(token, "yi") == 0 || strcmp(token, "Yi") == 0 ||
           strcmp(token, "y2") == 0 || strcmp(token, "Y2") == 0 ||
           strcmp(token, "z") == 0 || strcmp(token, "Z") == 0 ||
           strcmp(token, "zi") == 0 || strcmp(token, "Zi") == 0;
}

static bool apply_move_token(Cube* cube, const char* token) {
    if (strcmp(token, "U") == 0) { U(cube); return true; }
    if (strcmp(token, "Ui") == 0) { Ui(cube); return true; }
    if (strcmp(token, "U2") == 0) { U2(cube); return true; }
    if (strcmp(token, "L") == 0) { L(cube); return true; }
    if (strcmp(token, "Li") == 0) { Li(cube); return true; }
    if (strcmp(token, "L2") == 0) { L2(cube); return true; }
    if (strcmp(token, "F") == 0) { F(cube); return true; }
    if (strcmp(token, "Fi") == 0) { Fi(cube); return true; }
    if (strcmp(token, "F2") == 0) { F2(cube); return true; }
    if (strcmp(token, "R") == 0) { R(cube); return true; }
    if (strcmp(token, "Ri") == 0) { Ri(cube); return true; }
    if (strcmp(token, "R2") == 0) { R2(cube); return true; }
    if (strcmp(token, "B") == 0) { B(cube); return true; }
    if (strcmp(token, "Bi") == 0) { Bi(cube); return true; }
    if (strcmp(token, "B2") == 0) { B2(cube); return true; }
    if (strcmp(token, "D") == 0) { D(cube); return true; }
    if (strcmp(token, "Di") == 0) { Di(cube); return true; }
    if (strcmp(token, "D2") == 0) { D2(cube); return true; }
    if (strcmp(token, "x") == 0 || strcmp(token, "X") == 0) { X_rotation(cube); return true; }
    if (strcmp(token, "xi") == 0 || strcmp(token, "Xi") == 0) { Xi_rotation(cube); return true; }
    if (strcmp(token, "x2") == 0 || strcmp(token, "X2") == 0) { X2_rotation(cube); return true; }
    if (strcmp(token, "y") == 0 || strcmp(token, "Y") == 0) { Y_rotation(cube); return true; }
    if (strcmp(token, "yi") == 0 || strcmp(token, "Yi") == 0) { Yi_rotation(cube); return true; }
    if (strcmp(token, "y2") == 0 || strcmp(token, "Y2") == 0) { Y2_rotation(cube); return true; }
    if (strcmp(token, "z") == 0 || strcmp(token, "Z") == 0) { Z_rotation(cube); return true; }
    if (strcmp(token, "zi") == 0 || strcmp(token, "Zi") == 0) { Zi_rotation(cube); return true; }
    return false;
}

static bool apply_solution(Cube* cube, const char* solution) {
    ZZ_PROFILE_SCOPE(ApplySolution);
    char buffer[512];
    strncpy(buffer, solution, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    for (char* token = strtok(buffer, " "); token != nullptr; token = strtok(nullptr, " ")) {
        if (!apply_move_token(cube, token)) {
            return false;
        }
    }

    return true;
}

static const uint8_t* build_pattern_state_from_algorithm(const char* algorithm) {
    if (algorithm == nullptr || algorithm[0] == '\0') {
        return nullptr;
    }

    struct PatternCacheEntry {
        const char* algorithm;
        uint8_t state[54];
        bool initialized;
    };

    static PatternCacheEntry cache[] = {
        {"F L F Ui R U F2 L2 Ui Li B Di Bi L2 U", {}, false},
        {"F U F R L2 B Di R D2 L Di B R2 L F U F", {}, false},
        {"F2 Ri Bi U Ri L Fi L Fi B Di R B L2", {}, false},
        {"F2 B2 U Di R2 L2 U Di", {}, false},
        {"U Di R Li F Bi U Di", {}, false},
        {"U R2 F B R B2 R U2 L B2 R Ui Di R2 F Ri L B2 U2 F2", {}, false}
    };

    for (PatternCacheEntry& entry : cache) {
        if (strcmp(entry.algorithm, algorithm) == 0) {
            if (!entry.initialized) {
                Cube cube;
                cube_init(&cube, kSolvedState);
                if (!apply_solution(&cube, algorithm)) {
                    return nullptr;
                }
                memcpy(entry.state, cube_get_current_state(&cube), 54);
                entry.initialized = true;
            }
            return entry.state;
        }
    }

    return nullptr;
}

static int count_non_rotation_moves(const char* solution) {
    char buffer[512];
    strncpy(buffer, solution, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    int count = 0;

    for (char* token = strtok(buffer, " "); token != nullptr; token = strtok(nullptr, " ")) {
        if (!is_rotation_token(token)) {
            count++;
        }
    }

    return count;
}

static bool cube_matches_state(const Cube* cube, const uint8_t* state) {
    return cube != nullptr && state != nullptr && memcmp(cube->cube, state, 54) == 0;
}

static constexpr uint8_t kEdgePositions[12][2] = {
    {1,37}, {3,28}, {5,19}, {7,10}, {25,12}, {21,34},
    {43,30}, {39,16}, {46,23}, {48,32}, {50,41}, {52,14}
};

static constexpr uint8_t kCornerPositions[8][3] = {
    {0, 9, 38}, {2, 36, 29}, {4, 27, 20}, {6, 18, 11},
    {45, 13, 24}, {47, 22, 33}, {49, 31, 42}, {51, 40, 15}
};

static void extract_edges_from_state(const uint8_t* state, uint8_t out[12][2]) {
    for (int i = 0; i < 12; ++i) {
        out[i][0] = state[kEdgePositions[i][0]];
        out[i][1] = state[kEdgePositions[i][1]];
    }
}

static void extract_corners_from_state(const uint8_t* state, uint8_t out[8][3]) {
    for (int i = 0; i < 8; ++i) {
        out[i][0] = state[kCornerPositions[i][0]];
        out[i][1] = state[kCornerPositions[i][1]];
        out[i][2] = state[kCornerPositions[i][2]];
    }
}

static bool find_edge_positions_for_piece(const uint8_t edge[2],
                                          const uint8_t scrambled_edges[12][2],
                                          uint8_t out[2]) {
    for (int i = 0; i < 12; ++i) {
        if (scrambled_edges[i][0] == edge[0] && scrambled_edges[i][1] == edge[1]) {
            out[0] = kEdgePositions[i][0];
            out[1] = kEdgePositions[i][1];
            return true;
        }
        if (scrambled_edges[i][0] == edge[1] && scrambled_edges[i][1] == edge[0]) {
            out[0] = kEdgePositions[i][1];
            out[1] = kEdgePositions[i][0];
            return true;
        }
    }
    return false;
}

static bool find_corner_positions_for_piece(const uint8_t corner[3],
                                            const uint8_t scrambled_corners[8][3],
                                            uint8_t out[3]) {
    for (int i = 0; i < 8; ++i) {
        if (scrambled_corners[i][0] == corner[0] &&
            scrambled_corners[i][1] == corner[1] &&
            scrambled_corners[i][2] == corner[2]) {
            out[0] = kCornerPositions[i][0];
            out[1] = kCornerPositions[i][1];
            out[2] = kCornerPositions[i][2];
            return true;
        }
        if (scrambled_corners[i][0] == corner[2] &&
            scrambled_corners[i][1] == corner[0] &&
            scrambled_corners[i][2] == corner[1]) {
            out[0] = kCornerPositions[i][1];
            out[1] = kCornerPositions[i][2];
            out[2] = kCornerPositions[i][0];
            return true;
        }
        if (scrambled_corners[i][0] == corner[1] &&
            scrambled_corners[i][1] == corner[2] &&
            scrambled_corners[i][2] == corner[0]) {
            out[0] = kCornerPositions[i][2];
            out[1] = kCornerPositions[i][0];
            out[2] = kCornerPositions[i][1];
            return true;
        }
    }
    return false;
}

static bool build_decoy_state(const uint8_t* scrambled_state,
                              const uint8_t* pattern_state,
                              uint8_t* out_decoy_state) {
    if (scrambled_state == nullptr || pattern_state == nullptr || out_decoy_state == nullptr) {
        return false;
    }

    uint8_t scrambled_edges[12][2];
    uint8_t scrambled_corners[8][3];
    uint8_t pattern_edges[12][2];
    uint8_t pattern_corners[8][3];
    uint8_t solved_edges[12][2];
    uint8_t solved_corners[8][3];

    extract_edges_from_state(scrambled_state, scrambled_edges);
    extract_corners_from_state(scrambled_state, scrambled_corners);
    extract_edges_from_state(pattern_state, pattern_edges);
    extract_corners_from_state(pattern_state, pattern_corners);
    extract_edges_from_state(kSolvedState, solved_edges);
    extract_corners_from_state(kSolvedState, solved_corners);

    memcpy(out_decoy_state, scrambled_state, 54);

    for (int i = 0; i < 12; ++i) {
        uint8_t pos[2];
        if (!find_edge_positions_for_piece(pattern_edges[i], scrambled_edges, pos)) {
            return false;
        }
        out_decoy_state[pos[0]] = solved_edges[i][0];
        out_decoy_state[pos[1]] = solved_edges[i][1];
    }

    for (int i = 0; i < 8; ++i) {
        uint8_t pos[3];
        if (!find_corner_positions_for_piece(pattern_corners[i], scrambled_corners, pos)) {
            return false;
        }
        out_decoy_state[pos[0]] = solved_corners[i][0];
        out_decoy_state[pos[1]] = solved_corners[i][1];
        out_decoy_state[pos[2]] = solved_corners[i][2];
    }

    return true;
}

static void compute_int_summary(const int* values, int count,
                                double* avg, int* min_value, int* max_value,
                                int* p50, int* p90, int* p95, int* p99) {
    if (count <= 0) {
        *avg = 0.0;
        *min_value = 0;
        *max_value = 0;
        *p50 = 0;
        *p90 = 0;
        *p95 = 0;
        *p99 = 0;
        return;
    }

    long long sum = 0;
    int sorted[kMaxBenchmarkSamples];
    for (int i = 0; i < count; ++i) {
        sum += values[i];
        sorted[i] = values[i];
    }

    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (sorted[j] < sorted[i]) {
                const int tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
        }
    }

    *avg = static_cast<double>(sum) / count;
    *min_value = sorted[0];
    *max_value = sorted[count - 1];
    *p50 = sorted[(count - 1) * 50 / 100];
    *p90 = sorted[(count - 1) * 90 / 100];
    *p95 = sorted[(count - 1) * 95 / 100];
    *p99 = sorted[(count - 1) * 99 / 100];
}

static void compute_double_summary(const double* values, int count,
                                   double* avg, double* min_value, double* max_value) {
    if (count <= 0) {
        *avg = 0.0;
        *min_value = 0.0;
        *max_value = 0.0;
        return;
    }

    double sum = 0.0;
    *min_value = values[0];
    *max_value = values[0];
    for (int i = 0; i < count; ++i) {
        sum += values[i];
        if (values[i] < *min_value) *min_value = values[i];
        if (values[i] > *max_value) *max_value = values[i];
    }
    *avg = sum / count;
}

static void compute_size_summary(const size_t* values, int count,
                                 double* avg, size_t* min_value, size_t* max_value) {
    if (count <= 0) {
        *avg = 0.0;
        *min_value = 0;
        *max_value = 0;
        return;
    }

    unsigned long long sum = 0;
    *min_value = values[0];
    *max_value = values[0];
    for (int i = 0; i < count; ++i) {
        sum += values[i];
        if (values[i] < *min_value) *min_value = values[i];
        if (values[i] > *max_value) *max_value = values[i];
    }
    *avg = static_cast<double>(sum) / count;
}

bool app_run_solve(const AppRunConfig& config, SolveStats* stats) {
    if (stats == nullptr) {
        return false;
    }

    app_clear_move_buffers();

    Cube cube;
    cube_init(&cube, initial_state);

    if (config.use_fixed_scramble && config.fixed_scramble != nullptr && config.fixed_scramble_length > 0) {
        for (int i = 0; i < config.fixed_scramble_length; ++i) {
            apply_scramble_move(&cube, config.fixed_scramble[i]);
            strcat(scramble_moves, config.fixed_scramble[i]);
            strcat(scramble_moves, " ");
        }
        reset_moves(temporary_moves, sizeof(temporary_moves));
    } else if (config.use_seeded_scramble) {
        apply_seeded_scramble(&cube, config.random_scramble_length, config.scramble_seed, true);
    } else {
        scramble_cube(&cube, config.random_scramble_length);
        catenate_moves(scramble_moves, temporary_moves);
        reset_moves(temporary_moves, sizeof(temporary_moves));
    }

    uint8_t verification_initial_state[54];
    memcpy(verification_initial_state, cube_get_current_state(&cube), 54);
    cube_set_initial_state(&cube, cube_get_current_state(&cube));

    if (has_pattern_preset(config.pattern_preset)) {
        uint8_t decoy_state[54];
        if (!build_decoy_state(verification_initial_state,
                               pattern_preset_state(config.pattern_preset),
                               decoy_state)) {
            memset(stats, 0, sizeof(*stats));
            strncpy(stats->scramble, scramble_moves, sizeof(stats->scramble) - 1);
            stats->scramble[sizeof(stats->scramble) - 1] = '\0';
            strncpy(stats->solution, "", sizeof(stats->solution) - 1);
            stats->solution[sizeof(stats->solution) - 1] = '\0';
            return false;
        }
        cube_init(&cube, decoy_state);
        cube_set_initial_state(&cube, decoy_state);
    }

    if (config.print_scramble) {
        printf("Keveres: %s (%d lepesbol)\n", scramble_moves, count_moves(scramble_moves));
    }

    if (config.print_mode) {
        printf("Mod: %s\n", config.solver_mode == SolverMode::Fmc ? "FMC" : "Normal");
        if (has_pattern_preset(config.pattern_preset)) {
            printf("Pattern: %s\n", pattern_preset_name(config.pattern_preset));
        }
    }

    reset_solver_heap_stats();
    set_solver_verbose(config.print_mode);
    stats->free_heap_before_bytes = zz_platform_free_heap_bytes();
    const uint64_t started_at_us = zz_platform_now_us();

    if (config.solver_mode == SolverMode::Fmc) {
        solve_fmc(&cube);
    } else {
        solve_once(&cube);
    }

    const uint64_t finished_at_us = zz_platform_now_us();
    stats->elapsed_us = finished_at_us - started_at_us;
    stats->solver_heap_peak_bytes = get_solver_heap_peak_bytes();
    stats->free_heap_after_bytes = zz_platform_free_heap_bytes();
    stats->min_free_heap_bytes = zz_platform_min_free_heap_bytes();

    Cube verify;
    cube_init(&verify, verification_initial_state);
    const bool parsed = apply_solution(&verify, moves);
    if (has_pattern_preset(config.pattern_preset)) {
        stats->solved = parsed && cube_matches_state(&verify, pattern_preset_state(config.pattern_preset));
    } else {
        stats->solved = parsed && cube_is_solved_local(&verify);
    }
    stats->total_moves = count_moves(moves);
    stats->face_moves = count_non_rotation_moves(moves);
    stats->has_rotations =
        strstr(moves, "x") != nullptr || strstr(moves, "y") != nullptr ||
        strstr(moves, "z") != nullptr || strstr(moves, "X") != nullptr ||
        strstr(moves, "Y") != nullptr || strstr(moves, "Z") != nullptr;

    strncpy(stats->scramble, scramble_moves, sizeof(stats->scramble) - 1);
    stats->scramble[sizeof(stats->scramble) - 1] = '\0';
    strncpy(stats->solution, moves, sizeof(stats->solution) - 1);
    stats->solution[sizeof(stats->solution) - 1] = '\0';

    if (config.print_solution) {
        printf("%s megoldas: %s (%d lepesbol)\n",
               config.solver_mode == SolverMode::Fmc ? "FMC" : "Normal",
               moves,
               stats->total_moves);
    }

    if (config.visualize_solution) {
        cube_vizualize(scramble_moves, moves);
    }

    set_solver_verbose(true);

    return stats->solved;
}

bool app_run_solve_from_state(const uint8_t* state, const DirectSolveConfig& config, SolveStats* stats) {
    if (state == nullptr || stats == nullptr) {
        return false;
    }

    app_clear_move_buffers();

    Cube cube;
    cube_init(&cube, state);

    uint8_t verification_initial_state[54];
    memcpy(verification_initial_state, state, sizeof(verification_initial_state));

    if (has_pattern_preset(config.pattern_preset)) {
        uint8_t decoy_state[54];
        if (!build_decoy_state(verification_initial_state,
                               pattern_preset_state(config.pattern_preset),
                               decoy_state)) {
            memset(stats, 0, sizeof(*stats));
            stats->scramble[0] = '\0';
            stats->solution[0] = '\0';
            return false;
        }
        cube_init(&cube, decoy_state);
        cube_set_initial_state(&cube, decoy_state);
    } else {
        cube_set_initial_state(&cube, state);
    }

    if (config.print_mode) {
        printf("Mod: %s\n", config.solver_mode == SolverMode::Fmc ? "FMC" : "Normal");
        if (has_pattern_preset(config.pattern_preset)) {
            printf("Pattern: %s\n", pattern_preset_name(config.pattern_preset));
        }
    }

    reset_solver_heap_stats();
    set_solver_verbose(config.print_mode);
    stats->free_heap_before_bytes = zz_platform_free_heap_bytes();
    const uint64_t started_at_us = zz_platform_now_us();

    if (config.solver_mode == SolverMode::Fmc) {
        solve_fmc(&cube);
    } else {
        solve_once(&cube);
    }

    const uint64_t finished_at_us = zz_platform_now_us();
    stats->elapsed_us = finished_at_us - started_at_us;
    stats->solver_heap_peak_bytes = get_solver_heap_peak_bytes();
    stats->free_heap_after_bytes = zz_platform_free_heap_bytes();
    stats->min_free_heap_bytes = zz_platform_min_free_heap_bytes();

    Cube verify;
    cube_init(&verify, verification_initial_state);
    const bool parsed = apply_solution(&verify, moves);
    if (has_pattern_preset(config.pattern_preset)) {
        stats->solved = parsed && cube_matches_state(&verify, pattern_preset_state(config.pattern_preset));
    } else {
        stats->solved = parsed && cube_is_solved_local(&verify);
    }
    stats->total_moves = count_moves(moves);
    stats->face_moves = count_non_rotation_moves(moves);
    stats->has_rotations =
        strstr(moves, "x") != nullptr || strstr(moves, "y") != nullptr ||
        strstr(moves, "z") != nullptr || strstr(moves, "X") != nullptr ||
        strstr(moves, "Y") != nullptr || strstr(moves, "Z") != nullptr;

    stats->scramble[0] = '\0';
    strncpy(stats->solution, moves, sizeof(stats->solution) - 1);
    stats->solution[sizeof(stats->solution) - 1] = '\0';

    if (config.print_solution) {
        printf("%s megoldas: %s (%d lepesbol)\n",
               config.solver_mode == SolverMode::Fmc ? "FMC" : "Normal",
               moves,
               stats->total_moves);
    }

    if (config.visualize_solution) {
        cube_vizualize(scramble_moves, moves);
    }

    set_solver_verbose(true);
    return stats->solved;
}

bool app_run_fmc_benchmark(const BenchmarkConfig& config, BenchmarkSummary* summary) {
    if (summary == nullptr || config.run_count <= 0 || config.run_count > kMaxBenchmarkSamples) {
        return false;
    }

    int total_values[kMaxBenchmarkSamples] = {};
    int face_values[kMaxBenchmarkSamples] = {};
    double time_values_ms[kMaxBenchmarkSamples] = {};
    size_t solver_heap_peak_values[kMaxBenchmarkSamples] = {};
    size_t free_heap_before_values[kMaxBenchmarkSamples] = {};
    size_t free_heap_after_values[kMaxBenchmarkSamples] = {};
    size_t min_free_heap_values[kMaxBenchmarkSamples] = {};

    int success_count = 0;
    int failure_count = 0;
    int rotation_solution_count = 0;

#if !defined(ARDUINO) && !defined(ESP_PLATFORM)
    std::ofstream csv;
    if (config.write_csv && config.csv_path != nullptr) {
        csv.open(config.csv_path, std::ios::out | std::ios::trunc);
        if (csv.is_open()) {
            csv << "seed,success,total_moves,face_moves,has_rotations,time_ms,"
                   "solver_heap_peak_bytes,free_heap_before_bytes,free_heap_after_bytes,"
                   "min_free_heap_bytes\n";
        }
    }
#endif

    AppRunConfig run_config = {};
    run_config.solver_mode = config.solver_mode;
    run_config.print_mode = false;
    run_config.print_scramble = false;
    run_config.print_solution = false;
    run_config.visualize_solution = false;
    run_config.use_fixed_scramble = false;
    run_config.use_seeded_scramble = true;
    run_config.random_scramble_length = config.random_scramble_length;
    run_config.fixed_scramble = nullptr;
    run_config.fixed_scramble_length = 0;

    for (int run = 0; run < config.run_count; ++run) {
        const unsigned int seed = config.start_seed + run;
        run_config.scramble_seed = seed;

        SolveStats stats = {};
        const bool solved = app_run_solve(run_config, &stats);

        if (solved) {
            total_values[success_count] = stats.total_moves;
            face_values[success_count] = stats.face_moves;
            time_values_ms[success_count] = static_cast<double>(stats.elapsed_us) / 1000.0;
            solver_heap_peak_values[success_count] = stats.solver_heap_peak_bytes;
            free_heap_before_values[success_count] = stats.free_heap_before_bytes;
            free_heap_after_values[success_count] = stats.free_heap_after_bytes;
            min_free_heap_values[success_count] = stats.min_free_heap_bytes;
            if (stats.has_rotations) {
                rotation_solution_count++;
            }
            success_count++;
        } else {
            failure_count++;
            if (config.print_failures && failure_count <= 10) {
                printf("Benchmark fail seed=%u moves=%s\n", seed, stats.solution);
            }
        }

#if !defined(ARDUINO) && !defined(ESP_PLATFORM)
        if (csv.is_open()) {
            csv << seed << ","
                << (solved ? 1 : 0) << ","
                << stats.total_moves << ","
                << stats.face_moves << ","
                << (stats.has_rotations ? 1 : 0) << ","
                << (static_cast<double>(stats.elapsed_us) / 1000.0) << ","
                << stats.solver_heap_peak_bytes << ","
                << stats.free_heap_before_bytes << ","
                << stats.free_heap_after_bytes << ","
                << stats.min_free_heap_bytes << "\n";
        }
#endif

        if (config.print_progress_every > 0 &&
            ((run + 1) % config.print_progress_every) == 0) {
            printf("Benchmark progress: %d / %d\n", run + 1, config.run_count);
        }
    }

    memset(summary, 0, sizeof(*summary));
    summary->success_count = success_count;
    summary->failure_count = failure_count;
    summary->rotation_solution_count = rotation_solution_count;
    summary->cpu_freq_mhz = zz_platform_cpu_freq_mhz();

    compute_int_summary(total_values, success_count,
                        &summary->avg_total_moves, &summary->min_total_moves, &summary->max_total_moves,
                        &summary->p50_total_moves, &summary->p90_total_moves,
                        &summary->p95_total_moves, &summary->p99_total_moves);
    compute_int_summary(face_values, success_count,
                        &summary->avg_face_moves, &summary->min_face_moves, &summary->max_face_moves,
                        &summary->p50_face_moves, &summary->p90_face_moves,
                        &summary->p95_face_moves, &summary->p99_face_moves);
    compute_double_summary(time_values_ms, success_count,
                           &summary->avg_time_ms, &summary->min_time_ms, &summary->max_time_ms);
    compute_size_summary(solver_heap_peak_values, success_count,
                         &summary->avg_solver_heap_peak_bytes,
                         &summary->min_solver_heap_peak_bytes,
                         &summary->max_solver_heap_peak_bytes);
    compute_size_summary(free_heap_before_values, success_count,
                         &summary->avg_free_heap_before_bytes,
                         &summary->min_free_heap_before_bytes,
                         &summary->max_free_heap_before_bytes);
    compute_size_summary(free_heap_after_values, success_count,
                         &summary->avg_free_heap_after_bytes,
                         &summary->min_free_heap_after_bytes,
                         &summary->max_free_heap_after_bytes);
    compute_size_summary(min_free_heap_values, success_count,
                         &summary->avg_min_free_heap_bytes,
                         &summary->min_min_free_heap_bytes,
                         &summary->max_min_free_heap_bytes);

#if !defined(ARDUINO) && !defined(ESP_PLATFORM)
    if (csv.is_open()) {
        csv.close();
    }
#endif

    return failure_count == 0;
}

void app_print_benchmark_summary(const BenchmarkSummary& summary) {
    printf("FMC benchmark success/fail: %d / %d\n",
           summary.success_count, summary.failure_count);
    printf("FMC benchmark rotation solutions: %d\n",
           summary.rotation_solution_count);
    if (summary.cpu_freq_mhz > 0) {
        printf("CPU freq: %u MHz\n", summary.cpu_freq_mhz);
    }

    printf("Total avg/min/max: %.3f / %d / %d\n",
           summary.avg_total_moves, summary.min_total_moves, summary.max_total_moves);
    printf("Total p50/p90/p95/p99: %d / %d / %d / %d\n",
           summary.p50_total_moves, summary.p90_total_moves,
           summary.p95_total_moves, summary.p99_total_moves);

    printf("Face avg/min/max: %.3f / %d / %d\n",
           summary.avg_face_moves, summary.min_face_moves, summary.max_face_moves);
    printf("Face p50/p90/p95/p99: %d / %d / %d / %d\n",
           summary.p50_face_moves, summary.p90_face_moves,
           summary.p95_face_moves, summary.p99_face_moves);

    printf("Time avg/min/max (ms): %.3f / %.3f / %.3f\n",
           summary.avg_time_ms, summary.min_time_ms, summary.max_time_ms);

    std::cout << "Solver heap peak avg/min/max (bytes): "
              << summary.avg_solver_heap_peak_bytes
              << " / " << summary.min_solver_heap_peak_bytes
              << " / " << summary.max_solver_heap_peak_bytes << "\n";

    if (summary.max_free_heap_before_bytes > 0 || summary.max_free_heap_after_bytes > 0 ||
        summary.max_min_free_heap_bytes > 0) {
        std::cout << "Free heap before avg/min/max (bytes): "
                  << summary.avg_free_heap_before_bytes
                  << " / " << summary.min_free_heap_before_bytes
                  << " / " << summary.max_free_heap_before_bytes << "\n";
        std::cout << "Free heap after avg/min/max (bytes): "
                  << summary.avg_free_heap_after_bytes
                  << " / " << summary.min_free_heap_after_bytes
                  << " / " << summary.max_free_heap_after_bytes << "\n";
        std::cout << "Min free heap avg/min/max (bytes): "
                  << summary.avg_min_free_heap_bytes
                  << " / " << summary.min_min_free_heap_bytes
                  << " / " << summary.max_min_free_heap_bytes << "\n";
    }

    std::cout << "Static sizes: Cube=" << sizeof(Cube)
              << " bytes, scramble buffer=" << sizeof(scramble_moves)
              << ", moves buffer=" << sizeof(moves)
              << ", temp buffer=" << sizeof(temporary_moves) << "\n";
}
