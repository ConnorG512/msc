#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string_view>

namespace MSC::Key
{
template <std::size_t interval_size> class Properties
{
public:
  template <typename... Args>
  consteval Properties(std::string_view name, Args... args)
    :name_(name), intervals_{static_cast<std::int8_t>(args)...} {
      if(std::ranges::fold_left(intervals_, 0, std::plus<>()) != 12)
      {
        throw "Intervals do not add up to 12 tone scale!";
      }
    } 

  std::string_view name_{};
  std::array<std::int8_t, interval_size> intervals_{};
};

template <typename... Args>
Properties(std::string_view, Args...) -> Properties<sizeof...(Args)>;

} // namespace MSC::Key

namespace MSC::Key {
  inline constexpr Properties ionian{"Ionian", 2,2,1,2,2,2,1};
  inline constexpr Properties dorain{"Dorian", 2,1,2,2,2,1,2};
  inline constexpr Properties phrygian{"Phrygian", 1,2,2,2,1,2,2};
  inline constexpr Properties lydian{"Lydian", 2,2,2,1,2,2,1};
  inline constexpr Properties mixolydian{"Mixolydian", 2,2,1,2,2,1,2};
  inline constexpr Properties aeolian{"Aeolian", 2,1,2,2,1,2,2};
  inline constexpr Properties locrian{"Locrian", 1,2,2,1,2,2,2};
  
  inline constexpr Properties major{"Major", 2,2,1,2,2,2,1};
  inline constexpr Properties minor{"Minor", 2,1,2,2,1,2,2};
}
