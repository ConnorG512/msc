#include "music.hpp"

#include <print>

int main()
{
  static constexpr auto c_major{Music::Key<>{}};
  static constexpr auto d_major{Music::Key{2, "Major"}};
  static constexpr auto e_major{Music::Key{4, "Major"}};
  static constexpr auto cs_major{
      Music::Key{1, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}, {2, 2, 1, 2, 2, 2, 1}}};

  std::println("{:s}", Music::generate_title_and_notes(c_major));
  std::println("{:s}", Music::generate_title_and_notes(d_major));
  std::println("{:s}", Music::generate_title_and_notes(e_major));
  std::println("{:s}", Music::generate_title_and_notes(cs_major));

  return 0;
}
