#include "eo_solver.h"
#include "zz_profiler.h"


// EO_2
void eo2_0(Cube *c) { Bi(c); R(c); B(c); }
void eo2_1(Cube *c) { U(c); R(c); B(c); U(c); B(c); }
void eo2_2(Cube *c) { B(c); Li(c); B(c); }
void eo2_3(Cube *c) { F(c); U2(c); F(c); }
void eo2_4(Cube *c) { Fi(c); U2(c); F(c); }
void eo2_5(Cube *c) { U(c); B(c); Ui(c); B(c); }
void eo2_6(Cube *c) { U(c); Bi(c); Ui(c); B(c); }
void eo2_7(Cube *c) { U(c); Fi(c); Ri(c); F(c); }
void eo2_8(Cube *c) { Bi(c); Ri(c); B(c); }
void eo2_9(Cube *c) { U(c); B(c); R(c); B(c); }
void eo2_10(Cube *c) { B(c); L(c); B(c); }
void eo2_11(Cube *c) { F(c); Ri(c); F(c); }
void eo2_12(Cube *c) { R(c); B(c); U(c); B(c); }
void eo2_13(Cube *c) { F(c); U(c); F(c); }
void eo2_14(Cube *c) { Fi(c); U(c); F(c); }
void eo2_15(Cube *c) { B(c); Ui(c); B(c); }
void eo2_16(Cube *c) { Bi(c); Ui(c); B(c); }
void eo2_17(Cube *c) { Fi(c); Ri(c); F(c); }
void eo2_18(Cube *c) { U(c); F(c); R(c); F(c); }
void eo2_19(Cube *c) { B(c); R(c); B(c); }
void eo2_20(Cube *c) { U(c); Fi(c); Li(c); F(c); }
void eo2_21(Cube *c) { Fi(c); L(c); F(c); }
void eo2_22(Cube *c) { U(c); F(c); Ui(c); F(c); }
void eo2_23(Cube *c) { U(c); Fi(c); Ui(c); F(c); }
void eo2_24(Cube *c) { F(c); R2(c); F(c); }
void eo2_25(Cube *c) { Fi(c); L2(c); F(c); }
void eo2_26(Cube *c) { U(c); F(c); L(c); F(c); }
void eo2_27(Cube *c) { F(c); R(c); F(c); }
void eo2_28(Cube *c) { U(c); Bi(c); Li(c); B(c); }
void eo2_29(Cube *c) { Fi(c); Li(c); F(c); }
void eo2_30(Cube *c) { F(c); Ui(c); F(c); }
void eo2_31(Cube *c) { Fi(c); Ui(c); F(c); }
void eo2_32(Cube *c) { B(c); U(c); B(c); }
void eo2_33(Cube *c) { Bi(c); U(c); B(c); }
void eo2_34(Cube *c) { F(c); L(c); F(c); }
void eo2_35(Cube *c) { U(c); Bi(c); Ri(c); B(c); }
void eo2_36(Cube *c) { Bi(c); Li(c); B(c); }
void eo2_37(Cube *c) { U(c); B(c); L(c); B(c); }
void eo2_38(Cube *c) { R(c); F(c); U(c); F(c); }
void eo2_39(Cube *c) { R(c); Fi(c); Di(c); F(c); }
void eo2_40(Cube *c) { L(c); U(c); B(c); L(c); B(c); }
void eo2_41(Cube *c) { D(c); Fi(c); Di(c); F(c); }
void eo2_42(Cube *c) { Fi(c); Di(c); F(c); }
void eo2_43(Cube *c) { Fi(c); D2(c); F(c); }
void eo2_44(Cube *c) { Fi(c); D(c); F(c); }
void eo2_45(Cube *c) { R(c); U(c); F(c); R(c); F(c); }
void eo2_46(Cube *c) { R(c); Bi(c); Ui(c); B(c); }
void eo2_47(Cube *c) { D(c); F(c); Di(c); F(c); }
void eo2_48(Cube *c) { F(c); Di(c); F(c); }
void eo2_49(Cube *c) { F(c); D2(c); F(c); }
void eo2_50(Cube *c) { F(c); D(c); F(c); }
void eo2_51(Cube *c) { R(c); B(c); D(c); B(c); }
void eo2_52(Cube *c) { Fi(c); R2(c); F(c); }
void eo2_53(Cube *c) { Bi(c); D(c); B(c); }
void eo2_54(Cube *c) { D(c); Bi(c); Di(c); B(c); }
void eo2_55(Cube *c) { Bi(c); Di(c); B(c); }
void eo2_56(Cube *c) { F(c); L2(c); F(c); }
void eo2_57(Cube *c) { B(c); D(c); B(c); }
void eo2_58(Cube *c) { D(c); B(c); Di(c); B(c); }
void eo2_59(Cube *c) { B(c); Di(c); B(c); }
void eo2_60(Cube *c) { Fi(c); R(c); F(c); }
void eo2_61(Cube *c) { D(c); R(c); F(c); D(c); F(c); }
void eo2_62(Cube *c) { F(c); Li(c); F(c); }
void eo2_63(Cube *c) { B(c); Ri(c); B(c); }
void eo2_64(Cube *c) { R(c); F(c); D(c); F(c); }
void eo2_65(Cube *c) { Bi(c); L(c); B(c); }
static void (*const eo2_moves[66])(Cube*) = {eo2_0, eo2_1, eo2_2, eo2_3, eo2_4, eo2_5, eo2_6, eo2_7, eo2_8, eo2_9, eo2_10, eo2_11, eo2_12, eo2_13, eo2_14, eo2_15, eo2_16, eo2_17, eo2_18, eo2_19, eo2_20, eo2_21, eo2_22, eo2_23, eo2_24, eo2_25, eo2_26, eo2_27, eo2_28, eo2_29, eo2_30, eo2_31, eo2_32, eo2_33, eo2_34, eo2_35, eo2_36, eo2_37, eo2_38, eo2_39, eo2_40, eo2_41, eo2_42, eo2_43, eo2_44, eo2_45, eo2_46, eo2_47, eo2_48, eo2_49, eo2_50, eo2_51, eo2_52, eo2_53, eo2_54, eo2_55, eo2_56, eo2_57, eo2_58, eo2_59, eo2_60, eo2_61, eo2_62, eo2_63, eo2_64, eo2_65};


