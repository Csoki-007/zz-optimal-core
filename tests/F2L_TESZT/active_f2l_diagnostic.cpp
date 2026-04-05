#include "ZZOptimalCore.h"
#include "eo_solver.h"
#include "line_solver.h"
#include "f2l_solver.h"

#include <array>
#include <algorithm>
#include <cstdio>
#include <map>
#include <random>
#include <vector>

char scramble_moves[256] = {};
char moves[256] = {};
char temporary_moves[256] = {};

namespace {

constexpr uint8_t initial_state[54] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6
};

constexpr std::array<int, 12> B1_LUT = {0, 1, 2, 3, 4, 5, 6, 7, -1, 8, -1, 9};
constexpr std::array<int, 52> X1_map = {
    0, 0, 3, 0, 6, 0, 9, 0, 0, 1,
    0, 11, 0, 13, 0, 23, 0, 0, 10, 0,
    8, 0, 16, 0, 14, 0, 0, 7, 0, 5,
    0, 19, 0, 17, 0, 0, 4, 0, 2, 0,
    22, 0, 20, 0, 0, 12, 0, 15, 0, 18,
    0, 21
};

constexpr std::array<int, 12> B2_LUT = {0, 1, 2, 3, 4, -1, -1, 5, -1, -1, -1, 6};
constexpr std::array<int, 52> X2_map = {
    0, 0, 3, 0, 6, 0, 9, 0, 0, 1,
    0, 11, 0, 16, 0, 14, 0, 0, 10, 0,
    8, 0, 0, 0, 17, 0, 0, 7, 0, 5,
    0, 0, 0, 0, 0, 0, 4, 0, 2, 0,
    13, 0, 0, 0, 0, 12, 0, 0, 0, 0,
    0, 15
};

constexpr std::array<int, 12> B11_LUT = {0, 1, 2, 3, 4, 5, -1, 6, -1, -1, -1, 7};
constexpr std::array<int, 52> X11_map = {
    0, 0, 3, 0, 6, 0, 9, 0, 0, 1,
    0, 11, 0, 13, 0, 20, 0, 0, 10, 0,
    8, 0, 16, 0, 14, 0, 0, 7, 0, 5,
    0, 0, 0, 17, 0, 0, 4, 0, 2, 0,
    19, 0, 0, 0, 0, 12, 0, 15, 0, 0,
    0, 18
};

constexpr std::array<int, 12> B4_LUT = {0, 1, 2, 3, -1, -1, -1, 4, -1, -1, -1, -1};
constexpr std::array<int, 52> X4_map = {
    0, 0, 3, 0, 6, 0, 9, 0, 0, 1,
    0, 11, 0, 0, 0, 14, 0, 0, 10, 0,
    8, 0, 0, 0, 0, 0, 0, 7, 0, 5,
    0, 0, 0, 0, 0, 0, 4, 0, 2, 0,
    13, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 12
};

using Move = void(*)(Cube*);

const std::array<Move, 18> scramble_moves_table = {
    U, Ui, U2, D, Di, D2, F, Fi, F2,
    B, Bi, B2, R, Ri, R2, L, Li, L2
};

struct FailureInfo {
    int total = 0;
    int invalid_index = 0;
    int wrong_solution = 0;
};

struct StageSummary {
    const char* name;
    int max_index;
    std::map<int, FailureInfo> by_index;
    int total = 0;
    int invalid_index = 0;
    int wrong_solution = 0;
};

void record_invalid(StageSummary& stage, int index) {
    stage.total++;
    stage.invalid_index++;
    stage.by_index[index].total++;
    stage.by_index[index].invalid_index++;
}

void record_wrong(StageSummary& stage, int index) {
    stage.total++;
    stage.wrong_solution++;
    stage.by_index[index].total++;
    stage.by_index[index].wrong_solution++;
}

void record_ok(StageSummary& stage, int index) {
    stage.total++;
    stage.by_index[index].total++;
}

void reset_all_buffers() {
    reset_moves(scramble_moves, sizeof(scramble_moves));
    reset_moves(moves, sizeof(moves));
    reset_moves(temporary_moves, sizeof(temporary_moves));
}

