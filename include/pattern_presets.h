#ifndef PATTERN_PRESETS_H
#define PATTERN_PRESETS_H

#include <cstdint>

enum class PatternPreset {
    None,
    Checkerboard,
    Anaconda,
    CubeInCubeInCube,
    CubeInCube,
    VerticalStripes,
    Python,
    FourCenters,
    SixCenters,
    SuperFlip
};

static constexpr uint8_t kCheckerboardPattern[54] = {
    1, 6, 1, 6, 1, 6, 1, 6, 1,
    2, 4, 2, 4, 2, 4, 2, 4, 2,
    3, 5, 3, 5, 3, 5, 3, 5, 3,
    4, 2, 4, 2, 4, 2, 4, 2, 4,
    5, 3, 5, 3, 5, 3, 5, 3, 5,
    6, 1, 6, 1, 6, 1, 6, 1, 6
};

static constexpr uint8_t kAnacondaPattern[54] = {
    3, 1, 3, 3, 3, 3, 3, 1, 1,
    6, 2, 6, 2, 6, 6, 6, 6, 2,
    4, 4, 4, 4, 4, 3, 4, 3, 3,
    1, 1, 1, 4, 1, 4, 1, 1, 4,
    2, 5, 2, 2, 2, 2, 2, 5, 5,
    5, 6, 5, 6, 5, 5, 5, 5, 6
};

static constexpr uint8_t kCubeInCubeInCubePattern[54] = {
    4, 4, 4, 1, 3, 1, 4, 4, 1,
    5, 5, 5, 5, 5, 2, 6, 2, 2,
    1, 3, 4, 3, 1, 1, 1, 1, 3,
    1, 4, 3, 3, 3, 3, 3, 4, 4,
    6, 6, 6, 5, 2, 5, 6, 6, 5,
    2, 2, 2, 2, 2, 6, 5, 6, 6
};

#endif
