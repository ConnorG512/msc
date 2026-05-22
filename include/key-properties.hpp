#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace MSC::Key
{
inline constexpr bool is_correct_scale_size(std::integral auto target_value, std::integral auto... jumps)
{
  // Sum all the jumps to ensure they hit the target (chromatic scale usually 12).
  const auto result{(0 + ... + jumps)};
  return (result == target_value);
}

template <std::size_t interval_size> class Properties
{
public:
  template <std::integral... Intervals>
  consteval Properties(std::string_view name, Intervals... intervals)
      : name_(name), intervals_{static_cast<std::int8_t>(intervals)...}
  {

    static constexpr auto chromatic_scale_length{12};
    if (!is_correct_scale_size(chromatic_scale_length, intervals...))
    {
      throw "Intervals do not add up to given scale!";
    }
  }

  std::string_view name_{};
  std::array<std::int8_t, interval_size> intervals_{};
};

template <std::integral... Intervals> Properties(std::string_view, Intervals...) -> Properties<sizeof...(Intervals)>;

} // namespace MSC::Key

namespace MSC::Key
{
inline constexpr Properties ionian{"Ionian", 2, 2, 1, 2, 2, 2, 1};
inline constexpr Properties dorian{"Dorian", 2, 1, 2, 2, 2, 1, 2};
inline constexpr Properties phrygian{"Phrygian", 1, 2, 2, 2, 1, 2, 2};
inline constexpr Properties lydian{"Lydian", 2, 2, 2, 1, 2, 2, 1};
inline constexpr Properties mixolydian{"Mixolydian", 2, 2, 1, 2, 2, 1, 2};
inline constexpr Properties aeolian{"Aeolian", 2, 1, 2, 2, 1, 2, 2};
inline constexpr Properties locrian{"Locrian", 1, 2, 2, 1, 2, 2, 2};

inline constexpr Properties major{"Major", 2, 2, 1, 2, 2, 2, 1};
inline constexpr Properties minor{"Minor", 2, 1, 2, 2, 1, 2, 2};

inline constexpr Properties minor_pentatonic{"Minor Pentatonic", 3, 2, 2, 3, 2};
inline constexpr Properties major_pentatonic{"Major Pentatonic", 2, 2, 3, 2, 3};
} // namespace MSC::Key
