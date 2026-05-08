#pragma once

#include "music.hpp"

#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <functional>

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval MSC::Key<chromatic_scale_size, interval_size>::Key(
    const Tonic starting_interval, std::string_view scale_name,
    const std::array<std::string_view, chromatic_scale_size> &chromatic_scale,
    const std::array<std::int8_t, interval_size> &intervals)
    : chromatic_scale_(chromatic_scale), intervals_(intervals), scale_name_(scale_name),
      starting_interval_(std::to_underlying(starting_interval))
{
  if(std::ranges::fold_left(intervals_, 0, std::plus<>()) != 12)
    throw "Intervals do not count up to 12 tone equal temperment!";
}

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval std::array<char, 32> MSC::Key<chromatic_scale_size, interval_size>::generate_key() const
{
  std::string output{};

  auto current_interval{starting_interval_};
  ///
  for (const auto &interval : intervals_)
  {
    output.append(chromatic_scale_.at(current_interval % chromatic_scale_.size()).data());
    output += ' ';
    current_interval += interval;
  }
  ///
  output += chromatic_scale_.at(starting_interval_).data();
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
  return chromatic_scale_.at(starting_interval_).data();
}

template <std::size_t chromatic_scale_size, std::size_t interval_size>
consteval std::array<char, 16> MSC::generate_title(const MSC::Key<chromatic_scale_size, interval_size> &key)
{
  std::string output{};
  output.append(key.get_tonic_note());
  output += ' ';
  output.append(key.scale_name_);
  output += ':';
  output += ' ';
  output += '\0';

  std::array<char, 16> final_buffer{};
  if (output.size() > final_buffer.size())
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
  output.append(key.scale_name_.data());
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
