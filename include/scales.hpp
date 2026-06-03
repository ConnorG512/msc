#pragma once 

#include "enum-to-string.hpp"
#include <algorithm>
#include <array>
#include <ranges>
#include <string_view>

namespace MSC {
  enum class ScaleNames {
    Major, // Ionian
    Minor, // Aeolian
    
    Dorian,
    Phrygian,
    Lydian,
    Mixolydian,
    Locrian,

    Minor_Pentatonic,
    Major_Pentatonic,
  };

  inline constexpr auto scale_names_ {MSC::enum_to_view<ScaleNames>()};
  inline constexpr auto scale_titles = [&scale_names_](){
    std::array<std::array<char, 32>, scale_names_.size()> buffers {};
    std::ranges::transform(scale_names_, std::ranges::begin(buffers), [&](std::string_view scale_title){
          std::array<char, 32> buffer {};
          std::ranges::copy(scale_title, std::ranges::begin(buffer));
          buffer.at(scale_title.size()) = '\0';

          for(char &c : buffer | std::views::take(scale_title.size()))
          {
            if(c == '_')
              c = ' ';
          }
          return buffer;
        });
    return buffers;
  }();
}
