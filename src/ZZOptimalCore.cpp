#include "ZZOptimalCore.h"
#include "eo_solver.h"
#include "line_solver.h"
#include "f2l_solver.h"
#include "fmc_routes.h"
#include "zz_profiler.h"
#include "zz_platform.h"
#include "zbll_solver.h"
#include <string>

static size_t solver_heap_current_bytes = 0;
static size_t solver_heap_peak_bytes = 0;
static bool solver_verbose = true;
static bool fmc_reverse_enabled = true;
static const uint8_t kSolvedState[54] = {
    1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,
    4,4,4,4,4,4,4,4,4,
    5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6
};

static void* solver_malloc(size_t size) {
    const size_t total = sizeof(size_t) + size;
    unsigned char* raw = static_cast<unsigned char*>(malloc(total));
    if (raw == nullptr) {
        return nullptr;
    }
    *reinterpret_cast<size_t*>(raw) = size;
    solver_heap_current_bytes += size;
    if (solver_heap_current_bytes > solver_heap_peak_bytes) {
        solver_heap_peak_bytes = solver_heap_current_bytes;
    }
    return raw + sizeof(size_t);
}

static void solver_free(void* ptr) {
    if (ptr == nullptr) {
        return;
    }
    unsigned char* raw = static_cast<unsigned char*>(ptr) - sizeof(size_t);
    const size_t size = *reinterpret_cast<size_t*>(raw);
    if (solver_heap_current_bytes >= size) {
        solver_heap_current_bytes -= size;
    } else {
        solver_heap_current_bytes = 0;
    }
    free(raw);
}

void reset_solver_heap_stats() {
    solver_heap_current_bytes = 0;
    solver_heap_peak_bytes = 0;
}

size_t get_solver_heap_current_bytes() {
    return solver_heap_current_bytes;
}

size_t get_solver_heap_peak_bytes() {
    return solver_heap_peak_bytes;
}

void set_solver_verbose(bool enabled) {
    solver_verbose = enabled;
}

bool is_solver_verbose() {
    return solver_verbose;
}

void set_fmc_reverse_enabled(bool enabled) {
    fmc_reverse_enabled = enabled;
}

bool is_fmc_reverse_enabled() {
    return fmc_reverse_enabled;
}

// InicializĂˇlĂˇs memcpy-vel
void cube_init(Cube *c, const uint8_t *state) {
    memcpy(c->cube, state, 54);
    memcpy(c->initial, state, 54); // Eredeti Ăˇllapot mentĂ©se
}

// Kocka visszaĂˇllĂ­tĂˇsa az eredetire
void cube_reset(Cube *c) {
    memcpy(c->cube, c->initial, 54); // VisszaĂˇllĂ­tĂˇs az eredetire
}

// Eredeti Ăˇllapot felĂĽlĂ­rĂˇsa
void cube_set_initial_state(Cube *c, const uint8_t *state) {
    memcpy(c->initial, state, 54);
}

// Teljes aktuĂˇlis Ăˇllapot lekĂ©rdezĂ©se
const uint8_t* cube_get_current_state(const Cube *c) {
    return c->cube;
}

// Teljes eredeti Ăˇllapot lekĂ©rdezĂ©se
const uint8_t* cube_get_initial_state(const Cube *c) {
    return c->initial;
}

int find_edge(const Cube* cube, uint8_t target1, uint8_t target2) {
    ZZ_PROFILE_SCOPE(FindEdge);
    const uint8_t edges[12][2] = {
        {1,37}, {3,28}, {5,19}, {7,10}, {25,12}, {21,34},
        {43,30}, {39,16}, {46,23}, {48,32}, {50,41}, {52,14}
    };

    const uint8_t t_min = target1 < target2 ? target1 : target2;
    const uint8_t t_max = target1 < target2 ? target2 : target1;

    for (int i = 0; i < 12; i++) {
        uint8_t s1 = cube->cube[edges[i][0]];
        uint8_t s2 = cube->cube[edges[i][1]];
        uint8_t s_min = s1 < s2 ? s1 : s2;
        uint8_t s_max = s1 < s2 ? s2 : s1;
        
        if (s_min == t_min && s_max == t_max)
            return i;
    }
    return -1;
}

int find_corner(const Cube* cube, uint8_t target1, uint8_t target2, uint8_t target3) {
    ZZ_PROFILE_SCOPE(FindCorner);
    // Sarkok definĂ­ciĂłja a sarkok.png alapjĂˇn
    const uint8_t corners[8][3] = {
        {0, 9, 38}, {2, 36, 29}, {4, 27, 20}, {6, 18, 11},
        {45, 13, 24}, {47, 22, 33}, {49, 31, 42}, {51, 40, 15}
    };
    // CĂ©l szĂ­nek rendezĂ©se (kicsi â†’ nagy)
    uint8_t t[3] = {target1, target2, target3};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2 - i; ++j) {
            if (t[j] > t[j+1]) {
                uint8_t temp = t[j];
                t[j] = t[j+1];
                t[j+1] = temp;
            }
        }
    }
    // Sarkok bejĂˇrĂˇsa
    for (int i = 0; i < 8; ++i) {
        // Sark szĂ­neinek kinyerĂ©se Ă©s rendezĂ©se
        uint8_t c[3] = {
            cube->cube[corners[i][0]],
            cube->cube[corners[i][1]],
            cube->cube[corners[i][2]]
        };
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2 - j; ++k) {
                if (c[k] > c[k+1]) {
                    uint8_t temp = c[k];
                    c[k] = c[k+1];
                    c[k+1] = temp;
                }
            }
        }
        // Ă–sszehasonlĂ­tĂˇs rendezett tĂ¶mbĂ¶kkel
        if (memcmp(t, c, 3) == 0) {
            // Target1 keresĂ©se a sarkon belĂĽl
            for (int j = 0; j < 3; ++j) {
                if (cube->cube[corners[i][j]] == target1) {
                    return corners[i][j]; // PozĂ­ciĂł visszaadĂˇsa
                }
            }
        }
    }
    return 0xFF; // Nincs talĂˇlat
}

// // GyorsĂ­tott kiĂ­rĂˇs kevesebb printf hĂ­vĂˇssal
// void cube_print(const Cube *c) {
//     const uint8_t *d = c->cube;
//     printf(
//         "    %d%d%d\n"
//         "    %d%d%d\n"
//         "    %d%d%d\n"
//         "%d%d%d %d%d%d %d%d%d %d%d%d\n"
//         "%d%d%d %d%d%d %d%d%d %d%d%d\n"
//         "%d%d%d %d%d%d %d%d%d %d%d%d\n"
//         "    %d%d%d\n"
//         "    %d%d%d\n"
//         "    %d%d%d\n\n",
//         d[0], d[1], d[2], d[7], d[8], d[3], d[6], d[5], d[4],
//         d[9], d[10], d[11], d[18], d[19], d[20], d[27], d[28], d[29], d[36], d[37], d[38],
//         d[16], d[17], d[12], d[25], d[26], d[21], d[34], d[35], d[30], d[43], d[44], d[39],
//         d[15], d[14], d[13], d[24], d[23], d[22], d[33], d[32], d[31], d[42], d[41], d[40],
//         d[45], d[46], d[47], d[52], d[53], d[48], d[51], d[50], d[49]
//     );
// }


#define COLOR_RESET   "\033[0m"
#define COLOR_WHITE   "\033[97m"
#define COLOR_ORANGE  "\033[38;5;214m"
#define COLOR_RED     "\033[91m"
#define COLOR_BLUE    "\033[94m"
#define COLOR_GREEN   "\033[92m"
#define COLOR_YELLOW  "\033[33m"

// SzĂ­n kivĂˇlasztĂˇsa a szĂˇm alapjĂˇn
const char* get_color(uint8_t num) {
    switch (num) {
        case 1: return COLOR_WHITE;
        case 2: return COLOR_ORANGE;
        case 3: return COLOR_GREEN;
        case 4: return COLOR_RED;
        case 5: return COLOR_BLUE;
        case 6: return COLOR_YELLOW;
        default: return COLOR_RESET;
    }
}

