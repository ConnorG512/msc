#pragma once

#include "key-properties.hpp"
#include <algorithm>
#include <functional>
#include <string_view>

template <std::size_t interval_size>
template <typename... Args>
consteval MSC::Key::Properties<interval_size>::Properties(std::string_view name, Args... args)
  : name_(name), intervals_{static_cast<std::int8_t>(args)...}
{
  if(std::ranges::fold_left(intervals_, 0, std::plus<>()) != 12)
    throw "Intervals to not add up to the 12 equal temperment scale!";
}
