#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <ranges>
#include <string>
#include <string_view>

namespace MSC
{
template <std::size_t buffer_size>
constexpr std::array<char, buffer_size> append_strings_to_buffer(std::initializer_list<std::string_view> messages)
{
  static_assert(buffer_size != 0, "buffer_size cannot be 0!");

  std::string output{};
  for (const auto &msg : messages)
    output.append(msg);

  if (output.size() >= buffer_size)
    throw "Output string is too large for the buffer size, incease buffer!";
  
  std::array<char, buffer_size> final_buffer{}; 
  std::ranges::copy(output, std::ranges::begin(final_buffer));
  return final_buffer;
}
} // namespace MSC