// SzĂ­nes blokk kiĂ­rĂˇsa
void cube_print(const Cube *c) {
    const uint8_t *d = c->cube;

    // Itt most a &#11200; karaktert hasznĂˇljuk (â¬) - U+2B01
    printf("    "); 
    printf("%s\u25A0%s", get_color(d[0]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[1]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[2]), COLOR_RESET); 
    printf("\n");

    printf("    "); 
    printf("%s\u25A0%s", get_color(d[7]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[8]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[3]), COLOR_RESET); 
    printf("\n");

    printf("    "); 
    printf("%s\u25A0%s", get_color(d[6]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[5]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[4]), COLOR_RESET); 
    printf("\n");

    printf("%s\u25A0%s", get_color(d[9]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[10]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[11]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[18]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[19]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[20]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[27]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[28]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[29]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[36]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[37]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[38]), COLOR_RESET); 
    printf("\n");

    printf("%s\u25A0%s", get_color(d[16]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[17]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[12]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[25]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[26]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[21]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[34]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[35]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[30]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[43]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[44]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[39]), COLOR_RESET); 
    printf("\n");

    printf("%s\u25A0%s", get_color(d[15]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[14]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[13]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[24]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[23]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[22]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[33]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[32]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[31]), COLOR_RESET); 
    printf(" ");
    printf("%s\u25A0%s", get_color(d[42]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[41]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[40]), COLOR_RESET); 
    printf("\n");

    printf("    "); 
    printf("%s\u25A0%s", get_color(d[45]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[46]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[47]), COLOR_RESET); 
    printf("\n");

    printf("    "); 
    printf("%s\u25A0%s", get_color(d[52]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[53]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[48]), COLOR_RESET); 
    printf("\n");

    printf("    "); 
    printf("%s\u25A0%s", get_color(d[51]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[50]), COLOR_RESET); 
    printf("%s\u25A0%s", get_color(d[49]), COLOR_RESET); 
    printf("\n\n");
}

void cube_vizualize(char scramble_moves[256], char moves[256]) {
    char temp1[256];
    char temp2[256];
    int i;
    for (i = 0; i < 255 && scramble_moves[i] != '\0'; i++) {
        temp1[i] = scramble_moves[i];
    }
    temp1[i] = '\0';
    for (i = 0; i < 255 && moves[i] != '\0'; i++) {
        temp2[i] = moves[i];
    }
    temp2[i] = '\0';
    for (i = 0; temp1[i] != '\0'; i++) {
        if (temp1[i] == 'i') {
            temp1[i] = '-';
        }
        else if (temp1[i] == ' ') {
            temp1[i] = '_';
        }
    }
    for (i = 0; temp2[i] != '\0'; i++) {
        if (temp2[i] == 'i') {
            temp2[i] = '-';
        }
        else if (temp2[i] == ' ') {
            temp2[i] = '_';
        }
    }
    printf("https://alg.cubing.net/?setup=%s&alg=%s\n", temp1, temp2);
}




void swap_one(Cube *c, const uint8_t indices[20]) {
    uint8_t * cube = c->cube;
    uint8_t temp, v1, v2, v3;
    #define PROCESS_GROUP(o) {\
        temp = cube[indices[o]];\
        v1 = cube[indices[o+1]];\
        v2 = cube[indices[o+2]];\
        v3 = cube[indices[o+3]];\
        cube[indices[o]] = v1;\
        cube[indices[o+1]] = v2;\
        cube[indices[o+2]] = v3;\
        cube[indices[o+3]] = temp;\
    }
    PROCESS_GROUP(0)
    PROCESS_GROUP(4)
    PROCESS_GROUP(8)
    PROCESS_GROUP(12)
    PROCESS_GROUP(16)
    #undef PROCESS_GROUP
}

void swap_two(Cube *c, const uint8_t indices[20]) {
    uint8_t * cube = c->cube;
    const uint8_t *ptr = indices;
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
    { uint8_t i1=*ptr++, i2=*ptr++; uint8_t t=cube[i1]; cube[i1]=cube[i2]; cube[i2]=t; }
}






// Forgatasok elĹ‘re definiĂˇlt indexekkel
static const uint8_t U_indices[20] __attribute__((aligned(4))) = {0,6,4,2,1,7,5,3,18,27,36,9,19,28,37,10,20,29,38,11};
static const uint8_t Ui_indices[20] __attribute__((aligned(4))) = {0,2,4,6,1,3,5,7,18,9,36,27,19,10,37,28,20,11,38,29};
static const uint8_t U2_indices[20] __attribute__((aligned(4))) = {0,4,2,6,1,5,3,7,18,36,19,37,20,38,9,27,10,28,11,29};

static const uint8_t L_indices[20] __attribute__((aligned(4))) = {9, 15, 13, 11, 10, 16, 14, 12, 0, 40, 45, 18, 7, 39, 52, 25, 6, 38, 51, 24};
static const uint8_t Li_indices[20] __attribute__((aligned(4))) = {9, 11, 13, 15, 10, 12, 14, 16, 0, 18, 45, 40, 7, 25, 52, 39, 6, 24, 51, 38};
static const uint8_t L2_indices[20] __attribute__((aligned(4))) = {9, 13, 11, 15, 10, 14, 12, 16, 0, 45, 7, 52, 6, 51, 18, 40, 25, 39, 24, 38};

static const uint8_t F_indices[20] __attribute__((aligned(4))) = {18, 24, 22, 20, 19, 25, 23, 21, 6, 13, 47, 27, 5, 12, 46, 34, 4, 11, 45, 33};
static const uint8_t Fi_indices[20] __attribute__((aligned(4))) = {18, 20, 22, 24, 19, 21, 23, 25, 6, 27, 47, 13, 5, 34, 46, 12, 4, 33, 45, 11};
static const uint8_t F2_indices[20] __attribute__((aligned(4))) = {18, 22, 20, 24, 19, 23, 21, 25, 6, 47, 27, 13, 5, 46, 34, 12, 4, 45, 33, 11};

static const uint8_t R_indices[20] __attribute__((aligned(4))) = {20, 47, 42, 2, 21, 48, 43, 3, 22, 49, 36, 4, 27, 33, 31, 29, 34, 32, 30, 28};
static const uint8_t Ri_indices[20] __attribute__((aligned(4))) = {20, 2, 42, 47, 21, 3, 43, 48, 22, 4, 36, 49, 27, 29, 31, 33, 34, 28, 30, 32};
static const uint8_t R2_indices[20] __attribute__((aligned(4))) = {20, 42, 2, 47, 21, 43, 3, 48, 22, 36, 4, 49, 27, 31, 29, 33, 34, 30, 28, 32};

static const uint8_t B_indices[20] __attribute__((aligned(4))) = {36, 42, 40, 38, 37, 43, 41, 39, 0, 29, 49, 15, 1, 30, 50, 16, 2, 31, 51, 9};
static const uint8_t Bi_indices[20] __attribute__((aligned(4))) = {36, 38, 40, 42, 37, 39, 41, 43, 0, 15, 49, 29, 1, 16, 50, 30, 2, 9, 51, 31};
static const uint8_t B2_indices[20] __attribute__((aligned(4))) = {36, 40, 38, 42, 37, 41, 39, 43, 0, 49, 15, 29, 1, 50, 16, 30, 2, 51, 9, 31};

static const uint8_t D_indices[20] __attribute__((aligned(4))) = {24, 15, 42, 33, 23, 14, 41, 32, 22, 13, 40, 31, 45, 51, 49, 47, 46, 52, 50, 48};
static const uint8_t Di_indices[20] __attribute__((aligned(4))) = {24, 33, 42, 15, 23, 32, 41, 14, 22, 31, 40, 13, 45, 47, 49, 51, 46, 48, 50, 52};
static const uint8_t D2_indices[20] __attribute__((aligned(4))) = {24, 42, 33, 15, 23, 41, 32, 14, 22, 40, 31, 13, 45, 49, 47, 51, 46, 50, 48, 52};



void reset_moves(void* target_array, size_t array_size) {
    if (target_array != NULL) {
        memset(target_array, 0, array_size);
    }
}

void catenate_moves(char* moves, char* temporary_moves) {
    strcat(moves, temporary_moves);
}

int count_moves(const char* moves) {
    if (moves == NULL) return 0;
    int i = 0;
    while (moves[i] == ' ') i++;
    if (moves[i] == '\0') return 0;
    int count = 1;
    for (; moves[i] != '\0'; i++) {
        if (moves[i] == ' ' && moves[i+1] != '\0' && moves[i+1] != ' ') {
            count++;
        }
    }
    return count;
}

