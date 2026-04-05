// line_solver_optimized.c
#include "line_solver.h"
#include "zz_profiler.h"


void line_0(Cube *c) { Ui(c); L2(c); D(c); B2(c); }
void line_1(Cube *c) { U2(c); F2(c); B2(c); }
void line_2(Cube *c) { U(c); R2(c); Di(c); B2(c); }
void line_3(Cube *c) { U(c); R2(c); L(c); Di(c); }
void line_4(Cube *c) { Ui(c); Ri(c); L2(c); D(c); }
void line_5(Cube *c) { Ui(c); R(c); L2(c); D(c); }
void line_6(Cube *c) { U(c); R2(c); Li(c); Di(c); }
void line_7(Cube *c) { B2(c); D2(c); }
void line_8(Cube *c) { Ui(c); L2(c); D(c); }
void line_9(Cube *c) { U2(c); F2(c); }
void line_10(Cube *c) { U(c); R2(c); Di(c); }
void line_11(Cube *c) { R2(c); Di(c); B2(c); }
void line_12(Cube *c) { U(c); L2(c); Di(c); F2(c); }
void line_13(Cube *c) { U(c); F2(c); B2(c); }
void line_14(Cube *c) { R2(c); L(c); Di(c); }
void line_15(Cube *c) { U(c); Ri(c); D(c); F2(c); }
void line_16(Cube *c) { U(c); R(c); D(c); F2(c); }
void line_17(Cube *c) { R2(c); Li(c); Di(c); }
void line_18(Cube *c) { U(c); D2(c); F2(c); }
void line_19(Cube *c) { U(c); D(c); F2(c); }
void line_20(Cube *c) { U(c); F2(c); }
void line_21(Cube *c) { R2(c); Di(c); }
void line_22(Cube *c) { F2(c); B2(c); }
void line_23(Cube *c) { R2(c); D(c); F2(c); }
void line_24(Cube *c) { L2(c); Di(c); F2(c); }
void line_25(Cube *c) { L(c); Di(c); F2(c); }
void line_26(Cube *c) { Ri(c); D(c); F2(c); }
void line_27(Cube *c) { R(c); D(c); F2(c); }
void line_28(Cube *c) { Li(c); Di(c); F2(c); }
void line_29(Cube *c) { D2(c); F2(c); }
void line_30(Cube *c) { D(c); F2(c); }
void line_31(Cube *c) { F2(c); }
void line_32(Cube *c) { Di(c); F2(c); }
void line_33(Cube *c) { L2(c); D(c); B2(c); }
void line_34(Cube *c) { Ui(c); F2(c); B2(c); }
void line_35(Cube *c) { Ui(c); R2(c); D(c); F2(c); }
void line_36(Cube *c) { Ui(c); L(c); Di(c); F2(c); }
void line_37(Cube *c) { Ri(c); L2(c); D(c); }
void line_38(Cube *c) { R(c); L2(c); D(c); }
void line_39(Cube *c) { Ui(c); Li(c); Di(c); F2(c); }
void line_40(Cube *c) { U(c); B2(c); D2(c); }
void line_41(Cube *c) { L2(c); D(c); }
void line_42(Cube *c) { Ui(c); F2(c); }
void line_43(Cube *c) { Ui(c); Di(c); F2(c); }
void line_44(Cube *c) { L(c); D(c); B2(c); }
void line_45(Cube *c) { R2(c); L(c); D(c); }
void line_46(Cube *c) { Ui(c); R2(c); L(c); D(c); }
void line_47(Cube *c) { U(c); L(c); D(c); B2(c); }
void line_48(Cube *c) { Ri(c); L(c); D(c); }
void line_49(Cube *c) { R(c); L(c); D(c); }
void line_50(Cube *c) { L(c); U(c); D(c); B2(c); }
void line_51(Cube *c) { D(c); L(c); D(c); }
void line_52(Cube *c) { L(c); D(c); }
void line_53(Cube *c) { Di(c); L(c); D(c); }
void line_54(Cube *c) { D2(c); L(c); D(c); }
void line_55(Cube *c) { Ri(c); Di(c); B2(c); }
void line_56(Cube *c) { Ui(c); Ri(c); Di(c); B2(c); }
void line_57(Cube *c) { U(c); Ri(c); L2(c); Di(c); }
void line_58(Cube *c) { Ri(c); L2(c); Di(c); }
void line_59(Cube *c) { Ri(c); L(c); Di(c); }
void line_60(Cube *c) { R(c); U(c); D(c); F2(c); }
void line_61(Cube *c) { Ri(c); Li(c); Di(c); }
void line_62(Cube *c) { Di(c); Ri(c); Di(c); }
void line_63(Cube *c) { D2(c); Ri(c); Di(c); }
void line_64(Cube *c) { D(c); Ri(c); Di(c); }
void line_65(Cube *c) { Ri(c); Di(c); }
void line_66(Cube *c) { R(c); Di(c); B2(c); }
void line_67(Cube *c) { Ui(c); R(c); Di(c); B2(c); }
void line_68(Cube *c) { U(c); R(c); L2(c); Di(c); }
void line_69(Cube *c) { R(c); L2(c); Di(c); }
void line_70(Cube *c) { R(c); L(c); Di(c); }
void line_71(Cube *c) { R(c); Ui(c); Di(c); B2(c); }
void line_72(Cube *c) { R(c); Li(c); Di(c); }
void line_73(Cube *c) { Di(c); R(c); Di(c); }
void line_74(Cube *c) { D2(c); R(c); Di(c); }
void line_75(Cube *c) { D(c); R(c); Di(c); }
void line_76(Cube *c) { R(c); Di(c); }
void line_77(Cube *c) { Li(c); D(c); B2(c); }
void line_78(Cube *c) { R2(c); Li(c); D(c); }
void line_79(Cube *c) { Ui(c); R2(c); Li(c); D(c); }
void line_80(Cube *c) { U(c); Li(c); D(c); B2(c); }
void line_81(Cube *c) { L(c); Ui(c); Di(c); F2(c); }
void line_82(Cube *c) { Ri(c); Li(c); D(c); }
void line_83(Cube *c) { R(c); Li(c); D(c); }
void line_84(Cube *c) { D(c); Li(c); D(c); }
void line_85(Cube *c) { Li(c); D(c); }
void line_86(Cube *c) { Di(c); Li(c); D(c); }
void line_87(Cube *c) { D2(c); Li(c); D(c); }
void line_88(Cube *c) { B2(c); }
void line_89(Cube *c) { Ui(c); B2(c); }
void line_90(Cube *c) { U2(c); B2(c); }
void line_91(Cube *c) { U(c); B2(c); }
void line_92(Cube *c) { D(c); L(c); Di(c); }
void line_93(Cube *c) { Di(c); Ri(c); D(c); }
void line_94(Cube *c) { Di(c); R(c); D(c); }
void line_95(Cube *c) { D(c); Li(c); Di(c); }
void line_96(Cube *c) { R2(c); Ui(c); B2(c); }
void line_97(Cube *c) { L2(c); U(c); B2(c); }
void line_98(Cube *c) { Di(c); B2(c); }
void line_99(Cube *c) { Ui(c); Di(c); B2(c); }
void line_100(Cube *c) { U(c); L2(c); Di(c); }
void line_101(Cube *c) { L2(c); Di(c); }
void line_102(Cube *c) { L(c); Di(c); }
void line_103(Cube *c) { D2(c); Ri(c); D(c); }
void line_104(Cube *c) { D2(c); R(c); D(c); }
void line_105(Cube *c) { Li(c); Di(c); }
void line_106(Cube *c) { Di(c); L2(c); U(c); B2(c); }
void line_107(Cube *c) { R2(c); U(c); F2(c); }
void line_108(Cube *c) { Di(c); }
void line_109(Cube *c) { D2(c); B2(c); }
void line_110(Cube *c) { U(c); F2(c); D2(c); }
void line_111(Cube *c) { F2(c); D2(c); }
void line_112(Cube *c) { U(c); D2(c); B2(c); }
void line_113(Cube *c) { Di(c); L(c); Di(c); }
void line_114(Cube *c) { D(c); Ri(c); D(c); }
void line_115(Cube *c) { D(c); R(c); D(c); }
void line_116(Cube *c) { Di(c); Li(c); Di(c); }
void line_117(Cube *c) { D2(c); }
void line_118(Cube *c) { D(c); L2(c); Ui(c); F2(c); }
void line_119(Cube *c) { Di(c); R2(c); U(c); F2(c); }
void line_120(Cube *c) { D(c); B2(c); }
void line_121(Cube *c) { R2(c); D(c); }
void line_122(Cube *c) { Ui(c); R2(c); D(c); }
void line_123(Cube *c) { U(c); D(c); B2(c); }
void line_124(Cube *c) { D2(c); L(c); Di(c); }
void line_125(Cube *c) { Ri(c); D(c); }
void line_126(Cube *c) { R(c); D(c); }
void line_127(Cube *c) { D2(c); Li(c); Di(c); }
void line_128(Cube *c) { D(c); R2(c); Ui(c); B2(c); }
void line_129(Cube *c) { D(c); }
void line_130(Cube *c) { L2(c); Ui(c); F2(c); }
static void (*const line_moves[131])(Cube*) = {line_0, line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8, line_9, line_10, line_11, line_12, line_13, line_14, line_15, line_16, line_17, line_18, line_19, line_20, line_21, line_22, line_23, line_24, line_25, line_26, line_27, line_28, line_29, line_30, line_31, line_32, line_33, line_34, line_35, line_36, line_37, line_38, line_39, line_40, line_41, line_42, line_43, line_44, line_45, line_46, line_47, line_48, line_49, line_50, line_51, line_52, line_53, line_54, line_55, line_56, line_57, line_58, line_59, line_60, line_61, line_62, line_63, line_64, line_65, line_66, line_67, line_68, line_69, line_70, line_71, line_72, line_73, line_74, line_75, line_76, line_77, line_78, line_79, line_80, line_81, line_82, line_83, line_84, line_85, line_86, line_87, line_88, line_89, line_90, line_91, line_92, line_93, line_94, line_95, line_96, line_97, line_98, line_99, line_100, line_101, line_102, line_103, line_104, line_105, line_106, line_107, line_108, line_109, line_110, line_111, line_112, line_113, line_114, line_115, line_116, line_117, line_118, line_119, line_120, line_121, line_122, line_123, line_124, line_125, line_126, line_127, line_128, line_129, line_130};



