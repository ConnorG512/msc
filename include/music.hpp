#pragma once

#include <array>
#include <cstdint>

namespace Music
{
enum class Tonic
{
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

enum class Scale
{
  MAJOR,
  MINOR,
};

consteval auto calculate_key(const Tonic starting_interval,
                             const std::array<std::uint8_t, 7> intervals = {2, 2, 1, 2, 2, 2, 1},
                             const std::array<std::array<char, 4>, 12> chromatic_scale = {
                                 {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}});

consteval std::array<std::array<char, 32>, 12> create_circle_of_fiths();

consteval std::array<char, 64> prepend_title_to_key(const std::array<char, 32> calculated_key, const Tonic tonic,
                                                    const Scale scale);
} // namespace Music

#include "music.ipp"
