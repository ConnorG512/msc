#pragma once 

#include <cstdint>

namespace Music {
  enum class Tonic : std::int8_t {
    C = 0,
    D = 2,
    E = 4,
    F = 5,
    G = 7,
    A = 9,
    B = 11,
    
    C_SHARP = 1,
    D_SHARP = 3,
    E_SHARP = 5,
    F_SHARP = 6,
    G_SHARP = 8,
    A_SHARP = 10,
    B_SHARP = 0,

    C_FLAT = 11,
    D_FLAT = 1,
    E_FLAT = 3,
    F_FLAT = 4,
    G_FLAT = 6,
    A_FLAT = 8,
    B_FLAT = 10,
  };
}
