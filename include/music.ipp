#pragma once

#include "music.hpp"

#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

consteval auto Music::calculate_key(const Music::Tonic starting_interval, const std::array<std::uint8_t, 7> intervals,
                                    const std::array<std::array<char, 4>, 12> chromatic_scale)
{
  std::string output{};

  auto current_interval{std::to_underlying(starting_interval)};
  for (auto interval : intervals)
  {
    output.append(chromatic_scale.at(current_interval % chromatic_scale.size()).data());
    output.push_back(' ');
    current_interval += interval;
  }
  output.append(chromatic_scale.at(std::to_underlying(starting_interval)).data());

  std::array<char, 32> final_buffer{};
  if (output.size() >= final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";

  const auto copy_tail = std::ranges::copy(output, std::ranges::begin(final_buffer)).out;
  *copy_tail = '\0';
  return final_buffer;
}

consteval std::array<std::array<char, 64>, 12> Music::create_circle_of_fiths()
{
  constexpr auto intervals = std::to_array<std::uint8_t>({2, 2, 1, 2, 2, 2, 1});

  return std::to_array({
      Music::prepend_title_to_key(calculate_key(Music::Tonic::C), Music::Tonic::C, Music::Scale::MAJOR),
      Music::prepend_title_to_key(calculate_key(Music::Tonic::G), Music::Tonic::G, Music::Scale::MAJOR),
      Music::prepend_title_to_key(calculate_key(Music::Tonic::D), Music::Tonic::D, Music::Scale::MAJOR),
      Music::prepend_title_to_key(calculate_key(Music::Tonic::A), Music::Tonic::A, Music::Scale::MAJOR),
      Music::prepend_title_to_key(calculate_key(Music::Tonic::E), Music::Tonic::E, Music::Scale::MAJOR),
      Music::prepend_title_to_key(calculate_key(Music::Tonic::B), Music::Tonic::B, Music::Scale::MAJOR),
      Music::prepend_title_to_key(calculate_key(Music::Tonic::F_SHARP, intervals,
                                                {"C", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}),
                                  Music::Tonic::F_SHARP, Music::Scale::MAJOR),

      Music::prepend_title_to_key(calculate_key(Music::Tonic::C_SHARP, intervals,
                                                {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}),
                                  Music::Tonic::C_SHARP, Music::Scale::MAJOR),

      Music::prepend_title_to_key(
          calculate_key(Music::Tonic::F, intervals, {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}),
          Music::Tonic::F, Music::Scale::MAJOR),

      Music::prepend_title_to_key(calculate_key(Music::Tonic::B_FLAT, intervals,
                                                {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}),
                                  Music::Tonic::B_FLAT, Music::Scale::MAJOR),

      Music::prepend_title_to_key(calculate_key(Music::Tonic::E_FLAT, intervals,
                                                {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}),
                                  Music::Tonic::E_FLAT, Music::Scale::MAJOR),

      Music::prepend_title_to_key(calculate_key(Music::Tonic::A_FLAT, intervals,
                                                {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}),
                                  Music::Tonic::A_FLAT, Music::Scale::MAJOR),
  });
}

consteval std::array<char, 64> Music::prepend_title_to_key(const std::array<char, 32> calculated_key, const Tonic tonic,
                                                           const Scale scale)
{
  const std::string selected_tonic = [](const Tonic tonic)
  {
    if (tonic == Tonic::C)
      return "C";
    else if (tonic == Tonic::D)
      return "D";
    else if (tonic == Tonic::E)
      return "E";
    else if (tonic == Tonic::F)
      return "F";
    else if (tonic == Tonic::G)
      return "G";
    else if (tonic == Tonic::A)
      return "A";
    else if (tonic == Tonic::B)
      return "B";

    else if (tonic == Tonic::C_SHARP)
      return "C#";
    else if (tonic == Tonic::D_SHARP)
      return "D#";
    else if (tonic == Tonic::E_SHARP)
      return "E#";
    else if (tonic == Tonic::F_SHARP)
      return "F#";
    else if (tonic == Tonic::G_SHARP)
      return "G#";
    else if (tonic == Tonic::A_SHARP)
      return "G#";
    else if (tonic == Tonic::B_SHARP)
      return "G#";

    else if (tonic == Tonic::C_FLAT)
      return "Cb";
    else if (tonic == Tonic::D_FLAT)
      return "Db";
    else if (tonic == Tonic::E_FLAT)
      return "Eb";
    else if (tonic == Tonic::F_FLAT)
      return "Fb";
    else if (tonic == Tonic::G_FLAT)
      return "Gb";
    else if (tonic == Tonic::A_FLAT)
      return "Ab";
    else if (tonic == Tonic::B_FLAT)
      return "Bb";

    else
      return "FIX";
  }(tonic);

  const std::string_view selected_scale = [](const Scale scale)
  {
    if (scale == Scale::MAJOR)
      return "Major";
    else if (scale == Scale::MINOR)
      return "Minor";
    else
      return "FIX";
  }(scale);

  std::string output{selected_tonic};
  output += ' ';
  output += selected_scale;
  output += ':';
  output += ' ';
  output += calculated_key.data();

  std::array<char, 64> final_buffer{};
  if (output.size() >= final_buffer.size())
    throw "String too big for buffer!";
  else
  {
    std::ranges::copy(output, std::ranges::begin(final_buffer));
    return final_buffer;
  }
}
