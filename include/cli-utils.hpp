#pragma once

#include <array>
#include <cstddef>
#include <string_view>
#include <utility>

namespace MSC
{
template <std::size_t arg_size = 16, std::size_t desc_size = 32> class CmdArg
{
public:
  constexpr CmdArg<arg_size, desc_size>(const std::pair<std::string_view, std::string_view> args,
                                        const std::string_view description);

  std::string_view get_arg() const noexcept;
  std::string_view get_description() const noexcept;

private:
  std::array<char, desc_size> description_{};
  std::array<char, arg_size> args_{};
};
} // namespace MSC

#include "cli-utils.ipp"
