#include "chromatic-scales.hpp"
#include "fnv1a.hpp"
#include "key_intervals.hpp"
#include "music.hpp"
#include "search.hpp"
#include "tonic-offsets.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <print>
#include <string_view>
#include <utility>

namespace
{
static constexpr std::array<MSC::SearchTable, 13> major_keys{{
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::C}),
        MSC::generate_hash("c"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D}),
        MSC::generate_hash("d"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E}),
        MSC::generate_hash("e"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F, "Major", MSC::ChromaticScales::standard_flat}),
        MSC::generate_hash("f"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F_SHARP, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}}),
        MSC::generate_hash("f#"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::G}),
        MSC::generate_hash("g"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A}),
        MSC::generate_hash("a"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B}),
        MSC::generate_hash("b"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{
            MSC::Tonic::C_SHARP, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}}),
        MSC::generate_hash("c#"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B_FLAT, "Major", MSC::ChromaticScales::standard_flat}),
        MSC::generate_hash("bb"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E_FLAT}),
        MSC::generate_hash("eb"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A_FLAT, "Major", MSC::ChromaticScales::standard_flat}),
        MSC::generate_hash("ab"),
    },
    {
        MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D_FLAT}),
        MSC::generate_hash("db"),
    },
}};

static constexpr std::array<MSC::SearchTable, 13> minor_keys{{
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::C, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("c"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::D, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("d"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::E, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("e"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::F, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("f"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::G, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("g"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::A, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("a"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::B, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("b"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::C_SHARP, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("c#"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::B_FLAT, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("bb"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::E_FLAT, "Minor", MSC::ChromaticScales::standard_flat, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("eb"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::G_SHARP, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("g#"),
    },
    {
        MSC::generate_title_and_notes(
            MSC::Key{MSC::Tonic::F_SHARP, "Minor", MSC::ChromaticScales::standard_sharp, MSC::KeyIntervals::Minor}),
        MSC::generate_hash("f#"),
    },
}};

} // namespace

void MSC::search(const std::size_t scale_hash_input, const std::size_t tonic_hash_input)
{
  enum class Scales
  {
    Major = 0,
    Minor = 1,
  };
  static constexpr std::array scale_hashes{
      MSC::generate_hash("major"),
      MSC::generate_hash("minor"),
  };

  auto return_scale_value = [](const std::span<const MSC::SearchTable> search_table, const std::size_t scale_hash_input,
                               const std::size_t tonic_hash_input) -> std::string_view
  {
    const auto tonic_result = std::ranges::find_if(search_table, [&tonic_hash_input](const MSC::SearchTable &key)
                                                   { return key.arg_hash == tonic_hash_input; });
    if (tonic_result == search_table.end())
      return {};
    else
      return std::string_view(tonic_result->key_output).data();
  };

  if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Major)))
    std::println(stdout, "{:s}", return_scale_value(major_keys, scale_hash_input, tonic_hash_input));
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Minor)))
    std::println(stdout, "{:s}", return_scale_value(minor_keys, scale_hash_input, tonic_hash_input));
}