void apply_seeded_scramble(Cube* cube, std::mt19937& rng, int len) {
    static const std::array<char, 6> faces = {'U', 'D', 'F', 'B', 'R', 'L'};
    char last_moves[2] = {'\0', '\0'};
    std::uniform_int_distribution<int> face_dist(0, 5);
    std::uniform_int_distribution<int> dir_dist(0, 2);

    for (int i = 0; i < len; ++i) {
        char face_char;
        int dir_index;

        do {
            face_char = faces[face_dist(rng)];
            dir_index = dir_dist(rng);
        } while ((i > 0 && face_char == last_moves[0]) ||
                 (i > 1 && face_char == last_moves[1]));

        last_moves[1] = last_moves[0];
        last_moves[0] = face_char;

        int face_index = 0;
        switch (face_char) {
            case 'U': face_index = 0; break;
            case 'D': face_index = 1; break;
            case 'F': face_index = 2; break;
            case 'B': face_index = 3; break;
            case 'R': face_index = 4; break;
            case 'L': face_index = 5; break;
            default: face_index = 0; break;
        }

        scramble_moves_table[face_index * 3 + dir_index](cube);
    }
}

int diag_get_bbf2l_index(int n1, int n2, int n3, int x1, int x2,
                         const std::array<int, 52>& X,
                         const std::array<int, 12>& B) {
    int index_3 = B[n3] - (n2 < n3 ? 1 : 0);
    return X[n1] * x1 + B[n2] * x2 + index_3;
}

int diag_get_f2l_index(int n1, int n2, int x1,
                       const std::array<int, 52>& X,
                       const std::array<int, 12>& B) {
    return X[n1] * x1 + B[n2];
}

bool check_corner(const Cube& c, uint8_t a, uint8_t b, uint8_t c1,
                  uint8_t ca, uint8_t cb, uint8_t cc) {
    return c.cube[a] == ca && c.cube[b] == cb && c.cube[c1] == cc;
}

bool check_edge(const Cube& c, uint8_t a, uint8_t b, uint8_t ca, uint8_t cb) {
    return c.cube[a] == ca && c.cube[b] == cb;
}

bool bbb_r_solved(const Cube& cube) {
    const uint8_t D = cube.cube[53];
    const uint8_t R = cube.cube[35];
    const uint8_t Bc = cube.cube[44];
    return check_corner(cube, 49, 31, 42, D, R, Bc) &&
           check_edge(cube, 48, 32, D, R) &&
           check_edge(cube, 43, 30, Bc, R);
}

bool adv_fr_solved(const Cube& cube) {
    const uint8_t D = cube.cube[53];
    const uint8_t Fc = cube.cube[26];
    const uint8_t R = cube.cube[35];
    return bbb_r_solved(cube) &&
           check_corner(cube, 47, 22, 33, D, Fc, R) &&
           check_edge(cube, 21, 34, Fc, R);
}

bool sbb_fl_solved(const Cube& cube) {
    const uint8_t D = cube.cube[53];
    const uint8_t Lc = cube.cube[17];
    const uint8_t Fc = cube.cube[26];
    return adv_fr_solved(cube) &&
           check_corner(cube, 45, 13, 24, D, Lc, Fc) &&
           check_edge(cube, 52, 14, D, Lc) &&
           check_edge(cube, 25, 12, Fc, Lc);
}

bool f2l_bl_solved(const Cube& cube) {
    const uint8_t D = cube.cube[53];
    const uint8_t Bc = cube.cube[44];
    const uint8_t Lc = cube.cube[17];
    return sbb_fl_solved(cube) &&
           check_corner(cube, 51, 40, 15, D, Bc, Lc) &&
           check_edge(cube, 39, 16, Bc, Lc);
}

