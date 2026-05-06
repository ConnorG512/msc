#include "chromatic-scales.hpp"
#include "music.hpp"

#include "CLI11.hpp"

#include <array>
#include <cstdlib>
#include <print>
#include <string>

int main(int argc, char **argv)
{
  CLI::App app{"Music scale printer."};
  argv = app.ensure_utf8(argv);

  std::string scale{};
  std::string tonic{};
  app.add_option("-s,--scale", scale, "Chosen Scale.");
  app.add_option("-t,--tonic", tonic, "Chosen Tonic.");

  try
  {
    app.parse(argc, argv);
  }
  catch (const CLI::ParseError &e)
  {
    return app.exit(e);
  }

  if (scale == "major")
  {
    static constexpr auto major_keys =
        std::to_array<std::pair<const std::string_view, const std::array<char, 64>>, 13>({
            {"c", Music::generate_title_and_notes(Music::Key{Music::Tonic::C, "Major"})},
            {"d", Music::generate_title_and_notes(Music::Key{Music::Tonic::D, "Major"})},
            {"e", Music::generate_title_and_notes(Music::Key{Music::Tonic::E, "Major"})},
            {"f", Music::generate_title_and_notes(
                      Music::Key{Music::Tonic::F, "Major", Music::ChromaticScales::standard_flat})},
            {"g", Music::generate_title_and_notes(Music::Key{Music::Tonic::G, "Major"})},
            {"a", Music::generate_title_and_notes(Music::Key{Music::Tonic::A, "Major"})},
            {"b", Music::generate_title_and_notes(Music::Key{Music::Tonic::B, "Major"})},
            {"f#", Music::generate_title_and_notes(Music::Key{Music::Tonic::F_SHARP, "Major"})},
            {"c#",
             Music::generate_title_and_notes(Music::Key{
                 Music::Tonic::C_SHARP, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}})},
            {"bb", Music::generate_title_and_notes(
                       Music::Key{Music::Tonic::B_FLAT, "Major", Music::ChromaticScales::standard_flat})},
            {"eb", Music::generate_title_and_notes(
                       Music::Key{Music::Tonic::E_FLAT, "Major", Music::ChromaticScales::standard_flat})},
            {"ab", Music::generate_title_and_notes(
                       Music::Key{Music::Tonic::A_FLAT, "Major", Music::ChromaticScales::standard_flat})},
            {"db", Music::generate_title_and_notes(
                       Music::Key{Music::Tonic::D_FLAT, "Major", Music::ChromaticScales::standard_flat})},
        });

    for (const auto [flag, key_buffer] : major_keys)
    {
      if (flag == tonic)
      {
        std::println(stdout, "{:s}", key_buffer);
      }
    }
  }
  else
  {
    std::println("No args found, please use --help/-h for more information.");
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