void solve_LINE(Cube* cube) {
    ZZ_PROFILE_SCOPE(SolveLine);
    const uint8_t keyDown = cube->cube[53];
    const uint8_t keyFront = cube->cube[26];
    const uint8_t keyBack = cube->cube[44];

    int frontEdge = find_edge(cube, keyDown, keyFront);
    int backEdge = find_edge(cube, keyDown, keyBack);
    int moveIndex = get_Line_Index(frontEdge, backEdge);

    if (moveIndex != -1) {
        line_moves[moveIndex](cube);
    }
}

int get_Line_Index(int a, int b) {
    static const int indexMap[12][12] = {
        // a=0
        {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        // a=1
        {11, -1, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
        // a=2
        {22, 23, -1, 24, 25, 26, 27, 28, 29, 30, 31, 32},
        // a=3
        {33, 34, 35, -1, 36, 37, 38, 39, 40, 41, 42, 43},
        // a=4
        {44, 45, 46, 47, -1, 48, 49, 50, 51, 52, 53, 54},
        // a=5
        {55, 56, 57, 58, 59, -1, 60, 61, 62, 63, 64, 65},
        // a=6
        {66, 67, 68, 69, 70, 71, -1, 72, 73, 74, 75, 76},
        // a=7
        {77, 78, 79, 80, 81, 82, 83, -1, 84, 85, 86, 87},
        // a=8
        {88, 89, 90, 91, 92, 93, 94, 95, -1, 96, -1, 97},
        // a=9
        {98, 99, 100, 101, 102, 103, 104, 105, 106, -1, 107, 108},
        // a=10
        {109, 110, 111, 112, 113, 114, 115, 116, 117, 118, -1, 119},
        // a=11
        {120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, -1}
    };
    return indexMap[a][b];
}