void U(Cube *c)  { swap_one(c, U_indices); strcat(temporary_moves, "U ");}
void Ui(Cube *c) { swap_one(c, Ui_indices); strcat(temporary_moves, "Ui ");}
void U2(Cube *c) { swap_two(c, U2_indices); strcat(temporary_moves, "U2 ");}

void L(Cube *c)  { swap_one(c, L_indices); strcat(temporary_moves, "L ");}
void Li(Cube *c) { swap_one(c, Li_indices); strcat(temporary_moves, "Li ");}
void L2(Cube *c) { swap_two(c, L2_indices); strcat(temporary_moves, "L2 ");}

void F(Cube *c)  { swap_one(c, F_indices); strcat(temporary_moves, "F ");}
void Fi(Cube *c) { swap_one(c, Fi_indices); strcat(temporary_moves, "Fi ");}
void F2(Cube *c) { swap_two(c, F2_indices); strcat(temporary_moves, "F2 ");}

void R(Cube *c)  { swap_one(c, R_indices); strcat(temporary_moves, "R ");}
void Ri(Cube *c) { swap_one(c, Ri_indices); strcat(temporary_moves, "Ri ");}
void R2(Cube *c) { swap_two(c, R2_indices); strcat(temporary_moves, "R2 ");}

void B(Cube *c)  { swap_one(c, B_indices); strcat(temporary_moves, "B ");}
void Bi(Cube *c) { swap_one(c, Bi_indices); strcat(temporary_moves, "Bi ");}
void B2(Cube *c) { swap_two(c, B2_indices); strcat(temporary_moves, "B2 ");}

void D(Cube *c)  { swap_one(c, D_indices); strcat(temporary_moves, "D ");}
void Di(Cube *c) { swap_one(c, Di_indices); strcat(temporary_moves, "Di ");}
void D2(Cube *c) { swap_two(c, D2_indices); strcat(temporary_moves, "D2 ");}




// Face kezdĹ‘- Ă©s vĂ©gindexek elĹ‘re szĂˇmolva
static const struct {
    uint8_t start;
    uint8_t end;
} FACE_INDICES[] = {
    {0, 8},   // U
    {9, 17},  // L
    {18, 26}, // F
    {27, 35}, // R
    {36, 44}, // B
    {45, 53}  // D
};

void get_face(const Cube *c, CubeFace face, uint8_t *out) {
    const uint8_t *src = &c->cube[FACE_INDICES[face].start];
    memcpy(out, src, 9);
}


__attribute__((hot)) void X_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se X forgatĂˇshoz
    static uint8_t temp_faces[4][9];
    uint8_t *cube = c->cube;
    // Eredeti face-ek mentĂ©se
    memcpy(temp_faces[0], &cube[0], 9);   // U
    memcpy(temp_faces[1], &cube[18], 9);  // F
    memcpy(temp_faces[2], &cube[45], 9);  // D
    memcpy(temp_faces[3], &cube[36], 9);  // B
    // Face-ek Ăşj pozĂ­ciĂłkba helyezĂ©se
    memcpy(&cube[0],  temp_faces[1], 9);  // F -> U
    memcpy(&cube[18], temp_faces[2], 9);  // D -> F
    memcpy(&cube[45], temp_faces[3], 9);  // B -> D
    memcpy(&cube[36], temp_faces[0], 9);  // U -> B
    // 2. Oldallapok forgatĂˇsa
    static const uint8_t L_swap[8] = {9,11,13,15,10,12,14,16};
    static const uint8_t R_swap[8] = {27,33,31,29,34,32,30,28};
    static const uint8_t B_swap[8] = {36,40,38,42,37,41,39,43};
    static const uint8_t D_swap[8] = {45,49,47,51,46,50,48,52};
    // Bal Ă©s Jobb oldali forgatĂˇsok (90Â°)
    swap_face_one(c, L_swap[0], L_swap[1], L_swap[2], L_swap[3],L_swap[4], L_swap[5], L_swap[6], L_swap[7]);
    swap_face_one(c, R_swap[0], R_swap[1], R_swap[2], R_swap[3],R_swap[4], R_swap[5], R_swap[6], R_swap[7]);
    // HĂˇtsĂł Ă©s AlsĂł lapok 180Â°-os forgatĂˇs
    swap_face_two(c, B_swap[0], B_swap[1], B_swap[2], B_swap[3],B_swap[4], B_swap[5], B_swap[6], B_swap[7]);
    swap_face_two(c, D_swap[0], D_swap[1], D_swap[2], D_swap[3],D_swap[4], D_swap[5], D_swap[6], D_swap[7]);
    strcat(temporary_moves, "x ");
}

__attribute__((hot)) void Xi_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se
    static uint8_t temp_faces[4][9];
    uint8_t *cube = c->cube;
    // Eredeti face-ek mentĂ©se
    memcpy(temp_faces[0], &cube[0], 9);   // U
    memcpy(temp_faces[1], &cube[18], 9);  // F
    memcpy(temp_faces[2], &cube[45], 9);  // D
    memcpy(temp_faces[3], &cube[36], 9);  // B
    // Face-ek Ăşj pozĂ­ciĂłkba helyezĂ©se
    memcpy(&cube[0],  temp_faces[3], 9);  // B -> U
    memcpy(&cube[18], temp_faces[0], 9);  // U -> F
    memcpy(&cube[45], temp_faces[1], 9);  // F -> D
    memcpy(&cube[36], temp_faces[2], 9);  // D -> B
    // 2. Oldallapok forgatĂˇsa
    static const uint8_t L_swap[8] = {9,15,13,11,10,16,14,12};
    static const uint8_t R_swap[8] = {27,29,31,33,34,28,30,32};
    static const uint8_t U_swap[8] = {0,4,2,6,1,5,3,7};
    static const uint8_t B_swap[8] = {36,40,38,42,37,41,39,43};
    // Bal (CCW) Ă©s Jobb (CW) forgatĂˇsok
    swap_face_one(c, L_swap[0], L_swap[1], L_swap[2], L_swap[3],L_swap[4], L_swap[5], L_swap[6], L_swap[7]);
    swap_face_one(c, R_swap[0], R_swap[1], R_swap[2], R_swap[3],R_swap[4], R_swap[5], R_swap[6], R_swap[7]);
    // U Ă©s B lapok 180Â°-os forgatĂˇs
    swap_face_two(c, U_swap[0], U_swap[1], U_swap[2], U_swap[3],U_swap[4], U_swap[5], U_swap[6], U_swap[7]);
    swap_face_two(c, B_swap[0], B_swap[1], B_swap[2], B_swap[3],B_swap[4], B_swap[5], B_swap[6], B_swap[7]);
    strcat(temporary_moves, "xi ");
}

__attribute__((hot)) void X2_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se
    static uint8_t temp_faces[4][9];
    uint8_t *cube = c->cube;
    // Eredeti face-ek mentĂ©se
    memcpy(temp_faces[0], &cube[0], 9);   // U
    memcpy(temp_faces[1], &cube[18], 9);  // F
    memcpy(temp_faces[2], &cube[45], 9);  // D
    memcpy(temp_faces[3], &cube[36], 9);  // B
    // Face-ek 180Â°-os cserĂ©je
    memcpy(&cube[0],  temp_faces[2], 9);  // D -> U
    memcpy(&cube[45], temp_faces[0], 9);  // U -> D
    memcpy(&cube[18], temp_faces[3], 9);  // B -> F
    memcpy(&cube[36], temp_faces[1], 9);  // F -> B
    // 2. Minden oldallap 180Â°-os forgatĂˇsa
    static const uint8_t B_swap[8]  = {36,40,38,42,37,41,39,43};
    static const uint8_t R_swap[8]  = {27,31,29,33,34,30,28,32};
    static const uint8_t F_swap[8]  = {18,22,20,24,19,23,21,25};
    static const uint8_t L_swap[8]  = {9,13,11,15,10,14,12,16};
    swap_face_two(c, B_swap[0], B_swap[1], B_swap[2], B_swap[3],B_swap[4], B_swap[5], B_swap[6], B_swap[7]);
    swap_face_two(c, R_swap[0], R_swap[1], R_swap[2], R_swap[3],R_swap[4], R_swap[5], R_swap[6], R_swap[7]);
    swap_face_two(c, F_swap[0], F_swap[1], F_swap[2], F_swap[3],F_swap[4], F_swap[5], F_swap[6], F_swap[7]);
    swap_face_two(c, L_swap[0], L_swap[1], L_swap[2], L_swap[3],L_swap[4], L_swap[5], L_swap[6], L_swap[7]);
    strcat(temporary_moves, "x2 ");
}

