#include "zz_profiler.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstring>

namespace {

using Clock = std::chrono::steady_clock;

constexpr int kProfileSlotCount = static_cast<int>(ZzProfileSlot::Count);

std::array<ZzProfileStat, kProfileSlotCount> g_stats = {};

const char* kProfileNames[kProfileSlotCount] = {
    "solve_fmc",
    "solve_fmc_route",
    "solve_EO",
    "solve_LINE",
    "solve_BBFL",
    "solve_BBBL",
    "solve_BBBR",
    "solve_BBFR",
    "solve_SBBBL",
    "solve_SBBBR",
    "solve_SBBFL",
    "solve_SBBFR",
    "solve_ADVBL",
    "solve_ADVBR",
    "solve_ADVFL",
    "solve_ADVFR",
    "solve_F2LBL",
    "solve_F2LBR",
    "solve_F2LFL",
    "solve_F2LFR",
    "solve_ZBLL",
    "find_edge",
    "find_corner",
    "first_translate",
    "invert_solution_string",
    "apply_solution",
    "apply_solution_string"
};

#if ZZ_ENABLE_PROFILING
struct Frame {
    ZzProfileSlot slot;
    uint64_t start_ns;
    uint64_t child_ns;
};

thread_local std::array<Frame, 128> t_stack = {};
thread_local int t_stack_size = 0;

static uint64_t now_ns() {
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            Clock::now().time_since_epoch()).count());
}
#endif

}  // namespace

void zz_profiler_reset() {
    std::memset(g_stats.data(), 0, sizeof(ZzProfileStat) * g_stats.size());
#if ZZ_ENABLE_PROFILING
    t_stack_size = 0;
#endif
}

const ZzProfileStat* zz_profiler_stats() {
    return g_stats.data();
}

const char* zz_profiler_name(ZzProfileSlot slot) {
    return kProfileNames[static_cast<int>(slot)];
}

void zz_profiler_print(FILE* out) {
    if (out == nullptr) {
        return;
    }

    struct Row {
        int index;
        uint64_t self_ns;
    };

    Row rows[kProfileSlotCount];
    uint64_t total_self_ns = 0;
    int used = 0;

    for (int i = 0; i < kProfileSlotCount; ++i) {
        if (g_stats[i].call_count == 0) {
            continue;
        }
        rows[used++] = {i, g_stats[i].self_ns};
        total_self_ns += g_stats[i].self_ns;
    }

    std::sort(rows, rows + used, [](const Row& a, const Row& b) {
        return a.self_ns > b.self_ns;
    });

    std::fprintf(out, "=== Profiling Summary ===\n");
    std::fprintf(out, "%-24s %12s %14s %14s %14s %8s\n",
                 "Function", "Calls", "Total ms", "Self ms", "Avg us", "Self %");

    for (int i = 0; i < used; ++i) {
        const ZzProfileStat& stat = g_stats[rows[i].index];
        const double total_ms = static_cast<double>(stat.total_ns) / 1'000'000.0;
        const double self_ms = static_cast<double>(stat.self_ns) / 1'000'000.0;
        const double avg_us = stat.call_count == 0
            ? 0.0
            : static_cast<double>(stat.total_ns) / stat.call_count / 1'000.0;
        const double self_pct = total_self_ns == 0
            ? 0.0
            : 100.0 * static_cast<double>(stat.self_ns) / static_cast<double>(total_self_ns);

        std::fprintf(out, "%-24s %12llu %14.3f %14.3f %14.3f %7.2f\n",
                     kProfileNames[rows[i].index],
                     static_cast<unsigned long long>(stat.call_count),
                     total_ms,
                     self_ms,
                     avg_us,
                     self_pct);
    }
}

#if ZZ_ENABLE_PROFILING
ZzProfileScope::ZzProfileScope(ZzProfileSlot slot)
    : slot_(slot), start_ns_(0), active_(false) {
    if (t_stack_size >= static_cast<int>(t_stack.size())) {
        return;
    }

    start_ns_ = now_ns();
    t_stack[t_stack_size++] = {slot_, start_ns_, 0};
    active_ = true;
}

ZzProfileScope::~ZzProfileScope() {
    if (!active_ || t_stack_size <= 0) {
        return;
    }

    const uint64_t end_ns = now_ns();
    Frame frame = t_stack[--t_stack_size];
    const uint64_t elapsed_ns = end_ns - frame.start_ns;
    const uint64_t self_ns = elapsed_ns >= frame.child_ns ? elapsed_ns - frame.child_ns : 0;

    ZzProfileStat& stat = g_stats[static_cast<int>(frame.slot)];
    stat.call_count++;
    stat.total_ns += elapsed_ns;
    stat.self_ns += self_ns;

    if (t_stack_size > 0) {
        t_stack[t_stack_size - 1].child_ns += elapsed_ns;
    }
}
#endif
