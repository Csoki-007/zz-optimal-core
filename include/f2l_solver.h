#ifndef F2L_SOLVER_H
#define F2L_SOLVER_H

#include "ZZOptimalCore.h"
#include "zz_profiler.h"
#include <array>

void solve_BBFL(Cube* cube);
void solve_BBBL(Cube* cube);
void solve_BBBR(Cube* cube);
void solve_BBFR(Cube* cube);

void solve_SBBBL(Cube* cube);
void solve_SBBBR(Cube* cube);
void solve_SBBFL(Cube* cube);
void solve_SBBFR(Cube* cube);

void solve_ADVBL(Cube* cube);
void solve_ADVBR(Cube* cube);
void solve_ADVFL(Cube* cube);
void solve_ADVFR(Cube* cube);

void solve_F2LBL(Cube* cube);
void solve_F2LBR(Cube* cube);
void solve_F2LFL(Cube* cube);
void solve_F2LFR(Cube* cube);

extern int second_block_last_corner;
extern int second_block_last_edge_down;
extern int second_block_last_edge_side;
extern int second_block_last_index;
extern char second_block_last_name[8];
extern int adv_block_last_corner;
extern int adv_block_last_edge;
extern int adv_block_last_index;
extern char adv_block_last_name[8];

inline int get_BBF2L_Index(int n1, int n2, int n3, int x1, int x2, const std::array<int,52>& X, const std::array<int,12>& B);
inline int get_F2L_Index(int n1, int n2, int x1, const std::array<int,52>& X, const std::array<int,12>& B);

#endif // F2L_SOLVER_H
