#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace MSC::Key
{
template <std::size_t interval_size> class Properties
{
public:
  template <typename... Args>
  consteval Properties(std::string_view name, Args... args);

  std::string_view name_{"Major"};
  std::array<std::int8_t, interval_size> intervals_{};
};

template <typename... Args>
Properties(std::string_view, Args...) -> Properties<sizeof...(Args)>;

#include "key-properties.ipp"
} // namespace MSC::Key