__attribute__((hot)) void Y_rotation(Cube *c) {
    // Ideiglenes bufferek statikus allokĂˇciĂłval (nincs heap fragmentation)
    static uint8_t temp_faces[4][9];
    uint8_t *cube = c->cube;
    memcpy(temp_faces[0], &cube[9], 9);   // L
    memcpy(temp_faces[1], &cube[27], 9);  // R
    memcpy(temp_faces[2], &cube[36], 9);  // B
    memcpy(temp_faces[3], &cube[18], 9);  // F
    // 2. Face-ek rotĂˇciĂłja memcpy-kkel
    memcpy(&cube[9], temp_faces[3], 9);   // F -> L
    memcpy(&cube[18], temp_faces[1], 9);  // R -> F
    memcpy(&cube[27], temp_faces[2], 9);  // B -> R
    memcpy(&cube[36], temp_faces[0], 9);  // L -> B
    // 3. U Ă©s D face forgatĂˇsa optimalizĂˇlt swap-ekkel
    static const uint8_t U_swap[8] = {0,6,4,2,1,7,5,3};
    static const uint8_t D_swap[8] = {45,47,49,51,46,48,50,52};
    swap_face_one(c, U_swap[0], U_swap[1], U_swap[2], U_swap[3], U_swap[4], U_swap[5], U_swap[6], U_swap[7]);
    swap_face_one(c, D_swap[0], D_swap[1], D_swap[2], D_swap[3], D_swap[4], D_swap[5], D_swap[6], D_swap[7]);
    strcat(temporary_moves, "y ");
}

__attribute__((hot)) void Yi_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se memcpy-kkel
    static uint8_t temp_faces[5][9]; // Statikus buffer a fragmentĂˇciĂł elkerĂĽlĂ©sĂ©hez
    uint8_t *cube = c->cube;
    // Face adatok mentĂ©se
    memcpy(temp_faces[0], &cube[9], 9);   // L (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[1], &cube[18], 9);  // F (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[2], &cube[27], 9);  // R (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[3], &cube[36], 9);  // B (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[4], &cube[45], 9);  // D (csak a buffer mĂ©ret miatt)
    // Face-ek ĂşjrarendezĂ©se Yi forgatĂˇshoz
    memcpy(&cube[9],  temp_faces[3], 9);  // B -> L pozĂ­ciĂł
    memcpy(&cube[18], temp_faces[0], 9);  // L -> F pozĂ­ciĂł
    memcpy(&cube[27], temp_faces[1], 9);  // F -> R pozĂ­ciĂł
    memcpy(&cube[36], temp_faces[2], 9);  // R -> B pozĂ­ciĂł
    // 2. U Ă©s D face-ek forgatĂˇsa optimalizĂˇlt swap-ekkel
    static const uint8_t U_swap[8] = {0,2,4,6,1,3,5,7};
    static const uint8_t D_swap[8] = {45,51,49,47,46,52,50,48};
    swap_face_one(c, U_swap[0], U_swap[1], U_swap[2], U_swap[3], U_swap[4], U_swap[5], U_swap[6], U_swap[7]);
    swap_face_one(c, D_swap[0], D_swap[1], D_swap[2], D_swap[3], D_swap[4], D_swap[5], D_swap[6], D_swap[7]);
    strcat(temporary_moves, "yi ");
}

__attribute__((hot)) void Y2_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se memcpy-kkel
    static uint8_t temp_faces[4][9]; // Statikus buffer a fragmentĂˇciĂł elkerĂĽlĂ©sĂ©hez
    uint8_t *cube = c->cube;
    // Face adatok mentĂ©se
    memcpy(temp_faces[0], &cube[27], 9);  // R (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[1], &cube[36], 9);  // B (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[2], &cube[9], 9);   // L (eredeti pozĂ­ciĂł)
    memcpy(temp_faces[3], &cube[18], 9);  // F (eredeti pozĂ­ciĂł)
    // Face-ek ĂşjrarendezĂ©se Y2 forgatĂˇshoz
    memcpy(&cube[9],  temp_faces[0], 9);  // R -> L pozĂ­ciĂł
    memcpy(&cube[18], temp_faces[1], 9);  // B -> F pozĂ­ciĂł
    memcpy(&cube[27], temp_faces[2], 9);  // L -> R pozĂ­ciĂł
    memcpy(&cube[36], temp_faces[3], 9);  // F -> B pozĂ­ciĂł
    // 2. U Ă©s D face-ek 180Â°-os forgatĂˇsa optimalizĂˇlt swap-ekkel
    static const uint8_t U_swap[8] = {0,4,2,6,1,5,3,7};
    static const uint8_t D_swap[8] = {45,49,47,51,46,50,48,52};
    swap_face_two(c, U_swap[0], U_swap[1], U_swap[2], U_swap[3], U_swap[4], U_swap[5], U_swap[6], U_swap[7]);
    swap_face_two(c, D_swap[0], D_swap[1], D_swap[2], D_swap[3], D_swap[4], D_swap[5], D_swap[6], D_swap[7]);
    strcat(temporary_moves, "y2 ");
}

__attribute__((hot)) void Z_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se
    static uint8_t temp_faces[4][9];
    uint8_t *cube = c->cube;
    // Eredeti face-ek mentĂ©se
    memcpy(temp_faces[0], &cube[0], 9);   // U
    memcpy(temp_faces[1], &cube[9], 9);   // L
    memcpy(temp_faces[2], &cube[27], 9);  // R
    memcpy(temp_faces[3], &cube[45], 9);  // D
    // Face-ek 180Â°-os cserĂ©je
    memcpy(&cube[0],  temp_faces[1], 9);  // L -> U
    memcpy(&cube[9],  temp_faces[3], 9);  // D -> L
    memcpy(&cube[27], temp_faces[0], 9);  // U -> R
    memcpy(&cube[45], temp_faces[2], 9);  // R -> D
    // 2. Minden lap 90Â° CW forgatĂˇsa
    static const uint8_t F_swap[8]  = {18,24,22,20,19,25,23,21};
    static const uint8_t B_swap[8]  = {36,38,40,42,37,39,41,43};
    static const uint8_t D_swap[8]  = {45,51,49,47,46,52,50,48};
    static const uint8_t L_swap[8]  = {9,15,13,11,10,16,14,12};
    static const uint8_t R_swap[8]  = {27,33,31,29,34,32,30,28};
    static const uint8_t U_swap[8]  = {0,6,4,2,1,7,5,3};
    swap_face_one(c, F_swap[0], F_swap[1], F_swap[2], F_swap[3], F_swap[4], F_swap[5], F_swap[6], F_swap[7]);
    swap_face_one(c, B_swap[0], B_swap[1], B_swap[2], B_swap[3], B_swap[4], B_swap[5], B_swap[6], B_swap[7]);
    swap_face_one(c, D_swap[0], D_swap[1], D_swap[2], D_swap[3], D_swap[4], D_swap[5], D_swap[6], D_swap[7]);
    swap_face_one(c, L_swap[0], L_swap[1], L_swap[2], L_swap[3], L_swap[4], L_swap[5], L_swap[6], L_swap[7]);
    swap_face_one(c, R_swap[0], R_swap[1], R_swap[2], R_swap[3], R_swap[4], R_swap[5], R_swap[6], R_swap[7]);
    swap_face_one(c, U_swap[0], U_swap[1], U_swap[2], U_swap[3], U_swap[4], U_swap[5], U_swap[6], U_swap[7]);
    strcat(temporary_moves, "z ");
}

