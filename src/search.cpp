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
#include <ranges>
#include <stdexcept>
#include <string_view>

namespace
{
static constexpr auto major_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::major),
                     MSC::generate_hash("major"), MSC::generate_hash("f#"), "F# G# A# B C# D# E# F#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::major), MSC::generate_hash("major"),
                     MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::major),
                     MSC::generate_hash("major"), MSC::generate_hash("c#"), "C# D# E# F# G# A# B# C#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::major),
                     MSC::generate_hash("major"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::major),
                     MSC::generate_hash("major"), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::major),
                     MSC::generate_hash("major"), MSC::generate_hash("ab")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::major),
                     MSC::generate_hash("major"), MSC::generate_hash("db")),
});

static constexpr auto minor_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::minor), MSC::generate_hash("minor"),
                     MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::minor),
                     MSC::generate_hash("minor"), MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::minor),
                     MSC::generate_hash("minor"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::minor),
                     MSC::generate_hash("minor"), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::minor),
                     MSC::generate_hash("minor"), MSC::generate_hash("ab")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::minor),
                     MSC::generate_hash("minor"), MSC::generate_hash("gb")),
});

static constexpr auto dorian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian),
                     MSC::generate_hash("dorian"), MSC::generate_hash("f#"), "F# G# A B C# D# E F#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::dorian), MSC::generate_hash("dorian"),
                     MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian),
                     MSC::generate_hash("dorian"), MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::dorian),
                     MSC::generate_hash("dorian"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::dorian),
                     MSC::generate_hash("dorian"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian),
                     MSC::generate_hash("dorian"), MSC::generate_hash("g#"), "G# A# B C# D# E# F# G#"),
});

static constexpr auto phrygian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("f#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("d#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian),
                     MSC::generate_hash("phrygian"), MSC::generate_hash("g#")),
});

static constexpr auto lydian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("lydian"), MSC::generate_hash("gb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::lydian}, MSC::generate_hash("lydian"),
                     MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("lydian"), MSC::generate_hash("db")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("lydian"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("lydian"), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::lydian},
                     MSC::generate_hash("lydian"), MSC::generate_hash("ab")),
});

static constexpr auto mixolydian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("f#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("db")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian},
                     MSC::generate_hash("mixolydian"), MSC::generate_hash("ab")),
});

static constexpr auto locrian_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::E, MSC::NoteType::Flat, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("f#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A, MSC::NoteType::Flat, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::A_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("a#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::D_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("d#")),
    MSC::SearchTable(MSC::Key::Gen{MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian},
                     MSC::generate_hash("locrian"), MSC::generate_hash("g#")),
});

static constexpr auto pentatonic_major_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("f#"), "F# G# A# B C# D# E# F#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("c#"), "C# D# E# F# G# A# B# C#"),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("ab")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::major_pentatonic),
                     MSC::generate_hash("pentatonic_major"), MSC::generate_hash("db")),
});

static constexpr auto pentatonic_minor_keys = std::to_array<MSC::SearchTable>({
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("c")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("d")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("e")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("f")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("g")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("a")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("b")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("c#")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("bb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("eb")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("ab")),
    MSC::SearchTable(MSC::Key::Gen(MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic),
                     MSC::generate_hash("pentatonic_minor"), MSC::generate_hash("gb")),
});
} // namespace

void MSC::search(const std::uint64_t scale_hash_input, const std::uint64_t tonic_hash_input)
{
  auto find_table = [](const std::uint64_t scale_input, const std::uint64_t tonic_input)
  {
    auto search_tables =
        std::views::concat(major_keys, minor_keys, dorian_keys, phrygian_keys, lydian_keys, mixolydian_keys,
                           locrian_keys, pentatonic_major_keys, pentatonic_minor_keys);

    const auto table_result =
        std::ranges::find_if(search_tables, [s_hash = scale_input, t_hash = tonic_input](const auto &table)
                             { return table.scale_hash_ == s_hash && table.tonic_hash_ == t_hash; });
    if (table_result == search_tables.end())
      throw std::runtime_error("Could not find valid search table!");

    return *table_result;
  };

  std::println(stdout, "{:s}", (find_table(scale_hash_input, tonic_hash_input)).final_buffer_);
}