void print_stage_summary(const StageSummary& stage) {
    std::fprintf(stderr, "\n[%s]\n", stage.name);
    std::fprintf(stderr, "ossz futas: %d\n", stage.total);
    std::fprintf(stderr, "ervenyes index tartomany: 0..%d\n", stage.max_index - 1);
    std::fprintf(stderr, "ervenytelen index: %d\n", stage.invalid_index);
    std::fprintf(stderr, "rossz megoldas: %d\n", stage.wrong_solution);
    if (stage.total > 0) {
        const int total_failures = stage.invalid_index + stage.wrong_solution;
        std::fprintf(stderr, "osszes hiba: %d\n", total_failures);
        std::fprintf(stderr, "hiba arany: %.2f%%\n", 100.0 * total_failures / stage.total);
    }

    std::vector<std::pair<int, FailureInfo>> failing;
    std::vector<std::pair<int, FailureInfo>> invalid_only;
    std::vector<std::pair<int, FailureInfo>> wrong_only;
    for (const auto& kv : stage.by_index) {
        if (kv.second.invalid_index > 0 || kv.second.wrong_solution > 0) {
            failing.push_back(kv);
        }
        if (kv.second.invalid_index > 0) {
            invalid_only.push_back(kv);
        }
        if (kv.second.wrong_solution > 0) {
            wrong_only.push_back(kv);
        }
    }
    std::sort(failing.begin(), failing.end(), [](const auto& lhs, const auto& rhs) {
        const int lhs_total = lhs.second.invalid_index + lhs.second.wrong_solution;
        const int rhs_total = rhs.second.invalid_index + rhs.second.wrong_solution;
        if (lhs_total != rhs_total) {
            return lhs_total > rhs_total;
        }
        return lhs.first < rhs.first;
    });
    std::sort(invalid_only.begin(), invalid_only.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.second.invalid_index != rhs.second.invalid_index) {
            return lhs.second.invalid_index > rhs.second.invalid_index;
        }
        return lhs.first < rhs.first;
    });
    std::sort(wrong_only.begin(), wrong_only.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.second.wrong_solution != rhs.second.wrong_solution) {
            return lhs.second.wrong_solution > rhs.second.wrong_solution;
        }
        return lhs.first < rhs.first;
    });

    std::fprintf(stderr, "egyedi indexek szama: %u\n",
                 static_cast<unsigned>(stage.by_index.size()));
    std::fprintf(stderr, "hibas indexek szama: %u\n",
                 static_cast<unsigned>(failing.size()));
    for (size_t i = 0; i < failing.size() && i < 20; ++i) {
        const auto& item = failing[i];
        std::fprintf(stderr,
                     "index %d -> invalid %d, wrong %d, total %d\n",
                     item.first,
                     item.second.invalid_index,
                     item.second.wrong_solution,
                     item.second.total);
    }

    if (!invalid_only.empty()) {
        std::fprintf(stderr, "leggyakoribb ervenytelen indexek:\n");
        for (size_t i = 0; i < invalid_only.size() && i < 10; ++i) {
            const auto& item = invalid_only[i];
            std::fprintf(stderr,
                         "index %d -> invalid %d / %d\n",
                         item.first,
                         item.second.invalid_index,
                         item.second.total);
        }
    }

    if (!wrong_only.empty()) {
        std::fprintf(stderr, "leggyakoribb rossz megoldas indexek:\n");
        for (size_t i = 0; i < wrong_only.size() && i < 10; ++i) {
            const auto& item = wrong_only[i];
            std::fprintf(stderr,
                         "index %d -> wrong %d / %d\n",
                         item.first,
                         item.second.wrong_solution,
                         item.second.total);
        }
    }
}

} // namespace

