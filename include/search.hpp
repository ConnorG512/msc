#pragma once

#include <cstddef>
#include <array>

namespace MSC {
  void search(const std::size_t scale_hash, const std::size_t tonic_hash); 

  struct SearchTable 
  {
    std::array<char, 64> key_output{};
    std::size_t arg_hash{};
  };
}
