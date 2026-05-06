#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

namespace MSC
{
template <std::size_t arg_size = 16, std::size_t desc_size = 32> struct CmdArg
{
  std::array<char, desc_size> description{};
  std::array<char, arg_size> args{};
};

template <std::size_t arg_size = 16, std::size_t desc_size = 32>
consteval CmdArg<arg_size, desc_size> create_arg(const std::pair<const std::string_view, const std::string_view> flags,
                                                 const std::string_view description)
{
  std::array<char, arg_size> final_arg_buffer =
      [](const std::pair<const std::string_view, const std::string_view> flags)
  {
    std::string output{""};
    output += '-';
    output.append(flags.first);
    output += ',';
    output.append("--");
    output.append(flags.second);

    std::array<char, arg_size> buffer{};
    if (output.size() >= buffer.size())
      throw "Output is too large for buffer!";
    else
    {
      std::ranges::copy(output, std::ranges::begin(buffer));
      return buffer;
    }
  }(flags);

  std::array<char, desc_size> final_desc_buffer = [](const std::string_view description)
  {
    std::array<char, desc_size> buffer{};
    if (description.size() >= buffer.size())
      throw "Output is too large for buffer!";
    else
    {
      std::ranges::copy(description, std::ranges::begin(buffer));
      return buffer;
    }
  }(description);

  return {final_desc_buffer, final_arg_buffer};
}
} // namespace MSC
