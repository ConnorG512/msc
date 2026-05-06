#include "music.hpp"

#include "chromatic-scales.hpp"

#include <array>
#include <print>

int main()
{
  static constexpr auto circle_of_fiths = std::to_array({
      Music::generate_title_and_notes(Music::Key{Music::Tonic::C, "Major"}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::D, "Major"}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::A, "Major"}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::E, "Major"}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::B, "Major"}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::F_SHARP, "Major"}),
      Music::generate_title_and_notes(
          Music::Key{Music::Tonic::C_SHARP, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::F, "Major", Music::ChromaticScales::standard_flat}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::B_FLAT, "Major", Music::ChromaticScales::standard_flat}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::E_FLAT, "Major", Music::ChromaticScales::standard_flat}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::A_FLAT, "Major", Music::ChromaticScales::standard_flat}),
      Music::generate_title_and_notes(Music::Key{Music::Tonic::D_FLAT, "Major", Music::ChromaticScales::standard_flat}),
  });

  for (const auto &key : circle_of_fiths)
  {
    std::println("{:s}", key);
  }
  return 0;
}