// EO_4
void eo4_0(Cube *c) { R(c); F2(c); D2(c); Li(c); B(c); }
void eo4_1(Cube *c) { Ri(c); F2(c); U2(c); F(c); }
void eo4_2(Cube *c) { Fi(c); U2(c); L(c); F(c); }
void eo4_3(Cube *c) { B(c); U2(c); Li(c); B(c); }
void eo4_4(Cube *c) { R(c); F2(c); D2(c); B(c); }
void eo4_5(Cube *c) { U(c); R(c); L(c); R2(c); F(c); }
void eo4_6(Cube *c) { U(c); L(c); Di(c); Ri(c); F(c); }
void eo4_7(Cube *c) { U(c); R(c); U(c); Li(c); B(c); }
void eo4_8(Cube *c) { U(c); Ri(c); D(c); L(c); F(c); }
void eo4_9(Cube *c) { R(c); L2(c); Di(c); B(c); }
void eo4_10(Cube *c) { R2(c); D(c); Li(c); B(c); }
void eo4_11(Cube *c) { R(c); D(c); Li(c); B(c); }
void eo4_12(Cube *c) { R(c); B2(c); U(c); B(c); }
void eo4_13(Cube *c) { R(c); D2(c); Li(c); B(c); }
void eo4_14(Cube *c) { Li(c); D(c); R(c); B(c); }
void eo4_15(Cube *c) { R(c); F2(c); Li(c); B(c); }
void eo4_16(Cube *c) { R(c); Di(c); Li(c); B(c); }
void eo4_17(Cube *c) { U(c); Ri(c); Di(c); F(c); }
void eo4_18(Cube *c) { U(c); R2(c); Di(c); F(c); }
void eo4_19(Cube *c) { F2(c); R2(c); D(c); B(c); }
void eo4_20(Cube *c) { U(c); Ri(c); F(c); }
void eo4_21(Cube *c) { D(c); R(c); L2(c); B(c); }
void eo4_22(Cube *c) { R(c); L2(c); B(c); }
void eo4_23(Cube *c) { U(c); D(c); Ri(c); F(c); }
void eo4_24(Cube *c) { Bi(c); R2(c); D(c); B(c); }
void eo4_25(Cube *c) { R2(c); D(c); B(c); }
void eo4_26(Cube *c) { U2(c); L(c); F(c); }
void eo4_27(Cube *c) { U2(c); Di(c); L(c); F(c); }
void eo4_28(Cube *c) { Ui(c); R2(c); Li(c); B(c); }
void eo4_29(Cube *c) { U2(c); D(c); L(c); F(c); }
void eo4_30(Cube *c) { R(c); D(c); B(c); }
void eo4_31(Cube *c) { Ui(c); D2(c); Li(c); B(c); }
void eo4_32(Cube *c) { Ui(c); Li(c); D(c); B(c); }
void eo4_33(Cube *c) { Ui(c); Li(c); B(c); }
void eo4_34(Cube *c) { Ui(c); Di(c); Li(c); B(c); }
void eo4_35(Cube *c) { D2(c); R(c); B(c); }
void eo4_36(Cube *c) { D(c); R(c); B(c); }
void eo4_37(Cube *c) { R(c); B(c); }
void eo4_38(Cube *c) { Di(c); R(c); B(c); }
void eo4_39(Cube *c) { U2(c); R(c); L(c); F(c); }
void eo4_40(Cube *c) { D(c); L(c); D(c); R(c); B(c); }
void eo4_41(Cube *c) { U(c); Ri(c); Li(c); F(c); }
void eo4_42(Cube *c) { Ui(c); Ri(c); Li(c); B(c); }
void eo4_43(Cube *c) { L(c); D(c); R(c); B(c); }
void eo4_44(Cube *c) { R(c); L(c); B(c); }
void eo4_45(Cube *c) { F(c); U2(c); Ri(c); F(c); }
void eo4_46(Cube *c) { L(c); F2(c); U2(c); F(c); }
void eo4_47(Cube *c) { Li(c); F2(c); D2(c); B(c); }
void eo4_48(Cube *c) { Bi(c); U2(c); R(c); B(c); }
void eo4_49(Cube *c) { U(c); R(c); D2(c); Li(c); B(c); }
void eo4_50(Cube *c) { U(c); Li(c); D(c); R(c); B(c); }
void eo4_51(Cube *c) { U(c); R(c); F2(c); Li(c); B(c); }
void eo4_52(Cube *c) { U(c); R(c); Di(c); Li(c); B(c); }
void eo4_53(Cube *c) { F2(c); U2(c); F(c); }
void eo4_54(Cube *c) { R2(c); F2(c); U2(c); F(c); }
void eo4_55(Cube *c) { F2(c); U2(c); L2(c); F(c); }
void eo4_56(Cube *c) { U(c); Ri(c); Ui(c); F(c); }
void eo4_57(Cube *c) { R(c); F2(c); U2(c); F(c); }
void eo4_58(Cube *c) { U(c); D2(c); Ri(c); Ui(c); F(c); }
void eo4_59(Cube *c) { F2(c); U2(c); Li(c); F(c); }
void eo4_60(Cube *c) { F2(c); U2(c); R2(c); F(c); }
void eo4_61(Cube *c) { R2(c); F2(c); D2(c); B(c); }
void eo4_62(Cube *c) { U(c); L(c); U(c); F(c); }
void eo4_63(Cube *c) { F2(c); U2(c); R(c); F(c); }
void eo4_64(Cube *c) { U(c); D2(c); L(c); U(c); F(c); }
void eo4_65(Cube *c) { Li(c); F2(c); U2(c); F(c); }
void eo4_66(Cube *c) { F2(c); D2(c); B(c); }
void eo4_67(Cube *c) { U(c); D2(c); Li(c); Ui(c); B(c); }
void eo4_68(Cube *c) { F2(c); D2(c); L(c); B(c); }
void eo4_69(Cube *c) { U(c); Li(c); Ui(c); B(c); }
void eo4_70(Cube *c) { L(c); F2(c); D2(c); B(c); }
void eo4_71(Cube *c) { U(c); D2(c); R(c); U(c); B(c); }
void eo4_72(Cube *c) { Ri(c); F2(c); D2(c); B(c); }
void eo4_73(Cube *c) { U(c); R(c); U(c); B(c); }
void eo4_74(Cube *c) { F2(c); D2(c); Ri(c); B(c); }
void eo4_75(Cube *c) { U(c); L(c); U(c); R(c); F(c); }
void eo4_76(Cube *c) { U(c); R(c); F2(c); U(c); Li(c); B(c); }
void eo4_77(Cube *c) { U(c); Ri(c); Ui(c); Li(c); F(c); }
void eo4_78(Cube *c) { U(c); Li(c); Ui(c); Ri(c); B(c); }
void eo4_79(Cube *c) { R(c); Fi(c); U2(c); Li(c); F(c); }
void eo4_80(Cube *c) { U(c); R(c); U(c); L(c); B(c); }
void eo4_81(Cube *c) { Ui(c); L(c); D(c); F(c); }
void eo4_82(Cube *c) { L2(c); Di(c); B(c); }
void eo4_83(Cube *c) { B(c); L2(c); Di(c); B(c); }
void eo4_84(Cube *c) { U2(c); Ri(c); F(c); }
void eo4_85(Cube *c) { U2(c); Di(c); Ri(c); F(c); }
void eo4_86(Cube *c) { U(c); R(c); L2(c); B(c); }
void eo4_87(Cube *c) { U2(c); D(c); Ri(c); F(c); }
void eo4_88(Cube *c) { F2(c); L2(c); Di(c); B(c); }
void eo4_89(Cube *c) { U(c); R2(c); D(c); B(c); }
void eo4_90(Cube *c) { Ui(c); L(c); F(c); }
void eo4_91(Cube *c) { Ui(c); Di(c); L(c); F(c); }
void eo4_92(Cube *c) { R2(c); Li(c); B(c); }
void eo4_93(Cube *c) { D(c); L(c); U2(c); F(c); }
void eo4_94(Cube *c) { Li(c); Di(c); B(c); }
void eo4_95(Cube *c) { D2(c); Li(c); B(c); }
void eo4_96(Cube *c) { D(c); Li(c); B(c); }
void eo4_97(Cube *c) { Li(c); B(c); }
void eo4_98(Cube *c) { Di(c); Li(c); B(c); }
void eo4_99(Cube *c) { U(c); D2(c); R(c); B(c); }
void eo4_100(Cube *c) { U(c); D(c); R(c); B(c); }
void eo4_101(Cube *c) { U(c); R(c); B(c); }
void eo4_102(Cube *c) { U(c); R(c); Di(c); B(c); }
void eo4_103(Cube *c) { Ui(c); R(c); L(c); F(c); }
void eo4_104(Cube *c) { D(c); Ri(c); Di(c); Li(c); B(c); }
void eo4_105(Cube *c) { U2(c); Ri(c); Li(c); F(c); }
void eo4_106(Cube *c) { Ri(c); Li(c); B(c); }
void eo4_107(Cube *c) { Ri(c); Di(c); Li(c); B(c); }
void eo4_108(Cube *c) { U(c); R(c); L(c); B(c); }
void eo4_109(Cube *c) { U2(c); R(c); Di(c); Ri(c); F(c); }
void eo4_110(Cube *c) { U2(c); L(c); D(c); L(c); F(c); }
void eo4_111(Cube *c) { U2(c); F(c); }
void eo4_112(Cube *c) { U2(c); Di(c); F(c); }
void eo4_113(Cube *c) { U(c); D2(c); U(c); F(c); }
void eo4_114(Cube *c) { U2(c); D(c); F(c); }
void eo4_115(Cube *c) { L(c); Di(c); Li(c); B(c); }
void eo4_116(Cube *c) { U2(c); R2(c); F(c); }
void eo4_117(Cube *c) { D(c); L2(c); B(c); }
void eo4_118(Cube *c) { L2(c); B(c); }
void eo4_119(Cube *c) { Di(c); L2(c); B(c); }
void eo4_120(Cube *c) { U2(c); F2(c); L2(c); F(c); }
void eo4_121(Cube *c) { D(c); F2(c); R2(c); B(c); }
void eo4_122(Cube *c) { F2(c); R2(c); B(c); }
void eo4_123(Cube *c) { Di(c); F2(c); R2(c); B(c); }
void eo4_124(Cube *c) { U2(c); R(c); F(c); }
void eo4_125(Cube *c) { U(c); Ri(c); F2(c); D2(c); F(c); }
void eo4_126(Cube *c) { U2(c); D(c); R(c); F(c); }
void eo4_127(Cube *c) { Ri(c); L2(c); B(c); }
void eo4_128(Cube *c) { U2(c); R(c); D(c); F(c); }
void eo4_129(Cube *c) { Di(c); Ri(c); L2(c); B(c); }
void eo4_130(Cube *c) { R(c); D(c); R(c); B(c); }
void eo4_131(Cube *c) { U2(c); F2(c); R2(c); F(c); }
void eo4_132(Cube *c) { D(c); F2(c); L2(c); B(c); }
void eo4_133(Cube *c) { F2(c); L2(c); B(c); }
void eo4_134(Cube *c) { Di(c); F2(c); L2(c); B(c); }
void eo4_135(Cube *c) { U2(c); L2(c); F(c); }
void eo4_136(Cube *c) { D(c); R2(c); B(c); }
void eo4_137(Cube *c) { R2(c); B(c); }
void eo4_138(Cube *c) { Di(c); R2(c); B(c); }
void eo4_139(Cube *c) { U2(c); Di(c); Li(c); F(c); }
void eo4_140(Cube *c) { U(c); F2(c); D2(c); Ri(c); F(c); }
void eo4_141(Cube *c) { U2(c); Li(c); F(c); }
void eo4_142(Cube *c) { D(c); R2(c); L(c); B(c); }
void eo4_143(Cube *c) { U2(c); Li(c); Di(c); F(c); }
void eo4_144(Cube *c) { R2(c); L(c); B(c); }
void eo4_145(Cube *c) { D2(c); B(c); }
void eo4_146(Cube *c) { D(c); B(c); }
void eo4_147(Cube *c) { B(c); }
void eo4_148(Cube *c) { Di(c); B(c); }
void eo4_149(Cube *c) { D2(c); L(c); B(c); }
void eo4_150(Cube *c) { D(c); L(c); D(c); B(c); }
void eo4_151(Cube *c) { Di(c); L(c); B(c); }
void eo4_152(Cube *c) { D(c); L(c); B(c); }
void eo4_153(Cube *c) { L(c); D(c); B(c); }
void eo4_154(Cube *c) { L(c); B(c); }
void eo4_155(Cube *c) { D(c); Ri(c); B(c); }
void eo4_156(Cube *c) { D(c); Ri(c); Di(c); B(c); }
void eo4_157(Cube *c) { D2(c); Ri(c); B(c); }
void eo4_158(Cube *c) { Ri(c); B(c); }
void eo4_159(Cube *c) { Ri(c); Di(c); B(c); }
void eo4_160(Cube *c) { Di(c); Ri(c); B(c); }
void eo4_161(Cube *c) { D(c); R(c); L(c); R2(c); B(c); }
void eo4_162(Cube *c) { R(c); U2(c); Li(c); F(c); }
void eo4_163(Cube *c) { D(c); R(c); U2(c); Li(c); F(c); }
void eo4_164(Cube *c) { R(c); L(c); R2(c); B(c); }
void eo4_165(Cube *c) { Ri(c); F2(c); Ui(c); F(c); }
void eo4_166(Cube *c) { Ri(c); Di(c); L(c); F(c); }
void eo4_167(Cube *c) { R2(c); Di(c); L(c); F(c); }
void eo4_168(Cube *c) { Ri(c); L2(c); D(c); F(c); }
void eo4_169(Cube *c) { R(c); L(c); R2(c); F(c); }
void eo4_170(Cube *c) { L(c); Di(c); Ri(c); F(c); }
void eo4_171(Cube *c) { R(c); U(c); Li(c); B(c); }
void eo4_172(Cube *c) { Ri(c); D(c); L(c); F(c); }
void eo4_173(Cube *c) { Ri(c); Di(c); F(c); }
void eo4_174(Cube *c) { R2(c); Di(c); F(c); }
void eo4_175(Cube *c) { F2(c); U(c); L2(c); F(c); }
void eo4_176(Cube *c) { Ri(c); F(c); }
void eo4_177(Cube *c) { Di(c); Ri(c); F(c); }
void eo4_178(Cube *c) { D2(c); Ri(c); F(c); }
void eo4_179(Cube *c) { D(c); Ri(c); F(c); }
void eo4_180(Cube *c) { F(c); R2(c); Di(c); F(c); }
void eo4_181(Cube *c) { U(c); L2(c); D(c); F(c); }
void eo4_182(Cube *c) { U(c); L(c); F(c); }
void eo4_183(Cube *c) { U(c); L(c); Di(c); F(c); }
void eo4_184(Cube *c) { U(c); D2(c); L(c); F(c); }
void eo4_185(Cube *c) { U(c); D(c); L(c); F(c); }
void eo4_186(Cube *c) { Ui(c); R(c); D(c); B(c); }
void eo4_187(Cube *c) { U(c); R2(c); L(c); F(c); }
void eo4_188(Cube *c) { U2(c); D(c); Li(c); B(c); }
void eo4_189(Cube *c) { U2(c); Li(c); B(c); }
void eo4_190(Cube *c) { U2(c); Di(c); Li(c); B(c); }
void eo4_191(Cube *c) { Ri(c); L2(c); F(c); }
void eo4_192(Cube *c) { D(c); R(c); U2(c); B(c); }
void eo4_193(Cube *c) { Ui(c); R(c); B(c); }
void eo4_194(Cube *c) { Ui(c); Di(c); R(c); B(c); }
void eo4_195(Cube *c) { U(c); R(c); L(c); F(c); }
void eo4_196(Cube *c) { D(c); Li(c); Di(c); Ri(c); F(c); }
void eo4_197(Cube *c) { Ri(c); Li(c); F(c); }
void eo4_198(Cube *c) { U2(c); Ri(c); Li(c); B(c); }
void eo4_199(Cube *c) { Li(c); Di(c); Ri(c); F(c); }
void eo4_200(Cube *c) { Ui(c); R(c); L(c); B(c); }
void eo4_201(Cube *c) { U(c); F2(c); U2(c); F(c); }
void eo4_202(Cube *c) { R2(c); Ui(c); Di(c); F(c); }
void eo4_203(Cube *c) { U(c); F2(c); U2(c); L2(c); F(c); }
void eo4_204(Cube *c) { Ri(c); Ui(c); F(c); }
void eo4_205(Cube *c) { Di(c); Ri(c); Ui(c); F(c); }
void eo4_206(Cube *c) { D2(c); Ri(c); Ui(c); F(c); }
void eo4_207(Cube *c) { D(c); Ri(c); Ui(c); F(c); }
void eo4_208(Cube *c) { U(c); F2(c); U2(c); R2(c); F(c); }
void eo4_209(Cube *c) { R2(c); U(c); D(c); B(c); }
void eo4_210(Cube *c) { L(c); U(c); F(c); }
void eo4_211(Cube *c) { Di(c); L(c); U(c); F(c); }
void eo4_212(Cube *c) { D2(c); L(c); U(c); F(c); }
void eo4_213(Cube *c) { D(c); L(c); U(c); F(c); }
void eo4_214(Cube *c) { U(c); F2(c); D2(c); B(c); }
void eo4_215(Cube *c) { D2(c); Li(c); Ui(c); B(c); }
void eo4_216(Cube *c) { D(c); Li(c); Ui(c); B(c); }
void eo4_217(Cube *c) { Li(c); Ui(c); B(c); }
void eo4_218(Cube *c) { Di(c); Li(c); Ui(c); B(c); }
void eo4_219(Cube *c) { D2(c); R(c); U(c); B(c); }
void eo4_220(Cube *c) { D(c); R(c); U(c); B(c); }
void eo4_221(Cube *c) { R(c); U(c); B(c); }
void eo4_222(Cube *c) { Di(c); R(c); U(c); B(c); }
void eo4_223(Cube *c) { L(c); U(c); R(c); F(c); }
void eo4_224(Cube *c) { R(c); F2(c); U(c); Li(c); B(c); }
void eo4_225(Cube *c) { Ri(c); Ui(c); Li(c); F(c); }
void eo4_226(Cube *c) { Li(c); Ui(c); Ri(c); B(c); }
void eo4_227(Cube *c) { U(c); R(c); Fi(c); U2(c); Li(c); F(c); }
void eo4_228(Cube *c) { R(c); U(c); L(c); B(c); }
void eo4_229(Cube *c) { U(c); R(c); Di(c); Ri(c); F(c); }
void eo4_230(Cube *c) { U(c); L(c); D(c); L(c); F(c); }
void eo4_231(Cube *c) { U(c); F(c); }
void eo4_232(Cube *c) { U(c); B2(c); Di(c); F(c); }
void eo4_233(Cube *c) { U(c); D2(c); F(c); }
void eo4_234(Cube *c) { U(c); D(c); F(c); }
void eo4_235(Cube *c) { Ui(c); L(c); Di(c); Li(c); B(c); }
void eo4_236(Cube *c) { U(c); R2(c); F(c); }
void eo4_237(Cube *c) { U(c); R(c); Di(c); F(c); }
void eo4_238(Cube *c) { Ui(c); L2(c); B(c); }
void eo4_239(Cube *c) { U(c); D(c); R2(c); F(c); }
void eo4_240(Cube *c) { U(c); F2(c); L2(c); F(c); }
void eo4_241(Cube *c) { U(c); Fi(c); Di(c); L2(c); F(c); }
void eo4_242(Cube *c) { Ui(c); F2(c); R2(c); B(c); }
void eo4_243(Cube *c) { U(c); D(c); F2(c); L2(c); F(c); }
void eo4_244(Cube *c) { U(c); R(c); F(c); }
void eo4_245(Cube *c) { Ri(c); F2(c); D2(c); F(c); }
void eo4_246(Cube *c) { U(c); D(c); R(c); F(c); }
void eo4_247(Cube *c) { U(c); R(c); D2(c); F(c); }
void eo4_248(Cube *c) { U(c); R(c); D(c); F(c); }
void eo4_249(Cube *c) { U(c); D2(c); R(c); F(c); }
void eo4_250(Cube *c) { Ui(c); R(c); D(c); R(c); B(c); }
void eo4_251(Cube *c) { U(c); F2(c); R2(c); F(c); }
void eo4_252(Cube *c) { U(c); F(c); Di(c); R2(c); F(c); }
void eo4_253(Cube *c) { Ui(c); F2(c); L2(c); B(c); }
void eo4_254(Cube *c) { U(c); D(c); F2(c); R2(c); F(c); }
void eo4_255(Cube *c) { U(c); L2(c); F(c); }
void eo4_256(Cube *c) { U(c); L2(c); Di(c); F(c); }
void eo4_257(Cube *c) { Ui(c); R2(c); B(c); }
void eo4_258(Cube *c) { U(c); D(c); L2(c); F(c); }
void eo4_259(Cube *c) { U(c); F2(c); R(c); F(c); }
void eo4_260(Cube *c) { F2(c); D2(c); Ri(c); F(c); }
void eo4_261(Cube *c) { U(c); Li(c); F(c); }
void eo4_262(Cube *c) { U(c); D2(c); Li(c); F(c); }
void eo4_263(Cube *c) { U(c); Li(c); Di(c); F(c); }
void eo4_264(Cube *c) { U(c); D(c); Li(c); F(c); }
void eo4_265(Cube *c) { Ui(c); D2(c); B(c); }
void eo4_266(Cube *c) { U(c); D(c); U2(c); B(c); }
void eo4_267(Cube *c) { Ui(c); B(c); }
void eo4_268(Cube *c) { Ui(c); Di(c); B(c); }
void eo4_269(Cube *c) { Ui(c); D2(c); L(c); B(c); }
void eo4_270(Cube *c) { F2(c); U2(c); Li(c); B(c); }
void eo4_271(Cube *c) { U(c); R2(c); Li(c); F(c); }
void eo4_272(Cube *c) { Ui(c); B2(c); Ri(c); B(c); }
void eo4_273(Cube *c) { Ui(c); L(c); D(c); B(c); }
void eo4_274(Cube *c) { Ui(c); L(c); B(c); }
void eo4_275(Cube *c) { U(c); R(c); L2(c); F(c); }
void eo4_276(Cube *c) { R(c); F2(c); U2(c); B(c); }
void eo4_277(Cube *c) { Ui(c); D2(c); Ri(c); B(c); }
void eo4_278(Cube *c) { Ui(c); Ri(c); B(c); }
void eo4_279(Cube *c) { Ui(c); Ri(c); Di(c); B(c); }
void eo4_280(Cube *c) { Ui(c); Di(c); Ri(c); B(c); }
void eo4_281(Cube *c) { D(c); L(c); Ui(c); Ri(c); B(c); }
void eo4_282(Cube *c) { Li(c); U(c); R(c); F(c); }
void eo4_283(Cube *c) { D(c); Li(c); U(c); R(c); F(c); }
void eo4_284(Cube *c) { L(c); Ui(c); Ri(c); B(c); }
void eo4_285(Cube *c) { L(c); D(c); F(c); }
void eo4_286(Cube *c) { U(c); L2(c); Di(c); B(c); }
void eo4_287(Cube *c) { Fi(c); L2(c); D(c); F(c); }
void eo4_288(Cube *c) { Ui(c); Ri(c); F(c); }
void eo4_289(Cube *c) { Ui(c); Di(c); Ri(c); F(c); }
void eo4_290(Cube *c) { Ui(c); D2(c); Ri(c); F(c); }
void eo4_291(Cube *c) { Ui(c); Ri(c); D(c); F(c); }
void eo4_292(Cube *c) { F2(c); Ui(c); R2(c); F(c); }
void eo4_293(Cube *c) { L2(c); D(c); F(c); }
void eo4_294(Cube *c) { L(c); F(c); }
void eo4_295(Cube *c) { Di(c); L(c); F(c); }
void eo4_296(Cube *c) { D2(c); L(c); F(c); }
void eo4_297(Cube *c) { D(c); L(c); F(c); }
void eo4_298(Cube *c) { U(c); Li(c); Di(c); B(c); }
void eo4_299(Cube *c) { R2(c); L(c); F(c); }
void eo4_300(Cube *c) { U(c); D(c); Li(c); B(c); }
void eo4_301(Cube *c) { U(c); Li(c); B(c); }
void eo4_302(Cube *c) { D(c); R2(c); L(c); F(c); }
void eo4_303(Cube *c) { Ui(c); Ri(c); L2(c); F(c); }
void eo4_304(Cube *c) { U2(c); D(c); R(c); B(c); }
void eo4_305(Cube *c) { U2(c); R(c); B(c); }
void eo4_306(Cube *c) { U2(c); Di(c); R(c); B(c); }
void eo4_307(Cube *c) { R(c); L(c); F(c); }
void eo4_308(Cube *c) { D(c); R(c); D(c); L(c); F(c); }
void eo4_309(Cube *c) { Ui(c); Ri(c); Li(c); F(c); }
void eo4_310(Cube *c) { U(c); Ri(c); Li(c); B(c); }
void eo4_311(Cube *c) { R(c); D(c); L(c); F(c); }
void eo4_312(Cube *c) { U2(c); R(c); L(c); B(c); }
void eo4_313(Cube *c) { R(c); Di(c); Ri(c); F(c); }
void eo4_314(Cube *c) { L(c); D(c); L(c); F(c); }
void eo4_315(Cube *c) { F(c); }
void eo4_316(Cube *c) { Di(c); F(c); }
void eo4_317(Cube *c) { D2(c); F(c); }
void eo4_318(Cube *c) { D(c); F(c); }
void eo4_319(Cube *c) { U2(c); L(c); Di(c); Li(c); B(c); }
void eo4_320(Cube *c) { R2(c); F(c); }
void eo4_321(Cube *c) { Di(c); R2(c); F(c); }
void eo4_322(Cube *c) { U2(c); L2(c); B(c); }
void eo4_323(Cube *c) { D(c); R2(c); F(c); }
void eo4_324(Cube *c) { F2(c); L2(c); F(c); }
void eo4_325(Cube *c) { Di(c); F2(c); L2(c); F(c); }
void eo4_326(Cube *c) { U2(c); F2(c); R2(c); B(c); }
void eo4_327(Cube *c) { D(c); F2(c); L2(c); F(c); }
void eo4_328(Cube *c) { R(c); F(c); }
void eo4_329(Cube *c) { D(c); R(c); D(c); F(c); }
void eo4_330(Cube *c) { D(c); R(c); F(c); }
void eo4_331(Cube *c) { Di(c); R(c); F(c); }
void eo4_332(Cube *c) { R(c); D(c); F(c); }
void eo4_333(Cube *c) { D2(c); R(c); F(c); }
void eo4_334(Cube *c) { U2(c); R(c); D(c); R(c); B(c); }
void eo4_335(Cube *c) { F2(c); R2(c); F(c); }
void eo4_336(Cube *c) { Di(c); F2(c); R2(c); F(c); }
void eo4_337(Cube *c) { U2(c); F2(c); L2(c); B(c); }
void eo4_338(Cube *c) { D(c); F2(c); R2(c); F(c); }
void eo4_339(Cube *c) { L2(c); F(c); }
void eo4_340(Cube *c) { Di(c); L2(c); F(c); }
void eo4_341(Cube *c) { U2(c); R2(c); B(c); }
void eo4_342(Cube *c) { D(c); L2(c); F(c); }
void eo4_343(Cube *c) { Di(c); Li(c); F(c); }
void eo4_344(Cube *c) { D(c); Li(c); Di(c); F(c); }
void eo4_345(Cube *c) { Li(c); F(c); }
void eo4_346(Cube *c) { D2(c); Li(c); F(c); }
void eo4_347(Cube *c) { Li(c); Di(c); F(c); }
void eo4_348(Cube *c) { D(c); Li(c); F(c); }
void eo4_349(Cube *c) { U(c); D2(c); U(c); B(c); }
void eo4_350(Cube *c) { U2(c); D(c); B(c); }
void eo4_351(Cube *c) { U2(c); B(c); }
void eo4_352(Cube *c) { U2(c); Di(c); B(c); }
void eo4_353(Cube *c) { Di(c); R2(c); Li(c); F(c); }
void eo4_354(Cube *c) { U(c); Li(c); F2(c); U2(c); B(c); }
void eo4_355(Cube *c) { R2(c); Li(c); F(c); }
void eo4_356(Cube *c) { U2(c); D(c); L(c); B(c); }
void eo4_357(Cube *c) { U2(c); L(c); D(c); B(c); }
void eo4_358(Cube *c) { U2(c); L(c); B(c); }
void eo4_359(Cube *c) { R(c); L2(c); F(c); }
void eo4_360(Cube *c) { U(c); F2(c); U2(c); R(c); B(c); }
void eo4_361(Cube *c) { D(c); R(c); L2(c); F(c); }
void eo4_362(Cube *c) { U2(c); Ri(c); B(c); }
void eo4_363(Cube *c) { U2(c); Ri(c); Di(c); B(c); }
void eo4_364(Cube *c) { U2(c); Di(c); Ri(c); B(c); }
void eo4_365(Cube *c) { D(c); R(c); D(c); Li(c); F(c); }
void eo4_366(Cube *c) { R(c); B2(c); Li(c); F(c); }
void eo4_367(Cube *c) { D(c); R(c); B2(c); Li(c); F(c); }
void eo4_368(Cube *c) { R(c); D(c); Li(c); F(c); }
void eo4_369(Cube *c) { Ui(c); R(c); Di(c); Ri(c); F(c); }
void eo4_370(Cube *c) { Ui(c); L(c); D(c); L(c); F(c); }
void eo4_371(Cube *c) { Ui(c); F(c); }
void eo4_372(Cube *c) { Ui(c); Di(c); F(c); }
void eo4_373(Cube *c) { Ui(c); D2(c); F(c); }
void eo4_374(Cube *c) { U(c); D(c); U2(c); F(c); }
void eo4_375(Cube *c) { U(c); L(c); Di(c); Li(c); B(c); }
void eo4_376(Cube *c) { Ui(c); R2(c); F(c); }
void eo4_377(Cube *c) { U(c); D(c); L2(c); B(c); }
void eo4_378(Cube *c) { U(c); L2(c); B(c); }
void eo4_379(Cube *c) { U(c); L(c); Di(c); B(c); }
void eo4_380(Cube *c) { Ui(c); F2(c); L2(c); F(c); }
void eo4_381(Cube *c) { U(c); D(c); F2(c); R2(c); B(c); }
void eo4_382(Cube *c) { U(c); F2(c); R2(c); B(c); }
void eo4_383(Cube *c) { U(c); F2(c); Di(c); R2(c); B(c); }
void eo4_384(Cube *c) { Ui(c); R(c); F(c); }
void eo4_385(Cube *c) { F2(c); D2(c); L(c); F(c); }
void eo4_386(Cube *c) { Ui(c); F2(c); Li(c); F(c); }
void eo4_387(Cube *c) { U(c); Ri(c); L2(c); B(c); }
void eo4_388(Cube *c) { Ui(c); R(c); D(c); F(c); }
void eo4_389(Cube *c) { Ui(c); D2(c); R(c); F(c); }
void eo4_390(Cube *c) { U(c); R(c); D(c); R(c); B(c); }
void eo4_391(Cube *c) { Ui(c); F2(c); R2(c); F(c); }
void eo4_392(Cube *c) { U(c); D(c); F2(c); L2(c); B(c); }
void eo4_393(Cube *c) { U(c); F2(c); L2(c); B(c); }
void eo4_394(Cube *c) { U(c); F2(c); Di(c); L2(c); B(c); }
void eo4_395(Cube *c) { Ui(c); L2(c); F(c); }
void eo4_396(Cube *c) { U(c); D(c); R2(c); B(c); }
void eo4_397(Cube *c) { U(c); R2(c); B(c); }
void eo4_398(Cube *c) { U(c); R2(c); Di(c); B(c); }
void eo4_399(Cube *c) { Ui(c); Di(c); Li(c); F(c); }
void eo4_400(Cube *c) { L(c); F2(c); D2(c); F(c); }
void eo4_401(Cube *c) { Ui(c); Li(c); F(c); }
void eo4_402(Cube *c) { Ui(c); D2(c); Li(c); F(c); }
void eo4_403(Cube *c) { Ui(c); Li(c); Di(c); F(c); }
void eo4_404(Cube *c) { U(c); R2(c); L(c); B(c); }
void eo4_405(Cube *c) { U(c); D2(c); B(c); }
void eo4_406(Cube *c) { U(c); D(c); B(c); }
void eo4_407(Cube *c) { U(c); B(c); }
void eo4_408(Cube *c) { U(c); F2(c); Di(c); B(c); }
void eo4_409(Cube *c) { U(c); D2(c); L(c); B(c); }
void eo4_410(Cube *c) { Li(c); F2(c); U2(c); B(c); }
void eo4_411(Cube *c) { U(c); L(c); D2(c); B(c); }
void eo4_412(Cube *c) { U(c); D(c); L(c); B(c); }
void eo4_413(Cube *c) { U(c); L(c); D(c); B(c); }
void eo4_414(Cube *c) { U(c); L(c); B(c); }
void eo4_415(Cube *c) { U(c); D(c); Ri(c); B(c); }
void eo4_416(Cube *c) { F2(c); U2(c); R(c); B(c); }
void eo4_417(Cube *c) { U(c); D2(c); Ri(c); B(c); }
void eo4_418(Cube *c) { U(c); Ri(c); B(c); }
void eo4_419(Cube *c) { U(c); Ri(c); Di(c); B(c); }
void eo4_420(Cube *c) { U(c); B2(c); L(c); B(c); }
void eo4_421(Cube *c) { D(c); Ri(c); U(c); L(c); B(c); }
void eo4_422(Cube *c) { R(c); Ui(c); Li(c); F(c); }
void eo4_423(Cube *c) { D(c); R(c); Ui(c); Li(c); F(c); }
void eo4_424(Cube *c) { Ri(c); U(c); L(c); B(c); }
void eo4_425(Cube *c) { R(c); U(c); Fi(c); Di(c); L2(c); F(c); }
void eo4_426(Cube *c) { R(c); U(c); R(c); F(c); }
void eo4_427(Cube *c) { Di(c); R(c); U(c); R(c); F(c); }
void eo4_428(Cube *c) { D2(c); R(c); U(c); R(c); F(c); }
void eo4_429(Cube *c) { D(c); R(c); U(c); R(c); F(c); }
void eo4_430(Cube *c) { L(c); Ui(c); Li(c); F(c); }
void eo4_431(Cube *c) { Di(c); L(c); Ui(c); Li(c); F(c); }
void eo4_432(Cube *c) { D2(c); L(c); Ui(c); Li(c); F(c); }
void eo4_433(Cube *c) { D(c); L(c); Ui(c); Li(c); F(c); }
void eo4_434(Cube *c) { R(c); U(c); F(c); }
void eo4_435(Cube *c) { F2(c); D2(c); F(c); }
void eo4_436(Cube *c) { Li(c); Ui(c); F(c); }
void eo4_437(Cube *c) { Di(c); R(c); U(c); F(c); }
void eo4_438(Cube *c) { D(c); F2(c); D2(c); F(c); }
void eo4_439(Cube *c) { D(c); Li(c); Ui(c); F(c); }
void eo4_440(Cube *c) { D2(c); L(c); U(c); L(c); B(c); }
void eo4_441(Cube *c) { D(c); L(c); U(c); L(c); B(c); }
void eo4_442(Cube *c) { L(c); U(c); L(c); B(c); }
void eo4_443(Cube *c) { Di(c); L(c); U(c); L(c); B(c); }
void eo4_444(Cube *c) { R2(c); U(c); F(c); }
void eo4_445(Cube *c) { R2(c); F2(c); D2(c); F(c); }
void eo4_446(Cube *c) { D(c); R2(c); U(c); F(c); }
void eo4_447(Cube *c) { D(c); L2(c); U(c); B(c); }
void eo4_448(Cube *c) { R2(c); U(c); D(c); F(c); }
void eo4_449(Cube *c) { L2(c); U(c); B(c); }
void eo4_450(Cube *c) { F2(c); Di(c); L2(c); F(c); }
void eo4_451(Cube *c) { F2(c); U2(c); R2(c); B(c); }
void eo4_452(Cube *c) { F(c); L2(c); Ui(c); F(c); }
void eo4_453(Cube *c) { F2(c); R2(c); Ui(c); B(c); }
void eo4_454(Cube *c) { D(c); F2(c); U2(c); R2(c); B(c); }
void eo4_455(Cube *c) { Bi(c); L2(c); U(c); B(c); }
void eo4_456(Cube *c) { R(c); F2(c); D2(c); F(c); }
void eo4_457(Cube *c) { R(c); F2(c); D(c); F(c); }
void eo4_458(Cube *c) { Fi(c); D2(c); R(c); F(c); }
void eo4_459(Cube *c) { Ri(c); L2(c); U(c); B(c); }
void eo4_460(Cube *c) { D2(c); R(c); Ui(c); Ri(c); B(c); }
void eo4_461(Cube *c) { D(c); R(c); Ui(c); Ri(c); B(c); }
void eo4_462(Cube *c) { R(c); Ui(c); Ri(c); B(c); }
void eo4_463(Cube *c) { Di(c); R(c); Ui(c); Ri(c); B(c); }
void eo4_464(Cube *c) { Fi(c); R2(c); U(c); F(c); }
void eo4_465(Cube *c) { F2(c); U2(c); L2(c); B(c); }
void eo4_466(Cube *c) { F2(c); D(c); R2(c); F(c); }
void eo4_467(Cube *c) { B(c); R2(c); Ui(c); B(c); }
void eo4_468(Cube *c) { D(c); F2(c); U2(c); L2(c); B(c); }
void eo4_469(Cube *c) { F2(c); L2(c); U(c); B(c); }
void eo4_470(Cube *c) { D(c); R2(c); Ui(c); B(c); }
void eo4_471(Cube *c) { R2(c); F2(c); U2(c); B(c); }
void eo4_472(Cube *c) { L2(c); Ui(c); F(c); }
void eo4_473(Cube *c) { R2(c); Ui(c); B(c); }
void eo4_474(Cube *c) { R2(c); Ui(c); Di(c); B(c); }
void eo4_475(Cube *c) { D(c); L2(c); Ui(c); F(c); }
void eo4_476(Cube *c) { F(c); D2(c); Li(c); F(c); }
void eo4_477(Cube *c) { R(c); U(c); Li(c); F(c); }
void eo4_478(Cube *c) { Li(c); F2(c); D2(c); F(c); }
void eo4_479(Cube *c) { R2(c); Ui(c); L(c); B(c); }
void eo4_480(Cube *c) { D(c); Ri(c); Ui(c); B(c); }
void eo4_481(Cube *c) { F2(c); U2(c); B(c); }
void eo4_482(Cube *c) { Di(c); L(c); U(c); B(c); }
void eo4_483(Cube *c) { Ri(c); Ui(c); B(c); }
void eo4_484(Cube *c) { D(c); F2(c); U2(c); B(c); }
void eo4_485(Cube *c) { L(c); U(c); B(c); }
void eo4_486(Cube *c) { Bi(c); D2(c); L(c); B(c); }
void eo4_487(Cube *c) { R2(c); U(c); Li(c); F(c); }
void eo4_488(Cube *c) { L(c); F2(c); U2(c); B(c); }
void eo4_489(Cube *c) { Ri(c); Ui(c); L(c); B(c); }
void eo4_490(Cube *c) { Ri(c); F2(c); U2(c); B(c); }
void eo4_491(Cube *c) { R(c); L2(c); Ui(c); F(c); }
void eo4_492(Cube *c) { B(c); D2(c); Ri(c); B(c); }
void eo4_493(Cube *c) { Ri(c); B2(c); Di(c); B(c); }
void eo4_494(Cube *c) { R(c); F(c); D(c); Li(c); F(c); }
static void (*const eo4_moves[495])(Cube*) = {eo4_0, eo4_1, eo4_2, eo4_3, eo4_4, eo4_5, eo4_6, eo4_7, eo4_8, eo4_9, eo4_10, eo4_11, eo4_12, eo4_13, eo4_14, eo4_15, eo4_16, eo4_17, eo4_18, eo4_19, eo4_20, eo4_21, eo4_22, eo4_23, eo4_24, eo4_25, eo4_26, eo4_27, eo4_28, eo4_29, eo4_30, eo4_31, eo4_32, eo4_33, eo4_34, eo4_35, eo4_36, eo4_37, eo4_38, eo4_39, eo4_40, eo4_41, eo4_42, eo4_43, eo4_44, eo4_45, eo4_46, eo4_47, eo4_48, eo4_49, eo4_50, eo4_51, eo4_52, eo4_53, eo4_54, eo4_55, eo4_56, eo4_57, eo4_58, eo4_59, eo4_60, eo4_61, eo4_62, eo4_63, eo4_64, eo4_65, eo4_66, eo4_67, eo4_68, eo4_69, eo4_70, eo4_71, eo4_72, eo4_73, eo4_74, eo4_75, eo4_76, eo4_77, eo4_78, eo4_79, eo4_80, eo4_81, eo4_82, eo4_83, eo4_84, eo4_85, eo4_86, eo4_87, eo4_88, eo4_89, eo4_90, eo4_91, eo4_92, eo4_93, eo4_94, eo4_95, eo4_96, eo4_97, eo4_98, eo4_99, eo4_100, eo4_101, eo4_102, eo4_103, eo4_104, eo4_105, eo4_106, eo4_107, eo4_108, eo4_109, eo4_110, eo4_111, eo4_112, eo4_113, eo4_114, eo4_115, eo4_116, eo4_117, eo4_118, eo4_119, eo4_120, eo4_121, eo4_122, eo4_123, eo4_124, eo4_125, eo4_126, eo4_127, eo4_128, eo4_129, eo4_130, eo4_131, eo4_132, eo4_133, eo4_134, eo4_135, eo4_136, eo4_137, eo4_138, eo4_139, eo4_140, eo4_141, eo4_142, eo4_143, eo4_144, eo4_145, eo4_146, eo4_147, eo4_148, eo4_149, eo4_150, eo4_151, eo4_152, eo4_153, eo4_154, eo4_155, eo4_156, eo4_157, eo4_158, eo4_159, eo4_160, eo4_161, eo4_162, eo4_163, eo4_164, eo4_165, eo4_166, eo4_167, eo4_168, eo4_169, eo4_170, eo4_171, eo4_172, eo4_173, eo4_174, eo4_175, eo4_176, eo4_177, eo4_178, eo4_179, eo4_180, eo4_181, eo4_182, eo4_183, eo4_184, eo4_185, eo4_186, eo4_187, eo4_188, eo4_189, eo4_190, eo4_191, eo4_192, eo4_193, eo4_194, eo4_195, eo4_196, eo4_197, eo4_198, eo4_199, eo4_200, eo4_201, eo4_202, eo4_203, eo4_204, eo4_205, eo4_206, eo4_207, eo4_208, eo4_209, eo4_210, eo4_211, eo4_212, eo4_213, eo4_214, eo4_215, eo4_216, eo4_217, eo4_218, eo4_219, eo4_220, eo4_221, eo4_222, eo4_223, eo4_224, eo4_225, eo4_226, eo4_227, eo4_228, eo4_229, eo4_230, eo4_231, eo4_232, eo4_233, eo4_234, eo4_235, eo4_236, eo4_237, eo4_238, eo4_239, eo4_240, eo4_241, eo4_242, eo4_243, eo4_244, eo4_245, eo4_246, eo4_247, eo4_248, eo4_249, eo4_250, eo4_251, eo4_252, eo4_253, eo4_254, eo4_255, eo4_256, eo4_257, eo4_258, eo4_259, eo4_260, eo4_261, eo4_262, eo4_263, eo4_264, eo4_265, eo4_266, eo4_267, eo4_268, eo4_269, eo4_270, eo4_271, eo4_272, eo4_273, eo4_274, eo4_275, eo4_276, eo4_277, eo4_278, eo4_279, eo4_280, eo4_281, eo4_282, eo4_283, eo4_284, eo4_285, eo4_286, eo4_287, eo4_288, eo4_289, eo4_290, eo4_291, eo4_292, eo4_293, eo4_294, eo4_295, eo4_296, eo4_297, eo4_298, eo4_299, eo4_300, eo4_301, eo4_302, eo4_303, eo4_304, eo4_305, eo4_306, eo4_307, eo4_308, eo4_309, eo4_310, eo4_311, eo4_312, eo4_313, eo4_314, eo4_315, eo4_316, eo4_317, eo4_318, eo4_319, eo4_320, eo4_321, eo4_322, eo4_323, eo4_324, eo4_325, eo4_326, eo4_327, eo4_328, eo4_329, eo4_330, eo4_331, eo4_332, eo4_333, eo4_334, eo4_335, eo4_336, eo4_337, eo4_338, eo4_339, eo4_340, eo4_341, eo4_342, eo4_343, eo4_344, eo4_345, eo4_346, eo4_347, eo4_348, eo4_349, eo4_350, eo4_351, eo4_352, eo4_353, eo4_354, eo4_355, eo4_356, eo4_357, eo4_358, eo4_359, eo4_360, eo4_361, eo4_362, eo4_363, eo4_364, eo4_365, eo4_366, eo4_367, eo4_368, eo4_369, eo4_370, eo4_371, eo4_372, eo4_373, eo4_374, eo4_375, eo4_376, eo4_377, eo4_378, eo4_379, eo4_380, eo4_381, eo4_382, eo4_383, eo4_384, eo4_385, eo4_386, eo4_387, eo4_388, eo4_389, eo4_390, eo4_391, eo4_392, eo4_393, eo4_394, eo4_395, eo4_396, eo4_397, eo4_398, eo4_399, eo4_400, eo4_401, eo4_402, eo4_403, eo4_404, eo4_405, eo4_406, eo4_407, eo4_408, eo4_409, eo4_410, eo4_411, eo4_412, eo4_413, eo4_414, eo4_415, eo4_416, eo4_417, eo4_418, eo4_419, eo4_420, eo4_421, eo4_422, eo4_423, eo4_424, eo4_425, eo4_426, eo4_427, eo4_428, eo4_429, eo4_430, eo4_431, eo4_432, eo4_433, eo4_434, eo4_435, eo4_436, eo4_437, eo4_438, eo4_439, eo4_440, eo4_441, eo4_442, eo4_443, eo4_444, eo4_445, eo4_446, eo4_447, eo4_448, eo4_449, eo4_450, eo4_451, eo4_452, eo4_453, eo4_454, eo4_455, eo4_456, eo4_457, eo4_458, eo4_459, eo4_460, eo4_461, eo4_462, eo4_463, eo4_464, eo4_465, eo4_466, eo4_467, eo4_468, eo4_469, eo4_470, eo4_471, eo4_472, eo4_473, eo4_474, eo4_475, eo4_476, eo4_477, eo4_478, eo4_479, eo4_480, eo4_481, eo4_482, eo4_483, eo4_484, eo4_485, eo4_486, eo4_487, eo4_488, eo4_489, eo4_490, eo4_491, eo4_492, eo4_493, eo4_494};


