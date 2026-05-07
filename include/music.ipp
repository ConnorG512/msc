#pragma once

#include "music.hpp"

#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval MSC::Key<chromatic_scale_size, interval_size>::Key(
    const Tonic starting_interval, const std::string_view scale_name,
    std::array<std::array<char, 4>, chromatic_scale_size> chromatic_scale,
    std::array<std::int8_t, interval_size> intervals)
    : chromatic_scale{chromatic_scale}, intervals{intervals}, scale_name{scale_name},
      starting_interval{std::to_underlying(starting_interval)}
{
}

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval std::array<char, 32> MSC::Key<chromatic_scale_size, interval_size>::generate_key() const
{
  std::string output{};

  auto current_interval{starting_interval};
  ///
  for (const auto &interval : intervals)
  {
    output.append(chromatic_scale.at(current_interval % chromatic_scale.size()).data());
    output += ' ';
    current_interval += interval;
  }
  ///
  output += chromatic_scale.at(starting_interval).data();
  output += '\0';

  std::array<char, 32> final_buffer{};
  if (output.size() > final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";

  std::ranges::copy(output, std::ranges::begin(final_buffer));
  return final_buffer;
}

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval std::string_view MSC::Key<chromatic_scale_size, interval_size>::get_tonic_note() const
{
  return chromatic_scale.at(starting_interval).data();
}

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval std::array<char, 16> MSC::generate_title(const MSC::Key<chromatic_scale_size, interval_size> &key)
{
  std::string output{};
  output.append(key.get_tonic_note());
  output += ' ';
  output.append(key.scale_name);
  output += ':';
  output += ' ';
  output += '\0';

  std::array<char, 16> final_buffer{};
  if (output.size() >= final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";
  else
  {
    std::ranges::copy(output, std::ranges::begin(final_buffer));
    return final_buffer;
  }
}

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval std::array<char, 64> MSC::generate_title_and_notes(const Key<chromatic_scale_size, interval_size> &key)
{
  std::string output{};
  output.append(key.get_tonic_note().data());
  output += ' ';
  output.append(key.scale_name.data());
  output += ':';
  output += ' ';
  output.append(key.generate_key().data());
  output += ' ';
  output += '\0';

  std::array<char, 64> final_buffer{};
  if (output.size() > final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";
  else
  {
    std::ranges::copy(output, std::ranges::begin(final_buffer));
    return final_buffer;
  }
}
