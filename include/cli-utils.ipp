#pragma once

#include "cli-utils.hpp"
#include "string_append.hpp"

#include <cstddef>

template <std::size_t arg_size, std::size_t desc_size>
constexpr MSC::CmdArg<arg_size, desc_size>::CmdArg(const std::pair<std::string_view, std::string_view> args,
                                                   std::string_view description)
    : description_{MSC::append_strings_to_buffer<desc_size>({description})},
      args_{MSC::append_strings_to_buffer<arg_size>({args.first, args.second})}
{
  static_assert(arg_size > 0 && desc_size > 0, "arg_size and desc_size must be greater than 0!");
}