// EO_6
void eo6_0(Cube *c) { F(c); R(c); L2(c); Di(c); B(c); }
void eo6_1(Cube *c) { R(c); Di(c); F(c); D2(c); Li(c); B(c); }
void eo6_2(Cube *c) { R(c); U2(c); B(c); R2(c); Di(c); F(c); }
void eo6_3(Cube *c) { R(c); F(c); D2(c); Li(c); B(c); }
void eo6_4(Cube *c) { R(c); F(c); L2(c); Di(c); B(c); }
void eo6_5(Cube *c) { Ri(c); Fi(c); R2(c); Li(c); B(c); }
void eo6_6(Cube *c) { D(c); R(c); F(c); D2(c); Li(c); B(c); }
void eo6_7(Cube *c) { R2(c); D(c); L(c); B(c); D2(c); F(c); }
void eo6_8(Cube *c) { R(c); B(c); R2(c); Di(c); L(c); F(c); }
void eo6_9(Cube *c) { L(c); Fi(c); Bi(c); R(c); B(c); }
void eo6_10(Cube *c) { D(c); L(c); F(c); R(c); L2(c); B(c); }
void eo6_11(Cube *c) { L(c); F(c); R(c); L2(c); B(c); }
void eo6_12(Cube *c) { L(c); Fi(c); R2(c); D(c); B(c); }
void eo6_13(Cube *c) { B(c); R2(c); Di(c); L(c); F(c); }
void eo6_14(Cube *c) { Li(c); Bi(c); Ri(c); L2(c); F(c); }
void eo6_15(Cube *c) { D(c); L(c); B(c); D2(c); Ri(c); F(c); }
void eo6_16(Cube *c) { L(c); B(c); D2(c); Ri(c); F(c); }
void eo6_17(Cube *c) { L(c); B(c); R2(c); Di(c); F(c); }
void eo6_18(Cube *c) { R(c); B(c); R2(c); L(c); F(c); }
void eo6_19(Cube *c) { R(c); Bi(c); L2(c); D(c); F(c); }
void eo6_20(Cube *c) { R(c); Fi(c); Bi(c); L(c); F(c); }
void eo6_21(Cube *c) { Di(c); Ri(c); Bi(c); D2(c); L(c); F(c); }
void eo6_22(Cube *c) { R(c); Fi(c); D2(c); Li(c); B(c); }
void eo6_23(Cube *c) { R(c); Bi(c); Ui(c); Ri(c); L(c); F(c); }
void eo6_24(Cube *c) { R(c); L(c); F(c); D2(c); B(c); }
void eo6_25(Cube *c) { R(c); L(c); F(c); L2(c); B(c); }
void eo6_26(Cube *c) { R(c); D(c); Li(c); Fi(c); D2(c); Bi(c); }
void eo6_27(Cube *c) { R(c); Fi(c); L(c); F(c); B(c); }
void eo6_28(Cube *c) { U2(c); F(c); L2(c); Di(c); B(c); }
void eo6_29(Cube *c) { Fi(c); R2(c); D(c); B(c); }
void eo6_30(Cube *c) { Fi(c); Bi(c); R(c); B(c); }
void eo6_31(Cube *c) { D(c); F(c); R(c); L2(c); B(c); }
void eo6_32(Cube *c) { F(c); R(c); L2(c); B(c); }
void eo6_33(Cube *c) { D(c); Fi(c); Bi(c); R(c); B(c); }
void eo6_34(Cube *c) { B(c); R2(c); Di(c); F(c); }
void eo6_35(Cube *c) { U2(c); F(c); D2(c); Li(c); B(c); }
void eo6_36(Cube *c) { D(c); B(c); D2(c); Ri(c); F(c); }
void eo6_37(Cube *c) { B(c); D2(c); Ri(c); F(c); }
void eo6_38(Cube *c) { Di(c); B(c); D2(c); Ri(c); F(c); }
void eo6_39(Cube *c) { R(c); F(c); D2(c); B(c); }
void eo6_40(Cube *c) { D(c); Ri(c); Fi(c); R2(c); B(c); }
void eo6_41(Cube *c) { Ri(c); Fi(c); R2(c); B(c); }
void eo6_42(Cube *c) { D(c); R(c); F(c); D2(c); B(c); }
void eo6_43(Cube *c) { Bi(c); R(c); F(c); B(c); }
void eo6_44(Cube *c) { U(c); R(c); Fi(c); U(c); Li(c); B(c); }
void eo6_45(Cube *c) { D(c); Bi(c); R(c); F(c); B(c); }
void eo6_46(Cube *c) { R(c); F(c); L2(c); B(c); }
void eo6_47(Cube *c) { R(c); Di(c); F(c); L2(c); B(c); }
void eo6_48(Cube *c) { Di(c); R(c); F(c); L2(c); B(c); }
void eo6_49(Cube *c) { U2(c); Bi(c); L2(c); D(c); F(c); }
void eo6_50(Cube *c) { U2(c); Li(c); Fi(c); D2(c); B(c); }
void eo6_51(Cube *c) { U2(c); D(c); L(c); B(c); D2(c); F(c); }
void eo6_52(Cube *c) { U2(c); L(c); F(c); L2(c); B(c); }
void eo6_53(Cube *c) { U2(c); D(c); Li(c); Fi(c); D2(c); Bi(c); }
void eo6_54(Cube *c) { Fi(c); D2(c); R(c); B(c); }
void eo6_55(Cube *c) { Di(c); Fi(c); D2(c); R(c); B(c); }
void eo6_56(Cube *c) { U2(c); Bi(c); D2(c); L(c); F(c); }
void eo6_57(Cube *c) { D(c); Fi(c); D2(c); R(c); B(c); }
void eo6_58(Cube *c) { Ri(c); Fi(c); D2(c); L(c); B(c); }
void eo6_59(Cube *c) { U(c); L(c); B(c); F(c); R(c); B(c); }
void eo6_60(Cube *c) { U2(c); B(c); L(c); F(c); B(c); }
void eo6_61(Cube *c) { Ri(c); B(c); D2(c); Li(c); F(c); }
void eo6_62(Cube *c) { U2(c); L(c); D(c); Fi(c); R2(c); Bi(c); }
void eo6_63(Cube *c) { U2(c); L(c); Fi(c); R2(c); B(c); }
void eo6_64(Cube *c) { Bi(c); Ri(c); L2(c); F(c); }
void eo6_65(Cube *c) { D(c); F(c); B(c); Ri(c); F(c); }
void eo6_66(Cube *c) { F(c); B(c); Ri(c); F(c); }
void eo6_67(Cube *c) { D(c); Bi(c); Ri(c); L2(c); F(c); }
void eo6_68(Cube *c) { R(c); Fi(c); D2(c); L(c); B(c); }
void eo6_69(Cube *c) { U(c); L(c); Fi(c); U2(c); Li(c); B(c); }
void eo6_70(Cube *c) { U2(c); L(c); F(c); D2(c); B(c); }
void eo6_71(Cube *c) { R(c); B(c); D2(c); Li(c); F(c); }
void eo6_72(Cube *c) { U2(c); L(c); Di(c); F(c); D2(c); B(c); }
void eo6_73(Cube *c) { U2(c); Fi(c); L(c); F(c); B(c); }
void eo6_74(Cube *c) { R(c); Fi(c); D2(c); B(c); }
void eo6_75(Cube *c) { U(c); Ri(c); F(c); U2(c); R(c); B(c); }
void eo6_76(Cube *c) { D(c); R(c); Fi(c); D2(c); B(c); }
void eo6_77(Cube *c) { F(c); R(c); F(c); B(c); }
void eo6_78(Cube *c) { R(c); D(c); Fi(c); D2(c); B(c); }
void eo6_79(Cube *c) { Di(c); F(c); R(c); F(c); B(c); }
void eo6_80(Cube *c) { U(c); R(c); F(c); U(c); Li(c); B(c); }
void eo6_81(Cube *c) { R(c); L(c); Fi(c); D2(c); B(c); }
void eo6_82(Cube *c) { U(c); R(c); L(c); Fi(c); U2(c); Bi(c); }
void eo6_83(Cube *c) { R(c); B(c); D(c); Li(c); F(c); }
void eo6_84(Cube *c) { Ui(c); F(c); L2(c); Di(c); B(c); }
void eo6_85(Cube *c) { U(c); Fi(c); R2(c); D(c); B(c); }
void eo6_86(Cube *c) { U(c); Fi(c); Bi(c); R(c); B(c); }
void eo6_87(Cube *c) { U(c); D(c); F(c); R(c); L2(c); B(c); }
void eo6_88(Cube *c) { U(c); F(c); R(c); L2(c); B(c); }
void eo6_89(Cube *c) { U(c); D(c); Bi(c); Fi(c); R(c); Bi(c); }
void eo6_90(Cube *c) { U(c); B(c); R2(c); Di(c); F(c); }
void eo6_91(Cube *c) { Ui(c); F(c); D2(c); Li(c); B(c); }
void eo6_92(Cube *c) { U(c); D(c); B(c); D2(c); Ri(c); F(c); }
void eo6_93(Cube *c) { U(c); B(c); D2(c); Ri(c); F(c); }
void eo6_94(Cube *c) { Ui(c); L(c); D(c); F(c); D2(c); B(c); }
void eo6_95(Cube *c) { U(c); R(c); F(c); D2(c); B(c); }
void eo6_96(Cube *c) { U(c); D(c); Ri(c); Fi(c); R2(c); Bi(c); }
void eo6_97(Cube *c) { U(c); Ri(c); Fi(c); R2(c); B(c); }
void eo6_98(Cube *c) { U(c); D(c); R(c); F(c); D2(c); B(c); }
void eo6_99(Cube *c) { U(c); Bi(c); R(c); F(c); B(c); }
void eo6_100(Cube *c) { R(c); Bi(c); U2(c); Ri(c); F(c); }
void eo6_101(Cube *c) { U(c); D(c); Bi(c); R(c); F(c); B(c); }
void eo6_102(Cube *c) { U(c); R(c); F(c); L2(c); B(c); }
void eo6_103(Cube *c) { U(c); R(c); Di(c); B(c); D2(c); F(c); }
void eo6_104(Cube *c) { U(c); D2(c); Bi(c); R(c); F(c); B(c); }
void eo6_105(Cube *c) { Ui(c); Bi(c); L2(c); D(c); F(c); }
void eo6_106(Cube *c) { Ui(c); Li(c); Fi(c); D2(c); B(c); }
void eo6_107(Cube *c) { Ui(c); Di(c); Li(c); Fi(c); D2(c); Bi(c); }
void eo6_108(Cube *c) { Ui(c); L(c); F(c); L2(c); B(c); }
void eo6_109(Cube *c) { Ui(c); Di(c); L(c); B(c); D2(c); F(c); }
void eo6_110(Cube *c) { U(c); Fi(c); D2(c); R(c); B(c); }
void eo6_111(Cube *c) { U(c); Ri(c); Di(c); Fi(c); D2(c); Bi(c); }
void eo6_112(Cube *c) { Ui(c); Bi(c); D2(c); L(c); F(c); }
void eo6_113(Cube *c) { U(c); D(c); Fi(c); D2(c); R(c); B(c); }
void eo6_114(Cube *c) { U(c); Ri(c); Fi(c); D2(c); L(c); B(c); }
void eo6_115(Cube *c) { L(c); Fi(c); R(c); L2(c); B(c); }
void eo6_116(Cube *c) { Ui(c); B(c); L(c); F(c); B(c); }
void eo6_117(Cube *c) { U(c); Ri(c); B(c); D2(c); Li(c); F(c); }
void eo6_118(Cube *c) { Ui(c); L(c); D(c); Fi(c); R2(c); Bi(c); }
void eo6_119(Cube *c) { Ui(c); L(c); Fi(c); R2(c); B(c); }
void eo6_120(Cube *c) { U(c); Bi(c); Ri(c); L2(c); F(c); }
void eo6_121(Cube *c) { B(c); D(c); Li(c); Ui(c); B(c); }
void eo6_122(Cube *c) { U(c); F(c); B(c); Ri(c); F(c); }
void eo6_123(Cube *c) { B(c); Di(c); Li(c); Ui(c); B(c); }
void eo6_124(Cube *c) { U(c); R(c); Fi(c); D2(c); L(c); B(c); }
void eo6_125(Cube *c) { L(c); Bi(c); U(c); Ri(c); F(c); }
void eo6_126(Cube *c) { Ui(c); L(c); F(c); D2(c); B(c); }
void eo6_127(Cube *c) { B(c); Li(c); Ui(c); Ri(c); B(c); }
void eo6_128(Cube *c) { Ui(c); L(c); Di(c); F(c); D2(c); B(c); }
void eo6_129(Cube *c) { Ui(c); Fi(c); L(c); F(c); B(c); }
void eo6_130(Cube *c) { U(c); R(c); Fi(c); D2(c); B(c); }
void eo6_131(Cube *c) { R(c); F(c); B(c); L(c); F(c); }
void eo6_132(Cube *c) { U(c); D(c); R(c); Fi(c); D2(c); Bi(c); }
void eo6_133(Cube *c) { U(c); F(c); R(c); F(c); B(c); }
void eo6_134(Cube *c) { U(c); R(c); D(c); Fi(c); D2(c); Bi(c); }
void eo6_135(Cube *c) { B(c); R(c); Di(c); Li(c); B(c); }
void eo6_136(Cube *c) { R(c); L(c); Fi(c); L2(c); B(c); }
void eo6_137(Cube *c) { U(c); R(c); L(c); Fi(c); D2(c); Bi(c); }
void eo6_138(Cube *c) { R(c); F(c); L(c); F(c); B(c); }
void eo6_139(Cube *c) { U(c); R(c); B(c); D(c); Li(c); F(c); }
void eo6_140(Cube *c) { U(c); Fi(c); R(c); Ui(c); D(c); B(c); }
void eo6_141(Cube *c) { U(c); F(c); B(c); Ui(c); B(c); }
void eo6_142(Cube *c) { D(c); B(c); U(c); D2(c); F(c); }
void eo6_143(Cube *c) { B(c); U(c); D2(c); F(c); }
void eo6_144(Cube *c) { Di(c); B(c); U(c); D2(c); F(c); }
void eo6_145(Cube *c) { F(c); R2(c); D(c); B(c); }
void eo6_146(Cube *c) { D(c); Bi(c); U(c); D2(c); F(c); }
void eo6_147(Cube *c) { Bi(c); U(c); D2(c); F(c); }
void eo6_148(Cube *c) { D(c); F(c); R2(c); D(c); B(c); }
void eo6_149(Cube *c) { Ri(c); Fi(c); D(c); L2(c); B(c); }
void eo6_150(Cube *c) { Fi(c); R(c); L2(c); B(c); }
void eo6_151(Cube *c) { F(c); U2(c); D(c); L(c); F(c); }
void eo6_152(Cube *c) { R(c); B(c); U(c); D2(c); F(c); }
void eo6_153(Cube *c) { D(c); Fi(c); R(c); L2(c); B(c); }
void eo6_154(Cube *c) { U(c); F(c); U(c); D2(c); R(c); F(c); }
void eo6_155(Cube *c) { B(c); U(c); R2(c); F(c); }
void eo6_156(Cube *c) { D(c); F(c); B(c); U(c); F(c); }
void eo6_157(Cube *c) { F(c); B(c); U(c); F(c); }
void eo6_158(Cube *c) { D(c); B(c); U(c); R2(c); F(c); }
void eo6_159(Cube *c) { R(c); Fi(c); D(c); L2(c); B(c); }
void eo6_160(Cube *c) { Bi(c); U(c); Ri(c); F(c); }
void eo6_161(Cube *c) { U(c); F(c); U(c); R2(c); Li(c); F(c); }
void eo6_162(Cube *c) { R(c); Bi(c); U2(c); Di(c); F(c); }
void eo6_163(Cube *c) { D(c); Bi(c); U(c); Ri(c); F(c); }
void eo6_164(Cube *c) { B(c); U(c); D2(c); R(c); F(c); }
void eo6_165(Cube *c) { U(c); F(c); U(c); R(c); L2(c); F(c); }
void eo6_166(Cube *c) { Ri(c); F(c); R2(c); B(c); }
void eo6_167(Cube *c) { Ri(c); F(c); Di(c); R2(c); B(c); }
void eo6_168(Cube *c) { F(c); R(c); B(c); U(c); F(c); }
void eo6_169(Cube *c) { D(c); Ri(c); F(c); R2(c); B(c); }
void eo6_170(Cube *c) { R(c); Fi(c); Bi(c); D(c); F(c); }
void eo6_171(Cube *c) { R(c); Fi(c); L2(c); B(c); }
void eo6_172(Cube *c) { D(c); R(c); Fi(c); L2(c); B(c); }
void eo6_173(Cube *c) { D2(c); R(c); Fi(c); L2(c); B(c); }
void eo6_174(Cube *c) { Di(c); R(c); Fi(c); L2(c); B(c); }
void eo6_175(Cube *c) { Bi(c); U(c); L2(c); F(c); }
void eo6_176(Cube *c) { D(c); Fi(c); Bi(c); U(c); F(c); }
void eo6_177(Cube *c) { Fi(c); Bi(c); U(c); F(c); }
void eo6_178(Cube *c) { D(c); Bi(c); U(c); L2(c); F(c); }
void eo6_179(Cube *c) { U(c); F(c); U2(c); D(c); Li(c); B(c); }
void eo6_180(Cube *c) { Bi(c); U2(c); L(c); F(c); }
void eo6_181(Cube *c) { L(c); Bi(c); U(c); L2(c); F(c); }
void eo6_182(Cube *c) { B(c); U(c); D2(c); Li(c); F(c); }
void eo6_183(Cube *c) { D(c); Bi(c); U2(c); L(c); F(c); }
void eo6_184(Cube *c) { L(c); Fi(c); Bi(c); U(c); F(c); }
void eo6_185(Cube *c) { R(c); Bi(c); U(c); L2(c); F(c); }
void eo6_186(Cube *c) { B(c); U2(c); L(c); F(c); }
void eo6_187(Cube *c) { U(c); F(c); Ui(c); Di(c); R(c); B(c); }
void eo6_188(Cube *c) { R(c); Fi(c); Bi(c); U(c); F(c); }
void eo6_189(Cube *c) { D(c); B(c); U2(c); L(c); F(c); }
void eo6_190(Cube *c) { B(c); U2(c); D(c); L(c); F(c); }
void eo6_191(Cube *c) { R(c); Bi(c); U2(c); L(c); F(c); }
void eo6_192(Cube *c) { U(c); F(c); Li(c); Di(c); Ri(c); F(c); }
void eo6_193(Cube *c) { Ui(c); L(c); F(c); R2(c); B(c); }
void eo6_194(Cube *c) { Ui(c); L(c); B(c); U2(c); Di(c); F(c); }
void eo6_195(Cube *c) { Ri(c); Bi(c); U(c); L2(c); F(c); }
void eo6_196(Cube *c) { Fi(c); Bi(c); Ri(c); F(c); }
void eo6_197(Cube *c) { B(c); U(c); R2(c); Li(c); F(c); }
void eo6_198(Cube *c) { R(c); F(c); B(c); Di(c); F(c); }
void eo6_199(Cube *c) { D(c); Fi(c); Bi(c); Ri(c); F(c); }
void eo6_200(Cube *c) { B(c); U(c); Fi(c); Li(c); F(c); }
void eo6_201(Cube *c) { Ri(c); Bi(c); U2(c); L(c); F(c); }
void eo6_202(Cube *c) { Ui(c); Di(c); F(c); L(c); F(c); B(c); }
void eo6_203(Cube *c) { Ui(c); F(c); L(c); F(c); B(c); }
void eo6_204(Cube *c) { B(c); L(c); Ui(c); Ri(c); B(c); }
void eo6_205(Cube *c) { Fi(c); R(c); F(c); B(c); }
void eo6_206(Cube *c) { D(c); Fi(c); R(c); F(c); B(c); }
void eo6_207(Cube *c) { D2(c); Fi(c); R(c); F(c); B(c); }
void eo6_208(Cube *c) { Di(c); Fi(c); R(c); F(c); B(c); }
void eo6_209(Cube *c) { R(c); Bi(c); U2(c); Li(c); F(c); }
void eo6_210(Cube *c) { F(c); L2(c); Di(c); B(c); }
void eo6_211(Cube *c) { U2(c); Fi(c); R2(c); D(c); B(c); }
void eo6_212(Cube *c) { F(c); B(c); Li(c); B(c); }
void eo6_213(Cube *c) { D(c); Fi(c); R2(c); Li(c); B(c); }
void eo6_214(Cube *c) { Fi(c); R2(c); Li(c); B(c); }
void eo6_215(Cube *c) { D(c); F(c); B(c); Li(c); B(c); }
void eo6_216(Cube *c) { U2(c); B(c); R2(c); Di(c); F(c); }
void eo6_217(Cube *c) { F(c); D2(c); Li(c); B(c); }
void eo6_218(Cube *c) { Di(c); F(c); D2(c); Li(c); B(c); }
void eo6_219(Cube *c) { U2(c); B(c); D2(c); Ri(c); F(c); }
void eo6_220(Cube *c) { D(c); F(c); D2(c); Li(c); B(c); }
void eo6_221(Cube *c) { U2(c); R(c); F(c); D2(c); B(c); }
void eo6_222(Cube *c) { U2(c); D(c); Ri(c); Fi(c); R2(c); Bi(c); }
void eo6_223(Cube *c) { U2(c); Ri(c); Fi(c); R2(c); B(c); }
void eo6_224(Cube *c) { U2(c); D(c); R(c); F(c); D2(c); B(c); }
void eo6_225(Cube *c) { U2(c); Bi(c); R(c); F(c); B(c); }
void eo6_226(Cube *c) { U(c); R(c); Bi(c); U2(c); Ri(c); F(c); }
void eo6_227(Cube *c) { L(c); F(c); D2(c); Ri(c); B(c); }
void eo6_228(Cube *c) { U2(c); R(c); F(c); L2(c); B(c); }
void eo6_229(Cube *c) { U2(c); R(c); Di(c); B(c); D2(c); F(c); }
void eo6_230(Cube *c) { L(c); Bi(c); D2(c); R(c); F(c); }
void eo6_231(Cube *c) { Bi(c); L2(c); D(c); F(c); }
void eo6_232(Cube *c) { Li(c); Fi(c); D2(c); B(c); }
void eo6_233(Cube *c) { D(c); L(c); F(c); L2(c); B(c); }
void eo6_234(Cube *c) { L(c); F(c); L2(c); B(c); }
void eo6_235(Cube *c) { D(c); Li(c); Fi(c); D2(c); B(c); }
void eo6_236(Cube *c) { U2(c); Fi(c); D2(c); R(c); B(c); }
void eo6_237(Cube *c) { D(c); Bi(c); D2(c); L(c); F(c); }
void eo6_238(Cube *c) { Bi(c); D2(c); L(c); F(c); }
void eo6_239(Cube *c) { Di(c); Bi(c); D2(c); L(c); F(c); }
void eo6_240(Cube *c) { Di(c); B(c); L(c); F(c); B(c); }
void eo6_241(Cube *c) { U(c); L(c); Fi(c); R(c); L2(c); B(c); }
void eo6_242(Cube *c) { B(c); L(c); F(c); B(c); }
void eo6_243(Cube *c) { D(c); L(c); Fi(c); R2(c); B(c); }
void eo6_244(Cube *c) { L(c); D(c); Fi(c); R2(c); B(c); }
void eo6_245(Cube *c) { L(c); Fi(c); R2(c); B(c); }
void eo6_246(Cube *c) { B(c); R2(c); L(c); F(c); }
void eo6_247(Cube *c) { D(c); Fi(c); Bi(c); L(c); F(c); }
void eo6_248(Cube *c) { Fi(c); Bi(c); L(c); F(c); }
void eo6_249(Cube *c) { D(c); B(c); R2(c); L(c); F(c); }
void eo6_250(Cube *c) { Di(c); L(c); F(c); D2(c); B(c); }
void eo6_251(Cube *c) { U(c); L(c); Bi(c); U(c); Ri(c); F(c); }
void eo6_252(Cube *c) { L(c); F(c); D2(c); B(c); }
void eo6_253(Cube *c) { D(c); Fi(c); L(c); F(c); B(c); }
void eo6_254(Cube *c) { L(c); Di(c); F(c); D2(c); B(c); }
void eo6_255(Cube *c) { Fi(c); L(c); F(c); B(c); }
void eo6_256(Cube *c) { U2(c); R(c); Fi(c); D2(c); B(c); }
void eo6_257(Cube *c) { U(c); Ri(c); B(c); Ui(c); L(c); F(c); }
void eo6_258(Cube *c) { Li(c); F(c); D2(c); Ri(c); B(c); }
void eo6_259(Cube *c) { U2(c); F(c); R(c); F(c); B(c); }
void eo6_260(Cube *c) { U2(c); R(c); D(c); Fi(c); D2(c); Bi(c); }
void eo6_261(Cube *c) { Li(c); Bi(c); D2(c); R(c); F(c); }
void eo6_262(Cube *c) { U(c); R(c); L(c); Fi(c); L2(c); Bi(c); }
void eo6_263(Cube *c) { R(c); B(c); L(c); F(c); B(c); }
void eo6_264(Cube *c) { U(c); R(c); F(c); L(c); F(c); B(c); }
void eo6_265(Cube *c) { R(c); L(c); Fi(c); R2(c); B(c); }
void eo6_266(Cube *c) { F(c); L(c); Di(c); Li(c); B(c); }
void eo6_267(Cube *c) { D2(c); F(c); L2(c); B(c); }
void eo6_268(Cube *c) { D(c); F(c); L2(c); B(c); }
void eo6_269(Cube *c) { F(c); L2(c); B(c); }
void eo6_270(Cube *c) { Di(c); F(c); L2(c); B(c); }
void eo6_271(Cube *c) { D2(c); Fi(c); R2(c); B(c); }
void eo6_272(Cube *c) { D(c); Fi(c); R2(c); B(c); }
void eo6_273(Cube *c) { Fi(c); R2(c); B(c); }
void eo6_274(Cube *c) { Di(c); Fi(c); R2(c); B(c); }
void eo6_275(Cube *c) { Fi(c); Bi(c); Ri(c); B(c); }
void eo6_276(Cube *c) { F(c); U(c); B(c); R(c); B(c); }
void eo6_277(Cube *c) { F(c); B(c); L(c); B(c); }
void eo6_278(Cube *c) { F(c); Ri(c); L2(c); B(c); }
void eo6_279(Cube *c) { F(c); U2(c); R(c); D(c); F(c); }
void eo6_280(Cube *c) { Fi(c); R2(c); L(c); B(c); }
void eo6_281(Cube *c) { F(c); D2(c); B(c); }
void eo6_282(Cube *c) { Di(c); F(c); D2(c); B(c); }
void eo6_283(Cube *c) { D2(c); F(c); D2(c); B(c); }
void eo6_284(Cube *c) { D(c); F(c); D2(c); B(c); }
void eo6_285(Cube *c) { F(c); D2(c); L(c); B(c); }
void eo6_286(Cube *c) { F(c); D(c); L(c); D(c); B(c); }
void eo6_287(Cube *c) { F(c); Di(c); L(c); B(c); }
void eo6_288(Cube *c) { B(c); Di(c); R(c); F(c); }
void eo6_289(Cube *c) { D(c); F(c); D(c); L(c); D(c); B(c); }
void eo6_290(Cube *c) { B(c); D2(c); R(c); F(c); }
void eo6_291(Cube *c) { Ri(c); F(c); D2(c); B(c); }
void eo6_292(Cube *c) { F(c); D(c); Ri(c); Di(c); B(c); }
void eo6_293(Cube *c) { F(c); D2(c); Ri(c); B(c); }
void eo6_294(Cube *c) { R(c); Fi(c); R2(c); B(c); }
void eo6_295(Cube *c) { R(c); Di(c); Fi(c); R2(c); B(c); }
void eo6_296(Cube *c) { Bi(c); D2(c); R(c); F(c); }
void eo6_297(Cube *c) { U(c); R(c); U(c); Fi(c); L2(c); Bi(c); }
void eo6_298(Cube *c) { R(c); F(c); B(c); L(c); B(c); }
void eo6_299(Cube *c) { U2(c); F(c); Di(c); Ri(c); L(c); B(c); }
void eo6_300(Cube *c) { R(c); Fi(c); R2(c); L(c); B(c); }
void eo6_301(Cube *c) { Fi(c); D2(c); B(c); }
void eo6_302(Cube *c) { Di(c); Fi(c); D2(c); B(c); }
void eo6_303(Cube *c) { D2(c); Fi(c); D2(c); B(c); }
void eo6_304(Cube *c) { D(c); Fi(c); D2(c); B(c); }
void eo6_305(Cube *c) { Fi(c); D2(c); L(c); B(c); }
void eo6_306(Cube *c) { F(c); U(c); Li(c); Ui(c); B(c); }
void eo6_307(Cube *c) { L(c); Fi(c); D2(c); B(c); }
void eo6_308(Cube *c) { B(c); D2(c); Li(c); F(c); }
void eo6_309(Cube *c) { L(c); Di(c); Fi(c); D2(c); B(c); }
void eo6_310(Cube *c) { Li(c); F(c); L2(c); B(c); }
void eo6_311(Cube *c) { Fi(c); D(c); Ri(c); B(c); }
void eo6_312(Cube *c) { F(c); U(c); R(c); U(c); B(c); }
void eo6_313(Cube *c) { Fi(c); D2(c); Ri(c); B(c); }
void eo6_314(Cube *c) { Bi(c); D2(c); Li(c); F(c); }
void eo6_315(Cube *c) { D(c); F(c); U(c); R(c); U(c); B(c); }
void eo6_316(Cube *c) { Bi(c); D(c); Li(c); F(c); }
void eo6_317(Cube *c) { U2(c); Fi(c); D(c); Ri(c); L(c); B(c); }
void eo6_318(Cube *c) { L(c); Fi(c); D(c); Ri(c); B(c); }
void eo6_319(Cube *c) { U(c); L(c); Ui(c); B(c); U2(c); F(c); }
void eo6_320(Cube *c) { L(c); Bi(c); D2(c); Li(c); F(c); }
void eo6_321(Cube *c) { Bi(c); R(c); L2(c); F(c); }
void eo6_322(Cube *c) { B(c); U(c); F(c); L(c); F(c); }
void eo6_323(Cube *c) { B(c); R2(c); Li(c); F(c); }
void eo6_324(Cube *c) { F(c); B(c); R(c); F(c); }
void eo6_325(Cube *c) { F(c); D(c); B(c); R(c); F(c); }
void eo6_326(Cube *c) { Fi(c); Bi(c); Li(c); F(c); }
void eo6_327(Cube *c) { U2(c); B(c); Di(c); R(c); Li(c); F(c); }
void eo6_328(Cube *c) { L(c); Bi(c); R(c); L2(c); F(c); }
void eo6_329(Cube *c) { U(c); L(c); U(c); Fi(c); U2(c); Bi(c); }
void eo6_330(Cube *c) { L(c); F(c); B(c); R(c); F(c); }
void eo6_331(Cube *c) { U(c); R(c); Ui(c); F(c); U2(c); B(c); }
void eo6_332(Cube *c) { R(c); Fi(c); D2(c); Ri(c); B(c); }
void eo6_333(Cube *c) { U2(c); Bi(c); D(c); R(c); Li(c); F(c); }
void eo6_334(Cube *c) { R(c); Bi(c); D(c); Li(c); F(c); }
void eo6_335(Cube *c) { R(c); Fi(c); Di(c); Ri(c); L(c); B(c); }
void eo6_336(Cube *c) { U(c); B(c); Ri(c); U(c); Di(c); F(c); }
void eo6_337(Cube *c) { Fi(c); L2(c); Di(c); B(c); }
void eo6_338(Cube *c) { D(c); B(c); Ui(c); D2(c); F(c); }
void eo6_339(Cube *c) { B(c); Ui(c); D2(c); F(c); }
void eo6_340(Cube *c) { D(c); Fi(c); L2(c); Di(c); B(c); }
void eo6_341(Cube *c) { U(c); F(c); R2(c); D(c); B(c); }
void eo6_342(Cube *c) { D(c); Bi(c); Ui(c); D2(c); F(c); }
void eo6_343(Cube *c) { Bi(c); Ui(c); D2(c); F(c); }
void eo6_344(Cube *c) { Di(c); Bi(c); Ui(c); D2(c); F(c); }
void eo6_345(Cube *c) { F(c); Ui(c); Di(c); L(c); F(c); }
void eo6_346(Cube *c) { F(c); R2(c); Li(c); B(c); }
void eo6_347(Cube *c) { L(c); F(c); Di(c); R2(c); B(c); }
void eo6_348(Cube *c) { U(c); R(c); B(c); U(c); D2(c); F(c); }
void eo6_349(Cube *c) { D(c); F(c); R2(c); Li(c); B(c); }
void eo6_350(Cube *c) { L(c); B(c); U2(c); D(c); F(c); }
void eo6_351(Cube *c) { B(c); Ui(c); R2(c); F(c); }
void eo6_352(Cube *c) { D(c); F(c); B(c); Ui(c); F(c); }
void eo6_353(Cube *c) { F(c); B(c); Ui(c); F(c); }
void eo6_354(Cube *c) { D(c); B(c); Ui(c); R2(c); F(c); }
void eo6_355(Cube *c) { U(c); R(c); Fi(c); D(c); L2(c); B(c); }
void eo6_356(Cube *c) { Bi(c); U2(c); Ri(c); F(c); }
void eo6_357(Cube *c) { Li(c); B(c); Ui(c); R2(c); F(c); }
void eo6_358(Cube *c) { B(c); U(c); Ri(c); L2(c); B(c); }
void eo6_359(Cube *c) { D(c); Bi(c); U2(c); Ri(c); F(c); }
void eo6_360(Cube *c) { L(c); Fi(c); Bi(c); D(c); F(c); }
void eo6_361(Cube *c) { Ri(c); B(c); Ui(c); R2(c); F(c); }
void eo6_362(Cube *c) { B(c); U2(c); Ri(c); F(c); }
void eo6_363(Cube *c) { U(c); Ri(c); F(c); Di(c); R2(c); B(c); }
void eo6_364(Cube *c) { R(c); Bi(c); Ui(c); D2(c); F(c); }
void eo6_365(Cube *c) { D(c); B(c); U2(c); Ri(c); F(c); }
void eo6_366(Cube *c) { B(c); U2(c); D(c); Ri(c); F(c); }
void eo6_367(Cube *c) { U(c); R(c); Fi(c); L2(c); B(c); }
void eo6_368(Cube *c) { U(c); D(c); R(c); Fi(c); L2(c); Bi(c); }
void eo6_369(Cube *c) { Li(c); B(c); U2(c); Ri(c); F(c); }
void eo6_370(Cube *c) { U2(c); Di(c); B(c); R(c); F(c); B(c); }
void eo6_371(Cube *c) { Bi(c); Ui(c); L2(c); F(c); }
void eo6_372(Cube *c) { D(c); Fi(c); Bi(c); Ui(c); F(c); }
void eo6_373(Cube *c) { Fi(c); Bi(c); Ui(c); F(c); }
void eo6_374(Cube *c) { D(c); Bi(c); Ui(c); L2(c); F(c); }
void eo6_375(Cube *c) { L(c); Fi(c); D(c); L2(c); B(c); }
void eo6_376(Cube *c) { L(c); Fi(c); L2(c); B(c); }
void eo6_377(Cube *c) { U(c); L(c); Bi(c); U(c); L2(c); F(c); }
void eo6_378(Cube *c) { L(c); Bi(c); U2(c); Di(c); F(c); }
void eo6_379(Cube *c) { D(c); L(c); Fi(c); L2(c); B(c); }
void eo6_380(Cube *c) { F(c); L(c); B(c); D(c); F(c); }
void eo6_381(Cube *c) { U(c); R(c); Bi(c); U(c); L2(c); F(c); }
void eo6_382(Cube *c) { B(c); Ui(c); L(c); F(c); }
void eo6_383(Cube *c) { Li(c); F(c); Di(c); R2(c); B(c); }
void eo6_384(Cube *c) { B(c); Ui(c); Di(c); L(c); F(c); }
void eo6_385(Cube *c) { D(c); B(c); Ui(c); L(c); F(c); }
void eo6_386(Cube *c) { L(c); Bi(c); Ui(c); D2(c); F(c); }
void eo6_387(Cube *c) { D2(c); L(c); F(c); R2(c); B(c); }
void eo6_388(Cube *c) { Di(c); L(c); F(c); R2(c); B(c); }
void eo6_389(Cube *c) { L(c); F(c); R2(c); B(c); }
void eo6_390(Cube *c) { D(c); L(c); F(c); R2(c); B(c); }
void eo6_391(Cube *c) { B(c); U(c); D2(c); L(c); B(c); }
void eo6_392(Cube *c) { F(c); B(c); L(c); F(c); }
void eo6_393(Cube *c) { L(c); B(c); Ui(c); R2(c); F(c); }
void eo6_394(Cube *c) { B(c); U(c); Bi(c); Ri(c); B(c); }
void eo6_395(Cube *c) { D(c); F(c); B(c); L(c); F(c); }
void eo6_396(Cube *c) { L(c); F(c); B(c); Ui(c); F(c); }
void eo6_397(Cube *c) { D2(c); F(c); L(c); F(c); B(c); }
void eo6_398(Cube *c) { Di(c); F(c); L(c); F(c); B(c); }
void eo6_399(Cube *c) { F(c); L(c); F(c); B(c); }
void eo6_400(Cube *c) { D(c); F(c); L(c); F(c); B(c); }
void eo6_401(Cube *c) { U(c); Fi(c); R(c); F(c); B(c); }
void eo6_402(Cube *c) { U(c); D(c); Fi(c); R(c); F(c); B(c); }
void eo6_403(Cube *c) { L(c); B(c); U2(c); Ri(c); F(c); }
void eo6_404(Cube *c) { B(c); Ri(c); Di(c); Li(c); B(c); }
void eo6_405(Cube *c) { R(c); L(c); F(c); R2(c); B(c); }
void eo6_406(Cube *c) { F(c); R(c); D(c); R(c); B(c); }
void eo6_407(Cube *c) { U2(c); Fi(c); Ri(c); Ui(c); D(c); B(c); }
void eo6_408(Cube *c) { B(c); R(c); F(c); U(c); F(c); }
void eo6_409(Cube *c) { U2(c); F(c); L(c); U(c); Di(c); B(c); }
void eo6_410(Cube *c) { Fi(c); D(c); L2(c); B(c); }
void eo6_411(Cube *c) { Fi(c); L2(c); B(c); }
void eo6_412(Cube *c) { Fi(c); Di(c); L2(c); B(c); }
void eo6_413(Cube *c) { Bi(c); U2(c); Di(c); F(c); }
void eo6_414(Cube *c) { D(c); Fi(c); L2(c); B(c); }
void eo6_415(Cube *c) { Bi(c); U2(c); D(c); F(c); }
void eo6_416(Cube *c) { F(c); D(c); R2(c); B(c); }
void eo6_417(Cube *c) { F(c); R2(c); B(c); }
void eo6_418(Cube *c) { F(c); Di(c); R2(c); B(c); }
void eo6_419(Cube *c) { B(c); U2(c); Di(c); F(c); }
void eo6_420(Cube *c) { D(c); F(c); R2(c); B(c); }
void eo6_421(Cube *c) { B(c); U2(c); D(c); F(c); }
void eo6_422(Cube *c) { Fi(c); Ri(c); L2(c); B(c); }
void eo6_423(Cube *c) { D(c); Fi(c); Ri(c); L2(c); B(c); }
void eo6_424(Cube *c) { F(c); R2(c); L(c); B(c); }
void eo6_425(Cube *c) { D(c); F(c); R2(c); L(c); B(c); }
void eo6_426(Cube *c) { B(c); R2(c); U(c); F(c); }
void eo6_427(Cube *c) { U2(c); Fi(c); U2(c); B(c); }
void eo6_428(Cube *c) { U2(c); Fi(c); U2(c); Di(c); B(c); }
void eo6_429(Cube *c) { Fi(c); Bi(c); Di(c); F(c); }
void eo6_430(Cube *c) { Fi(c); D(c); F(c); B(c); }
void eo6_431(Cube *c) { Fi(c); Bi(c); D(c); F(c); }
void eo6_432(Cube *c) { Bi(c); U2(c); R(c); F(c); }
void eo6_433(Cube *c) { D(c); Bi(c); U2(c); R(c); F(c); }
void eo6_434(Cube *c) { U2(c); Fi(c); U2(c); L(c); B(c); }
void eo6_435(Cube *c) { Di(c); Bi(c); U2(c); R(c); F(c); }
void eo6_436(Cube *c) { R(c); F(c); R2(c); B(c); }
void eo6_437(Cube *c) { D(c); R(c); F(c); R2(c); B(c); }
void eo6_438(Cube *c) { D2(c); R(c); F(c); R2(c); B(c); }
void eo6_439(Cube *c) { Di(c); R(c); F(c); R2(c); B(c); }
void eo6_440(Cube *c) { R(c); F(c); R2(c); L(c); B(c); }
void eo6_441(Cube *c) { U2(c); F(c); U2(c); D(c); B(c); }
void eo6_442(Cube *c) { U2(c); F(c); U2(c); B(c); }
void eo6_443(Cube *c) { Bi(c); L2(c); Ui(c); F(c); }
void eo6_444(Cube *c) { F(c); B(c); Di(c); F(c); }
void eo6_445(Cube *c) { F(c); D(c); F(c); B(c); }
void eo6_446(Cube *c) { F(c); B(c); D(c); F(c); }
void eo6_447(Cube *c) { D2(c); Li(c); Fi(c); L2(c); B(c); }
void eo6_448(Cube *c) { Di(c); Li(c); Fi(c); L2(c); B(c); }
void eo6_449(Cube *c) { Li(c); Fi(c); L2(c); B(c); }
void eo6_450(Cube *c) { D(c); Li(c); Fi(c); L2(c); B(c); }
void eo6_451(Cube *c) { U2(c); F(c); U2(c); Ri(c); B(c); }
void eo6_452(Cube *c) { Di(c); B(c); U2(c); Li(c); F(c); }
void eo6_453(Cube *c) { B(c); U2(c); Li(c); F(c); }
void eo6_454(Cube *c) { D(c); B(c); U2(c); Li(c); F(c); }
void eo6_455(Cube *c) { Li(c); Fi(c); Ri(c); L2(c); B(c); }
void eo6_456(Cube *c) { Fi(c); Bi(c); R(c); F(c); }
void eo6_457(Cube *c) { D(c); Fi(c); Bi(c); R(c); F(c); }
void eo6_458(Cube *c) { F(c); B(c); Li(c); F(c); }
void eo6_459(Cube *c) { D(c); F(c); B(c); Li(c); F(c); }
void eo6_460(Cube *c) { L(c); Fi(c); Bi(c); R(c); F(c); }
void eo6_461(Cube *c) { R(c); B(c); U2(c); Li(c); F(c); }
void eo6_462(Cube *c) { U(c); F(c); L2(c); Di(c); B(c); }
void eo6_463(Cube *c) { Ui(c); Fi(c); R2(c); D(c); B(c); }
void eo6_464(Cube *c) { U(c); F(c); B(c); Li(c); B(c); }
void eo6_465(Cube *c) { F(c); Di(c); Ri(c); Ui(c); F(c); }
void eo6_466(Cube *c) { U(c); Fi(c); R2(c); Li(c); B(c); }
void eo6_467(Cube *c) { F(c); D(c); Ri(c); Ui(c); F(c); }
void eo6_468(Cube *c) { Ui(c); B(c); R2(c); Di(c); F(c); }
void eo6_469(Cube *c) { U(c); F(c); D2(c); Li(c); B(c); }
void eo6_470(Cube *c) { Ui(c); R(c); D(c); B(c); D2(c); F(c); }
void eo6_471(Cube *c) { Ui(c); B(c); D2(c); Ri(c); F(c); }
void eo6_472(Cube *c) { U(c); D(c); F(c); D2(c); Li(c); B(c); }
void eo6_473(Cube *c) { Ui(c); R(c); F(c); D2(c); B(c); }
void eo6_474(Cube *c) { Ui(c); Di(c); R(c); F(c); D2(c); B(c); }
void eo6_475(Cube *c) { Ui(c); Ri(c); Fi(c); R2(c); B(c); }
void eo6_476(Cube *c) { Ui(c); Di(c); Ri(c); Fi(c); R2(c); Bi(c); }
void eo6_477(Cube *c) { Ui(c); Bi(c); R(c); F(c); B(c); }
void eo6_478(Cube *c) { R(c); Fi(c); U(c); Li(c); B(c); }
void eo6_479(Cube *c) { F(c); Ri(c); Ui(c); Li(c); F(c); }
void eo6_480(Cube *c) { Ui(c); R(c); F(c); L2(c); B(c); }
void eo6_481(Cube *c) { Ui(c); R(c); Di(c); B(c); D2(c); F(c); }
void eo6_482(Cube *c) { U(c); L(c); Bi(c); D2(c); R(c); F(c); }
void eo6_483(Cube *c) { U(c); Bi(c); L2(c); D(c); F(c); }
void eo6_484(Cube *c) { U(c); Li(c); Fi(c); D2(c); B(c); }
void eo6_485(Cube *c) { U(c); D(c); L(c); B(c); D2(c); F(c); }
void eo6_486(Cube *c) { U(c); L(c); F(c); L2(c); B(c); }
void eo6_487(Cube *c) { U(c); D(c); Li(c); Fi(c); D2(c); Bi(c); }
void eo6_488(Cube *c) { Ui(c); Fi(c); D2(c); R(c); B(c); }
void eo6_489(Cube *c) { U(c); D(c); Bi(c); D2(c); L(c); F(c); }
void eo6_490(Cube *c) { U(c); Bi(c); D2(c); L(c); F(c); }
void eo6_491(Cube *c) { U(c); Li(c); Di(c); Fi(c); R2(c); Bi(c); }
void eo6_492(Cube *c) { F(c); L(c); Di(c); Ri(c); F(c); }
void eo6_493(Cube *c) { L(c); F(c); B(c); R(c); B(c); }
void eo6_494(Cube *c) { U(c); B(c); L(c); F(c); B(c); }
void eo6_495(Cube *c) { U(c); D(c); L(c); Fi(c); R2(c); Bi(c); }
void eo6_496(Cube *c) { U(c); L(c); D(c); Fi(c); R2(c); Bi(c); }
void eo6_497(Cube *c) { U(c); L(c); Fi(c); R2(c); B(c); }
void eo6_498(Cube *c) { U(c); B(c); R2(c); L(c); F(c); }
void eo6_499(Cube *c) { U(c); B(c); U(c); D(c); Li(c); B(c); }
void eo6_500(Cube *c) { U(c); Fi(c); Bi(c); L(c); F(c); }
void eo6_501(Cube *c) { U(c); Li(c); D(c); F(c); D2(c); B(c); }
void eo6_502(Cube *c) { U(c); D2(c); Fi(c); L(c); F(c); B(c); }
void eo6_503(Cube *c) { L(c); Fi(c); U2(c); Li(c); B(c); }
void eo6_504(Cube *c) { U(c); L(c); F(c); D2(c); B(c); }
void eo6_505(Cube *c) { U(c); D(c); Fi(c); L(c); F(c); B(c); }
void eo6_506(Cube *c) { U(c); L(c); Di(c); F(c); D2(c); B(c); }
void eo6_507(Cube *c) { U(c); Fi(c); L(c); F(c); B(c); }
void eo6_508(Cube *c) { Ui(c); R(c); Fi(c); D2(c); B(c); }
void eo6_509(Cube *c) { R(c); Bi(c); R2(c); L(c); F(c); }
void eo6_510(Cube *c) { U(c); Li(c); F(c); D2(c); Ri(c); B(c); }
void eo6_511(Cube *c) { Ui(c); F(c); R(c); F(c); B(c); }
void eo6_512(Cube *c) { Ui(c); R(c); D(c); Fi(c); D2(c); Bi(c); }
void eo6_513(Cube *c) { U(c); Li(c); Bi(c); D2(c); R(c); F(c); }
void eo6_514(Cube *c) { R(c); F(c); U(c); Li(c); B(c); }
void eo6_515(Cube *c) { U(c); R(c); B(c); L(c); F(c); B(c); }
void eo6_516(Cube *c) { R(c); L(c); Fi(c); U2(c); B(c); }
void eo6_517(Cube *c) { U(c); R(c); L(c); Fi(c); R2(c); Bi(c); }
void eo6_518(Cube *c) { U(c); F(c); Li(c); U(c); Di(c); B(c); }
void eo6_519(Cube *c) { F(c); B(c); Ui(c); B(c); }
void eo6_520(Cube *c) { D(c); F(c); Ui(c); L2(c); B(c); }
void eo6_521(Cube *c) { F(c); Ui(c); L2(c); B(c); }
void eo6_522(Cube *c) { D(c); F(c); B(c); Ui(c); B(c); }
void eo6_523(Cube *c) { Fi(c); Bi(c); Ui(c); B(c); }
void eo6_524(Cube *c) { D(c); Fi(c); Ui(c); R2(c); B(c); }
void eo6_525(Cube *c) { Fi(c); Ui(c); R2(c); B(c); }
void eo6_526(Cube *c) { D(c); Fi(c); Bi(c); Ui(c); B(c); }
void eo6_527(Cube *c) { R(c); F(c); B(c); Ui(c); B(c); }
void eo6_528(Cube *c) { F(c); B(c); R(c); B(c); }
void eo6_529(Cube *c) { F(c); U(c); Fi(c); Li(c); F(c); }
void eo6_530(Cube *c) { R(c); F(c); Ui(c); L2(c); B(c); }
void eo6_531(Cube *c) { D(c); F(c); B(c); R(c); B(c); }
void eo6_532(Cube *c) { F(c); U(c); D2(c); R(c); F(c); }
void eo6_533(Cube *c) { F(c); Ui(c); D2(c); B(c); }
void eo6_534(Cube *c) { D(c); Bi(c); R2(c); Di(c); F(c); }
void eo6_535(Cube *c) { Bi(c); R2(c); Di(c); F(c); }
void eo6_536(Cube *c) { D(c); F(c); Ui(c); D2(c); B(c); }
void eo6_537(Cube *c) { R(c); Fi(c); Bi(c); D(c); B(c); }
void eo6_538(Cube *c) { Fi(c); U2(c); Li(c); B(c); }
void eo6_539(Cube *c) { F(c); U(c); R2(c); Li(c); F(c); }
void eo6_540(Cube *c) { Ri(c); F(c); Ui(c); L2(c); B(c); }
void eo6_541(Cube *c) { D(c); Fi(c); U2(c); Li(c); B(c); }
void eo6_542(Cube *c) { U(c); L(c); Bi(c); D(c); R2(c); F(c); }
void eo6_543(Cube *c) { F(c); U(c); R(c); L2(c); F(c); }
void eo6_544(Cube *c) { R(c); Fi(c); U2(c); B(c); }
void eo6_545(Cube *c) { R(c); Fi(c); U2(c); Di(c); B(c); }
void eo6_546(Cube *c) { U(c); R(c); Fi(c); U(c); R2(c); B(c); }
void eo6_547(Cube *c) { D(c); R(c); Fi(c); U2(c); B(c); }
void eo6_548(Cube *c) { R(c); Bi(c); D(c); R2(c); F(c); }
void eo6_549(Cube *c) { B(c); R(c); F(c); B(c); }
void eo6_550(Cube *c) { D(c); B(c); R(c); F(c); B(c); }
void eo6_551(Cube *c) { D2(c); B(c); R(c); F(c); B(c); }
void eo6_552(Cube *c) { Di(c); B(c); R(c); F(c); B(c); }
void eo6_553(Cube *c) { Fi(c); Ui(c); D2(c); B(c); }
void eo6_554(Cube *c) { Di(c); Fi(c); Ui(c); D2(c); B(c); }
void eo6_555(Cube *c) { U(c); B(c); L2(c); D(c); F(c); }
void eo6_556(Cube *c) { D(c); Fi(c); Ui(c); D2(c); B(c); }
void eo6_557(Cube *c) { F(c); U2(c); D(c); Li(c); B(c); }
void eo6_558(Cube *c) { F(c); U2(c); Li(c); B(c); }
void eo6_559(Cube *c) { L(c); Fi(c); Ui(c); D2(c); B(c); }
void eo6_560(Cube *c) { U(c); Li(c); B(c); Di(c); L2(c); F(c); }
void eo6_561(Cube *c) { D(c); F(c); U2(c); Li(c); B(c); }
void eo6_562(Cube *c) { Li(c); F(c); Ui(c); L2(c); B(c); }
void eo6_563(Cube *c) { R(c); Fi(c); Ui(c); D2(c); B(c); }
void eo6_564(Cube *c) { F(c); Ui(c); R(c); B(c); }
void eo6_565(Cube *c) { F(c); Ui(c); Di(c); R(c); B(c); }
void eo6_566(Cube *c) { Ri(c); B(c); Di(c); L2(c); F(c); }
void eo6_567(Cube *c) { D(c); F(c); Ui(c); R(c); B(c); }
void eo6_568(Cube *c) { U(c); L(c); Fi(c); U(c); R2(c); B(c); }
void eo6_569(Cube *c) { R(c); F(c); U2(c); Li(c); B(c); }
void eo6_570(Cube *c) { F(c); Li(c); Di(c); Ri(c); F(c); }
void eo6_571(Cube *c) { U(c); Bi(c); L(c); F(c); B(c); }
void eo6_572(Cube *c) { U(c); D(c); Bi(c); L(c); F(c); B(c); }
void eo6_573(Cube *c) { R(c); F(c); U2(c); D(c); B(c); }
void eo6_574(Cube *c) { B(c); Ri(c); L2(c); F(c); }
void eo6_575(Cube *c) { U(c); L(c); F(c); U(c); D2(c); B(c); }
void eo6_576(Cube *c) { R(c); B(c); Di(c); L2(c); F(c); }
void eo6_577(Cube *c) { D(c); B(c); Ri(c); L2(c); F(c); }
void eo6_578(Cube *c) { B(c); Ui(c); Di(c); R(c); B(c); }
void eo6_579(Cube *c) { Ri(c); F(c); U2(c); Li(c); B(c); }
void eo6_580(Cube *c) { U2(c); Di(c); F(c); L(c); F(c); B(c); }
void eo6_581(Cube *c) { U(c); L(c); Fi(c); U2(c); B(c); }
void eo6_582(Cube *c) { U(c); D(c); L(c); Fi(c); U2(c); Bi(c); }
void eo6_583(Cube *c) { R(c); F(c); U2(c); B(c); }
void eo6_584(Cube *c) { D(c); R(c); F(c); U2(c); B(c); }
void eo6_585(Cube *c) { D2(c); R(c); F(c); U2(c); B(c); }
void eo6_586(Cube *c) { Di(c); R(c); F(c); U2(c); B(c); }
void eo6_587(Cube *c) { R(c); L(c); F(c); U2(c); B(c); }
void eo6_588(Cube *c) { U(c); F(c); L(c); Di(c); Li(c); B(c); }
void eo6_589(Cube *c) { B(c); U(c); F(c); B(c); }
void eo6_590(Cube *c) { U(c); D(c); F(c); L2(c); B(c); }
void eo6_591(Cube *c) { U(c); F(c); L2(c); B(c); }
void eo6_592(Cube *c) { U(c); F(c); Di(c); L2(c); B(c); }
void eo6_593(Cube *c) { Bi(c); U(c); F(c); B(c); }
void eo6_594(Cube *c) { U(c); D(c); Fi(c); R2(c); B(c); }
void eo6_595(Cube *c) { U(c); Fi(c); R2(c); B(c); }
void eo6_596(Cube *c) { U(c); Fi(c); Di(c); R2(c); B(c); }
void eo6_597(Cube *c) { U(c); Fi(c); Bi(c); Ri(c); B(c); }
void eo6_598(Cube *c) { F(c); D2(c); L(c); U(c); F(c); }
void eo6_599(Cube *c) { U(c); F(c); B(c); L(c); B(c); }
void eo6_600(Cube *c) { U(c); F(c); Ri(c); L2(c); B(c); }
void eo6_601(Cube *c) { U(c); F(c); Ri(c); Di(c); L2(c); B(c); }
void eo6_602(Cube *c) { U(c); Fi(c); R2(c); L(c); B(c); }
void eo6_603(Cube *c) { U(c); F(c); D2(c); B(c); }
void eo6_604(Cube *c) { U(c); B(c); Di(c); R2(c); F(c); }
void eo6_605(Cube *c) { F(c); U(c); F(c); B(c); }
void eo6_606(Cube *c) { U(c); D(c); F(c); D2(c); B(c); }
void eo6_607(Cube *c) { U(c); F(c); D2(c); L(c); B(c); }
void eo6_608(Cube *c) { U(c); F(c); D(c); L(c); D(c); B(c); }
void eo6_609(Cube *c) { U(c); F(c); Di(c); L(c); B(c); }
void eo6_610(Cube *c) { U(c); B(c); Di(c); R(c); F(c); }
void eo6_611(Cube *c) { R(c); U(c); D(c); Fi(c); L2(c); Bi(c); }
void eo6_612(Cube *c) { U(c); B(c); D2(c); R(c); F(c); }
void eo6_613(Cube *c) { U(c); Ri(c); F(c); D2(c); B(c); }
void eo6_614(Cube *c) { R(c); Ui(c); Fi(c); U2(c); B(c); }
void eo6_615(Cube *c) { U(c); F(c); D2(c); Ri(c); B(c); }
void eo6_616(Cube *c) { U(c); R(c); Fi(c); R2(c); B(c); }
void eo6_617(Cube *c) { U(c); R(c); Di(c); Fi(c); R2(c); Bi(c); }
void eo6_618(Cube *c) { U(c); Bi(c); D2(c); R(c); F(c); }
void eo6_619(Cube *c) { R(c); U(c); Fi(c); L2(c); B(c); }
void eo6_620(Cube *c) { U(c); Ri(c); F(c); Di(c); L(c); B(c); }
void eo6_621(Cube *c) { U(c); F(c); Di(c); Ri(c); L(c); B(c); }
void eo6_622(Cube *c) { U(c); Ri(c); B(c); D2(c); R(c); F(c); }
void eo6_623(Cube *c) { U(c); Fi(c); D2(c); B(c); }
void eo6_624(Cube *c) { U(c); Bi(c); Di(c); L2(c); F(c); }
void eo6_625(Cube *c) { Fi(c); U(c); F(c); B(c); }
void eo6_626(Cube *c) { U(c); D(c); Fi(c); D2(c); B(c); }
void eo6_627(Cube *c) { U(c); Fi(c); D2(c); L(c); B(c); }
void eo6_628(Cube *c) { L(c); Ui(c); Fi(c); L2(c); B(c); }
void eo6_629(Cube *c) { U(c); L(c); Fi(c); D2(c); B(c); }
void eo6_630(Cube *c) { U(c); B(c); D2(c); Li(c); F(c); }
void eo6_631(Cube *c) { U(c); L(c); Di(c); Fi(c); D2(c); Bi(c); }
void eo6_632(Cube *c) { U(c); Li(c); F(c); L2(c); B(c); }
void eo6_633(Cube *c) { U(c); Fi(c); D(c); Ri(c); B(c); }
void eo6_634(Cube *c) { U(c); F(c); U(c); R(c); U(c); B(c); }
void eo6_635(Cube *c) { U(c); Fi(c); D2(c); Ri(c); B(c); }
void eo6_636(Cube *c) { U(c); Bi(c); D2(c); Li(c); F(c); }
void eo6_637(Cube *c) { R(c); U(c); D(c); Fi(c); D2(c); Bi(c); }
void eo6_638(Cube *c) { U(c); Bi(c); D(c); Li(c); F(c); }
void eo6_639(Cube *c) { U(c); Fi(c); D(c); Ri(c); L(c); B(c); }
void eo6_640(Cube *c) { U(c); L(c); Fi(c); D(c); Ri(c); B(c); }
void eo6_641(Cube *c) { L(c); Ui(c); F(c); R2(c); B(c); }
void eo6_642(Cube *c) { U(c); L(c); Bi(c); D2(c); Li(c); F(c); }
void eo6_643(Cube *c) { U(c); Bi(c); R(c); L2(c); F(c); }
void eo6_644(Cube *c) { F(c); U(c); B(c); L(c); F(c); }
void eo6_645(Cube *c) { U(c); B(c); R2(c); Li(c); F(c); }
void eo6_646(Cube *c) { U(c); F(c); B(c); R(c); F(c); }
void eo6_647(Cube *c) { U(c); F(c); D(c); B(c); R(c); F(c); }
void eo6_648(Cube *c) { U(c); Fi(c); Bi(c); Li(c); F(c); }
void eo6_649(Cube *c) { U(c); B(c); Di(c); R(c); Li(c); F(c); }
void eo6_650(Cube *c) { U(c); L(c); Bi(c); R(c); L2(c); F(c); }
void eo6_651(Cube *c) { L(c); U(c); Fi(c); U2(c); B(c); }
void eo6_652(Cube *c) { U(c); L(c); F(c); B(c); R(c); F(c); }
void eo6_653(Cube *c) { R(c); Ui(c); F(c); U2(c); B(c); }
void eo6_654(Cube *c) { U(c); R(c); Fi(c); D2(c); Ri(c); B(c); }
void eo6_655(Cube *c) { U(c); Bi(c); D(c); R(c); Li(c); F(c); }
void eo6_656(Cube *c) { U(c); R(c); Bi(c); D(c); Li(c); F(c); }
void eo6_657(Cube *c) { R(c); U(c); Li(c); Fi(c); L2(c); Bi(c); }
void eo6_658(Cube *c) { Ui(c); F(c); R(c); D(c); R(c); B(c); }
void eo6_659(Cube *c) { U(c); Fi(c); Ri(c); Ui(c); D(c); B(c); }
void eo6_660(Cube *c) { U(c); F(c); L(c); U(c); L(c); B(c); }
void eo6_661(Cube *c) { U(c); F(c); L(c); U(c); Di(c); B(c); }
void eo6_662(Cube *c) { U(c); Fi(c); Bi(c); D(c); B(c); }
void eo6_663(Cube *c) { Ui(c); Fi(c); L2(c); B(c); }
void eo6_664(Cube *c) { U(c); Fi(c); Bi(c); Di(c); B(c); }
void eo6_665(Cube *c) { Ui(c); Bi(c); U2(c); Di(c); F(c); }
void eo6_666(Cube *c) { U(c); Bi(c); D(c); F(c); B(c); }
void eo6_667(Cube *c) { U(c); F(c); L2(c); U(c); B(c); }
void eo6_668(Cube *c) { U(c); F(c); B(c); D(c); B(c); }
void eo6_669(Cube *c) { Ui(c); F(c); R2(c); B(c); }
void eo6_670(Cube *c) { U(c); F(c); B(c); Di(c); B(c); }
void eo6_671(Cube *c) { U(c); Fi(c); R2(c); Ui(c); B(c); }
void eo6_672(Cube *c) { U(c); B(c); D(c); F(c); B(c); }
void eo6_673(Cube *c) { Ui(c); B(c); U2(c); D(c); F(c); }
void eo6_674(Cube *c) { U(c); F(c); B(c); Ri(c); B(c); }
void eo6_675(Cube *c) { F(c); U(c); Li(c); Di(c); F(c); }
void eo6_676(Cube *c) { U(c); Fi(c); Bi(c); L(c); B(c); }
void eo6_677(Cube *c) { U(c); F(c); Ri(c); L2(c); U(c); B(c); }
void eo6_678(Cube *c) { U(c); Fi(c); U2(c); D(c); B(c); }
void eo6_679(Cube *c) { U(c); Fi(c); U2(c); B(c); }
void eo6_680(Cube *c) { U(c); Fi(c); U2(c); Di(c); B(c); }
void eo6_681(Cube *c) { U(c); Bi(c); Di(c); R2(c); F(c); }
void eo6_682(Cube *c) { U(c); D(c); Fi(c); U2(c); B(c); }
void eo6_683(Cube *c) { U(c); Bi(c); D(c); R2(c); F(c); }
void eo6_684(Cube *c) { Ui(c); Bi(c); U2(c); R(c); F(c); }
void eo6_685(Cube *c) { U(c); F(c); R2(c); U(c); Li(c); F(c); }
void eo6_686(Cube *c) { U(c); Fi(c); U2(c); L(c); B(c); }
void eo6_687(Cube *c) { U(c); D(c); Fi(c); U2(c); L(c); B(c); }
void eo6_688(Cube *c) { U(c); Ri(c); Fi(c); U2(c); B(c); }
void eo6_689(Cube *c) { U(c); D(c); Ri(c); Fi(c); U2(c); Bi(c); }
void eo6_690(Cube *c) { U(c); D2(c); Ri(c); Fi(c); U2(c); Bi(c); }
void eo6_691(Cube *c) { U(c); Ri(c); Bi(c); D(c); R2(c); F(c); }
void eo6_692(Cube *c) { R(c); Fi(c); L2(c); U(c); B(c); }
void eo6_693(Cube *c) { U(c); F(c); U2(c); D(c); B(c); }
void eo6_694(Cube *c) { U(c); F(c); U2(c); B(c); }
void eo6_695(Cube *c) { U(c); F(c); U2(c); Di(c); B(c); }
void eo6_696(Cube *c) { U(c); B(c); Di(c); L2(c); F(c); }
void eo6_697(Cube *c) { U(c); D(c); F(c); U2(c); B(c); }
void eo6_698(Cube *c) { U(c); B(c); D(c); L2(c); F(c); }
void eo6_699(Cube *c) { U(c); D2(c); L(c); F(c); U2(c); B(c); }
void eo6_700(Cube *c) { U(c); Li(c); Bi(c); Fi(c); D(c); Bi(c); }
void eo6_701(Cube *c) { U(c); L(c); F(c); U2(c); B(c); }
void eo6_702(Cube *c) { U(c); D(c); L(c); F(c); U2(c); B(c); }
void eo6_703(Cube *c) { U(c); F(c); U2(c); Ri(c); B(c); }
void eo6_704(Cube *c) { U(c); D(c); F(c); U2(c); Ri(c); B(c); }
void eo6_705(Cube *c) { Ui(c); B(c); U2(c); Li(c); F(c); }
void eo6_706(Cube *c) { Ui(c); F(c); Di(c); F(c); Ri(c); B(c); }
void eo6_707(Cube *c) { U(c); L(c); F(c); U2(c); Ri(c); B(c); }
void eo6_708(Cube *c) { U(c); B(c); R(c); L2(c); F(c); }
void eo6_709(Cube *c) { U(c); D(c); B(c); R(c); L2(c); F(c); }
void eo6_710(Cube *c) { U(c); Bi(c); R2(c); Li(c); F(c); }
void eo6_711(Cube *c) { B(c); Ui(c); Ri(c); Di(c); B(c); }
void eo6_712(Cube *c) { U(c); L(c); B(c); R(c); L2(c); F(c); }
void eo6_713(Cube *c) { R(c); B(c); L2(c); Ui(c); F(c); }
void eo6_714(Cube *c) { U(c); Bi(c); L(c); Ui(c); D(c); F(c); }
void eo6_715(Cube *c) { F(c); B(c); U(c); B(c); }
void eo6_716(Cube *c) { D(c); F(c); U(c); L2(c); B(c); }
void eo6_717(Cube *c) { F(c); U(c); L2(c); B(c); }
void eo6_718(Cube *c) { D(c); F(c); B(c); U(c); B(c); }
void eo6_719(Cube *c) { Fi(c); Bi(c); U(c); B(c); }
void eo6_720(Cube *c) { D(c); Fi(c); U(c); R2(c); B(c); }
void eo6_721(Cube *c) { Fi(c); U(c); R2(c); B(c); }
void eo6_722(Cube *c) { D(c); Fi(c); Bi(c); U(c); B(c); }
void eo6_723(Cube *c) { F(c); U(c); Bi(c); Ri(c); B(c); }
void eo6_724(Cube *c) { Fi(c); Bi(c); Li(c); B(c); }
void eo6_725(Cube *c) { L(c); F(c); B(c); Di(c); B(c); }
void eo6_726(Cube *c) { F(c); U(c); Ri(c); L2(c); B(c); }
void eo6_727(Cube *c) { D(c); Fi(c); Bi(c); Li(c); B(c); }
void eo6_728(Cube *c) { Li(c); Fi(c); U(c); R2(c); B(c); }
void eo6_729(Cube *c) { F(c); U(c); D2(c); B(c); }
void eo6_730(Cube *c) { Di(c); F(c); U(c); D2(c); B(c); }
void eo6_731(Cube *c) { U(c); F(c); B(c); Ui(c); F(c); }
void eo6_732(Cube *c) { D(c); F(c); U(c); D2(c); B(c); }
void eo6_733(Cube *c) { F(c); U(c); D2(c); L(c); B(c); }
void eo6_734(Cube *c) { Fi(c); U(c); Li(c); B(c); }
void eo6_735(Cube *c) { L(c); Fi(c); U2(c); Di(c); B(c); }
void eo6_736(Cube *c) { U(c); B(c); U(c); Ri(c); L2(c); B(c); }
void eo6_737(Cube *c) { D(c); Fi(c); U(c); Li(c); B(c); }
void eo6_738(Cube *c) { L(c); Bi(c); D(c); R2(c); F(c); }
void eo6_739(Cube *c) { R(c); Fi(c); Bi(c); U(c); B(c); }
void eo6_740(Cube *c) { Fi(c); U2(c); R(c); B(c); }
void eo6_741(Cube *c) { F(c); U(c); D2(c); Ri(c); B(c); }
void eo6_742(Cube *c) { R(c); Fi(c); U(c); R2(c); B(c); }
void eo6_743(Cube *c) { D(c); Fi(c); U2(c); R(c); B(c); }
void eo6_744(Cube *c) { U(c); B(c); U2(c); D(c); Ri(c); F(c); }
void eo6_745(Cube *c) { Ui(c); B(c); R(c); F(c); B(c); }
void eo6_746(Cube *c) { F(c); R(c); Ui(c); Li(c); F(c); }
void eo6_747(Cube *c) { Li(c); Fi(c); U2(c); R(c); B(c); }
void eo6_748(Cube *c) { Ui(c); Di(c); B(c); R(c); F(c); B(c); }
void eo6_749(Cube *c) { Fi(c); U(c); D2(c); B(c); }
void eo6_750(Cube *c) { D(c); B(c); L2(c); D(c); F(c); }
void eo6_751(Cube *c) { B(c); L2(c); D(c); F(c); }
void eo6_752(Cube *c) { D(c); Fi(c); U(c); D2(c); B(c); }
void eo6_753(Cube *c) { L(c); Fi(c); Bi(c); D(c); B(c); }
void eo6_754(Cube *c) { Li(c); F(c); U2(c); B(c); }
void eo6_755(Cube *c) { F(c); D(c); R2(c); L(c); F(c); }
void eo6_756(Cube *c) { Li(c); B(c); Di(c); L2(c); F(c); }
void eo6_757(Cube *c) { D(c); Li(c); F(c); U2(c); B(c); }
void eo6_758(Cube *c) { U(c); F(c); L(c); B(c); D(c); F(c); }
void eo6_759(Cube *c) { F(c); U2(c); D(c); R(c); B(c); }
void eo6_760(Cube *c) { F(c); U2(c); R(c); B(c); }
void eo6_761(Cube *c) { L(c); Fi(c); Bi(c); U(c); B(c); }
void eo6_762(Cube *c) { U(c); B(c); Ui(c); Di(c); L(c); F(c); }
void eo6_763(Cube *c) { D(c); F(c); U2(c); R(c); B(c); }
void eo6_764(Cube *c) { L(c); Fi(c); U(c); R2(c); B(c); }
void eo6_765(Cube *c) { D2(c); Bi(c); L(c); F(c); B(c); }
void eo6_766(Cube *c) { Di(c); Bi(c); L(c); F(c); B(c); }
void eo6_767(Cube *c) { Bi(c); L(c); F(c); B(c); }
void eo6_768(Cube *c) { D(c); Bi(c); L(c); F(c); B(c); }
void eo6_769(Cube *c) { U(c); B(c); U(c); D2(c); L(c); B(c); }
void eo6_770(Cube *c) { Bi(c); R2(c); L(c); F(c); }
void eo6_771(Cube *c) { L(c); F(c); U(c); D2(c); B(c); }
void eo6_772(Cube *c) { B(c); U2(c); D(c); R(c); B(c); }
void eo6_773(Cube *c) { D(c); Bi(c); R2(c); L(c); F(c); }
void eo6_774(Cube *c) { Li(c); Bi(c); D(c); R2(c); F(c); }
void eo6_775(Cube *c) { D2(c); L(c); Fi(c); U2(c); B(c); }
void eo6_776(Cube *c) { Di(c); L(c); Fi(c); U2(c); B(c); }
void eo6_777(Cube *c) { L(c); Fi(c); U2(c); B(c); }
void eo6_778(Cube *c) { D(c); L(c); Fi(c); U2(c); B(c); }
void eo6_779(Cube *c) { Ui(c); R(c); F(c); U2(c); B(c); }
void eo6_780(Cube *c) { Ui(c); R(c); F(c); U2(c); Di(c); B(c); }
void eo6_781(Cube *c) { L(c); Fi(c); U2(c); R(c); B(c); }
void eo6_782(Cube *c) { U(c); B(c); Ri(c); Di(c); Li(c); B(c); }
void eo6_783(Cube *c) { R(c); Bi(c); L(c); F(c); B(c); }
void eo6_784(Cube *c) { F(c); R(c); B(c); D(c); B(c); }
void eo6_785(Cube *c) { U2(c); B(c); R(c); U(c); Di(c); F(c); }
void eo6_786(Cube *c) { F(c); L(c); U(c); L(c); B(c); }
void eo6_787(Cube *c) { U2(c); Bi(c); Li(c); Ui(c); D(c); F(c); }
void eo6_788(Cube *c) { Fi(c); Bi(c); D(c); B(c); }
void eo6_789(Cube *c) { U2(c); Fi(c); L2(c); B(c); }
void eo6_790(Cube *c) { Fi(c); Bi(c); Di(c); B(c); }
void eo6_791(Cube *c) { U2(c); Bi(c); U2(c); Di(c); F(c); }
void eo6_792(Cube *c) { Bi(c); D(c); F(c); B(c); }
void eo6_793(Cube *c) { F(c); L2(c); U(c); B(c); }
void eo6_794(Cube *c) { F(c); B(c); D(c); B(c); }
void eo6_795(Cube *c) { U2(c); F(c); R2(c); B(c); }
void eo6_796(Cube *c) { F(c); B(c); Di(c); B(c); }
void eo6_797(Cube *c) { Fi(c); R2(c); Ui(c); B(c); }
void eo6_798(Cube *c) { B(c); D(c); F(c); B(c); }
void eo6_799(Cube *c) { U2(c); B(c); U2(c); D(c); F(c); }
void eo6_800(Cube *c) { F(c); B(c); Ri(c); B(c); }
void eo6_801(Cube *c) { D(c); F(c); B(c); Ri(c); B(c); }
void eo6_802(Cube *c) { Fi(c); Bi(c); L(c); B(c); }
void eo6_803(Cube *c) { D(c); Fi(c); Bi(c); L(c); B(c); }
void eo6_804(Cube *c) { Fi(c); U2(c); D(c); B(c); }
void eo6_805(Cube *c) { Fi(c); U2(c); B(c); }
void eo6_806(Cube *c) { Fi(c); U2(c); Di(c); B(c); }
void eo6_807(Cube *c) { Bi(c); Di(c); R2(c); F(c); }
void eo6_808(Cube *c) { D(c); Fi(c); U2(c); B(c); }
void eo6_809(Cube *c) { Bi(c); D(c); R2(c); F(c); }
void eo6_810(Cube *c) { U2(c); Bi(c); U2(c); R(c); F(c); }
void eo6_811(Cube *c) { Di(c); Fi(c); U2(c); L(c); B(c); }
void eo6_812(Cube *c) { Fi(c); U2(c); L(c); B(c); }
void eo6_813(Cube *c) { D(c); Fi(c); U2(c); L(c); B(c); }
void eo6_814(Cube *c) { Ri(c); Fi(c); U2(c); B(c); }
void eo6_815(Cube *c) { D(c); Ri(c); Fi(c); U2(c); B(c); }
void eo6_816(Cube *c) { D2(c); Ri(c); Fi(c); U2(c); B(c); }
void eo6_817(Cube *c) { Di(c); Ri(c); Fi(c); U2(c); B(c); }
void eo6_818(Cube *c) { R(c); Fi(c); Bi(c); L(c); B(c); }
void eo6_819(Cube *c) { F(c); U2(c); D(c); B(c); }
void eo6_820(Cube *c) { F(c); U2(c); B(c); }
void eo6_821(Cube *c) { F(c); U2(c); Di(c); B(c); }
void eo6_822(Cube *c) { B(c); Di(c); L2(c); F(c); }
void eo6_823(Cube *c) { D(c); F(c); U2(c); B(c); }
void eo6_824(Cube *c) { B(c); D(c); L2(c); F(c); }
void eo6_825(Cube *c) { D2(c); L(c); F(c); U2(c); B(c); }
void eo6_826(Cube *c) { Di(c); L(c); F(c); U2(c); B(c); }
void eo6_827(Cube *c) { L(c); F(c); U2(c); B(c); }
void eo6_828(Cube *c) { D(c); L(c); F(c); U2(c); B(c); }
void eo6_829(Cube *c) { F(c); U2(c); Ri(c); B(c); }
void eo6_830(Cube *c) { D(c); F(c); U2(c); Ri(c); B(c); }
void eo6_831(Cube *c) { U2(c); B(c); U2(c); Li(c); F(c); }
void eo6_832(Cube *c) { Di(c); F(c); U2(c); Ri(c); B(c); }
void eo6_833(Cube *c) { L(c); F(c); U2(c); Ri(c); B(c); }
void eo6_834(Cube *c) { B(c); R(c); L2(c); F(c); }
void eo6_835(Cube *c) { D(c); B(c); R(c); L2(c); F(c); }
void eo6_836(Cube *c) { Bi(c); R2(c); Li(c); F(c); }
void eo6_837(Cube *c) { D(c); Bi(c); R2(c); Li(c); F(c); }
void eo6_838(Cube *c) { L(c); B(c); R(c); L2(c); F(c); }
void eo6_839(Cube *c) { Ri(c); Bi(c); R2(c); Li(c); F(c); }
void eo6_840(Cube *c) { U(c); F(c); R(c); D(c); R(c); B(c); }
void eo6_841(Cube *c) { U(c); B(c); R(c); U(c); Di(c); F(c); }
void eo6_842(Cube *c) { Ui(c); F(c); L(c); U(c); L(c); B(c); }
void eo6_843(Cube *c) { U(c); Bi(c); Li(c); Ui(c); D(c); F(c); }
void eo6_844(Cube *c) { U(c); Fi(c); D(c); L2(c); B(c); }
void eo6_845(Cube *c) { U(c); Fi(c); L2(c); B(c); }
void eo6_846(Cube *c) { U(c); Fi(c); Di(c); L2(c); B(c); }
void eo6_847(Cube *c) { U(c); Bi(c); U2(c); Di(c); F(c); }
void eo6_848(Cube *c) { U(c); D(c); Fi(c); L2(c); B(c); }
void eo6_849(Cube *c) { U(c); Bi(c); U2(c); D(c); F(c); }
void eo6_850(Cube *c) { U(c); F(c); D(c); R2(c); B(c); }
void eo6_851(Cube *c) { U(c); F(c); R2(c); B(c); }
void eo6_852(Cube *c) { U(c); F(c); Di(c); R2(c); B(c); }
void eo6_853(Cube *c) { U(c); B(c); U2(c); Di(c); F(c); }
void eo6_854(Cube *c) { U(c); D(c); F(c); R2(c); B(c); }
void eo6_855(Cube *c) { U(c); B(c); U2(c); D(c); F(c); }
void eo6_856(Cube *c) { U(c); Fi(c); Ri(c); L2(c); B(c); }
void eo6_857(Cube *c) { F(c); Ui(c); Li(c); Di(c); F(c); }
void eo6_858(Cube *c) { U(c); F(c); R2(c); L(c); B(c); }
void eo6_859(Cube *c) { Ui(c); Di(c); B(c); F(c); Ri(c); B(c); }
void eo6_860(Cube *c) { U(c); B(c); R2(c); U(c); F(c); }
void eo6_861(Cube *c) { Ui(c); Fi(c); U2(c); B(c); }
void eo6_862(Cube *c) { Ui(c); Fi(c); U2(c); Di(c); B(c); }
void eo6_863(Cube *c) { U(c); Fi(c); Bi(c); Di(c); F(c); }
void eo6_864(Cube *c) { U(c); Fi(c); D(c); F(c); B(c); }
void eo6_865(Cube *c) { U(c); Fi(c); Bi(c); D(c); F(c); }
void eo6_866(Cube *c) { U(c); Bi(c); U2(c); R(c); F(c); }
void eo6_867(Cube *c) { U(c); D(c); Bi(c); U2(c); R(c); F(c); }
void eo6_868(Cube *c) { Ui(c); Fi(c); U2(c); L(c); B(c); }
void eo6_869(Cube *c) { U(c); Fi(c); D(c); Fi(c); L(c); Bi(c); }
void eo6_870(Cube *c) { U(c); R(c); F(c); R2(c); B(c); }
void eo6_871(Cube *c) { U(c); D(c); R(c); B(c); U2(c); F(c); }
void eo6_872(Cube *c) { U(c); D2(c); R(c); B(c); U2(c); F(c); }
void eo6_873(Cube *c) { U(c); Ri(c); Fi(c); Bi(c); D(c); Fi(c); }
void eo6_874(Cube *c) { Ui(c); Ri(c); Fi(c); U2(c); L(c); B(c); }
void eo6_875(Cube *c) { Ui(c); F(c); U2(c); D(c); B(c); }
void eo6_876(Cube *c) { Ui(c); F(c); U2(c); B(c); }
void eo6_877(Cube *c) { U(c); Bi(c); L2(c); Ui(c); F(c); }
void eo6_878(Cube *c) { U(c); F(c); B(c); Di(c); F(c); }
void eo6_879(Cube *c) { U(c); F(c); D(c); F(c); B(c); }
void eo6_880(Cube *c) { U(c); F(c); B(c); D(c); F(c); }
void eo6_881(Cube *c) { U(c); D2(c); Li(c); Fi(c); L2(c); Bi(c); }
void eo6_882(Cube *c) { U(c); Li(c); Fi(c); D(c); L2(c); B(c); }
void eo6_883(Cube *c) { U(c); Li(c); Fi(c); L2(c); B(c); }
void eo6_884(Cube *c) { U(c); D(c); Li(c); Fi(c); L2(c); Bi(c); }
void eo6_885(Cube *c) { Ui(c); F(c); U2(c); Ri(c); B(c); }
void eo6_886(Cube *c) { Ui(c); F(c); U2(c); Ri(c); Di(c); B(c); }
void eo6_887(Cube *c) { U(c); B(c); U2(c); Li(c); F(c); }
void eo6_888(Cube *c) { U(c); D(c); B(c); U2(c); Li(c); F(c); }
void eo6_889(Cube *c) { L(c); F(c); R2(c); Ui(c); B(c); }
void eo6_890(Cube *c) { U(c); Fi(c); Bi(c); R(c); F(c); }
void eo6_891(Cube *c) { U(c); D(c); Fi(c); Bi(c); R(c); Fi(c); }
void eo6_892(Cube *c) { U(c); F(c); B(c); Li(c); F(c); }
void eo6_893(Cube *c) { B(c); U(c); Ri(c); Di(c); B(c); }
void eo6_894(Cube *c) { L(c); Bi(c); R2(c); U(c); F(c); }
void eo6_895(Cube *c) { U(c); R(c); B(c); U2(c); Li(c); F(c); }
void eo6_896(Cube *c) { U(c); F(c); Ri(c); Ui(c); D(c); B(c); }
void eo6_897(Cube *c) { F(c); R(c); Ui(c); Ri(c); B(c); }
void eo6_898(Cube *c) { U(c); Fi(c); L(c); U(c); Di(c); B(c); }
void eo6_899(Cube *c) { U(c); Bi(c); R(c); U(c); Di(c); F(c); }
void eo6_900(Cube *c) { D(c); F(c); R(c); Ui(c); Ri(c); B(c); }
void eo6_901(Cube *c) { U(c); B(c); Li(c); Ui(c); D(c); F(c); }
void eo6_902(Cube *c) { D2(c); Fi(c); L2(c); U(c); B(c); }
void eo6_903(Cube *c) { Di(c); Fi(c); L2(c); U(c); B(c); }
void eo6_904(Cube *c) { Fi(c); L2(c); U(c); B(c); }
void eo6_905(Cube *c) { D(c); Fi(c); L2(c); U(c); B(c); }
void eo6_906(Cube *c) { F(c); R2(c); Ui(c); B(c); }
void eo6_907(Cube *c) { D(c); F(c); R2(c); Ui(c); B(c); }
void eo6_908(Cube *c) { D2(c); F(c); R2(c); Ui(c); B(c); }
void eo6_909(Cube *c) { Di(c); F(c); R2(c); Ui(c); B(c); }
void eo6_910(Cube *c) { F(c); R2(c); Ui(c); L(c); B(c); }
void eo6_911(Cube *c) { Bi(c); R2(c); U(c); F(c); }
void eo6_912(Cube *c) { D(c); Bi(c); R2(c); U(c); F(c); }
void eo6_913(Cube *c) { D2(c); Bi(c); R2(c); U(c); F(c); }
void eo6_914(Cube *c) { Di(c); Bi(c); R2(c); U(c); F(c); }
void eo6_915(Cube *c) { R(c); F(c); R2(c); Ui(c); L(c); B(c); }
void eo6_916(Cube *c) { R(c); D2(c); F(c); R2(c); Ui(c); B(c); }
void eo6_917(Cube *c) { D2(c); B(c); L2(c); Ui(c); F(c); }
void eo6_918(Cube *c) { Di(c); B(c); L2(c); Ui(c); F(c); }
void eo6_919(Cube *c) { B(c); L2(c); Ui(c); F(c); }
void eo6_920(Cube *c) { D(c); B(c); L2(c); Ui(c); F(c); }
void eo6_921(Cube *c) { R2(c); U(c); L(c); F(c); U2(c); B(c); }
void eo6_922(Cube *c) { R(c); Ui(c); B(c); U2(c); Li(c); F(c); }
void eo6_923(Cube *c) { B(c); R(c); L2(c); Ui(c); F(c); }
static void (*const eo6_moves[924])(Cube*) = {eo6_0, eo6_1, eo6_2, eo6_3, eo6_4, eo6_5, eo6_6, eo6_7, eo6_8, eo6_9, eo6_10, eo6_11, eo6_12, eo6_13, eo6_14, eo6_15, eo6_16, eo6_17, eo6_18, eo6_19, eo6_20, eo6_21, eo6_22, eo6_23, eo6_24, eo6_25, eo6_26, eo6_27, eo6_28, eo6_29, eo6_30, eo6_31, eo6_32, eo6_33, eo6_34, eo6_35, eo6_36, eo6_37, eo6_38, eo6_39, eo6_40, eo6_41, eo6_42, eo6_43, eo6_44, eo6_45, eo6_46, eo6_47, eo6_48, eo6_49, eo6_50, eo6_51, eo6_52, eo6_53, eo6_54, eo6_55, eo6_56, eo6_57, eo6_58, eo6_59, eo6_60, eo6_61, eo6_62, eo6_63, eo6_64, eo6_65, eo6_66, eo6_67, eo6_68, eo6_69, eo6_70, eo6_71, eo6_72, eo6_73, eo6_74, eo6_75, eo6_76, eo6_77, eo6_78, eo6_79, eo6_80, eo6_81, eo6_82, eo6_83, eo6_84, eo6_85, eo6_86, eo6_87, eo6_88, eo6_89, eo6_90, eo6_91, eo6_92, eo6_93, eo6_94, eo6_95, eo6_96, eo6_97, eo6_98, eo6_99, eo6_100, eo6_101, eo6_102, eo6_103, eo6_104, eo6_105, eo6_106, eo6_107, eo6_108, eo6_109, eo6_110, eo6_111, eo6_112, eo6_113, eo6_114, eo6_115, eo6_116, eo6_117, eo6_118, eo6_119, eo6_120, eo6_121, eo6_122, eo6_123, eo6_124, eo6_125, eo6_126, eo6_127, eo6_128, eo6_129, eo6_130, eo6_131, eo6_132, eo6_133, eo6_134, eo6_135, eo6_136, eo6_137, eo6_138, eo6_139, eo6_140, eo6_141, eo6_142, eo6_143, eo6_144, eo6_145, eo6_146, eo6_147, eo6_148, eo6_149, eo6_150, eo6_151, eo6_152, eo6_153, eo6_154, eo6_155, eo6_156, eo6_157, eo6_158, eo6_159, eo6_160, eo6_161, eo6_162, eo6_163, eo6_164, eo6_165, eo6_166, eo6_167, eo6_168, eo6_169, eo6_170, eo6_171, eo6_172, eo6_173, eo6_174, eo6_175, eo6_176, eo6_177, eo6_178, eo6_179, eo6_180, eo6_181, eo6_182, eo6_183, eo6_184, eo6_185, eo6_186, eo6_187, eo6_188, eo6_189, eo6_190, eo6_191, eo6_192, eo6_193, eo6_194, eo6_195, eo6_196, eo6_197, eo6_198, eo6_199, eo6_200, eo6_201, eo6_202, eo6_203, eo6_204, eo6_205, eo6_206, eo6_207, eo6_208, eo6_209, eo6_210, eo6_211, eo6_212, eo6_213, eo6_214, eo6_215, eo6_216, eo6_217, eo6_218, eo6_219, eo6_220, eo6_221, eo6_222, eo6_223, eo6_224, eo6_225, eo6_226, eo6_227, eo6_228, eo6_229, eo6_230, eo6_231, eo6_232, eo6_233, eo6_234, eo6_235, eo6_236, eo6_237, eo6_238, eo6_239, eo6_240, eo6_241, eo6_242, eo6_243, eo6_244, eo6_245, eo6_246, eo6_247, eo6_248, eo6_249, eo6_250, eo6_251, eo6_252, eo6_253, eo6_254, eo6_255, eo6_256, eo6_257, eo6_258, eo6_259, eo6_260, eo6_261, eo6_262, eo6_263, eo6_264, eo6_265, eo6_266, eo6_267, eo6_268, eo6_269, eo6_270, eo6_271, eo6_272, eo6_273, eo6_274, eo6_275, eo6_276, eo6_277, eo6_278, eo6_279, eo6_280, eo6_281, eo6_282, eo6_283, eo6_284, eo6_285, eo6_286, eo6_287, eo6_288, eo6_289, eo6_290, eo6_291, eo6_292, eo6_293, eo6_294, eo6_295, eo6_296, eo6_297, eo6_298, eo6_299, eo6_300, eo6_301, eo6_302, eo6_303, eo6_304, eo6_305, eo6_306, eo6_307, eo6_308, eo6_309, eo6_310, eo6_311, eo6_312, eo6_313, eo6_314, eo6_315, eo6_316, eo6_317, eo6_318, eo6_319, eo6_320, eo6_321, eo6_322, eo6_323, eo6_324, eo6_325, eo6_326, eo6_327, eo6_328, eo6_329, eo6_330, eo6_331, eo6_332, eo6_333, eo6_334, eo6_335, eo6_336, eo6_337, eo6_338, eo6_339, eo6_340, eo6_341, eo6_342, eo6_343, eo6_344, eo6_345, eo6_346, eo6_347, eo6_348, eo6_349, eo6_350, eo6_351, eo6_352, eo6_353, eo6_354, eo6_355, eo6_356, eo6_357, eo6_358, eo6_359, eo6_360, eo6_361, eo6_362, eo6_363, eo6_364, eo6_365, eo6_366, eo6_367, eo6_368, eo6_369, eo6_370, eo6_371, eo6_372, eo6_373, eo6_374, eo6_375, eo6_376, eo6_377, eo6_378, eo6_379, eo6_380, eo6_381, eo6_382, eo6_383, eo6_384, eo6_385, eo6_386, eo6_387, eo6_388, eo6_389, eo6_390, eo6_391, eo6_392, eo6_393, eo6_394, eo6_395, eo6_396, eo6_397, eo6_398, eo6_399, eo6_400, eo6_401, eo6_402, eo6_403, eo6_404, eo6_405, eo6_406, eo6_407, eo6_408, eo6_409, eo6_410, eo6_411, eo6_412, eo6_413, eo6_414, eo6_415, eo6_416, eo6_417, eo6_418, eo6_419, eo6_420, eo6_421, eo6_422, eo6_423, eo6_424, eo6_425, eo6_426, eo6_427, eo6_428, eo6_429, eo6_430, eo6_431, eo6_432, eo6_433, eo6_434, eo6_435, eo6_436, eo6_437, eo6_438, eo6_439, eo6_440, eo6_441, eo6_442, eo6_443, eo6_444, eo6_445, eo6_446, eo6_447, eo6_448, eo6_449, eo6_450, eo6_451, eo6_452, eo6_453, eo6_454, eo6_455, eo6_456, eo6_457, eo6_458, eo6_459, eo6_460, eo6_461, eo6_462, eo6_463, eo6_464, eo6_465, eo6_466, eo6_467, eo6_468, eo6_469, eo6_470, eo6_471, eo6_472, eo6_473, eo6_474, eo6_475, eo6_476, eo6_477, eo6_478, eo6_479, eo6_480, eo6_481, eo6_482, eo6_483, eo6_484, eo6_485, eo6_486, eo6_487, eo6_488, eo6_489, eo6_490, eo6_491, eo6_492, eo6_493, eo6_494, eo6_495, eo6_496, eo6_497, eo6_498, eo6_499, eo6_500, eo6_501, eo6_502, eo6_503, eo6_504, eo6_505, eo6_506, eo6_507, eo6_508, eo6_509, eo6_510, eo6_511, eo6_512, eo6_513, eo6_514, eo6_515, eo6_516, eo6_517, eo6_518, eo6_519, eo6_520, eo6_521, eo6_522, eo6_523, eo6_524, eo6_525, eo6_526, eo6_527, eo6_528, eo6_529, eo6_530, eo6_531, eo6_532, eo6_533, eo6_534, eo6_535, eo6_536, eo6_537, eo6_538, eo6_539, eo6_540, eo6_541, eo6_542, eo6_543, eo6_544, eo6_545, eo6_546, eo6_547, eo6_548, eo6_549, eo6_550, eo6_551, eo6_552, eo6_553, eo6_554, eo6_555, eo6_556, eo6_557, eo6_558, eo6_559, eo6_560, eo6_561, eo6_562, eo6_563, eo6_564, eo6_565, eo6_566, eo6_567, eo6_568, eo6_569, eo6_570, eo6_571, eo6_572, eo6_573, eo6_574, eo6_575, eo6_576, eo6_577, eo6_578, eo6_579, eo6_580, eo6_581, eo6_582, eo6_583, eo6_584, eo6_585, eo6_586, eo6_587, eo6_588, eo6_589, eo6_590, eo6_591, eo6_592, eo6_593, eo6_594, eo6_595, eo6_596, eo6_597, eo6_598, eo6_599, eo6_600, eo6_601, eo6_602, eo6_603, eo6_604, eo6_605, eo6_606, eo6_607, eo6_608, eo6_609, eo6_610, eo6_611, eo6_612, eo6_613, eo6_614, eo6_615, eo6_616, eo6_617, eo6_618, eo6_619, eo6_620, eo6_621, eo6_622, eo6_623, eo6_624, eo6_625, eo6_626, eo6_627, eo6_628, eo6_629, eo6_630, eo6_631, eo6_632, eo6_633, eo6_634, eo6_635, eo6_636, eo6_637, eo6_638, eo6_639, eo6_640, eo6_641, eo6_642, eo6_643, eo6_644, eo6_645, eo6_646, eo6_647, eo6_648, eo6_649, eo6_650, eo6_651, eo6_652, eo6_653, eo6_654, eo6_655, eo6_656, eo6_657, eo6_658, eo6_659, eo6_660, eo6_661, eo6_662, eo6_663, eo6_664, eo6_665, eo6_666, eo6_667, eo6_668, eo6_669, eo6_670, eo6_671, eo6_672, eo6_673, eo6_674, eo6_675, eo6_676, eo6_677, eo6_678, eo6_679, eo6_680, eo6_681, eo6_682, eo6_683, eo6_684, eo6_685, eo6_686, eo6_687, eo6_688, eo6_689, eo6_690, eo6_691, eo6_692, eo6_693, eo6_694, eo6_695, eo6_696, eo6_697, eo6_698, eo6_699, eo6_700, eo6_701, eo6_702, eo6_703, eo6_704, eo6_705, eo6_706, eo6_707, eo6_708, eo6_709, eo6_710, eo6_711, eo6_712, eo6_713, eo6_714, eo6_715, eo6_716, eo6_717, eo6_718, eo6_719, eo6_720, eo6_721, eo6_722, eo6_723, eo6_724, eo6_725, eo6_726, eo6_727, eo6_728, eo6_729, eo6_730, eo6_731, eo6_732, eo6_733, eo6_734, eo6_735, eo6_736, eo6_737, eo6_738, eo6_739, eo6_740, eo6_741, eo6_742, eo6_743, eo6_744, eo6_745, eo6_746, eo6_747, eo6_748, eo6_749, eo6_750, eo6_751, eo6_752, eo6_753, eo6_754, eo6_755, eo6_756, eo6_757, eo6_758, eo6_759, eo6_760, eo6_761, eo6_762, eo6_763, eo6_764, eo6_765, eo6_766, eo6_767, eo6_768, eo6_769, eo6_770, eo6_771, eo6_772, eo6_773, eo6_774, eo6_775, eo6_776, eo6_777, eo6_778, eo6_779, eo6_780, eo6_781, eo6_782, eo6_783, eo6_784, eo6_785, eo6_786, eo6_787, eo6_788, eo6_789, eo6_790, eo6_791, eo6_792, eo6_793, eo6_794, eo6_795, eo6_796, eo6_797, eo6_798, eo6_799, eo6_800, eo6_801, eo6_802, eo6_803, eo6_804, eo6_805, eo6_806, eo6_807, eo6_808, eo6_809, eo6_810, eo6_811, eo6_812, eo6_813, eo6_814, eo6_815, eo6_816, eo6_817, eo6_818, eo6_819, eo6_820, eo6_821, eo6_822, eo6_823, eo6_824, eo6_825, eo6_826, eo6_827, eo6_828, eo6_829, eo6_830, eo6_831, eo6_832, eo6_833, eo6_834, eo6_835, eo6_836, eo6_837, eo6_838, eo6_839, eo6_840, eo6_841, eo6_842, eo6_843, eo6_844, eo6_845, eo6_846, eo6_847, eo6_848, eo6_849, eo6_850, eo6_851, eo6_852, eo6_853, eo6_854, eo6_855, eo6_856, eo6_857, eo6_858, eo6_859, eo6_860, eo6_861, eo6_862, eo6_863, eo6_864, eo6_865, eo6_866, eo6_867, eo6_868, eo6_869, eo6_870, eo6_871, eo6_872, eo6_873, eo6_874, eo6_875, eo6_876, eo6_877, eo6_878, eo6_879, eo6_880, eo6_881, eo6_882, eo6_883, eo6_884, eo6_885, eo6_886, eo6_887, eo6_888, eo6_889, eo6_890, eo6_891, eo6_892, eo6_893, eo6_894, eo6_895, eo6_896, eo6_897, eo6_898, eo6_899, eo6_900, eo6_901, eo6_902, eo6_903, eo6_904, eo6_905, eo6_906, eo6_907, eo6_908, eo6_909, eo6_910, eo6_911, eo6_912, eo6_913, eo6_914, eo6_915, eo6_916, eo6_917, eo6_918, eo6_919, eo6_920, eo6_921, eo6_922, eo6_923};


