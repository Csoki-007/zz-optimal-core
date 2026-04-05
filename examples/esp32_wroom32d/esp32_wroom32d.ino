#include "app_runner.h"

static const char* kFixedScramble[] = {
    "D2", "B2", "L2", "Di", "U", "F", "B", "Li", "R", "B",
    "Di", "U", "R", "B2", "Di", "R2", "U2", "F", "Bi", "Di"
};

void setup() {
    Serial.begin(115200);
    delay(1000);

    printf("\nZZOptimalCore ESP32 demo indul\n");

    AppRunConfig config = {};
    config.solver_mode = SolverMode::Fmc;
    config.print_mode = true;
    config.print_scramble = true;
    config.print_solution = true;
    config.visualize_solution = false;
    config.use_fixed_scramble = false;
    config.use_seeded_scramble = true;
    config.random_scramble_length = 20;
    config.scramble_seed = 12345;
    config.fixed_scramble = kFixedScramble;
    config.fixed_scramble_length =
        static_cast<int>(sizeof(kFixedScramble) / sizeof(kFixedScramble[0]));

    SolveStats stats = {};
    const bool solved = app_run_solve(config, &stats);

    printf("ESP32 solved=%d time_ms=%.3f total=%d face=%d heap_peak=%u free_before=%u free_after=%u min_free=%u\n",
           solved ? 1 : 0,
           static_cast<double>(stats.elapsed_us) / 1000.0,
           stats.total_moves,
           stats.face_moves,
           static_cast<unsigned>(stats.solver_heap_peak_bytes),
           static_cast<unsigned>(stats.free_heap_before_bytes),
           static_cast<unsigned>(stats.free_heap_after_bytes),
           static_cast<unsigned>(stats.min_free_heap_bytes));
}

void loop() {
    delay(1000);
}
