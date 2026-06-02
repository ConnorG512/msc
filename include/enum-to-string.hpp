#pragma once 

#include "concepts.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <meta>

namespace MSC 
{
  template <EnumT ET>
  inline consteval auto enum_to_view() {
    constexpr std::size_t enum_size {std::meta::enumerators_of(^^ET).size()};
    auto passed_enum {std::meta::enumerators_of(^^ET)};
    
    auto enum_str_view = passed_enum | std::views::transform([](std::meta::info e){
          return std::meta::identifier_of(e);
        });
    
    std::array<std::string_view, enum_size> final_views {};
    std::ranges::copy(enum_str_view, std::ranges::begin(final_views));

    return final_views;
  };
}