// EO_8
void eo8_0(Cube *c) { R(c); L2(c); D(c); B(c); Ri(c); F(c); }
void eo8_1(Cube *c) { R2(c); F(c); D(c); Li(c); B(c); }
void eo8_2(Cube *c) { D(c); F2(c); Ui(c); Fi(c); Li(c); Bi(c); }
void eo8_3(Cube *c) { F2(c); Ui(c); F(c); Li(c); B(c); }
void eo8_4(Cube *c) { R2(c); D(c); F(c); Li(c); B(c); }
void eo8_5(Cube *c) { L2(c); F(c); Di(c); R(c); B(c); }
void eo8_6(Cube *c) { Ri(c); L2(c); D(c); F(c); B(c); }
void eo8_7(Cube *c) { F2(c); U(c); F(c); R(c); B(c); }
void eo8_8(Cube *c) { D(c); L2(c); F(c); Di(c); R(c); B(c); }
void eo8_9(Cube *c) { Ri(c); F(c); D(c); Li(c); B(c); }
void eo8_10(Cube *c) { Ri(c); F(c); Ri(c); Li(c); B(c); }
void eo8_11(Cube *c) { L(c); F(c); Di(c); R(c); B(c); }
void eo8_12(Cube *c) { Di(c); Ri(c); F(c); D(c); Li(c); B(c); }
void eo8_13(Cube *c) { Ri(c); D(c); F(c); Li(c); B(c); }
void eo8_14(Cube *c) { D(c); L(c); F(c); Di(c); R(c); B(c); }
void eo8_15(Cube *c) { B2(c); Ui(c); B(c); Ri(c); F(c); }
void eo8_16(Cube *c) { R(c); L2(c); D(c); F(c); B(c); }
void eo8_17(Cube *c) { L2(c); B(c); D(c); Ri(c); F(c); }
void eo8_18(Cube *c) { D(c); B2(c); Ui(c); B(c); Ri(c); F(c); }
void eo8_19(Cube *c) { R(c); F(c); D(c); Li(c); B(c); }
void eo8_20(Cube *c) { R2(c); F(c); Ri(c); Li(c); B(c); }
void eo8_21(Cube *c) { D(c); R(c); F(c); D(c); Li(c); B(c); }
void eo8_22(Cube *c) { D(c); L(c); B(c); D(c); Ri(c); F(c); }
void eo8_23(Cube *c) { R(c); D(c); F(c); Li(c); B(c); }
void eo8_24(Cube *c) { L(c); B(c); D(c); Ri(c); F(c); }
void eo8_25(Cube *c) { R(c); L2(c); F(c); Di(c); B(c); }
void eo8_26(Cube *c) { R(c); U2(c); B(c); Ri(c); F(c); }
void eo8_27(Cube *c) { D(c); R(c); L2(c); F(c); Di(c); B(c); }
void eo8_28(Cube *c) { R(c); L2(c); B(c); D(c); F(c); }
void eo8_29(Cube *c) { D(c); R(c); U2(c); B(c); Ri(c); F(c); }
void eo8_30(Cube *c) { Di(c); R(c); L2(c); B(c); D(c); F(c); }
void eo8_31(Cube *c) { R(c); F(c); Li(c); B(c); }
void eo8_32(Cube *c) { D(c); R(c); F(c); Li(c); B(c); }
void eo8_33(Cube *c) { D2(c); R(c); F(c); Li(c); B(c); }
void eo8_34(Cube *c) { Di(c); R(c); F(c); Li(c); B(c); }
void eo8_35(Cube *c) { B2(c); U(c); B(c); L(c); F(c); }
void eo8_36(Cube *c) { D(c); R2(c); B(c); Di(c); L(c); F(c); }
void eo8_37(Cube *c) { R2(c); B(c); Di(c); L(c); F(c); }
void eo8_38(Cube *c) { R2(c); D(c); B(c); L(c); F(c); }
void eo8_39(Cube *c) { Di(c); R2(c); Di(c); L(c); F(c); B(c); }
void eo8_40(Cube *c) { R2(c); D2(c); L(c); F(c); B(c); }
void eo8_41(Cube *c) { R2(c); Di(c); L(c); F(c); B(c); }
void eo8_42(Cube *c) { D(c); R2(c); D(c); L(c); F(c); B(c); }
void eo8_43(Cube *c) { D(c); R2(c); D2(c); L(c); F(c); B(c); }
void eo8_44(Cube *c) { R2(c); D(c); L(c); F(c); B(c); }
void eo8_45(Cube *c) { D(c); Ri(c); B(c); Di(c); L(c); F(c); }
void eo8_46(Cube *c) { R2(c); B(c); R(c); L(c); F(c); }
void eo8_47(Cube *c) { Li(c); F(c); Di(c); R(c); B(c); }
void eo8_48(Cube *c) { Ri(c); B(c); Di(c); L(c); F(c); }
void eo8_49(Cube *c) { Ri(c); D(c); B(c); L(c); F(c); }
void eo8_50(Cube *c) { D(c); Li(c); F(c); Di(c); R(c); B(c); }
void eo8_51(Cube *c) { D2(c); L(c); F(c); R(c); B(c); }
void eo8_52(Cube *c) { Di(c); L(c); F(c); R(c); B(c); }
void eo8_53(Cube *c) { L(c); F(c); R(c); B(c); }
void eo8_54(Cube *c) { D(c); L(c); F(c); R(c); B(c); }
void eo8_55(Cube *c) { D(c); R(c); B(c); Di(c); L(c); F(c); }
void eo8_56(Cube *c) { R(c); B(c); R(c); L(c); F(c); }
void eo8_57(Cube *c) { Di(c); Li(c); B(c); D(c); Ri(c); F(c); }
void eo8_58(Cube *c) { R(c); B(c); Di(c); L(c); F(c); }
void eo8_59(Cube *c) { R(c); D(c); B(c); L(c); F(c); }
void eo8_60(Cube *c) { Li(c); B(c); D(c); Ri(c); F(c); }
void eo8_61(Cube *c) { D2(c); L(c); B(c); Ri(c); F(c); }
void eo8_62(Cube *c) { Di(c); L(c); B(c); Ri(c); F(c); }
void eo8_63(Cube *c) { L(c); B(c); Ri(c); F(c); }
void eo8_64(Cube *c) { D(c); L(c); B(c); Ri(c); F(c); }
void eo8_65(Cube *c) { R(c); B(c); L(c); F(c); }
void eo8_66(Cube *c) { D(c); R(c); B(c); L(c); F(c); }
void eo8_67(Cube *c) { D2(c); R(c); B(c); L(c); F(c); }
void eo8_68(Cube *c) { Di(c); R(c); B(c); L(c); F(c); }
void eo8_69(Cube *c) { R(c); L(c); F(c); B(c); }
void eo8_70(Cube *c) { R2(c); F(c); D(c); B(c); }
void eo8_71(Cube *c) { U2(c); L2(c); D(c); F(c); B(c); }
void eo8_72(Cube *c) { R2(c); B(c); Di(c); F(c); }
void eo8_73(Cube *c) { R2(c); D(c); F(c); B(c); }
void eo8_74(Cube *c) { U2(c); F(c); D(c); Li(c); B(c); }
void eo8_75(Cube *c) { U2(c); F(c); Li(c); B(c); }
void eo8_76(Cube *c) { U2(c); L(c); F(c); Di(c); B(c); }
void eo8_77(Cube *c) { B2(c); Ri(c); B(c); Di(c); F(c); }
void eo8_78(Cube *c) { U2(c); D(c); F(c); Li(c); B(c); }
void eo8_79(Cube *c) { U2(c); L(c); B(c); D(c); F(c); }
void eo8_80(Cube *c) { Ri(c); F(c); D(c); B(c); }
void eo8_81(Cube *c) { F(c); R(c); B(c); }
void eo8_82(Cube *c) { F(c); Di(c); R(c); B(c); }
void eo8_83(Cube *c) { Ri(c); B(c); Di(c); F(c); }
void eo8_84(Cube *c) { D(c); F(c); R(c); B(c); }
void eo8_85(Cube *c) { D(c); F(c); Di(c); R(c); B(c); }
void eo8_86(Cube *c) { U2(c); F(c); Ri(c); Li(c); B(c); }
void eo8_87(Cube *c) { Di(c); F(c); R(c); L(c); B(c); }
void eo8_88(Cube *c) { F(c); R(c); L(c); B(c); }
void eo8_89(Cube *c) { D(c); F(c); R(c); L(c); B(c); }
void eo8_90(Cube *c) { R(c); F(c); D(c); B(c); }
void eo8_91(Cube *c) { B(c); Ri(c); F(c); }
void eo8_92(Cube *c) { D(c); R(c); F(c); D(c); B(c); }
void eo8_93(Cube *c) { R(c); B(c); Di(c); F(c); }
void eo8_94(Cube *c) { D(c); B(c); Ri(c); F(c); }
void eo8_95(Cube *c) { B(c); D(c); Ri(c); F(c); }
void eo8_96(Cube *c) { B2(c); R(c); F(c); B(c); }
void eo8_97(Cube *c) { D(c); B2(c); R(c); F(c); B(c); }
void eo8_98(Cube *c) { U2(c); F2(c); L(c); F(c); B(c); }
void eo8_99(Cube *c) { Di(c); B2(c); R(c); F(c); B(c); }
void eo8_100(Cube *c) { R(c); F(c); B(c); }
void eo8_101(Cube *c) { D(c); R(c); F(c); B(c); }
void eo8_102(Cube *c) { D2(c); R(c); F(c); B(c); }
void eo8_103(Cube *c) { Di(c); R(c); F(c); B(c); }
void eo8_104(Cube *c) { R(c); F(c); L(c); B(c); }
void eo8_105(Cube *c) { F2(c); R(c); F(c); D(c); B(c); }
void eo8_106(Cube *c) { U2(c); B(c); L(c); F(c); }
void eo8_107(Cube *c) { U2(c); Li(c); F(c); Di(c); B(c); }
void eo8_108(Cube *c) { U2(c); B(c); Di(c); L(c); F(c); }
void eo8_109(Cube *c) { U2(c); D(c); B(c); L(c); F(c); }
void eo8_110(Cube *c) { U2(c); Li(c); B(c); D(c); F(c); }
void eo8_111(Cube *c) { U(c); D2(c); U(c); L(c); F(c); B(c); }
void eo8_112(Cube *c) { U2(c); Di(c); L(c); F(c); B(c); }
void eo8_113(Cube *c) { U2(c); L(c); F(c); B(c); }
void eo8_114(Cube *c) { U2(c); D(c); L(c); F(c); B(c); }
void eo8_115(Cube *c) { F2(c); R(c); F(c); B(c); }
void eo8_116(Cube *c) { D(c); F2(c); R(c); F(c); B(c); }
void eo8_117(Cube *c) { U2(c); B2(c); L(c); F(c); B(c); }
void eo8_118(Cube *c) { Di(c); F2(c); R(c); F(c); B(c); }
void eo8_119(Cube *c) { U2(c); L(c); F(c); Ri(c); B(c); }
void eo8_120(Cube *c) { U2(c); B(c); R(c); L(c); F(c); }
void eo8_121(Cube *c) { Di(c); B(c); Ri(c); Li(c); F(c); }
void eo8_122(Cube *c) { B(c); Ri(c); Li(c); F(c); }
void eo8_123(Cube *c) { D(c); B(c); Ri(c); Li(c); F(c); }
void eo8_124(Cube *c) { U2(c); L(c); B(c); R(c); F(c); }
void eo8_125(Cube *c) { R(c); B(c); Li(c); F(c); }
void eo8_126(Cube *c) { B2(c); U(c); F(c); B(c); }
void eo8_127(Cube *c) { Ui(c); L2(c); D(c); F(c); B(c); }
void eo8_128(Cube *c) { U(c); R2(c); B(c); Di(c); F(c); }
void eo8_129(Cube *c) { U(c); R2(c); D(c); F(c); B(c); }
void eo8_130(Cube *c) { Ui(c); F(c); D(c); Li(c); B(c); }
void eo8_131(Cube *c) { Ui(c); F(c); Li(c); B(c); }
void eo8_132(Cube *c) { Ui(c); L(c); F(c); Di(c); B(c); }
void eo8_133(Cube *c) { U(c); B2(c); Ri(c); B(c); Di(c); F(c); }
void eo8_134(Cube *c) { Ui(c); Di(c); F(c); Li(c); B(c); }
void eo8_135(Cube *c) { Ui(c); L(c); B(c); D(c); F(c); }
void eo8_136(Cube *c) { U(c); Ri(c); F(c); D(c); B(c); }
void eo8_137(Cube *c) { U(c); F(c); R(c); B(c); }
void eo8_138(Cube *c) { U(c); F(c); Di(c); R(c); B(c); }
void eo8_139(Cube *c) { U(c); Ri(c); B(c); Di(c); F(c); }
void eo8_140(Cube *c) { U(c); D(c); F(c); R(c); B(c); }
void eo8_141(Cube *c) { U(c); D(c); F(c); Di(c); R(c); B(c); }
void eo8_142(Cube *c) { Ui(c); F(c); Ri(c); Li(c); B(c); }
void eo8_143(Cube *c) { U(c); Ri(c); Di(c); Fi(c); L(c); Bi(c); }
void eo8_144(Cube *c) { U(c); F(c); R(c); L(c); B(c); }
void eo8_145(Cube *c) { U(c); D(c); F(c); R(c); L(c); B(c); }
void eo8_146(Cube *c) { U(c); R(c); F(c); D(c); B(c); }
void eo8_147(Cube *c) { U(c); B(c); Ri(c); F(c); }
void eo8_148(Cube *c) { U(c); D(c); R(c); F(c); D(c); B(c); }
void eo8_149(Cube *c) { U(c); R(c); B(c); Di(c); F(c); }
void eo8_150(Cube *c) { U(c); D(c); B(c); Ri(c); F(c); }
void eo8_151(Cube *c) { U(c); B(c); D(c); Ri(c); F(c); }
void eo8_152(Cube *c) { U(c); B2(c); R(c); F(c); B(c); }
void eo8_153(Cube *c) { U(c); D(c); B2(c); R(c); F(c); B(c); }
void eo8_154(Cube *c) { Ui(c); F2(c); L(c); F(c); B(c); }
void eo8_155(Cube *c) { U(c); R(c); D(c); Fi(c); L(c); Bi(c); }
void eo8_156(Cube *c) { U(c); R(c); F(c); B(c); }
void eo8_157(Cube *c) { U(c); D(c); R(c); F(c); B(c); }
void eo8_158(Cube *c) { U(c); D2(c); R(c); F(c); B(c); }
void eo8_159(Cube *c) { U(c); R(c); B(c); D(c); F(c); }
void eo8_160(Cube *c) { U(c); R(c); F(c); L(c); B(c); }
void eo8_161(Cube *c) { U(c); F2(c); R(c); F(c); D(c); B(c); }
void eo8_162(Cube *c) { Ui(c); B(c); L(c); F(c); }
void eo8_163(Cube *c) { Ui(c); Li(c); F(c); Di(c); B(c); }
void eo8_164(Cube *c) { Ui(c); B(c); Di(c); L(c); F(c); }
void eo8_165(Cube *c) { Ui(c); Di(c); B(c); L(c); F(c); }
void eo8_166(Cube *c) { Ui(c); Li(c); B(c); D(c); F(c); }
void eo8_167(Cube *c) { Ui(c); D2(c); L(c); F(c); B(c); }
void eo8_168(Cube *c) { Ui(c); Di(c); L(c); F(c); B(c); }
void eo8_169(Cube *c) { Ui(c); L(c); F(c); B(c); }
void eo8_170(Cube *c) { Ui(c); L(c); B(c); Di(c); F(c); }
void eo8_171(Cube *c) { U(c); F2(c); R(c); F(c); B(c); }
void eo8_172(Cube *c) { U(c); D(c); F2(c); R(c); F(c); B(c); }
void eo8_173(Cube *c) { Ui(c); B2(c); L(c); F(c); B(c); }
void eo8_174(Cube *c) { U(c); Ri(c); D(c); B(c); Li(c); F(c); }
void eo8_175(Cube *c) { Ui(c); L(c); F(c); Ri(c); B(c); }
void eo8_176(Cube *c) { Ui(c); B(c); R(c); L(c); F(c); }
void eo8_177(Cube *c) { U(c); R(c); Di(c); B(c); Li(c); F(c); }
void eo8_178(Cube *c) { U(c); B(c); Ri(c); Li(c); F(c); }
void eo8_179(Cube *c) { U(c); R(c); D(c); B(c); Li(c); F(c); }
void eo8_180(Cube *c) { Ui(c); L(c); B(c); R(c); F(c); }
void eo8_181(Cube *c) { U(c); R(c); B(c); Li(c); F(c); }
void eo8_182(Cube *c) { U2(c); F(c); U(c); D(c); B(c); }
void eo8_183(Cube *c) { B(c); U(c); F(c); }
void eo8_184(Cube *c) { U(c); F(c); Ui(c); Di(c); B(c); }
void eo8_185(Cube *c) { Ui(c); B(c); Ui(c); Di(c); F(c); }
void eo8_186(Cube *c) { D(c); B(c); U(c); F(c); }
void eo8_187(Cube *c) { B(c); U(c); D(c); F(c); }
void eo8_188(Cube *c) { B2(c); R(c); B(c); U(c); F(c); }
void eo8_189(Cube *c) { U(c); F(c); Ui(c); L(c); D(c); B(c); }
void eo8_190(Cube *c) { U(c); F(c); Ui(c); L(c); B(c); }
void eo8_191(Cube *c) { U(c); D(c); F(c); Ui(c); L(c); B(c); }
void eo8_192(Cube *c) { R(c); B(c); U(c); F(c); }
void eo8_193(Cube *c) { D(c); R(c); B(c); U(c); F(c); }
void eo8_194(Cube *c) { D2(c); R(c); B(c); U(c); F(c); }
void eo8_195(Cube *c) { Di(c); R(c); B(c); U(c); F(c); }
void eo8_196(Cube *c) { U(c); R(c); F(c); Ui(c); L(c); B(c); }
void eo8_197(Cube *c) { Ri(c); B(c); U(c); F(c); }
void eo8_198(Cube *c) { D(c); Ri(c); B(c); U(c); F(c); }
void eo8_199(Cube *c) { D2(c); Ri(c); B(c); U(c); F(c); }
void eo8_200(Cube *c) { Di(c); Ri(c); B(c); U(c); F(c); }
void eo8_201(Cube *c) { U(c); Ri(c); F(c); Ui(c); L(c); B(c); }
void eo8_202(Cube *c) { R(c); L2(c); B(c); Ui(c); F(c); }
void eo8_203(Cube *c) { D2(c); B(c); U(c); Li(c); F(c); }
void eo8_204(Cube *c) { Di(c); B(c); U(c); Li(c); F(c); }
void eo8_205(Cube *c) { B(c); U(c); Li(c); F(c); }
void eo8_206(Cube *c) { D(c); B(c); U(c); Li(c); F(c); }
void eo8_207(Cube *c) { Ui(c); R2(c); Ui(c); L(c); F(c); B(c); }
void eo8_208(Cube *c) { R(c); B(c); U(c); Li(c); F(c); }
void eo8_209(Cube *c) { Ri(c); B(c); U(c); Li(c); F(c); }
void eo8_210(Cube *c) { L2(c); F(c); Di(c); B(c); }
void eo8_211(Cube *c) { L2(c); D(c); F(c); B(c); }
void eo8_212(Cube *c) { L2(c); B(c); D(c); F(c); }
void eo8_213(Cube *c) { U2(c); R2(c); D(c); F(c); B(c); }
void eo8_214(Cube *c) { F(c); D(c); Li(c); B(c); }
void eo8_215(Cube *c) { F(c); Li(c); B(c); }
void eo8_216(Cube *c) { L(c); F(c); Di(c); B(c); }
void eo8_217(Cube *c) { D(c); L(c); B(c); D(c); F(c); }
void eo8_218(Cube *c) { D(c); F(c); Li(c); B(c); }
void eo8_219(Cube *c) { L(c); B(c); D(c); F(c); }
void eo8_220(Cube *c) { U2(c); Ri(c); F(c); D(c); B(c); }
void eo8_221(Cube *c) { U2(c); F(c); R(c); B(c); }
void eo8_222(Cube *c) { U2(c); F(c); Di(c); R(c); B(c); }
void eo8_223(Cube *c) { U2(c); Ri(c); B(c); Di(c); F(c); }
void eo8_224(Cube *c) { U2(c); D(c); F(c); R(c); B(c); }
void eo8_225(Cube *c) { B2(c); L(c); B(c); D(c); F(c); }
void eo8_226(Cube *c) { F(c); Ri(c); Li(c); B(c); }
void eo8_227(Cube *c) { D(c); F(c); Ri(c); Li(c); B(c); }
void eo8_228(Cube *c) { U2(c); F(c); R(c); L(c); B(c); }
void eo8_229(Cube *c) { Di(c); F(c); Ri(c); Li(c); B(c); }
void eo8_230(Cube *c) { U2(c); R(c); F(c); D(c); B(c); }
void eo8_231(Cube *c) { U2(c); B(c); Ri(c); F(c); }
void eo8_232(Cube *c) { F2(c); Li(c); F(c); Di(c); B(c); }
void eo8_233(Cube *c) { U2(c); R(c); B(c); Di(c); F(c); }
void eo8_234(Cube *c) { U2(c); D(c); B(c); Ri(c); F(c); }
void eo8_235(Cube *c) { U2(c); B(c); D(c); Ri(c); F(c); }
void eo8_236(Cube *c) { U2(c); B2(c); R(c); F(c); B(c); }
void eo8_237(Cube *c) { Di(c); F2(c); L(c); F(c); B(c); }
void eo8_238(Cube *c) { F2(c); L(c); F(c); B(c); }
void eo8_239(Cube *c) { D(c); F2(c); L(c); F(c); B(c); }
void eo8_240(Cube *c) { U2(c); R(c); F(c); B(c); }
void eo8_241(Cube *c) { U2(c); D(c); R(c); F(c); B(c); }
void eo8_242(Cube *c) { U(c); D2(c); U(c); R(c); F(c); B(c); }
void eo8_243(Cube *c) { U2(c); Di(c); R(c); F(c); B(c); }
void eo8_244(Cube *c) { U2(c); R(c); F(c); L(c); B(c); }
void eo8_245(Cube *c) { D(c); B(c); Di(c); L(c); F(c); }
void eo8_246(Cube *c) { B(c); L(c); F(c); }
void eo8_247(Cube *c) { Li(c); F(c); Di(c); B(c); }
void eo8_248(Cube *c) { B(c); Di(c); L(c); F(c); }
void eo8_249(Cube *c) { D(c); B(c); L(c); F(c); }
void eo8_250(Cube *c) { Li(c); B(c); D(c); F(c); }
void eo8_251(Cube *c) { D2(c); L(c); F(c); B(c); }
void eo8_252(Cube *c) { Di(c); L(c); F(c); B(c); }
void eo8_253(Cube *c) { L(c); F(c); B(c); }
void eo8_254(Cube *c) { D(c); L(c); F(c); B(c); }
void eo8_255(Cube *c) { U2(c); F2(c); R(c); F(c); B(c); }
void eo8_256(Cube *c) { Di(c); B2(c); L(c); F(c); B(c); }
void eo8_257(Cube *c) { B2(c); L(c); F(c); B(c); }
void eo8_258(Cube *c) { D(c); B2(c); L(c); F(c); B(c); }
void eo8_259(Cube *c) { L(c); F(c); Ri(c); B(c); }
void eo8_260(Cube *c) { B(c); R(c); L(c); F(c); }
void eo8_261(Cube *c) { D(c); B(c); R(c); L(c); F(c); }
void eo8_262(Cube *c) { U2(c); B(c); Ri(c); Li(c); F(c); }
void eo8_263(Cube *c) { Di(c); B(c); R(c); L(c); F(c); }
void eo8_264(Cube *c) { L(c); B(c); R(c); F(c); }
void eo8_265(Cube *c) { U2(c); R(c); B(c); Li(c); F(c); }
void eo8_266(Cube *c) { F(c); D(c); B(c); }
void eo8_267(Cube *c) { F(c); B(c); }
void eo8_268(Cube *c) { F(c); Di(c); B(c); }
void eo8_269(Cube *c) { B(c); Di(c); F(c); }
void eo8_270(Cube *c) { D(c); F(c); B(c); }
void eo8_271(Cube *c) { B(c); D(c); F(c); }
void eo8_272(Cube *c) { D2(c); F(c); L(c); B(c); }
void eo8_273(Cube *c) { Di(c); F(c); L(c); B(c); }
void eo8_274(Cube *c) { F(c); L(c); B(c); }
void eo8_275(Cube *c) { D(c); F(c); L(c); B(c); }
void eo8_276(Cube *c) { F(c); Ri(c); B(c); }
void eo8_277(Cube *c) { D(c); F(c); Ri(c); B(c); }
void eo8_278(Cube *c) { D2(c); F(c); Ri(c); B(c); }
void eo8_279(Cube *c) { Di(c); F(c); Ri(c); B(c); }
void eo8_280(Cube *c) { R(c); F(c); R(c); L(c); B(c); }
void eo8_281(Cube *c) { B(c); R(c); F(c); }
void eo8_282(Cube *c) { D(c); B(c); R(c); F(c); }
void eo8_283(Cube *c) { D2(c); B(c); R(c); F(c); }
void eo8_284(Cube *c) { Di(c); B(c); R(c); F(c); }
void eo8_285(Cube *c) { R2(c); F(c); R(c); L(c); B(c); }
void eo8_286(Cube *c) { R(c); D2(c); F(c); Ri(c); B(c); }
void eo8_287(Cube *c) { D2(c); B(c); Li(c); F(c); }
void eo8_288(Cube *c) { Di(c); B(c); Li(c); F(c); }
void eo8_289(Cube *c) { B(c); Li(c); F(c); }
void eo8_290(Cube *c) { D(c); B(c); Li(c); F(c); }
void eo8_291(Cube *c) { R2(c); U2(c); L(c); F(c); B(c); }
void eo8_292(Cube *c) { R2(c); B(c); Ri(c); Li(c); F(c); }
void eo8_293(Cube *c) { Ri(c); B(c); Ri(c); Li(c); F(c); }
void eo8_294(Cube *c) { Ui(c); F(c); U(c); D(c); B(c); }
void eo8_295(Cube *c) { B(c); Ui(c); F(c); }
void eo8_296(Cube *c) { U2(c); F(c); Ui(c); Di(c); B(c); }
void eo8_297(Cube *c) { B(c); Ui(c); Di(c); F(c); }
void eo8_298(Cube *c) { D(c); B(c); Ui(c); F(c); }
void eo8_299(Cube *c) { U(c); B(c); U(c); D(c); F(c); }
void eo8_300(Cube *c) { D2(c); Li(c); B(c); Ui(c); F(c); }
void eo8_301(Cube *c) { Di(c); Li(c); B(c); Ui(c); F(c); }
void eo8_302(Cube *c) { Li(c); B(c); Ui(c); F(c); }
void eo8_303(Cube *c) { D(c); Li(c); B(c); Ui(c); F(c); }
void eo8_304(Cube *c) { U(c); R(c); B(c); U(c); F(c); }
void eo8_305(Cube *c) { U(c); D(c); R(c); B(c); U(c); F(c); }
void eo8_306(Cube *c) { B2(c); Li(c); B(c); Ui(c); F(c); }
void eo8_307(Cube *c) { U(c); R(c); B(c); U(c); D(c); F(c); }
void eo8_308(Cube *c) { Ui(c); Li(c); F(c); U(c); Ri(c); B(c); }
void eo8_309(Cube *c) { B(c); Ui(c); R(c); F(c); }
void eo8_310(Cube *c) { D(c); B(c); Ui(c); R(c); F(c); }
void eo8_311(Cube *c) { D2(c); B(c); Ui(c); R(c); F(c); }
void eo8_312(Cube *c) { Di(c); B(c); Ui(c); R(c); F(c); }
void eo8_313(Cube *c) { Li(c); B(c); Ui(c); R(c); F(c); }
void eo8_314(Cube *c) { U(c); R(c); L2(c); B(c); Ui(c); F(c); }
void eo8_315(Cube *c) { D2(c); L(c); B(c); Ui(c); F(c); }
void eo8_316(Cube *c) { Di(c); L(c); B(c); Ui(c); F(c); }
void eo8_317(Cube *c) { L(c); B(c); Ui(c); F(c); }
void eo8_318(Cube *c) { D(c); L(c); B(c); Ui(c); F(c); }
void eo8_319(Cube *c) { R2(c); Ui(c); L(c); F(c); B(c); }
void eo8_320(Cube *c) { U(c); R(c); B(c); U(c); Li(c); F(c); }
void eo8_321(Cube *c) { L(c); B(c); Ui(c); R(c); F(c); }
void eo8_322(Cube *c) { R2(c); B(c); U(c); F(c); }
void eo8_323(Cube *c) { F2(c); D(c); F(c); B(c); }
void eo8_324(Cube *c) { L2(c); B(c); Ui(c); F(c); }
void eo8_325(Cube *c) { U2(c); B2(c); D(c); F(c); B(c); }
void eo8_326(Cube *c) { F2(c); D(c); F(c); L(c); B(c); }
void eo8_327(Cube *c) { F2(c); Di(c); F(c); Ri(c); B(c); }
void eo8_328(Cube *c) { L2(c); B(c); Ui(c); R(c); F(c); }
void eo8_329(Cube *c) { R2(c); B(c); U(c); Li(c); F(c); }
void eo8_330(Cube *c) { U(c); L2(c); F(c); Di(c); B(c); }
void eo8_331(Cube *c) { U(c); L2(c); D(c); F(c); B(c); }
void eo8_332(Cube *c) { F2(c); U(c); F(c); B(c); }
void eo8_333(Cube *c) { Ui(c); R2(c); D(c); F(c); B(c); }
void eo8_334(Cube *c) { U(c); F(c); D(c); Li(c); B(c); }
void eo8_335(Cube *c) { U(c); F(c); Li(c); B(c); }
void eo8_336(Cube *c) { U(c); L(c); F(c); Di(c); B(c); }
void eo8_337(Cube *c) { U(c); D(c); L(c); B(c); D(c); F(c); }
void eo8_338(Cube *c) { U(c); D(c); F(c); Li(c); B(c); }
void eo8_339(Cube *c) { U(c); L(c); B(c); D(c); F(c); }
void eo8_340(Cube *c) { Ui(c); Ri(c); F(c); D(c); B(c); }
void eo8_341(Cube *c) { Ui(c); F(c); R(c); B(c); }
void eo8_342(Cube *c) { Ui(c); F(c); Di(c); R(c); B(c); }
void eo8_343(Cube *c) { Ui(c); Ri(c); B(c); Di(c); F(c); }
void eo8_344(Cube *c) { Ui(c); Di(c); F(c); R(c); B(c); }
void eo8_345(Cube *c) { U(c); B2(c); L(c); B(c); D(c); F(c); }
void eo8_346(Cube *c) { U(c); F(c); Ri(c); Li(c); B(c); }
void eo8_347(Cube *c) { U(c); L(c); D(c); F(c); Ri(c); B(c); }
void eo8_348(Cube *c) { Ui(c); F(c); R(c); L(c); B(c); }
void eo8_349(Cube *c) { U(c); L(c); Di(c); F(c); Ri(c); B(c); }
void eo8_350(Cube *c) { Ui(c); R(c); F(c); D(c); B(c); }
void eo8_351(Cube *c) { Ui(c); B(c); Ri(c); F(c); }
void eo8_352(Cube *c) { U(c); F2(c); Li(c); F(c); Di(c); B(c); }
void eo8_353(Cube *c) { Ui(c); R(c); B(c); Di(c); F(c); }
void eo8_354(Cube *c) { Ui(c); Di(c); B(c); Ri(c); F(c); }
void eo8_355(Cube *c) { Ui(c); B(c); D(c); Ri(c); F(c); }
void eo8_356(Cube *c) { Ui(c); B2(c); R(c); F(c); B(c); }
void eo8_357(Cube *c) { U(c); L(c); D(c); B(c); R(c); F(c); }
void eo8_358(Cube *c) { U(c); F2(c); L(c); F(c); B(c); }
void eo8_359(Cube *c) { U(c); D(c); F2(c); L(c); F(c); B(c); }
void eo8_360(Cube *c) { Ui(c); R(c); F(c); B(c); }
void eo8_361(Cube *c) { Ui(c); R(c); F(c); Di(c); B(c); }
void eo8_362(Cube *c) { Ui(c); D2(c); R(c); F(c); B(c); }
void eo8_363(Cube *c) { Ui(c); Di(c); R(c); F(c); B(c); }
void eo8_364(Cube *c) { Ui(c); R(c); F(c); L(c); B(c); }
void eo8_365(Cube *c) { U(c); D(c); B(c); Di(c); L(c); F(c); }
void eo8_366(Cube *c) { U(c); B(c); L(c); F(c); }
void eo8_367(Cube *c) { U(c); Li(c); F(c); Di(c); B(c); }
void eo8_368(Cube *c) { U(c); B(c); Di(c); L(c); F(c); }
void eo8_369(Cube *c) { U(c); D(c); B(c); L(c); F(c); }
void eo8_370(Cube *c) { U(c); Li(c); B(c); D(c); F(c); }
void eo8_371(Cube *c) { U(c); D2(c); L(c); F(c); B(c); }
void eo8_372(Cube *c) { U(c); L(c); F(c); D(c); B(c); }
void eo8_373(Cube *c) { U(c); L(c); F(c); B(c); }
void eo8_374(Cube *c) { U(c); D(c); L(c); F(c); B(c); }
void eo8_375(Cube *c) { Ui(c); F2(c); R(c); F(c); B(c); }
void eo8_376(Cube *c) { U(c); Li(c); D(c); F(c); Ri(c); B(c); }
void eo8_377(Cube *c) { U(c); B2(c); L(c); F(c); B(c); }
void eo8_378(Cube *c) { U(c); D(c); B2(c); L(c); F(c); B(c); }
void eo8_379(Cube *c) { U(c); L(c); F(c); Ri(c); B(c); }
void eo8_380(Cube *c) { U(c); B(c); R(c); L(c); F(c); }
void eo8_381(Cube *c) { U(c); D(c); B(c); R(c); L(c); F(c); }
void eo8_382(Cube *c) { Ui(c); B(c); Ri(c); Li(c); F(c); }
void eo8_383(Cube *c) { U(c); Li(c); Di(c); B(c); R(c); F(c); }
void eo8_384(Cube *c) { U(c); L(c); B(c); R(c); F(c); }
void eo8_385(Cube *c) { Ui(c); R(c); B(c); Li(c); F(c); }
void eo8_386(Cube *c) { U(c); F(c); U(c); D(c); B(c); }
void eo8_387(Cube *c) { F(c); Ui(c); B(c); }
void eo8_388(Cube *c) { F(c); Ui(c); Di(c); B(c); }
void eo8_389(Cube *c) { U2(c); B(c); Ui(c); Di(c); F(c); }
void eo8_390(Cube *c) { D(c); F(c); Ui(c); B(c); }
void eo8_391(Cube *c) { Ui(c); B(c); U(c); D(c); F(c); }
void eo8_392(Cube *c) { D2(c); F(c); Ui(c); L(c); B(c); }
void eo8_393(Cube *c) { Di(c); F(c); Ui(c); L(c); B(c); }
void eo8_394(Cube *c) { F(c); Ui(c); L(c); B(c); }
void eo8_395(Cube *c) { D(c); F(c); Ui(c); L(c); B(c); }
void eo8_396(Cube *c) { R(c); F(c); Ui(c); B(c); }
void eo8_397(Cube *c) { D(c); R(c); F(c); Ui(c); B(c); }
void eo8_398(Cube *c) { D2(c); R(c); F(c); Ui(c); B(c); }
void eo8_399(Cube *c) { Di(c); R(c); F(c); Ui(c); B(c); }
void eo8_400(Cube *c) { R(c); F(c); Ui(c); L(c); B(c); }
void eo8_401(Cube *c) { Ri(c); F(c); Ui(c); B(c); }
void eo8_402(Cube *c) { D(c); Ri(c); F(c); Ui(c); B(c); }
void eo8_403(Cube *c) { D2(c); Ri(c); F(c); Ui(c); B(c); }
void eo8_404(Cube *c) { Di(c); Ri(c); F(c); Ui(c); B(c); }
void eo8_405(Cube *c) { Ri(c); F(c); Ui(c); L(c); B(c); }
void eo8_406(Cube *c) { R(c); L2(c); F(c); U(c); B(c); }
void eo8_407(Cube *c) { F2(c); Ri(c); F(c); Ui(c); B(c); }
void eo8_408(Cube *c) { U(c); L(c); F(c); U(c); D(c); B(c); }
void eo8_409(Cube *c) { U(c); L(c); F(c); U(c); B(c); }
void eo8_410(Cube *c) { U(c); D(c); L(c); F(c); U(c); B(c); }
void eo8_411(Cube *c) { U(c); R2(c); U(c); L(c); F(c); B(c); }
void eo8_412(Cube *c) { U(c); L(c); F(c); U(c); Ri(c); B(c); }
void eo8_413(Cube *c) { Ui(c); Ri(c); B(c); U(c); Li(c); F(c); }
void eo8_414(Cube *c) { U(c); F(c); D(c); B(c); }
void eo8_415(Cube *c) { U(c); F(c); B(c); }
void eo8_416(Cube *c) { U(c); F(c); Di(c); B(c); }
void eo8_417(Cube *c) { U(c); B(c); Di(c); F(c); }
void eo8_418(Cube *c) { U(c); D(c); F(c); B(c); }
void eo8_419(Cube *c) { U(c); B(c); D(c); F(c); }
void eo8_420(Cube *c) { U(c); D2(c); F(c); L(c); B(c); }
void eo8_421(Cube *c) { U(c); F(c); L(c); D(c); B(c); }
void eo8_422(Cube *c) { U(c); F(c); L(c); B(c); }
void eo8_423(Cube *c) { U(c); D(c); F(c); L(c); B(c); }
void eo8_424(Cube *c) { U(c); F(c); Ri(c); B(c); }
void eo8_425(Cube *c) { U(c); D(c); F(c); Ri(c); B(c); }
void eo8_426(Cube *c) { U(c); D2(c); F(c); Ri(c); B(c); }
void eo8_427(Cube *c) { Ui(c); Di(c); F(c); Ri(c); B(c); }
void eo8_428(Cube *c) { R(c); U(c); F(c); L(c); B(c); }
void eo8_429(Cube *c) { U(c); B(c); R(c); F(c); }
void eo8_430(Cube *c) { U(c); D(c); B(c); R(c); F(c); }
void eo8_431(Cube *c) { U(c); D2(c); B(c); R(c); F(c); }
void eo8_432(Cube *c) { U(c); B(c); R(c); D(c); F(c); }
void eo8_433(Cube *c) { Ri(c); U(c); F(c); L(c); B(c); }
void eo8_434(Cube *c) { U(c); R(c); D2(c); F(c); Ri(c); B(c); }
void eo8_435(Cube *c) { U(c); D2(c); B(c); Li(c); F(c); }
void eo8_436(Cube *c) { Ui(c); Di(c); B(c); Li(c); F(c); }
void eo8_437(Cube *c) { U(c); B(c); Li(c); F(c); }
void eo8_438(Cube *c) { U(c); D(c); B(c); Li(c); F(c); }
void eo8_439(Cube *c) { U(c); R2(c); U2(c); L(c); F(c); B(c); }
void eo8_440(Cube *c) { R(c); U(c); B(c); Li(c); F(c); }
void eo8_441(Cube *c) { Ri(c); U(c); B(c); Li(c); F(c); }
void eo8_442(Cube *c) { U(c); R2(c); F(c); Ui(c); B(c); }
void eo8_443(Cube *c) { Ui(c); F2(c); D(c); F(c); B(c); }
void eo8_444(Cube *c) { L2(c); U(c); F(c); B(c); }
void eo8_445(Cube *c) { U(c); B2(c); D(c); F(c); B(c); }
void eo8_446(Cube *c) { U(c); R2(c); F(c); Ui(c); L(c); B(c); }
void eo8_447(Cube *c) { R(c); L2(c); U(c); F(c); B(c); }
void eo8_448(Cube *c) { Ri(c); L2(c); U(c); F(c); B(c); }
void eo8_449(Cube *c) { U(c); B2(c); Di(c); B(c); Li(c); F(c); }
void eo8_450(Cube *c) { F(c); U(c); D(c); B(c); }
void eo8_451(Cube *c) { F(c); U(c); B(c); }
void eo8_452(Cube *c) { Ui(c); F(c); Ui(c); Di(c); B(c); }
void eo8_453(Cube *c) { U(c); B(c); Ui(c); Di(c); F(c); }
void eo8_454(Cube *c) { D(c); F(c); U(c); B(c); }
void eo8_455(Cube *c) { U2(c); B(c); U(c); D(c); F(c); }
void eo8_456(Cube *c) { D2(c); Li(c); F(c); U(c); B(c); }
void eo8_457(Cube *c) { Di(c); Li(c); F(c); U(c); B(c); }
void eo8_458(Cube *c) { Li(c); F(c); U(c); B(c); }
void eo8_459(Cube *c) { D(c); Li(c); F(c); U(c); B(c); }
void eo8_460(Cube *c) { F(c); U(c); Ri(c); B(c); }
void eo8_461(Cube *c) { D(c); F(c); U(c); Ri(c); B(c); }
void eo8_462(Cube *c) { D2(c); F(c); U(c); Ri(c); B(c); }
void eo8_463(Cube *c) { Di(c); F(c); U(c); Ri(c); B(c); }
void eo8_464(Cube *c) { Li(c); F(c); U(c); Ri(c); B(c); }
void eo8_465(Cube *c) { U(c); B(c); Ui(c); R(c); F(c); }
void eo8_466(Cube *c) { U(c); D(c); B(c); Ui(c); R(c); F(c); }
void eo8_467(Cube *c) { F2(c); L(c); F(c); U(c); B(c); }
void eo8_468(Cube *c) { U(c); B(c); R(c); Ui(c); D(c); F(c); }
void eo8_469(Cube *c) { U(c); Li(c); B(c); Ui(c); R(c); F(c); }
void eo8_470(Cube *c) { Ui(c); R(c); L2(c); F(c); U(c); B(c); }
void eo8_471(Cube *c) { D2(c); L(c); F(c); U(c); B(c); }
void eo8_472(Cube *c) { Di(c); L(c); F(c); U(c); B(c); }
void eo8_473(Cube *c) { L(c); F(c); U(c); B(c); }
void eo8_474(Cube *c) { D(c); L(c); F(c); U(c); B(c); }
void eo8_475(Cube *c) { R2(c); U(c); L(c); F(c); B(c); }
void eo8_476(Cube *c) { L(c); F(c); U(c); Ri(c); B(c); }
void eo8_477(Cube *c) { U(c); L(c); B(c); Ui(c); R(c); F(c); }
void eo8_478(Cube *c) { R2(c); F(c); Ui(c); B(c); }
void eo8_479(Cube *c) { U2(c); F2(c); D(c); F(c); B(c); }
void eo8_480(Cube *c) { L2(c); F(c); U(c); B(c); }
void eo8_481(Cube *c) { B2(c); D(c); F(c); B(c); }
void eo8_482(Cube *c) { R2(c); F(c); Ui(c); L(c); B(c); }
void eo8_483(Cube *c) { L2(c); F(c); U(c); Ri(c); B(c); }
void eo8_484(Cube *c) { B2(c); D(c); B(c); R(c); F(c); }
void eo8_485(Cube *c) { B2(c); Di(c); B(c); Li(c); F(c); }
void eo8_486(Cube *c) { R2(c); U(c); F(c); B(c); }
void eo8_487(Cube *c) { U(c); F2(c); D(c); F(c); B(c); }
void eo8_488(Cube *c) { U(c); L2(c); B(c); Ui(c); F(c); }
void eo8_489(Cube *c) { Ui(c); B2(c); D(c); F(c); B(c); }
void eo8_490(Cube *c) { R2(c); U(c); F(c); L(c); B(c); }
void eo8_491(Cube *c) { U(c); F2(c); Di(c); F(c); Ri(c); B(c); }
void eo8_492(Cube *c) { U(c); L2(c); B(c); Ui(c); R(c); F(c); }
void eo8_493(Cube *c) { R2(c); U(c); B(c); Li(c); F(c); }
void eo8_494(Cube *c) { R(c); L2(c); U(c); F(c); Ri(c); B(c); }
static void (*const eo8_moves[496])(Cube*) = {eo8_0, eo8_1, eo8_2, eo8_3, eo8_4, eo8_5, eo8_6, eo8_7, eo8_8, eo8_9, eo8_10, eo8_11, eo8_12, eo8_13, eo8_14, eo8_15, eo8_16, eo8_17, eo8_18, eo8_19, eo8_20, eo8_21, eo8_22, eo8_23, eo8_24, eo8_25, eo8_26, eo8_27, eo8_28, eo8_29, eo8_30, eo8_31, eo8_32, eo8_33, eo8_34, eo8_35, eo8_36, eo8_37, eo8_38, eo8_39, eo8_40, eo8_41, eo8_42, eo8_43, eo8_44, eo8_45, eo8_46, eo8_47, eo8_48, eo8_49, eo8_50, eo8_51, eo8_52, eo8_53, eo8_54, eo8_55, eo8_56, eo8_57, eo8_58, eo8_59, eo8_60, eo8_61, eo8_62, eo8_63, eo8_64, eo8_65, eo8_66, eo8_67, eo8_68, eo8_69, eo8_70, eo8_71, eo8_72, eo8_73, eo8_74, eo8_75, eo8_76, eo8_77, eo8_78, eo8_79, eo8_80, eo8_81, eo8_82, eo8_83, eo8_84, eo8_85, eo8_86, eo8_87, eo8_88, eo8_89, eo8_90, eo8_91, eo8_92, eo8_93, eo8_94, eo8_95, eo8_96, eo8_97, eo8_98, eo8_99, eo8_100, eo8_101, eo8_102, eo8_103, eo8_104, eo8_105, eo8_106, eo8_107, eo8_108, eo8_109, eo8_110, eo8_111, eo8_112, eo8_113, eo8_114, eo8_115, eo8_116, eo8_117, eo8_118, eo8_119, eo8_120, eo8_121, eo8_122, eo8_123, eo8_124, eo8_125, eo8_126, eo8_127, eo8_128, eo8_129, eo8_130, eo8_131, eo8_132, eo8_133, eo8_134, eo8_135, eo8_136, eo8_137, eo8_138, eo8_139, eo8_140, eo8_141, eo8_142, eo8_143, eo8_144, eo8_145, eo8_146, eo8_147, eo8_148, eo8_149, eo8_150, eo8_151, eo8_152, eo8_153, eo8_154, eo8_155, eo8_156, eo8_157, eo8_158, eo8_159, eo8_160, eo8_161, eo8_162, eo8_163, eo8_164, eo8_165, eo8_166, eo8_167, eo8_168, eo8_169, eo8_170, eo8_171, eo8_172, eo8_173, eo8_174, eo8_175, eo8_176, eo8_177, eo8_178, eo8_179, eo8_180, eo8_181, eo8_182, eo8_183, eo8_184, eo8_185, eo8_186, eo8_187, eo8_188, eo8_189, eo8_190, eo8_191, eo8_192, eo8_193, eo8_194, eo8_195, eo8_196, eo8_197, eo8_198, eo8_199, eo8_200, eo8_201, eo8_202, eo8_203, eo8_204, eo8_205, eo8_206, eo8_207, eo8_208, eo8_209, eo8_210, eo8_211, eo8_212, eo8_213, eo8_214, eo8_215, eo8_216, eo8_217, eo8_218, eo8_219, eo8_220, eo8_221, eo8_222, eo8_223, eo8_224, eo8_225, eo8_226, eo8_227, eo8_228, eo8_229, eo8_230, eo8_231, eo8_232, eo8_233, eo8_234, eo8_235, eo8_236, eo8_237, eo8_238, eo8_239, eo8_240, eo8_241, eo8_242, eo8_243, eo8_244, eo8_245, eo8_246, eo8_247, eo8_248, eo8_249, eo8_250, eo8_251, eo8_252, eo8_253, eo8_254, eo8_255, eo8_256, eo8_257, eo8_258, eo8_259, eo8_260, eo8_261, eo8_262, eo8_263, eo8_264, eo8_265, eo8_266, eo8_267, eo8_268, eo8_269, eo8_270, eo8_271, eo8_272, eo8_273, eo8_274, eo8_275, eo8_276, eo8_277, eo8_278, eo8_279, eo8_280, eo8_281, eo8_282, eo8_283, eo8_284, eo8_285, eo8_286, eo8_287, eo8_288, eo8_289, eo8_290, eo8_291, eo8_292, eo8_293, eo8_294, eo8_295, eo8_296, eo8_297, eo8_298, eo8_299, eo8_300, eo8_301, eo8_302, eo8_303, eo8_304, eo8_305, eo8_306, eo8_307, eo8_308, eo8_309, eo8_310, eo8_311, eo8_312, eo8_313, eo8_314, eo8_315, eo8_316, eo8_317, eo8_318, eo8_319, eo8_320, eo8_321, eo8_322, eo8_323, eo8_324, eo8_325, eo8_326, eo8_327, eo8_328, eo8_329, eo8_330, eo8_331, eo8_332, eo8_333, eo8_334, eo8_335, eo8_336, eo8_337, eo8_338, eo8_339, eo8_340, eo8_341, eo8_342, eo8_343, eo8_344, eo8_345, eo8_346, eo8_347, eo8_348, eo8_349, eo8_350, eo8_351, eo8_352, eo8_353, eo8_354, eo8_355, eo8_356, eo8_357, eo8_358, eo8_359, eo8_360, eo8_361, eo8_362, eo8_363, eo8_364, eo8_365, eo8_366, eo8_367, eo8_368, eo8_369, eo8_370, eo8_371, eo8_372, eo8_373, eo8_374, eo8_375, eo8_376, eo8_377, eo8_378, eo8_379, eo8_380, eo8_381, eo8_382, eo8_383, eo8_384, eo8_385, eo8_386, eo8_387, eo8_388, eo8_389, eo8_390, eo8_391, eo8_392, eo8_393, eo8_394, eo8_395, eo8_396, eo8_397, eo8_398, eo8_399, eo8_400, eo8_401, eo8_402, eo8_403, eo8_404, eo8_405, eo8_406, eo8_407, eo8_408, eo8_409, eo8_410, eo8_411, eo8_412, eo8_413, eo8_414, eo8_415, eo8_416, eo8_417, eo8_418, eo8_419, eo8_420, eo8_421, eo8_422, eo8_423, eo8_424, eo8_425, eo8_426, eo8_427, eo8_428, eo8_429, eo8_430, eo8_431, eo8_432, eo8_433, eo8_434, eo8_435, eo8_436, eo8_437, eo8_438, eo8_439, eo8_440, eo8_441, eo8_442, eo8_443, eo8_444, eo8_445, eo8_446, eo8_447, eo8_448, eo8_449, eo8_450, eo8_451, eo8_452, eo8_453, eo8_454, eo8_455, eo8_456, eo8_457, eo8_458, eo8_459, eo8_460, eo8_461, eo8_462, eo8_463, eo8_464, eo8_465, eo8_466, eo8_467, eo8_468, eo8_469, eo8_470, eo8_471, eo8_472, eo8_473, eo8_474, eo8_475, eo8_476, eo8_477, eo8_478, eo8_479, eo8_480, eo8_481, eo8_482, eo8_483, eo8_484, eo8_485, eo8_486, eo8_487, eo8_488, eo8_489, eo8_490, eo8_491, eo8_492, eo8_493, eo8_494};


