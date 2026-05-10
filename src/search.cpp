#include "chromatic-scales.hpp"
#include "fnv1a.hpp"
#include "key-properties.hpp"
#include "key_intervals.hpp"
#include "music.hpp"
#include "search.hpp"
#include "sharp-flat.hpp"
#include "tonic-offsets.hpp"

#include "key-properties.hpp"
#include "sharp-flat.hpp"
#include <algorithm>
#include <array>

#include <print>
#include <string_view>
#include <utility>

namespace
{
static constexpr std::array<MSC::SearchTable, 13> major_keys{{
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::major}),
        MSC::generate_hash("c"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::major}),
        MSC::generate_hash("d"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::major}),
        MSC::generate_hash("e"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::major}),
        MSC::generate_hash("f"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::major},
                                           "F# G# A# B C# D# E# F#"),
        MSC::generate_hash("f#"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::major}),
        MSC::generate_hash("g"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::major}),
        MSC::generate_hash("a"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::major}),
        MSC::generate_hash("b"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::major},
                                           std::string_view{"C# D# E# F# G# A# B# C#"}),
        MSC::generate_hash("c#"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::major}),
        MSC::generate_hash("bb"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::major}),
        MSC::generate_hash("eb"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::major}),
        MSC::generate_hash("ab"),
    },
    {
        MSC::Key::generate_title_and_notes(MSC::Key::Gen{MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::major}),
        MSC::generate_hash("db"),
    },
}};

static constexpr std::array<MSC::SearchTable, 13> minor_keys{{
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("c"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("d"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::minor}),
        MSC::generate_hash("e"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("f"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("g"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::minor}),
        MSC::generate_hash("a"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::minor}),
        MSC::generate_hash("b"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::minor}),
        MSC::generate_hash("c#"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("bb"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("eb"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::G_SHARP, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("g#"),
    },
    {
        MSC::Key::generate_title_and_notes(
            MSC::Key::Gen{MSC::Tonic::F_SHARP, MSC::NoteType::Flat, MSC::Key::minor}),
        MSC::generate_hash("f#"),
    },
}};

} // namespace

void MSC::search(const std::uint64_t scale_hash_input, const std::uint64_t tonic_hash_input)
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

  auto return_scale_value = [](const std::span<const MSC::SearchTable> search_table, const std::uint64_t scale_hash_input,
                               const std::uint64_t tonic_hash_input) -> std::string_view
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
