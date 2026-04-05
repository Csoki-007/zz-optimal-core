#ifndef ZZ_PROFILER_H
#define ZZ_PROFILER_H

#include <cstdint>
#include <cstdio>

#ifndef ZZ_ENABLE_PROFILING
#define ZZ_ENABLE_PROFILING 0
#endif

enum class ZzProfileSlot : uint8_t {
    SolveFmc,
    SolveFmcRoute,
    SolveEO,
    SolveLine,
    SolveBBFL,
    SolveBBBL,
    SolveBBBR,
    SolveBBFR,
    SolveSBBBL,
    SolveSBBBR,
    SolveSBBFL,
    SolveSBBFR,
    SolveADVBL,
    SolveADVBR,
    SolveADVFL,
    SolveADVFR,
    SolveF2LBL,
    SolveF2LBR,
    SolveF2LFL,
    SolveF2LFR,
    SolveZBLL,
    FindEdge,
    FindCorner,
    FirstTranslate,
    InvertSolutionString,
    ApplySolution,
    ApplySolutionString,
    Count
};

struct ZzProfileStat {
    uint64_t call_count;
    uint64_t total_ns;
    uint64_t self_ns;
};

void zz_profiler_reset();
void zz_profiler_print(FILE* out);
const ZzProfileStat* zz_profiler_stats();
const char* zz_profiler_name(ZzProfileSlot slot);

#if ZZ_ENABLE_PROFILING
class ZzProfileScope {
public:
    explicit ZzProfileScope(ZzProfileSlot slot);
    ~ZzProfileScope();

private:
    ZzProfileSlot slot_;
    uint64_t start_ns_;
    bool active_;
};

#define ZZ_PROFILE_SCOPE(slot_name) \
    ZzProfileScope zz_profile_scope_instance_##__LINE__(ZzProfileSlot::slot_name)
#else
class ZzProfileScope {
public:
    explicit ZzProfileScope(ZzProfileSlot) {}
};

#define ZZ_PROFILE_SCOPE(slot_name) do { } while (0)
#endif

#endif