__attribute__((hot)) void Zi_rotation(Cube *c) {
    // 1. Face-ek ĂˇtrendezĂ©se
    static uint8_t temp_faces[4][9];
    uint8_t *cube = c->cube;
    // Eredeti face-ek mentĂ©se
    memcpy(temp_faces[0], &cube[0], 9);   // U
    memcpy(temp_faces[1], &cube[9], 9);   // L
    memcpy(temp_faces[2], &cube[27], 9);  // R
    memcpy(temp_faces[3], &cube[45], 9);  // D
    // Face-ek Ăşj pozĂ­ciĂłkba helyezĂ©se
    memcpy(&cube[0],  temp_faces[2], 9);  // R -> U
    memcpy(&cube[9],  temp_faces[0], 9);  // U -> L
    memcpy(&cube[27], temp_faces[3], 9);  // D -> R
    memcpy(&cube[45], temp_faces[1], 9);  // L -> D
    // 2. Minden lap 90Â° CCW forgatĂˇsa
    static const uint8_t F_swap[8]  = {18,20,22,24,19,21,23,25};
    static const uint8_t B_swap[8]  = {36,42,40,38,37,43,41,39};
    static const uint8_t D_swap[8]  = {45,47,49,51,46,48,50,52};
    static const uint8_t L_swap[8]  = {9,11,13,15,10,12,14,16};
    static const uint8_t R_swap[8]  = {27,29,31,33,34,28,30,32};
    static const uint8_t U_swap[8]  = {0,2,4,6,1,3,5,7};
    swap_face_one(c, F_swap[0], F_swap[1], F_swap[2], F_swap[3], F_swap[4], F_swap[5], F_swap[6], F_swap[7]);
    swap_face_one(c, B_swap[0], B_swap[1], B_swap[2], B_swap[3], B_swap[4], B_swap[5], B_swap[6], B_swap[7]);
    swap_face_one(c, D_swap[0], D_swap[1], D_swap[2], D_swap[3], D_swap[4], D_swap[5], D_swap[6], D_swap[7]);
    swap_face_one(c, L_swap[0], L_swap[1], L_swap[2], L_swap[3], L_swap[4], L_swap[5], L_swap[6], L_swap[7]);
    swap_face_one(c, R_swap[0], R_swap[1], R_swap[2], R_swap[3], R_swap[4], R_swap[5], R_swap[6], R_swap[7]);
    swap_face_one(c, U_swap[0], U_swap[1], U_swap[2], U_swap[3], U_swap[4], U_swap[5], U_swap[6], U_swap[7]);
    strcat(temporary_moves, "zi ");
}


// scramble_cube tĂ¶mbje
typedef void (*CubeMove)(Cube*);
extern void U(Cube*), Ui(Cube*), U2(Cube*);
extern void L(Cube*), Li(Cube*), L2(Cube*);
extern void F(Cube*), Fi(Cube*), F2(Cube*);
extern void R(Cube*), Ri(Cube*), R2(Cube*);
extern void B(Cube*), Bi(Cube*), B2(Cube*);
extern void D(Cube*), Di(Cube*), D2(Cube*);

const CubeMove all_moves[] = {
    U, Ui, U2, L, Li, L2, F, Fi, F2, 
    R, Ri, R2, B, Bi, B2, D, Di, D2
};

void scramble_cube(Cube* c, int slen) {
    std::srand((unsigned)std::time(nullptr));
    const char faces[6] = { 'U', 'D', 'F', 'B', 'R', 'L' };
    const int dirCount = 3;
    char last_moves[2] = { '\0', '\0' }; // last_moves[0]: elĹ‘zĹ‘, last_moves[1]: kettĹ‘vel ezelĹ‘tti

    for (int i = 0; i < slen; ++i) {
        char faceChar;
        int dirIndex;

        do {
            faceChar = faces[std::rand() % 6];
            dirIndex = std::rand() % dirCount;
            // Ha i > 0, ne legyen ugyanaz, mint az elĹ‘zĹ‘
            // Ha i > 1, ne legyen ugyanaz, mint az elĹ‘zĹ‘ vagy a kettĹ‘vel ezelĹ‘tti
        } while ((i > 0 && faceChar == last_moves[0]) ||
                 (i > 1 && faceChar == last_moves[1]));

        // LĂ©pĂ©s tĂˇrolĂˇsa a kĂ¶vetkezĹ‘hĂ¶z
        last_moves[1] = last_moves[0];
        last_moves[0] = faceChar;

        // Index meghatĂˇrozĂˇs
        int faceIndex;
        switch (faceChar) {
            case 'U': faceIndex = 0; break;
            case 'D': faceIndex = 1; break;
            case 'F': faceIndex = 2; break;
            case 'B': faceIndex = 3; break;
            case 'R': faceIndex = 4; break;
            case 'L': faceIndex = 5; break;
            default:  faceIndex = 0; break;
        }
        int moveIndex = faceIndex * dirCount + dirIndex;
        all_moves[moveIndex](c);
    }
}

int remrep(char* s) {
    if (s == NULL) return 0; // NULL pointer ellenĹ‘rzĂ©s
    char face[128]; int val[128]; int top = 0;
    for (char* p = s; *p != '\0'; ) {
        while (*p == ' ') p++;
        if (*p == '\0') break;
        char c = *p++;
        int v = 1;
        if (*p == '2') { v = 2; p++; }
        else if (*p == 'i') { v = 3; p++; }
        if (top > 0 && face[top - 1] == c) {
            int sum = (val[top - 1] + v) % 4;
            if (sum == 0) { top--; }
            else { val[top - 1] = sum; }
        }
        else { face[top] = c; val[top]  = v; top++; }
    }
    int w = 0;
    for (int i = 0; i < top; i++) {
        s[w++] = face[i];
        if (val[i] == 2) { s[w++] = '2'; }
        else if (val[i] == 3) { s[w++] = 'i'; }
        if (i < top - 1) { s[w++] = ' '; }
    }
    s[w] = '\0';
    return top;
}

int normalize_moves(char* s) {
    if (s == NULL) return 0;

    char previous[1024];
    int passes = 0;

    while (true) {
        strncpy(previous, s, sizeof(previous) - 1);
        previous[sizeof(previous) - 1] = '\0';
        int remaining = remrep(s);
        passes++;

        if (strcmp(previous, s) == 0 || passes >= 64) {
            return remaining;
        }
    }
}

void solve_once(Cube* myCube) {
    extern char temporary_moves[256];

    solve_EO(myCube);
    if (solver_verbose) printf("EO megoldas: %s\n", temporary_moves);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_LINE(myCube);
    if (solver_verbose) printf("LINE megoldas: %s\n", temporary_moves);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_BBBR(myCube);
    if (solver_verbose) printf("BBBR megoldas: %s\n", temporary_moves);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_ADVFR(myCube);
    if (solver_verbose) printf("ADVFR megoldas: %s\n", temporary_moves);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_SBBFL(myCube);
    if (solver_verbose) printf("SBBFL megoldas: %s\n", temporary_moves);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_F2LBL(myCube);
    if (solver_verbose) printf("F2LBL megoldas: %s\n", temporary_moves);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_ZBLL(myCube);
    if (solver_verbose) cube_print(myCube);
    catenate_moves(moves, temporary_moves);
    reset_moves(temporary_moves, sizeof(temporary_moves));

    normalize_moves(moves);
}


// Define the OrientationFunc type if not already defined
typedef void (*OrientationFunc)(Cube*);

// Define do_nothing at file scope
void do_nothing(Cube*) {}

static bool cube_is_solved(const Cube* cube) {
    static const int faces[6][9] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8},
        {9, 10, 11, 12, 13, 14, 15, 16, 17},
        {18, 19, 20, 21, 22, 23, 24, 25, 26},
        {27, 28, 29, 30, 31, 32, 33, 34, 35},
        {36, 37, 38, 39, 40, 41, 42, 43, 44},
        {45, 46, 47, 48, 49, 50, 51, 52, 53}
    };

    for (int face = 0; face < 6; ++face) {
        const uint8_t color = cube->cube[faces[face][0]];
        for (int i = 1; i < 9; ++i) {
            if (cube->cube[faces[face][i]] != color) {
                return false;
            }
        }
    }

    return true;
}

enum class ParsedMoveType : uint8_t {
    Invalid,
    FaceQuarter,
    FaceHalf,
    Rotation
};

struct ParsedMove {
    ParsedMoveType type;
    char face;
    uint8_t modifier;  // 0=normal, 1=inverse, 2=double
};

