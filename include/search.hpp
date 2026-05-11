#pragma once

#include "music.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace MSC
{
void search(const std::uint64_t scale_hash, const std::uint64_t tonic_hash);

struct SearchTable
{
  template <std::size_t intervals>
  consteval SearchTable(const MSC::Key::Gen<intervals> &key, std::uint64_t hash, std::string_view override = {})
      : key_output_{MSC::Key::generate_title_and_notes(key)}, jump_strings_{key.get_jump_names()}, arg_hash_{hash}
  {
  }

  std::array<char, 64> key_output_{};
  std::array<char, 64> jump_strings_{};
  std::uint64_t arg_hash_{};
};
} // namespace MSC
