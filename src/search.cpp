#include "chromatic-scales.hpp"
#include "fnv1a.hpp"
#include "key_intervals.hpp"
#include "music.hpp"
#include "search.hpp"
#include "tonic-offsets.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string_view>
#include <print>

namespace
{
//static constexpr std::array<MSC::SearchTable, 13> major_keys{
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::C, "Major"}),
//    MSC::generate_hash("c"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D, "Major"}),
//    MSC::generate_hash("d"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E, "Major"}),
//    MSC::generate_hash("e"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F, "Major"}),
//    MSC::generate_hash("f"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::G, "Major"}),
//    MSC::generate_hash("g"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A, "Major"}),
//    MSC::generate_hash("a"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B, "Major"}),
//    MSC::generate_hash("b"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F_SHARP, "Major"}),
//    MSC::generate_hash("f#"),
//    MSC::generate_title_and_notes(
//        MSC::Key{MSC::Tonic::C_SHARP, "Major", {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}}),
//    MSC::generate_hash("c#"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B_FLAT, "Major"}),
//    MSC::generate_hash("bb"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E_FLAT, "Major"}),
//    MSC::generate_hash("eb"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A_FLAT, "Major"}),
//    MSC::generate_hash("ab"),
//    MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D_FLAT, "Major"}),
//    MSC::generate_hash("db"),
//};
  
  static constexpr std::array<MSC::SearchTable, 13> major_keys {{
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
//    {
//      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::F}),
//      MSC::generate_hash("f"),
//    },
//    {
//      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::G}),
//      MSC::generate_hash("g"),
//    },
//    {
//      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A}),
//      MSC::generate_hash("a"),
//    },
    {
      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B}),
      MSC::generate_hash("b"),
    },
//    {
//      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::C_SHARP, {"B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}}),
//      MSC::generate_hash("c#"),
//    },
    {
      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::B_FLAT, MSC::ChromaticScales::standard_flat}),
      MSC::generate_hash("bb"),
    },
//    {
//      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::E_FLAT}),
//      MSC::generate_hash("eb"),
//    },
    {
      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::A_FLAT, MSC::ChromaticScales::standard_flat}),
      MSC::generate_hash("ab"),
    },
//    {
//      MSC::generate_title_and_notes(MSC::Key{MSC::Tonic::D_FLAT}),
//      MSC::generate_hash("db"),
//    },
  }};

} // namespace

void MSC::search(const std::size_t scale_hash, const std::size_t tonic_hash)
{
  static constexpr std::array<std::size_t, 2> scale_hashes {
    MSC::generate_hash("major"),
    MSC::generate_hash("minor"),
  };

  if(scale_hash == scale_hashes.at(0))
  {
    const auto tonic_result = std::ranges::find_if(major_keys, [&tonic_hash](const MSC::SearchTable& key){return key.arg_hash == tonic_hash;});
    if(tonic_result == major_keys.end())
      return;
    else 
      std::println(stdout, "{:s}", tonic_result->key_output);
  }
  else if(scale_hash == scale_hashes.at(1))
  {
    std::println(stdout, "Minor {} found!", scale_hashes.at(1));
  }
}
