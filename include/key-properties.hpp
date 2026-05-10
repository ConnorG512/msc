#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string_view>

namespace MSC::Key
{
template <std::size_t interval_size> class Properties
{
public:
  template <std::integral... Intervals>
  consteval Properties(std::string_view name, Intervals... intervals)
    :name_(name), intervals_{static_cast<std::int8_t>(intervals)...} {
      if(std::ranges::fold_left(intervals_, 0, std::plus<>()) != 12)
      {
        throw "Intervals do not add up to 12 tone scale!";
      }
    } 

  std::string_view name_{};
  std::array<std::int8_t, interval_size> intervals_{};
};

template <std::integral... Intervals>
Properties(std::string_view, Intervals...) -> Properties<sizeof...(Intervals)>;

} // namespace MSC::Key

namespace MSC::Key {
  inline constexpr Properties ionian{"Ionian", 2,2,1,2,2,2,1};
  inline constexpr Properties dorian{"Dorian", 2,1,2,2,2,1,2};
  inline constexpr Properties phrygian{"Phrygian", 1,2,2,2,1,2,2};
  inline constexpr Properties lydian{"Lydian", 2,2,2,1,2,2,1};
  inline constexpr Properties mixolydian{"Mixolydian", 2,2,1,2,2,1,2};
  inline constexpr Properties aeolian{"Aeolian", 2,1,2,2,1,2,2};
  inline constexpr Properties locrian{"Locrian", 1,2,2,1,2,2,2};
  
  inline constexpr Properties major{"Major", 2,2,1,2,2,2,1};
  inline constexpr Properties minor{"Minor", 2,1,2,2,1,2,2};
}
