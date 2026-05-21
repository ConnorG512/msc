#pragma once

#include "string_append.hpp"

#include <ranges>
#include <string_view>
#include <vector>

namespace MSC::Key
{
inline constexpr auto standard_chord = [](std::string_view key)
{
  std::string_view current_key{key.data(), key.find('\0')};

  auto notes = current_key | std::views::split(' ') |
               std::views::transform([](auto &&note_str) { return std::string_view(note_str); }) |
               std::ranges::to<std::vector<std::string_view>>();

  std::string output{};
  for (const auto [index, note] : notes | std::views::enumerate)
  {
    const auto root{index};
    const auto third{(index + 2) % notes.size()};
    const auto fith{(index + 4) % notes.size()};

    output += "\t";
    output += note;
    output += "-";
    output += notes.at(third);
    output += "-";
    output += notes.at(fith);
    output += "\n";
  }

  return append_strings_to_buffer<128>({{output.data(), output.size()}});
};

inline constexpr auto pentatonic_chord = [](std::string_view key)
{
  std::string_view current_key{key.data(), key.find('\0')};

  auto notes = current_key | std::views::split(' ') |
               std::views::transform([](auto &&note_str) { return std::string_view(note_str); }) |
               std::ranges::to<std::vector<std::string_view>>();

  std::string output{};
  for (const auto [index, note] : notes | std::views::enumerate)
  {
    const auto root{index};
    const auto third{(index + 2) % notes.size()};
    const auto fith{(index + 4) % notes.size()};

    output += "\t";
    output += note;
    output += "-";
    output += notes.at(third);
    output += "-";
    output += notes.at(fith);
    output += "\n";
  }

  return append_strings_to_buffer<128>(
      {"Consider using the Major / Minor of the derived key for harmoy.\n", {output.data(), output.size()}});
};
} // namespace MSC::Key
