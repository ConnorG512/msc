#pragma once 

#include "enum-to-string.hpp"

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
}
