#pragma once 

#include <type_traits>
#include <concepts>

namespace MSC {
  template <typename T>
  concept EnumT = std::is_enum_v<T>;

  template <typename T>
  concept StrT = std::constructible_from<T, const char *>;
}