// EO_10
void eo10_0(Cube *c) { F(c); B(c); D(c); Li(c); Ui(c); B(c); }
void eo10_1(Cube *c) { F(c); U(c); F(c); B(c); Ri(c); F(c); }
void eo10_2(Cube *c) { F(c); B(c); Di(c); Li(c); Ui(c); B(c); }
void eo10_3(Cube *c) { F(c); U(c); R(c); B(c); Di(c); F(c); }
void eo10_4(Cube *c) { F(c); U(c); D(c); B(c); Ri(c); F(c); }
void eo10_5(Cube *c) { F(c); U(c); B(c); D(c); Ri(c); F(c); }
void eo10_6(Cube *c) { F(c); B(c); Li(c); Ui(c); Ri(c); B(c); }
void eo10_7(Cube *c) { F(c); R(c); F(c); L(c); D(c); F(c); B(c); }
void eo10_8(Cube *c) { F(c); Ui(c); Fi(c); L(c); F(c); B(c); }
void eo10_9(Cube *c) { Fi(c); Ui(c); L(c); B(c); Di(c); F(c); }
void eo10_10(Cube *c) { F(c); U(c); F(c); R(c); F(c); B(c); }
void eo10_11(Cube *c) { R(c); F(c); B(c); Di(c); Li(c); Ui(c); B(c); }
void eo10_12(Cube *c) { F(c); B(c); Di(c); R(c); Li(c); B(c); }
void eo10_13(Cube *c) { F(c); U(c); R(c); B(c); D(c); F(c); }
void eo10_14(Cube *c) { R(c); F(c); Ui(c); Fi(c); L(c); F(c); B(c); }
void eo10_15(Cube *c) { F(c); Ui(c); B(c); R(c); L(c); F(c); }
void eo10_16(Cube *c) { Fi(c); D(c); B(c); Ri(c); L(c); F(c); }
void eo10_17(Cube *c) { F(c); L(c); U(c); B(c); Ri(c); F(c); }
void eo10_18(Cube *c) { B(c); F2(c); L(c); U(c); F(c); B(c); D(c); B(c); }
void eo10_19(Cube *c) { F(c); Ui(c); L(c); B(c); R(c); F(c); }
void eo10_20(Cube *c) { F(c); U(c); R(c); B(c); Li(c); F(c); }
void eo10_21(Cube *c) { F(c); R(c); B(c); Di(c); L(c); F(c); }
void eo10_22(Cube *c) { F(c); D(c); B(c); Ri(c); L(c); F(c); }
void eo10_23(Cube *c) { F(c); Li(c); B(c); D(c); Ri(c); F(c); }
void eo10_24(Cube *c) { L(c); F(c); R(c); B(c); Ui(c); Di(c); F(c); }
void eo10_25(Cube *c) { F(c); D(c); L(c); B(c); Ri(c); F(c); }
void eo10_26(Cube *c) { F(c); Di(c); R(c); B(c); L(c); F(c); }
void eo10_27(Cube *c) { R(c); F(c); Li(c); Di(c); B(c); R(c); F(c); }
void eo10_28(Cube *c) { F(c); R(c); F(c); B(c); Di(c); F(c); }
void eo10_29(Cube *c) { F(c); D(c); Fi(c); Bi(c); Ri(c); Fi(c); }
void eo10_30(Cube *c) { F(c); B(c); R(c); Bi(c); Di(c); B(c); }
void eo10_31(Cube *c) { F(c); Di(c); Ri(c); B(c); U(c); F(c); }
void eo10_32(Cube *c) { F(c); B(c); Ui(c); Ri(c); L(c); B(c); }
void eo10_33(Cube *c) { F(c); Di(c); Fi(c); R(c); F(c); B(c); }
void eo10_34(Cube *c) { F(c); Ri(c); B(c); U(c); Li(c); F(c); }
void eo10_35(Cube *c) { F(c); R(c); D(c); B(c); Li(c); F(c); }
void eo10_36(Cube *c) { F(c); Ui(c); B(c); Di(c); L(c); F(c); }
void eo10_37(Cube *c) { F(c); Ui(c); Di(c); B(c); L(c); F(c); }
void eo10_38(Cube *c) { F(c); Ui(c); Li(c); B(c); D(c); F(c); }
void eo10_39(Cube *c) { U(c); F(c); Ri(c); B(c); U(c); D(c); F(c); }
void eo10_40(Cube *c) { F(c); Ui(c); L(c); B(c); Di(c); F(c); }
void eo10_41(Cube *c) { Fi(c); U(c); R(c); B(c); D(c); F(c); }
void eo10_42(Cube *c) { R(c); F(c); L(c); B(c); Ui(c); Di(c); F(c); }
void eo10_43(Cube *c) { U(c); F(c); R(c); D(c); B(c); Li(c); F(c); }
void eo10_44(Cube *c) { F(c); D(c); B(c); U(c); Li(c); F(c); }
void eo10_45(Cube *c) { F(c); B(c); R(c); Fi(c); Ui(c); F(c); }
void eo10_46(Cube *c) { F(c); Li(c); Fi(c); D(c); F(c); B(c); }
void eo10_47(Cube *c) { F(c); L(c); F(c); B(c); Ui(c); F(c); }
void eo10_48(Cube *c) { F(c); Di(c); B(c); Ui(c); R(c); F(c); }
void eo10_49(Cube *c) { F(c); D(c); F(c); L(c); F(c); B(c); }
void eo10_50(Cube *c) { F(c); B(c); Ri(c); Di(c); Li(c); B(c); }
void eo10_51(Cube *c) { F(c); L(c); B(c); Ui(c); R(c); F(c); }
void eo10_52(Cube *c) { F(c); Di(c); B(c); R(c); L(c); F(c); }
void eo10_53(Cube *c) { F(c); Di(c); Fi(c); Bi(c); R(c); Fi(c); }
void eo10_54(Cube *c) { F(c); D(c); L(c); B(c); Ui(c); F(c); }
void eo10_55(Cube *c) { F(c); U(c); F(c); B(c); R(c); F(c); }
void eo10_56(Cube *c) { U(c); F(c); Li(c); Fi(c); D(c); F(c); B(c); }
void eo10_57(Cube *c) { F(c); L(c); F(c); U(c); F(c); B(c); }
void eo10_58(Cube *c) { F(c); Ui(c); Di(c); B(c); R(c); F(c); }
void eo10_59(Cube *c) { U(c); F(c); L(c); Fi(c); B(c); Di(c); F(c); }
void eo10_60(Cube *c) { R(c); F(c); U(c); Fi(c); B(c); Li(c); F(c); }
void eo10_61(Cube *c) { F(c); U(c); B(c); R(c); Li(c); F(c); }
void eo10_62(Cube *c) { Fi(c); U(c); B(c); R(c); Li(c); F(c); }
void eo10_63(Cube *c) { F(c); B(c); Ui(c); Ri(c); Di(c); B(c); }
void eo10_64(Cube *c) { F(c); U(c); D(c); B(c); Li(c); F(c); }
void eo10_65(Cube *c) { F(c); B(c); U(c); Ri(c); Di(c); B(c); }    
static void (*const eo10_moves[66])(Cube*) = {eo10_0, eo10_1, eo10_2, eo10_3, eo10_4, eo10_5, eo10_6, eo10_7, eo10_8, eo10_9, eo10_10, eo10_11, eo10_12, eo10_13, eo10_14, eo10_15, eo10_16, eo10_17, eo10_18, eo10_19, eo10_20, eo10_21, eo10_22, eo10_23, eo10_24, eo10_25, eo10_26, eo10_27, eo10_28, eo10_29, eo10_30, eo10_31, eo10_32, eo10_33, eo10_34, eo10_35, eo10_36, eo10_37, eo10_38, eo10_39, eo10_40, eo10_41, eo10_42, eo10_43, eo10_44, eo10_45, eo10_46, eo10_47, eo10_48, eo10_49, eo10_50, eo10_51, eo10_52, eo10_53, eo10_54, eo10_55, eo10_56, eo10_57, eo10_58, eo10_59, eo10_60, eo10_61, eo10_62, eo10_63, eo10_64, eo10_65};



