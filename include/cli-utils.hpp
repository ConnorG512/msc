#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <string_view>
#include <utility>

namespace MSC
{
template <typename T>
concept StrT = std::constructible_from<T, const char *>;

template <std::size_t arg_size = 16, std::size_t desc_size = 32> class CmdArg
{
public:
  constexpr CmdArg(const std::pair<std::string_view, std::string_view> args, const std::string_view description);

  template <StrT RetT = std::string_view> RetT get_arg() const noexcept;

  template <StrT RetT = std::string_view> RetT get_description() const noexcept;

private:
  std::array<char, desc_size> description_{};
  std::array<char, arg_size> args_{};
};
} // namespace MSC

#include "cli-utils.ipp"
