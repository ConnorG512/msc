#pragma once

#include <array>
#include <cstddef>

namespace MSC
{
template <std::size_t arg_size = 16, std::size_t desc_size = 32> struct CmdArg
{
  std::array<char, desc_size> description{};
  std::array<char, arg_size> args{};
};
} // namespace MSC