// EO_12
void eo12_0(Cube *c) { F(c); R(c); L(c); B(c); Ui(c); Di(c); F(c); }
static void (*const eo12_moves[1])(Cube*) = {eo12_0};











void solve_EO(Cube* cube) {
    ZZ_PROFILE_SCOPE(SolveEO);
    int bad_edges[12];
    int bad_ctr = get_bad_edges(cube, bad_edges);

    switch (bad_ctr) {
        case 0:
            break;
        case 2:
            eo2_moves[get_2_Index(bad_edges)](cube);
            break;
        case 4:
            eo4_moves[get_4_Index(bad_edges)](cube);
            break;
        case 6:
            eo6_moves[get_6_Index(bad_edges)](cube);
            break;
        case 8:
            eo8_moves[get_8_Index(bad_edges)](cube);
            break;
        case 10:
            eo10_moves[get_10_Index(bad_edges)](cube);
            break;
        case 12:
            eo12_moves[get_12_Index(bad_edges)](cube);
            break;
    }
}



int get_bad_edges(const Cube* cube, int* bad_edges) {
    // Középső kockák színei
    const uint8_t U = cube->cube[8];   // U közép
    const uint8_t D = cube->cube[53];  // D közép
    const uint8_t L = cube->cube[17];  // L közép
    const uint8_t R = cube->cube[35];  // R közép

    // INLINE get_edges: élek pozíciói
    const uint8_t edge_indices[12][2] = {
        { 1,37}, { 3,28}, { 5,19}, { 7,10},
        {25,12}, {21,34}, {43,30}, {39,16},
        {46,23}, {48,32}, {50,41}, {52,14}
    };
    uint8_t edges[12][2];
    for(int i = 0; i < 12; i++) {
        edges[i][0] = cube->cube[edge_indices[i][0]];  // Első matrica
        edges[i][1] = cube->cube[edge_indices[i][1]];  // Második matrica
    }

    // Rossz élek (bad edges) megszámlálása és indexelése
    int cnt = 0;
    for(int i = 0; i < 12; i++) {
        uint8_t s1 = edges[i][0];
        uint8_t s2 = edges[i][1];

        // Eredeti feltétel: az él egyik fele L/R, vagy a másik fele U/D
        if ((s1 == L || s1 == R) || (s2 == U || s2 == D)) {
            if (bad_edges) bad_edges[cnt] = i;
            cnt++;
        }
    }
    return cnt;
}


