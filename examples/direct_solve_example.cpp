#include <cstdint>
#include <cstdio>

#if defined(ARDUINO)
#include <Arduino.h>
#ifdef F
#undef F
#endif
#endif

#include "app_runner.h"

namespace example_config {
constexpr SolverMode kSolverMode = SolverMode::Fmc;
constexpr PatternPreset kPatternPreset = PatternPreset::None;
constexpr bool kPrintModeInsideSolver = false;
constexpr bool kPrintSolutionInsideSolver = false;
constexpr bool kVisualizeSolution = false;

// Example cube state produced from the solved cube by:
// R U F2 Li D
constexpr uint8_t kCubeState[54] = {
    6, 1, 1, 1, 6, 6, 4, 6, 1,
    4, 4, 1, 2, 1, 5, 1, 3, 2,
    3, 3, 3, 3, 2, 2, 3, 6, 3,
    2, 5, 5, 4, 4, 4, 6, 2, 4,
    2, 2, 5, 1, 4, 4, 6, 1, 5,
    2, 5, 5, 3, 3, 5, 5, 6, 6
};
}

static void print_line(const char* text) {
#if defined(ARDUINO)
    Serial.println(text);
#else
    std::printf("%s\n", text);
#endif
}

static void print_result(const SolveStats& stats) {
#if defined(ARDUINO)
    Serial.printf("Solved: %s\n", stats.solved ? "yes" : "no");
    Serial.printf("Solution: %s\n", stats.solution);
    Serial.printf("Total moves: %d\n", stats.total_moves);
    Serial.printf("Face moves: %d\n", stats.face_moves);
    Serial.printf("Time: %.3f ms\n", static_cast<double>(stats.elapsed_us) / 1000.0);
#else
    std::printf("Solved: %s\n", stats.solved ? "yes" : "no");
    std::printf("Solution: %s\n", stats.solution);
    std::printf("Total moves: %d\n", stats.total_moves);
    std::printf("Face moves: %d\n", stats.face_moves);
    std::printf("Time: %.3f ms\n", static_cast<double>(stats.elapsed_us) / 1000.0);
#endif
}

static bool run_direct_solve_example() {
    const DirectSolveConfig config = make_direct_solve_config(
        example_config::kSolverMode,
        example_config::kPatternPreset,
        example_config::kPrintModeInsideSolver,
        example_config::kPrintSolutionInsideSolver,
        example_config::kVisualizeSolution);

    SolveStats stats = {};
    const bool ok = app_run_solve_from_state(example_config::kCubeState, config, &stats);
    print_result(stats);
    return ok;
}

#if defined(ARDUINO)
void setup() {
    Serial.begin(115200);
    delay(1000);
    print_line("ZZOptimalCore direct solve example");
    run_direct_solve_example();
}

void loop() {
    delay(1000);
}
#else
int main() {
    print_line("ZZOptimalCore direct solve example");
    return run_direct_solve_example() ? 0 : 1;
}
#endif
