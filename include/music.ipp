#pragma once

#include "music.hpp"
#include "sharp-flat.hpp"

#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

// Constructor

template <std::size_t interval_size>
consteval MSC::Key::Gen<interval_size>::Gen(Tonic tonic, NoteType type,
                                            const MSC::Key::Properties<interval_size> &key_properties)
    : chromatic_scale_(
          (type == NoteType::Sharp)
              ? std::array<std::string_view, 12>{"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}
              : std::array<std::string_view, 12>{"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}),
      intervals_(key_properties.intervals_), scale_name_(key_properties.name_),
      starting_interval_(std::to_underlying(tonic))

{
}

template <std::size_t interval_size>
consteval std::array<char, 32> MSC::Key::Gen<interval_size>::generate_key(std::string_view key_override) const
{
  auto write_from_chromatic = [this](std::string &output) consteval
  {
    auto current_interval{starting_interval_};
    for (const auto &interval : intervals_)
    {
      output.append(chromatic_scale_.at(current_interval % chromatic_scale_.size()).data());
      output += ' ';
      current_interval += interval;
    }
    output += chromatic_scale_.at(starting_interval_).data();
  };

  std::string output{};
  std::array<char, 32> final_buffer{};

  if (!key_override.empty())
    std::ranges::copy(key_override, std::ranges::begin(final_buffer));
  else
  {
    write_from_chromatic(output);
    if (output.size() > final_buffer.size())
    {
      throw "Output is too big for the final buffer, increase buffer size!";
    }
    else
      std::ranges::copy(output, std::ranges::begin(final_buffer));
  }

  return final_buffer;
}

template <std::size_t interval_size> consteval std::string_view MSC::Key::Gen<interval_size>::get_tonic_note() const
{
  return chromatic_scale_.at(starting_interval_).data();
}

template <std::size_t interval_size> consteval std::array<char, 64> MSC::Key::Gen<interval_size>::get_jump_names() const
{
  enum class Tones
  {
    Semitone = 1,
    Tone = 2,
    MinorThird = 3,
    MajorThird = 4,
  };

  auto setup = intervals_ |
               std::views::transform(
                   [&](const auto interval) consteval -> std::string_view
                   {
                     if (interval == std::to_underlying(Tones::Semitone))
                       return "Semitone";
                     else if (interval == std::to_underlying(Tones::Tone))
                       return "Tone";
                     else if (interval == std::to_underlying(Tones::MinorThird))
                       return "Minor-Third";
                     else if (interval == std::to_underlying(Tones::MajorThird))
                       return "Major-Third";
                     else
                       return "FIXME";
                   }) |
               std::views::join_with(std::string_view{", "}) | std::views::take(63);

  std::array<char, 64> final_buffer{};
  std::ranges::copy(setup, final_buffer.begin());
  return final_buffer;
}

// Outer Interface:
template <std::size_t interval_size>
consteval std::array<char, 16> MSC::Key::generate_title(const MSC::Key::Gen<interval_size> &gen)
{
  std::string output{};
  output.append(gen.get_tonic_note());
  output += ' ';
  output.append(gen.scale_name_);
  output += ':';
  output += ' ';

  std::array<char, 16> final_buffer{};
  if (output.size() > final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";
  else
  {
    std::ranges::copy(output, std::ranges::begin(final_buffer));
    return final_buffer;
  }
}

template <std::size_t interval_size>
consteval std::array<char, 64> MSC::Key::generate_title_and_notes(const MSC::Key::Gen<interval_size> &gen,
                                                                  std::string_view key_override)
{
  std::string output{};
  output.append(gen.get_tonic_note().data());
  output += ' ';
  output.append(gen.scale_name_.data());
  output += ':';
  output += ' ';
  output.append((key_override.empty() ? gen.generate_key(key_override).data() : key_override.data()));
  output += ' ';

  std::array<char, 64> final_buffer{};
  if (output.size() > final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";
  else
  {
    std::ranges::copy(output, std::ranges::begin(final_buffer));
    return final_buffer;
  }
}