int get_2_Index(const int arr[2]) {
    return arr[0] * (2 * 12 - arr[0] - 1) / 2 + (arr[1] - arr[0] - 1);
}

int get_4_Index(const int arr[4]) {
    return
        495
        - ((12 - arr[0]) * (11 - arr[0]) * (10 - arr[0]) * ( 9 - arr[0])    / 24)  // - C(12-a,4)
        + ((11 - arr[0]) * (10 - arr[0]) * ( 9 - arr[0])                    /  6)  // + C(11-a,3)
        - ((12 - arr[1]) * (11 - arr[1]) * (10 - arr[1])                    /  6)  // - C(12-b,3)
        + ((11 - arr[1]) * (10 - arr[1])                                    /  2)  // + C(11-b,2)
        - ((12 - arr[2]) * (11 - arr[2])                                    /  2)  // - C(12-c,2)
        + (arr[3] - arr[2] - 1);                                                   // + C(d-c-1,1)
}

int get_6_Index(const int arr[6]) {
    return
        924
      - ((12 - arr[0]) * (11 - arr[0]) * (10 - arr[0]) * ( 9 - arr[0]) * ( 8 - arr[0]) * ( 7 - arr[0])  / 720)  // - C(12-a,6)
      + ((11 - arr[0]) * (10 - arr[0]) * ( 9 - arr[0]) * ( 8 - arr[0]) * ( 7 - arr[0])                  / 120)  // + C(11-a,5)
      - ((12 - arr[1]) * (11 - arr[1]) * (10 - arr[1]) * ( 9 - arr[1]) * ( 8 - arr[1])                  / 120)  // - C(12-b,5)
      + ((11 - arr[1]) * (10 - arr[1]) * ( 9 - arr[1]) * ( 8 - arr[1])                                  /  24)  // + C(11-b,4)
      - ((12 - arr[2]) * (11 - arr[2]) * (10 - arr[2]) * ( 9 - arr[2])                                  /  24)  // - C(12-c,4)
      + ((11 - arr[2]) * (10 - arr[2]) * ( 9 - arr[2])                                                  /   6)  // + C(11-c,3)
      - ((12 - arr[3]) * (11 - arr[3]) * (10 - arr[3])                                                  /   6)  // - C(12-d,3)
      + ((11 - arr[3]) * (10 - arr[3])                                                                  /   2)  // + C(11-d,2)
      - ((12 - arr[4]) * (11 - arr[4])                                                                  /   2)  // - C(12-e,2)
      +  (11 - arr[4])                                                                                          // + C(11-e,1)
      -  (12 - arr[5])                                                                                          // - C(12-f,1)
    ;
}

