#ifndef EO_SOLVER_H
#define EO_SOLVER_H

#include "ZZOptimalCore.h"

// Fő függvények
void solve_EO(Cube* cube);

// Segédfüggvények
int get_bad_edges(const Cube* cube, int* bad_indexes);

// Hatékony indexelő függvények
int get_2_Index(const int arr[2]);
int get_4_Index(const int arr[4]);
int get_6_Index(const int arr[6]);
int get_8_Index(const int arr[8]);
int get_10_Index(const int arr[10]);
int get_12_Index(const int arr[12]);

#endif // EO_SOLVER_H