int main() {
    constexpr int runs = 5000;

    StageSummary eo_stage{"EO", 923, {}, 0, 0, 0};
    StageSummary bbb_stage{"BBBR", 2160, {}, 0, 0, 0};
    StageSummary adv_stage{"ADVFR", 168, {}, 0, 0, 0};
    StageSummary sbb_stage{"SBBFL", 756, {}, 0, 0, 0};
    StageSummary f2l_stage{"F2LBL", 75, {}, 0, 0, 0};

    std::mt19937 rng(123456789u);
    std::freopen("NUL", "w", stdout);

    for (int run = 0; run < runs; ++run) {
        reset_all_buffers();

        Cube cube;
        cube_init(&cube, initial_state);
        apply_seeded_scramble(&cube, rng, 20);
        cube_set_initial_state(&cube, cube_get_current_state(&cube));

        reset_moves(temporary_moves, sizeof(temporary_moves));
        int bad_edges[12] = {};
        const int bad_ctr = get_bad_edges(&cube, bad_edges);
        int eo_index = -1;
        bool eo_valid = true;
        switch (bad_ctr) {
            case 0:
                eo_index = 0;
                break;
            case 2:
                eo_index = get_2_Index(bad_edges);
                eo_valid = eo_index >= 0 && eo_index < 66;
                break;
            case 4:
                eo_index = get_4_Index(bad_edges);
                eo_valid = eo_index >= 0 && eo_index < 495;
                break;
            case 6:
                eo_index = get_6_Index(bad_edges);
                eo_valid = eo_index >= 0 && eo_index < 923;
                break;
            case 8:
                eo_index = get_8_Index(bad_edges);
                eo_valid = eo_index >= 0 && eo_index < 495;
                break;
            case 10:
                eo_index = get_10_Index(bad_edges);
                eo_valid = eo_index >= 0 && eo_index < 66;
                break;
            case 12:
                eo_index = get_12_Index(bad_edges);
                eo_valid = eo_index == 0;
                break;
            default:
                eo_valid = false;
                break;
        }

        if (!eo_valid) {
            record_invalid(eo_stage, eo_index);
            continue;
        }
        record_ok(eo_stage, eo_index);
        solve_EO(&cube);
        reset_moves(temporary_moves, sizeof(temporary_moves));
        solve_LINE(&cube);
        reset_moves(temporary_moves, sizeof(temporary_moves));

        const uint8_t D = cube.cube[53];
        const uint8_t Lc = cube.cube[17];
        const uint8_t Fc = cube.cube[26];
        const uint8_t R = cube.cube[35];
        const uint8_t Bc = cube.cube[44];

        const int bbb_index = diag_get_bbf2l_index(
            find_corner(&cube, D, R, Bc),
            find_edge(&cube, R, D),
            find_edge(&cube, R, Bc),
            90, 9, X1_map, B1_LUT);
        if (bbb_index < 0 || bbb_index >= bbb_stage.max_index) {
            record_invalid(bbb_stage, bbb_index);
            continue;
        }
        solve_BBBR(&cube);
        if (!bbb_r_solved(cube)) {
            record_wrong(bbb_stage, bbb_index);
            continue;
        }
        record_ok(bbb_stage, bbb_index);
        reset_moves(temporary_moves, sizeof(temporary_moves));

        const int adv_index = diag_get_f2l_index(
            find_corner(&cube, D, R, Fc),
            find_edge(&cube, R, Fc),
            8, X11_map, B11_LUT);
        if (adv_index < 0 || adv_index >= adv_stage.max_index) {
            record_invalid(adv_stage, adv_index);
            continue;
        }
        solve_ADVFR(&cube);
        if (!adv_fr_solved(cube)) {
            record_wrong(adv_stage, adv_index);
            continue;
        }
        record_ok(adv_stage, adv_index);
        reset_moves(temporary_moves, sizeof(temporary_moves));

        const int sbb_index = diag_get_bbf2l_index(
            find_corner(&cube, D, Lc, Fc),
            find_edge(&cube, Lc, D),
            find_edge(&cube, Lc, Fc),
            42, 6, X2_map, B2_LUT);
        if (sbb_index < 0 || sbb_index >= sbb_stage.max_index) {
            record_invalid(sbb_stage, sbb_index);
            continue;
        }
        solve_SBBFL(&cube);
        if (!sbb_fl_solved(cube)) {
            record_wrong(sbb_stage, sbb_index);
            continue;
        }
        record_ok(sbb_stage, sbb_index);
        reset_moves(temporary_moves, sizeof(temporary_moves));

        const int f2l_index = diag_get_f2l_index(
            find_corner(&cube, D, Lc, Bc),
            find_edge(&cube, Lc, Bc),
            5, X4_map, B4_LUT);
        if (f2l_index < 0 || f2l_index >= f2l_stage.max_index) {
            record_invalid(f2l_stage, f2l_index);
            continue;
        }
        solve_F2LBL(&cube);
        if (!f2l_bl_solved(cube)) {
            record_wrong(f2l_stage, f2l_index);
            continue;
        }
        record_ok(f2l_stage, f2l_index);
        reset_moves(temporary_moves, sizeof(temporary_moves));
    }

    print_stage_summary(eo_stage);
    print_stage_summary(bbb_stage);
    print_stage_summary(adv_stage);
    print_stage_summary(sbb_stage);
    print_stage_summary(f2l_stage);

    return 0;
}