int get_8_Index(const int arr[8]) {
    // 1. Bitmask összeállítása
    uint16_t mask = 0;
    for (int i = 0; i < 8; ++i) {
        mask |= (1u << arr[i]);
    }
    // 2. Maradék bitjei (0–11 között)
    uint16_t rem = static_cast<uint16_t>(~mask) & 0x0FFF;
    // 3. Az első négy '0' bit pozíciója
    int a = __builtin_ctz(rem); rem &= rem - 1;
    int b = __builtin_ctz(rem); rem &= rem - 1;
    int c = __builtin_ctz(rem); rem &= rem - 1;
    int d = __builtin_ctz(rem);
    // 4. Segédtömb létrehozása, hogy C++-ban is átadhassuk
    int tmp4[4] = { a, b, c, d };
    // 5. Végső index kiszámolása
    return 494 - get_4_Index(tmp4);
}


int get_10_Index(const int arr[10]) {
    // 1. Bitmask összeállítása
    uint16_t mask = 0;
    for (int i = 0; i < 10; ++i) {
        mask |= (1u << arr[i]);
    }
    // 2. Maradék bitjei (0–11 között)
    uint16_t rem = static_cast<uint16_t>(~mask) & 0x0FFF;
    // 3. A két legkisebb '0' bit pozíciója
    int a = __builtin_ctz(rem);
    int b = __builtin_ctz(rem & (rem - 1));
    // 4. Segédtömb létrehozása
    int tmp2[2] = { a, b };
    // 5. Visszatérés
    return 65 - get_2_Index(tmp2);
}


int get_12_Index(const int arr[12]) {
    return 0;
}













