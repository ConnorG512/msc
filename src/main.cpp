#include "music.hpp"

#include <array>
#include <print>

int main()
{
  static constexpr auto c_major{Music::Key<>{}};
  static constexpr auto d_major{Music::Key{2, "Major"}};
  static constexpr auto e_major{Music::Key{4, "Major"}};
  static constexpr auto cs_major{Music::Key{
      1, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}, {2, 2, 1, 2, 2, 2, 1}}};

  static constexpr auto circle_of_fiths = std::to_array({
      Music::generate_title_and_notes(Music::Key{}),
      Music::generate_title_and_notes(Music::Key{7, "Major"}),
      Music::generate_title_and_notes(Music::Key{2, "Major"}),
      Music::generate_title_and_notes(Music::Key{9, "Major"}),
      Music::generate_title_and_notes(Music::Key{4, "Major"}),
      Music::generate_title_and_notes(Music::Key{11, "Major"}),
      Music::generate_title_and_notes(Music::Key{6, "Major"}),
      Music::generate_title_and_notes(
          Music::Key{1, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}}),
  });

  for (const auto &key : circle_of_fiths)
  {
    std::println("{:s}", key);
  }
  return 0;
}
