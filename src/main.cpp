#include "chromatic-scales.hpp"
#include "key_intervals.hpp"
#include "music.hpp"
#include "cli-utils.hpp"

#include "CLI11.hpp"

#include <array>
#include <cstdlib>
#include <print>
#include <string>
#include <string_view>

int main(int argc, char **argv)
{
  static constexpr auto scale_arg {MSC::create_arg({"s", "scale"}, "Chosen Scale.")};
  static constexpr auto tonic_arg {MSC::create_arg({"t", "tonic"}, "Chosen Tonic.")};

  CLI::App app{"Music scale printer."};
  argv = app.ensure_utf8(argv);

  std::string scale{};
  std::string tonic{};
  
  app.add_option(scale_arg.args.data(), scale, scale_arg.description.data());
  app.add_option(tonic_arg.args.data(), tonic, tonic_arg.description.data());

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
            {"c", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::C, "Major"})},
            {"d", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D, "Major"})},
            {"e", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E, "Major"})},
            {"f", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F, "Major", MSC::ChromaticScales::standard_flat})},
            {"g", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::G, "Major"})},
            {"a", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A, "Major"})},
            {"b", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B, "Major"})},
            {"f#", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F_SHARP, "Major"})},
            {"c#",
             MSC::generate_title_and_notes(MSC::Key{
                 MSC::Tonic::C_SHARP, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}})},
            {"bb",
             MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B_FLAT, "Major", MSC::ChromaticScales::standard_flat})},
            {"eb",
             MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E_FLAT, "Major", MSC::ChromaticScales::standard_flat})},
            {"ab",
             MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A_FLAT, "Major", MSC::ChromaticScales::standard_flat})},
            {"db",
             MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D_FLAT, "Major", MSC::ChromaticScales::standard_flat})},
        });

    for (const auto [flag, key_buffer] : major_keys)
    {
      if (flag == tonic)
      {
        std::println(stdout, "{:s}", key_buffer);
      }
    }
  }
  else if (scale == "minor")
  {
    static constexpr auto minor_keys =
        std::to_array<std::pair<const std::string_view, const std::array<char, 64>>, 12>({
            {"c", MSC::generate_title_and_notes(
                      MSC::Key{MSC::Tonic::C, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor})},
            {"d", MSC::generate_title_and_notes(
                      MSC::Key{MSC::Tonic::D, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor})},
            {"e", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E, "Minor", MSC::ChromaticScales::standard_sharp,
                                                         MSC::KeyIntervals::Minor})},
            {"f", MSC::generate_title_and_notes(
                      MSC::Key{MSC::Tonic::F, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor})},
            {"g", MSC::generate_title_and_notes(
                      MSC::Key{MSC::Tonic::G, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor})},
            {"a", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A, "Minor", MSC::ChromaticScales::standard_sharp,
                                                         MSC::KeyIntervals::Minor})},
            {"b", MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B, "Minor", MSC::ChromaticScales::standard_sharp,
                                                         MSC::KeyIntervals::Minor})},
            {"f#", MSC::generate_title_and_notes(MSC::Key{
                       MSC::Tonic::F_SHARP, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor})},
            {"bb", MSC::generate_title_and_notes(MSC::Key{
                       MSC::Tonic::B_FLAT, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor})},
            {"eb", MSC::generate_title_and_notes(MSC::Key{
                       MSC::Tonic::E_FLAT, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor})},
            {"g#", MSC::generate_title_and_notes(MSC::Key{
                       MSC::Tonic::G_SHARP, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor})},
            {"c#", MSC::generate_title_and_notes(MSC::Key{
                       MSC::Tonic::C_SHARP, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor})},
        });

    for (const auto [flag, key_buffer] : minor_keys)
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
