#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace Music
{

template <std::size_t chromatic_scale_size = 12, std::size_t interval_size = 7> class Key
{
public:
  // Functions:
  consteval Key(const std::int8_t starting_interval, const std::string_view scale_name,
                std::array<std::array<char, 4>, chromatic_scale_size> chromatic_scale = {"C", "C#", "D", "D#", "E", "F",
                                                                                         "F#", "G", "G#", "A", "A#",
                                                                                         "B"},
                std::array<std::int8_t, interval_size> intervals = {2, 2, 1, 2, 2, 2, 1});
  consteval Key() = default;
  consteval std::array<char, 32> generate_key() const;
  consteval std::string_view get_tonic_note() const;

  // Data:
  std::array<std::array<char, 4>, chromatic_scale_size> chromatic_scale{"C",  "C#", "D",  "D#", "E",  "F",
                                                                        "F#", "G",  "G#", "A",  "A#", "B"};
  std::array<std::int8_t, interval_size> intervals{2, 2, 1, 2, 2, 2, 1};
  std::string_view scale_name{"Major"};
  std::int8_t starting_interval{0};
};

template <std::size_t chromatic_scale_size = 12, std::size_t interval_size = 7>
consteval std::array<char, 16> generate_title(const Key<chromatic_scale_size, interval_size> &key);

} // namespace Music

#include "music.ipp"
