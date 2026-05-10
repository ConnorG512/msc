#pragma once

#include <cstdint>
#include <array>

namespace MSC {
  void search(const std::uint64_t scale_hash, const std::uint64_t tonic_hash); 

  struct SearchTable 
  {
    std::array<char, 64> key_output{};
    std::uint64_t arg_hash{};
  };
}
