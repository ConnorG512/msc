#pragma once

#include "chromatic-scales.hpp"
#include "key_intervals.hpp"
#include "tonic-offsets.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace MSC
{

template <std::size_t chromatic_scale_size = 12, std::size_t interval_size = 7> class Key
{
public:
  // Functions:
  consteval Key(
      const Tonic starting_interval, std::string_view scale_name = "Major",
      const std::array<std::string_view, chromatic_scale_size> &chromatic_scale = ChromaticScales::standard_sharp,
      const std::array<const std::int8_t, interval_size> &intervals = {KeyIntervals::Major});

  consteval Key() = default;
  consteval std::array<char, 32> generate_key() const;
  consteval std::string_view get_tonic_note() const;

  // Data:
  std::array<std::string_view, chromatic_scale_size> chromatic_scale{ChromaticScales::standard_sharp};
  std::array<std::int8_t, interval_size> intervals{KeyIntervals::Major};
  std::string_view scale_name{"Major"};
  std::int8_t starting_interval{0};
};

// User defined CTAD:
template <std::size_t chromatic_scale_size, std::size_t interval_size>
Key(Tonic, std::string_view, const std::array<std::string_view, chromatic_scale_size> &,
    const std::array<const std::int8_t, interval_size> &) -> Key<chromatic_scale_size, interval_size>;

// Outer Interface:
template <std::size_t chromatic_scale_size = 12, std::size_t interval_size = 7>
consteval std::array<char, 16> generate_title(const Key<chromatic_scale_size, interval_size> &key);

template <std::size_t chromatic_scale_size = 12, std::size_t interval_size = 7>
consteval std::array<char, 64> generate_title_and_notes(const Key<chromatic_scale_size, interval_size> &key);

} // namespace MSC

#include "music.ipp"
