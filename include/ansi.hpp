#pragma once 

#include <string_view>

namespace MSC {
  struct Code {
    consteval Code(std::string_view start, std::string_view end)
      : start_{start}, end_{end} {}

    std::string_view start_ {};
    std::string_view end_ {};
  };
}

namespace MSC::Ansi {
  inline constexpr Code bold {"\u001b[1m", "\u001b[22m"};
  inline constexpr Code italic {"\u001b[3m", "\u001b[23m"};
  inline constexpr Code underline {"\u001b[4m", "\u001b[24m"};
}