static inline bool is_space_char(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

static inline void skip_spaces(const char*& p) {
    while (*p != '\0' && is_space_char(*p)) {
        ++p;
    }
}

static bool parse_move_token_fast(const char*& p, ParsedMove* out_move) {
    skip_spaces(p);
    if (*p == '\0') {
        return false;
    }

    const char first = *p++;
    char second = '\0';
    if (*p == 'i' || *p == 'I' || *p == '2') {
        second = *p++;
    }

    // Reject malformed merged tokens like "Uii" or "R2x".
    if (*p != '\0' && !is_space_char(*p)) {
        if (out_move != nullptr) {
            out_move->type = ParsedMoveType::Invalid;
        }
        return true;
    }

    ParsedMove parsed = {ParsedMoveType::Invalid, first, 0};
    if (second == 'i' || second == 'I') parsed.modifier = 1;
    else if (second == '2') parsed.modifier = 2;

    switch (first) {
        case 'U': case 'L': case 'F': case 'R': case 'B': case 'D':
            parsed.type = parsed.modifier == 2 ? ParsedMoveType::FaceHalf : ParsedMoveType::FaceQuarter;
            break;
        case 'x': case 'X': case 'y': case 'Y': case 'z': case 'Z':
            parsed.type = ParsedMoveType::Rotation;
            break;
        default:
            parsed.type = ParsedMoveType::Invalid;
            break;
    }

    if (out_move != nullptr) {
        *out_move = parsed;
    }
    return true;
}

static inline bool apply_parsed_move_without_recording(Cube* cube, const ParsedMove& move) {
    switch (move.face) {
        case 'U':
            if (move.modifier == 0) swap_one(cube, U_indices);
            else if (move.modifier == 1) swap_one(cube, Ui_indices);
            else swap_two(cube, U2_indices);
            return true;
        case 'L':
            if (move.modifier == 0) swap_one(cube, L_indices);
            else if (move.modifier == 1) swap_one(cube, Li_indices);
            else swap_two(cube, L2_indices);
            return true;
        case 'F':
            if (move.modifier == 0) swap_one(cube, F_indices);
            else if (move.modifier == 1) swap_one(cube, Fi_indices);
            else swap_two(cube, F2_indices);
            return true;
        case 'R':
            if (move.modifier == 0) swap_one(cube, R_indices);
            else if (move.modifier == 1) swap_one(cube, Ri_indices);
            else swap_two(cube, R2_indices);
            return true;
        case 'B':
            if (move.modifier == 0) swap_one(cube, B_indices);
            else if (move.modifier == 1) swap_one(cube, Bi_indices);
            else swap_two(cube, B2_indices);
            return true;
        case 'D':
            if (move.modifier == 0) swap_one(cube, D_indices);
            else if (move.modifier == 1) swap_one(cube, Di_indices);
            else swap_two(cube, D2_indices);
            return true;
        case 'x': case 'X':
            if (move.modifier == 0) X_rotation(cube);
            else if (move.modifier == 1) Xi_rotation(cube);
            else X2_rotation(cube);
            return true;
        case 'y': case 'Y':
            if (move.modifier == 0) Y_rotation(cube);
            else if (move.modifier == 1) Yi_rotation(cube);
            else Y2_rotation(cube);
            return true;
        case 'z': case 'Z':
            if (move.modifier == 0) Z_rotation(cube);
            else if (move.modifier == 1) Zi_rotation(cube);
            else {
                Z_rotation(cube);
                Z_rotation(cube);
            }
            return true;
        default:
            return false;
    }
}

static bool apply_solution_string(Cube* cube, const char* solution) {
    ZZ_PROFILE_SCOPE(ApplySolutionString);
    char backup_temporary[256];
    strncpy(backup_temporary, temporary_moves, sizeof(backup_temporary) - 1);
    backup_temporary[sizeof(backup_temporary) - 1] = '\0';
    reset_moves(temporary_moves, sizeof(temporary_moves));

    const char* p = solution;
    ParsedMove move = {};
    while (parse_move_token_fast(p, &move)) {
        if (move.type == ParsedMoveType::Invalid || !apply_parsed_move_without_recording(cube, move)) {
            strncpy(temporary_moves, backup_temporary, sizeof(temporary_moves) - 1);
            temporary_moves[sizeof(temporary_moves) - 1] = '\0';
            return false;
        }
    }

    strncpy(temporary_moves, backup_temporary, sizeof(temporary_moves) - 1);
    temporary_moves[sizeof(temporary_moves) - 1] = '\0';
    return true;
}

static bool solution_solves_scramble(const Cube* scrambled, const char* solution) {
    Cube verify;
    cube_init(&verify, cube_get_current_state(scrambled));
    if (!apply_solution_string(&verify, solution)) {
        return false;
    }
    return cube_is_solved(&verify);
}

static bool invert_move_token(const char* token, char* out, size_t out_size) {
    if (token == nullptr || out == nullptr || out_size == 0) {
        return false;
    }

    if (strcmp(token, "U") == 0) strncpy(out, "Ui", out_size - 1);
    else if (strcmp(token, "Ui") == 0) strncpy(out, "U", out_size - 1);
    else if (strcmp(token, "U2") == 0) strncpy(out, "U2", out_size - 1);
    else if (strcmp(token, "L") == 0) strncpy(out, "Li", out_size - 1);
    else if (strcmp(token, "Li") == 0) strncpy(out, "L", out_size - 1);
    else if (strcmp(token, "L2") == 0) strncpy(out, "L2", out_size - 1);
    else if (strcmp(token, "F") == 0) strncpy(out, "Fi", out_size - 1);
    else if (strcmp(token, "Fi") == 0) strncpy(out, "F", out_size - 1);
    else if (strcmp(token, "F2") == 0) strncpy(out, "F2", out_size - 1);
    else if (strcmp(token, "R") == 0) strncpy(out, "Ri", out_size - 1);
    else if (strcmp(token, "Ri") == 0) strncpy(out, "R", out_size - 1);
    else if (strcmp(token, "R2") == 0) strncpy(out, "R2", out_size - 1);
    else if (strcmp(token, "B") == 0) strncpy(out, "Bi", out_size - 1);
    else if (strcmp(token, "Bi") == 0) strncpy(out, "B", out_size - 1);
    else if (strcmp(token, "B2") == 0) strncpy(out, "B2", out_size - 1);
    else if (strcmp(token, "D") == 0) strncpy(out, "Di", out_size - 1);
    else if (strcmp(token, "Di") == 0) strncpy(out, "D", out_size - 1);
    else if (strcmp(token, "D2") == 0) strncpy(out, "D2", out_size - 1);
    else if (strcmp(token, "x") == 0 || strcmp(token, "X") == 0) strncpy(out, "xi", out_size - 1);
    else if (strcmp(token, "xi") == 0 || strcmp(token, "Xi") == 0) strncpy(out, "x", out_size - 1);
    else if (strcmp(token, "x2") == 0 || strcmp(token, "X2") == 0) strncpy(out, "x2", out_size - 1);
    else if (strcmp(token, "y") == 0 || strcmp(token, "Y") == 0) strncpy(out, "yi", out_size - 1);
    else if (strcmp(token, "yi") == 0 || strcmp(token, "Yi") == 0) strncpy(out, "y", out_size - 1);
    else if (strcmp(token, "y2") == 0 || strcmp(token, "Y2") == 0) strncpy(out, "y2", out_size - 1);
    else if (strcmp(token, "z") == 0 || strcmp(token, "Z") == 0) strncpy(out, "zi", out_size - 1);
    else if (strcmp(token, "zi") == 0 || strcmp(token, "Zi") == 0) strncpy(out, "z", out_size - 1);
    else return false;

    out[out_size - 1] = '\0';
    return true;
}

bool invert_solution_string(const char* solution, char* out, size_t out_size) {
    ZZ_PROFILE_SCOPE(InvertSolutionString);
    if (solution == nullptr || out == nullptr || out_size == 0) {
        return false;
    }

    char buffer[512];
    strncpy(buffer, solution, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char tokens[128][8];
    int token_count = 0;
    for (char* token = strtok(buffer, " "); token != nullptr; token = strtok(nullptr, " ")) {
        if (token_count >= 128) {
            return false;
        }
        strncpy(tokens[token_count], token, sizeof(tokens[token_count]) - 1);
        tokens[token_count][sizeof(tokens[token_count]) - 1] = '\0';
        token_count++;
    }

    out[0] = '\0';
    for (int i = token_count - 1; i >= 0; --i) {
        char inverse[8];
        if (!invert_move_token(tokens[i], inverse, sizeof(inverse))) {
            return false;
        }
        if (out[0] != '\0') {
            strncat(out, " ", out_size - strlen(out) - 1);
        }
        strncat(out, inverse, out_size - strlen(out) - 1);
    }
    return true;
}

static bool check_corner_colors(const Cube* cube, uint8_t a, uint8_t b, uint8_t c,
                                uint8_t ca, uint8_t cb, uint8_t cc) {
    return cube->cube[a] == ca && cube->cube[b] == cb && cube->cube[c] == cc;
}

static bool cube_is_solved(const Cube* cube);
static bool solution_solves_scramble(const Cube* scrambled, const char* solution);
static bool first_translate_into_buffer(const char* moves, char* result, size_t out_size);

static bool check_edge_colors(const Cube* cube, uint8_t a, uint8_t b,
                              uint8_t ca, uint8_t cb) {
    return cube->cube[a] == ca && cube->cube[b] == cb;
}

static bool route_right_side_solved(const Cube* cube) {
    const uint8_t down = cube->cube[53];
    const uint8_t front = cube->cube[26];
    const uint8_t right = cube->cube[35];
    const uint8_t back = cube->cube[44];

    return
        check_corner_colors(cube, 49, 31, 42, down, right, back) &&
        check_edge_colors(cube, 48, 32, down, right) &&
        check_edge_colors(cube, 43, 30, back, right) &&
        check_corner_colors(cube, 47, 22, 33, down, front, right) &&
        check_edge_colors(cube, 21, 34, front, right);
}

static bool route_left_back_slot_solved(const Cube* cube) {
    const uint8_t down = cube->cube[53];
    const uint8_t left = cube->cube[17];
    const uint8_t back = cube->cube[44];

    return
        check_corner_colors(cube, 51, 40, 15, down, back, left) &&
        check_edge_colors(cube, 52, 14, down, left) &&
        check_edge_colors(cube, 39, 16, back, left);
}

bool solve_fmc_route(const Cube* scrambled, const FmcRoute& route, char* out_solution, size_t out_size, int* out_move_count) {
    ZZ_PROFILE_SCOPE(SolveFmcRoute);
    extern char temporary_moves[256];
    extern char moves[256];

    if (out_solution == nullptr || out_size == 0) {
        return false;
    }

    out_solution[0] = '\0';
    if (out_move_count != nullptr) {
        *out_move_count = -1;
    }

    OrientationFunc solve_orientations[] = {
        do_nothing,
        X_rotation,
        Xi_rotation,
        Z_rotation,
        Zi_rotation,
        X2_rotation
    };
    OrientationFunc solve_EO_orientations[] = {
        do_nothing,
        Y_rotation,
        Y2_rotation,
        Yi_rotation
    };
    OrientationFunc solve_BBF2L_orientations[] = {
        solve_BBFL,
        solve_BBBL,
        solve_BBFR,
        solve_BBBR
    };
    OrientationFunc solve_ADVF2L_orientations[] = {
        solve_ADVFL,
        solve_ADVBL,
        solve_ADVFR,
        solve_ADVBR
    };
    OrientationFunc solve_SBBF2L_orientations[] = {
        solve_SBBFL,
        solve_SBBBL,
        solve_SBBFR,
        solve_SBBBR
    };
    OrientationFunc solve_F2L_orientations[] = {
        solve_F2LFL,
        solve_F2LBL,
        solve_F2LFR,
        solve_F2LBR
    };

    char backup_temporary[256];
    char backup_moves[256];
    strncpy(backup_temporary, temporary_moves, sizeof(backup_temporary) - 1);
    backup_temporary[sizeof(backup_temporary) - 1] = '\0';
    strncpy(backup_moves, moves, sizeof(backup_moves) - 1);
    backup_moves[sizeof(backup_moves) - 1] = '\0';

    Cube working;
    cube_init(&working, cube_get_current_state(scrambled));
    Cube route_start;
    cube_init(&route_start, cube_get_current_state(scrambled));
    reset_moves(temporary_moves, sizeof(temporary_moves));

    solve_orientations[route.orientation](&working);
    solve_EO_orientations[route.eo_orientation](&working);
    solve_EO(&working);
    solve_LINE(&working);
    solve_BBF2L_orientations[route.first_block](&working);
    solve_ADVF2L_orientations[route.adv_block](&working);
    solve_SBBF2L_orientations[route.second_block](&working);
    solve_F2L_orientations[route.final_f2l](&working);
    solve_ZBLL(&working);

    bool success = false;
    if (cube_is_solved(&working)) {
        char translated[256];
        if (first_translate_into_buffer(temporary_moves, translated, sizeof(translated))) {
            normalize_moves(translated);

            const char* accepted_solution = temporary_moves;
            if (strcmp(translated, temporary_moves) != 0 &&
                solution_solves_scramble(&route_start, translated)) {
                accepted_solution = translated;
            }

            strncpy(out_solution, accepted_solution, out_size - 1);
            out_solution[out_size - 1] = '\0';
            if (out_move_count != nullptr) {
                *out_move_count = count_moves(accepted_solution);
            }
            success = true;
        }
    }

    strncpy(temporary_moves, backup_temporary, sizeof(temporary_moves) - 1);
    temporary_moves[sizeof(temporary_moves) - 1] = '\0';
    strncpy(moves, backup_moves, sizeof(moves) - 1);
    moves[sizeof(moves) - 1] = '\0';
    return success;
}

bool build_inverse_scramble_state(const Cube* scrambled, Cube* out_inverse_scrambled) {
    if (scrambled == nullptr || out_inverse_scrambled == nullptr) {
        return false;
    }

    char backup_temporary[256];
    char backup_moves[256];
    strncpy(backup_temporary, temporary_moves, sizeof(backup_temporary) - 1);
    backup_temporary[sizeof(backup_temporary) - 1] = '\0';
    strncpy(backup_moves, moves, sizeof(backup_moves) - 1);
    backup_moves[sizeof(backup_moves) - 1] = '\0';
    const bool previous_verbose = solver_verbose;

    Cube forward;
    cube_init(&forward, cube_get_current_state(scrambled));
    reset_moves(moves, sizeof(moves));
    reset_moves(temporary_moves, sizeof(temporary_moves));
    solver_verbose = false;
    solve_once(&forward);

    const bool solved = cube_is_solved(&forward) && solution_solves_scramble(scrambled, moves);
    if (!solved) {
        strncpy(temporary_moves, backup_temporary, sizeof(temporary_moves) - 1);
        temporary_moves[sizeof(temporary_moves) - 1] = '\0';
        strncpy(moves, backup_moves, sizeof(moves) - 1);
        moves[sizeof(moves) - 1] = '\0';
        solver_verbose = previous_verbose;
        return false;
    }

    cube_init(out_inverse_scrambled, kSolvedState);
    const bool built = apply_solution_string(out_inverse_scrambled, moves);

    strncpy(temporary_moves, backup_temporary, sizeof(temporary_moves) - 1);
    temporary_moves[sizeof(temporary_moves) - 1] = '\0';
    strncpy(moves, backup_moves, sizeof(moves) - 1);
    moves[sizeof(moves) - 1] = '\0';
    solver_verbose = previous_verbose;

    return built;
}

bool build_inverse_scramble_state_from_solution(const char* solution, Cube* out_inverse_scrambled) {
    if (solution == nullptr || out_inverse_scrambled == nullptr || solution[0] == '\0') {
        return false;
    }

    char backup_temporary[256];
    strncpy(backup_temporary, temporary_moves, sizeof(backup_temporary) - 1);
    backup_temporary[sizeof(backup_temporary) - 1] = '\0';

    cube_init(out_inverse_scrambled, kSolvedState);
    const bool built = apply_solution_string(out_inverse_scrambled, solution);

    strncpy(temporary_moves, backup_temporary, sizeof(temporary_moves) - 1);
    temporary_moves[sizeof(temporary_moves) - 1] = '\0';
    return built;
}

bool solve_fmc_reverse_route(const Cube* original_scrambled,
                             const Cube* inverse_scrambled,
                             const FmcRoute& route,
                             char* out_solution,
                             size_t out_size,
                             int* out_move_count) {
    (void)original_scrambled;

    if (inverse_scrambled == nullptr ||
        out_solution == nullptr || out_size == 0) {
        return false;
    }

    if (!solve_fmc_route(inverse_scrambled, route, out_solution, out_size, out_move_count)) {
        return false;
    }
    return true;
}

void solve_fmc(Cube* myCube) {
    ZZ_PROFILE_SCOPE(SolveFmc);
    extern char temporary_moves[256];
    extern char moves[256];
    const auto& routes = kFmcRoutes;

    char best_moves[256] = {};
    int best_move_count = 1000000;

    reset_moves(moves, sizeof(moves));

    for (const FmcRoute& route : routes) {
        zz_platform_checkpoint();
        char route_solution[256] = {};
        int move_count = -1;
        if (solve_fmc_route(myCube, route, route_solution, sizeof(route_solution), &move_count) &&
            move_count <= best_move_count) {
            strncpy(best_moves, route_solution, sizeof(best_moves) - 1);
            best_moves[sizeof(best_moves) - 1] = '\0';
            best_move_count = move_count;
        }
    }

    if (fmc_reverse_enabled && best_move_count < 1000000) {
        Cube inverse_scrambled;
        if (build_inverse_scramble_state_from_solution(best_moves, &inverse_scrambled)) {
            for (const FmcRoute& route : routes) {
                zz_platform_checkpoint();
                char reverse_route_solution[256] = {};
                int reverse_route_move_count = -1;
                if (solve_fmc_route(&inverse_scrambled, route, reverse_route_solution, sizeof(reverse_route_solution), &reverse_route_move_count) &&
                    reverse_route_move_count <= best_move_count) {
                    char reverse_solution[256] = {};
                    if (!invert_solution_string(reverse_route_solution, reverse_solution, sizeof(reverse_solution))) {
                        continue;
                    }
                    strncpy(best_moves, reverse_solution, sizeof(best_moves) - 1);
                    best_moves[sizeof(best_moves) - 1] = '\0';
                    best_move_count = reverse_route_move_count;
                }
            }
        }
    }

    strncpy(moves, best_moves, sizeof(moves) - 1);
    moves[sizeof(moves) - 1] = '\0';
    reset_moves(temporary_moves, sizeof(temporary_moves));
}

// GlobĂˇlis konstansok
const char* neg_rotations[] = {"xi", "x", "x2", "yi", "y", "y2", "zi", "z"};
const char* notations[6][3] = {
    {"U", "Ui", "U2"},
    {"L", "Li", "L2"},
    {"F", "Fi", "F2"},
    {"R", "Ri", "R2"},
    {"B", "Bi", "B2"},
    {"D", "Di", "D2"}
};

typedef void (*CenterSwapFunc)(char*);
const CenterSwapFunc functions[] = {
    center_x, center_xi, center_x2,
    center_y, center_yi, center_y2,
    center_z, center_zi
};

int find_index_in_neg_rotations(const char* token) {
    char lowered[8];
    int n = strlen(token);
    for (int i = 0; i < n && i < 7; ++i)
        lowered[i] = tolower((unsigned char)token[i]);
    lowered[n] = '\0';
    for (int i = 0; i < 8; ++i) {
        if (strcmp(lowered, neg_rotations[i]) == 0)
            return i;
    }
    return -1;
}

static bool first_translate_into_buffer(const char* moves, char* result, size_t out_size) {
    if (moves == nullptr || result == nullptr || out_size == 0) {
        return false;
    }

    const int MAX_LEN = 1024;
    if (out_size < 2 || out_size > static_cast<size_t>(MAX_LEN)) {
        return false;
    }

    char orientation[6] = {'U', 'L', 'F', 'R', 'B', 'D'};
    int leading_rotations[32];
    int leading_rotation_count = 0;

    const char* p = moves;
    const char* non_rotation_start = moves;
    ParsedMove move = {};

    while (parse_move_token_fast(p, &move)) {
        if (move.type != ParsedMoveType::Rotation) {
            non_rotation_start = p;
            // rewind to start of current token
            const char* q = p;
            while (q > moves && is_space_char(*(q - 1))) {
                --q;
            }
            const char* token_start = q;
            while (token_start > moves && !is_space_char(*(token_start - 1))) {
                --token_start;
            }
            non_rotation_start = token_start;
            break;
        }

        int rotation_index = -1;
        const char lower_face = static_cast<char>(tolower(static_cast<unsigned char>(move.face)));
        if (lower_face == 'x') {
            rotation_index = move.modifier == 0 ? 1 : (move.modifier == 1 ? 0 : 2);
        } else if (lower_face == 'y') {
            rotation_index = move.modifier == 0 ? 4 : (move.modifier == 1 ? 3 : 5);
        } else if (lower_face == 'z') {
            rotation_index = move.modifier == 0 ? 7 : (move.modifier == 1 ? 6 : -1);
        }

        if (rotation_index == -1 || leading_rotation_count >= static_cast<int>(sizeof(leading_rotations) / sizeof(leading_rotations[0]))) {
            return false;
        }
        leading_rotations[leading_rotation_count++] = rotation_index;
        non_rotation_start = p;
    }

    for (int i = leading_rotation_count - 1; i >= 0; --i) {
        functions[leading_rotations[i]](orientation);
    }

    // LefordĂ­tĂˇs
    char* out = result;
    int remaining = static_cast<int>(out_size);
    bool first_token = true;
    result[0] = '\0';

    p = non_rotation_start;
    while (parse_move_token_fast(p, &move)) {
        if (move.type == ParsedMoveType::Invalid) {
            return false;
        }

        int orientation_index = -1;
        for (int j = 0; j < 6; ++j) {
            if (orientation[j] == move.face) {
                orientation_index = j;
                break;
            }
        }

        const char* translated = nullptr;
        char fallback[4];
        if (orientation_index == -1) {
            fallback[0] = move.face;
            int len = 1;
            if (move.modifier == 1) fallback[len++] = 'i';
            else if (move.modifier == 2) fallback[len++] = '2';
            fallback[len] = '\0';
            translated = fallback;
        } else {
            translated = notations[orientation_index][move.modifier];
        }

        const size_t translated_len = strlen(translated);
        const int needed = static_cast<int>(translated_len) + (first_token ? 0 : 1) + 1;
        if (needed > remaining) {
            return false;
        }

        if (!first_token) {
            *out++ = ' ';
            --remaining;
        }
        memcpy(out, translated, translated_len);
        out += translated_len;
        remaining -= static_cast<int>(translated_len);
        *out = '\0';
        first_token = false;
    }
    return true;
}

char* first_translate(const char* moves) {
    ZZ_PROFILE_SCOPE(FirstTranslate);
    const size_t kBufferSize = 1024;
    char stack_result[kBufferSize];
    if (!first_translate_into_buffer(moves, stack_result, sizeof(stack_result))) {
        return nullptr;
    }

    const size_t len = strlen(stack_result) + 1;
    char* result = static_cast<char*>(solver_malloc(len));
    if (!result) {
        return nullptr;
    }
    memcpy(result, stack_result, len);
    return result;
}

void swap_center_one(char* orientation, int a, int b, int c, int d) {
    char temp = orientation[a];
    orientation[a] = orientation[b];
    orientation[b] = orientation[c];
    orientation[c] = orientation[d];
    orientation[d] = temp;
}

void swap_center_two(char* orientation, int a, int b, int c, int d) {
    char temp = orientation[a];
    orientation[a] = orientation[b];
    orientation[b] = temp;
    temp = orientation[c];
    orientation[c] = orientation[d];
    orientation[d] = temp;
}

void center_y(char* orientation) { swap_center_one(orientation, 1, 2, 3, 4); }
void center_yi(char* orientation) { swap_center_one(orientation, 1, 4, 3, 2); }
void center_y2(char* orientation) { swap_center_two(orientation, 1, 3, 2, 4); }
void center_x(char* orientation) { swap_center_one(orientation, 0, 2, 5, 4); }
void center_xi(char* orientation) { swap_center_one(orientation, 0, 4, 5, 2); }
void center_x2(char* orientation) { swap_center_two(orientation, 0, 5, 4, 2); }
void center_zi(char* orientation) { swap_center_one(orientation, 0, 3, 5, 1); }
void center_z(char* orientation) { swap_center_one(orientation, 0, 1, 5, 3); }


