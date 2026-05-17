#pragma once

#include "fnv1a.hpp"
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
      : final_buffer_{MSC::Key::generate_final_output(key)}, arg_hash_{hash}
  {
  }

  std::array<char, 256> final_buffer_{};
  std::uint64_t arg_hash_{};
};
} // namespace MSC
