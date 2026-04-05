#ifndef ZBLL_SOLVER_H
#define ZBLL_SOLVER_H

#include "ZZOptimalCore.h"
#include "zz_profiler.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <cstdint>
#include <string>

// Fő függvények
void solve_ZBLL(Cube* cube);
extern bool zbll_last_lookup_failed;
extern char zbll_last_case[12];
extern char zbll_last_family[8];

// Segédfüggvények
bool check4(char a, char b, char c, char d);
bool check3(char a, char b, char c);


constexpr uint32_t packKey(const char s[11]) noexcept {
    uint32_t c = 0;
    for (int i = 0; i < 11; ++i) {
        c = (c << 2) | static_cast<uint32_t>(s[i] - '1');
    }
    return c;
}
template <size_t N> const char* get_ZBLL_Index(const char key[11], const std::array<std::pair<uint32_t, const char*>, N>& table) noexcept;

#endif // ZBLL_SOLVER_H
