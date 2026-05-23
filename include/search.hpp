#pragma once

#include <array>
#include <cstdint>

namespace MSC
{
void search(const std::uint64_t scale_hash, const std::uint64_t tonic_hash);

struct SearchTable
{
  std::array<char, 512> final_buffer_{};
  std::uint64_t scale_hash_{};
  std::uint64_t tonic_hash_{};
};
}

// namespace MSC
