#pragma once

#include "string_append.hpp"

#include <cstdint>
#include <initializer_list>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace MSC::Key
{
inline constexpr auto generate_chord = [](const std::vector<std::string_view> &notes,
                                          const std::vector<std::int8_t> &jumps = {2, 4, 6}) -> std::string
{
  std::string output{};

  const std::span trimmed_notes{notes.begin(), notes.size() - 1};
  for (const auto &[index, note] : trimmed_notes | std::views::enumerate)
  {
    const auto root{index};
    const auto third{(index + jumps.at(0)) % trimmed_notes.size()};
    const auto fith{(index + jumps.at(1)) % trimmed_notes.size()};
    const auto seventh{(index + jumps.at(2)) % trimmed_notes.size()};

    output += "\t";
    output += note;
    output += "-";
    output += notes.at(third);
    output += "-";
    output += notes.at(fith);
    output += "-(";
    output += notes.at(seventh);
    output += ")";
    output += "\n";
  }

  return output;
};

inline constexpr auto standard_chord = [](std::string_view key)
{
  std::string_view current_key{key.data(), key.find('\0')};

  auto notes = current_key | std::views::split(' ') |
               std::views::transform([](auto &&note_str) { return std::string_view(note_str); }) |
               std::ranges::to<std::vector<std::string_view>>();

  std::string output{generate_chord(notes)};
  return output;
};

inline constexpr auto pentatonic_chord = [](std::string_view key)
{
  std::string_view current_key{key.data(), key.find('\0')};

  auto notes = current_key | std::views::split(' ') |
               std::views::transform([](auto &&note_str) { return std::string_view(note_str); }) |
               std::ranges::to<std::vector<std::string_view>>();

  return std::string{"Consider using the Major / Minor of the derived key for harmoy.\n\n" + generate_chord(notes)};
};
} // namespace MSC::Key
