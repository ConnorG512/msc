#include "fnv1a.hpp"
#include "key-properties.hpp"
#include "music.hpp"
#include "search.hpp"
#include "sharp-flat.hpp"
#include "tonic-offsets.hpp"

#include "key-properties.hpp"
#include "sharp-flat.hpp"
#include <algorithm>
#include <array>

#include <print>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace
{
static constexpr auto major_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::major), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::major),
                     MSC::generate_hash("f#"), "F# G# A# B C# D# E# F#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::major),
                     MSC::generate_hash("c#"), "C# D# E# F# G# A# B# C#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::major), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::major), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::major), MSC::generate_hash("ab")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::major), MSC::generate_hash("db")),
});

static constexpr auto minor_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::minor), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::minor), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::minor), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::minor),
                     MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("ab")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("gb")),
});

static constexpr auto dorian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::dorian), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::dorian), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian),
                     MSC::generate_hash("f#"), "F# G# A B C# D# E F#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::dorian), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian),
                     MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::dorian),
                     MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::dorian),
                     MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian),
                     MSC::generate_hash("g#"), "G# A# B C# D# E# F# G#"),
});

static constexpr auto phrygian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::phrygian), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::phrygian), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::phrygian), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::phrygian), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("f#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::phrygian), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Flat, MSC::Key::phrygian), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::phrygian), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("d#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("g#")),
});

static constexpr auto lydian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::lydian}, MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("gb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("db")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("ab")),
});

static constexpr auto mixolydian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::mixolydian}, MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::mixolydian}, MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::mixolydian}, MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::mixolydian}, MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::mixolydian},
                     MSC::generate_hash("f#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::mixolydian}, MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::mixolydian}, MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::mixolydian}, MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("db")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("ab")),
});

static constexpr auto locrian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::locrian}, MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::locrian}, MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Flat, MSC::Key::locrian}, MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::locrian}, MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("f#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::locrian}, MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Flat, MSC::Key::locrian}, MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::locrian}, MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("a#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("d#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("g#")),
});

} // namespace

void MSC::search(const std::uint64_t scale_hash_input, const std::uint64_t tonic_hash_input)
{
  enum class Scales
  {
    Ionian = 0,
    Dorian = 1,
    Phrygian = 2,
    Lydian = 3,
    Mixolydian = 4,
    Aeolian = 5,
    Locrian = 6,

    Major = 7,
    Minor = 8,

    MinorPentatonic = 9,
    MajorPentatonic = 10,
  };
  static constexpr std::array scale_hashes{
      MSC::generate_hash("ionian"),           MSC::generate_hash("dorian"),          MSC::generate_hash("phrygian"),
      MSC::generate_hash("lydian"),           MSC::generate_hash("mixolydian"),      MSC::generate_hash("aeolian"),
      MSC::generate_hash("locrian"),          MSC::generate_hash("major"),           MSC::generate_hash("minor"),
      MSC::generate_hash("minor-pentatonic"), MSC::generate_hash("major-pentatonic")};

  auto find_table = [](const std::span<const MSC::SearchTable> search_tables,
                       std::uint64_t input_tonic_hash) -> const MSC::SearchTable &
  {
    const auto found_table = std::ranges::find_if(search_tables, [input_tonic_hash](const MSC::SearchTable &table)
                                                  { return table.arg_hash_ == input_tonic_hash; });

    if (found_table == search_tables.end())
      throw std::runtime_error("Failed to find valid table!");
    else
      return *found_table;
  };

  if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Ionian)) ||
      scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Major)))
  {
    const auto found_table{find_table(major_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Dorian)))
  {
    const auto found_table{find_table(dorian_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Phrygian)))
  {
    const auto found_table{find_table(phrygian_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Lydian)))
  {
    const auto found_table{find_table(lydian_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Mixolydian)))
  {
    const auto found_table{find_table(mixolydian_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Aeolian)) ||
           scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Minor)))
  {
    const auto found_table{find_table(minor_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
  else if (scale_hash_input == scale_hashes.at(std::to_underlying(Scales::Locrian)))
  {
    const auto found_table{find_table(locrian_keys, tonic_hash_input)};
    std::println(stdout, "{:s}", found_table.final_buffer_);
  }
}
