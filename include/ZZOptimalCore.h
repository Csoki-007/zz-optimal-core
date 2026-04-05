#ifndef ZZOPTIMALCORE_H
#define ZZOPTIMALCORE_H

#include "fmc_routes.h"
#include <cstdint>   // uint8_t
#include <cstring>   // memcpy, memset, strcat, memcmp
#include <cstdio>    // printf
#include <cstdlib>   // srand, rand
#include <ctime>     // time

#include <cctype>   // tolower

// Memóriaigazítás a struktúrának
typedef struct {
  uint8_t cube[54];       // Aktuális állapot
  uint8_t initial[54];    // Eredeti inicializálási állapot
} Cube __attribute__((aligned(4)));

// Optimalizált függvénydeklarációk
void cube_init(Cube *c, const uint8_t *state);
void cube_reset(Cube *c);
void cube_print(const Cube *c);
void cube_vizualize(char scramble_moves[256], char moves[256]);

// Forgatásokhoz szükséges alapfüggvények
void swap_one(Cube *c, const uint8_t indices[20]);
void swap_two(Cube *c, const uint8_t indices[20]);

// Face indexek előre definiálva
typedef enum { U_FACE, L_FACE, F_FACE, R_FACE, B_FACE, D_FACE} CubeFace;
void get_face(const Cube *c, CubeFace face, uint8_t *out);

// Setterek
void cube_set_initial_state(Cube *c, const uint8_t *state);

int find_edge(const Cube* cube, uint8_t target1, uint8_t target2);
int find_corner(const Cube* cube, uint8_t target1, uint8_t target2, uint8_t target3);

// Getterek
const uint8_t* cube_get_current_state(const Cube *c);
const uint8_t* cube_get_initial_state(const Cube *c);



static inline void swap_face_one(Cube * c, uint8_t a, uint8_t b, uint8_t c1, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h) {
    uint8_t * cube = c->cube;
    uint8_t temp;
    // Első csoport
    temp = cube[a];
    cube[a] = cube[b];
    cube[b] = cube[c1];
    cube[c1] = cube[d];
    cube[d] = temp;
    // Második csoport
    temp = cube[e];
    cube[e] = cube[f];
    cube[f] = cube[g];
    cube[g] = cube[h];
    cube[h] = temp;
}

static inline void swap_face_two(Cube * c, uint8_t a, uint8_t b, uint8_t c1, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h) {
    uint8_t * cube = c->cube;
    uint8_t temp;
    // Páronkénti csere műveletek
    temp = cube[a]; cube[a] = cube[b]; cube[b] = temp;
    temp = cube[c1]; cube[c1] = cube[d]; cube[d] = temp;
    temp = cube[e]; cube[e] = cube[f]; cube[f] = temp;
    temp = cube[g]; cube[g] = cube[h]; cube[h] = temp;
}

extern char moves[256];
extern char temporary_moves[256];
extern int moves_ctr;
extern int temporary_moves_ctr;

void reset_moves(void* target_array, size_t array_size);
void catenate_moves(char* moves, char* temporary_moves);
int count_moves(const char* moves);

void U(Cube *c);
void Ui(Cube *c);
void U2(Cube *c);
void L(Cube *c);
void Li(Cube *c);
void L2(Cube *c);
void F(Cube *c);
void Fi(Cube *c);
void F2(Cube *c);
void R(Cube *c);
void Ri(Cube *c);
void R2(Cube *c);
void B(Cube *c);
void Bi(Cube *c);
void B2(Cube *c);
void D(Cube *c);
void Di(Cube *c);
void D2(Cube *c);

void X_rotation(Cube *c);
void Xi_rotation(Cube *c);
void X2_rotation(Cube *c);
void Y_rotation(Cube *c);
void Yi_rotation(Cube *c);
void Y2_rotation(Cube *c);
void Z_rotation(Cube *c);
void Zi_rotation(Cube *c);

void scramble_cube(Cube* c, int slen);

int remrep(char* s);
int normalize_moves(char* s);
void reset_solver_heap_stats();
size_t get_solver_heap_current_bytes();
size_t get_solver_heap_peak_bytes();
void set_solver_verbose(bool enabled);
bool is_solver_verbose();
void set_fmc_reverse_enabled(bool enabled);
bool is_fmc_reverse_enabled();
bool invert_solution_string(const char* solution, char* out, size_t out_size);

char* first_translate(const char* moves);
int find_index_in_neg_rotations(const char* token);
// Segédfüggvények deklarációi
void swap_center_one(char* orientation, int a, int b, int c, int d);
void swap_center_two(char* orientation, int a, int b, int c, int d);
void center_y(char* orientation);
void center_yi(char* orientation);
void center_y2(char* orientation);
void center_x(char* orientation);
void center_xi(char* orientation);
void center_x2(char* orientation);
void center_zi(char* orientation);
void center_z(char* orientation);



void solve_once(Cube* myCube);
typedef void (*OrientationFunc)(Cube*);
void do_nothing(Cube*);
bool solve_fmc_route(const Cube* scrambled, const FmcRoute& route, char* out_solution, size_t out_size, int* out_move_count);
bool build_inverse_scramble_state(const Cube* scrambled, Cube* out_inverse_scrambled);
bool build_inverse_scramble_state_from_solution(const char* solution, Cube* out_inverse_scrambled);
bool solve_fmc_reverse_route(const Cube* original_scrambled, const Cube* inverse_scrambled, const FmcRoute& route, char* out_solution, size_t out_size, int* out_move_count);
void solve_fmc(Cube* myCube);

#endif // CUBE_H
