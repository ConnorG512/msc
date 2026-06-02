#include "chord-policies.hpp"
#include "fnv1a.hpp"
#include "key-properties.hpp"
#include "music.hpp"
#include "search.hpp"
#include "sharp-flat.hpp"
#include "tonic-offsets.hpp"
#include "key-properties.hpp"
#include "sharp-flat.hpp"
#include "string_append.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <meta>

namespace
{
template <std::size_t size> using KeyGen = MSC::Key::Gen<size>;

static constexpr auto major_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("f#"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::B_FLAT, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::E_FLAT, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::A_FLAT, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::D_FLAT, MSC::NoteType::Sharp, MSC::Key::major})},
        .scale_hash_ = MSC::generate_hash("major"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
});

static constexpr auto minor_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("c#"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen{MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("minor"),
        .tonic_hash_ = MSC::generate_hash("gb"),
    },
});

static constexpr auto dorian_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen{MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::minor})},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("f#"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("c#"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::dorian))},
        .scale_hash_ = MSC::generate_hash("dorian"),
        .tonic_hash_ = MSC::generate_hash("g#"),
    },
});

static constexpr auto phrygian_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("f#"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A, MSC::NoteType::Flat, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("c#"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("d#"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::phrygian))},
        .scale_hash_ = MSC::generate_hash("phrygian"),
        .tonic_hash_ = MSC::generate_hash("g#"),
    },
});

static constexpr auto lydian_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("gb"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("db"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::lydian))},
        .scale_hash_ = MSC::generate_hash("lydian"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
});

static constexpr auto mixolydian_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("f#"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("db"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::mixolydian))},
        .scale_hash_ = MSC::generate_hash("mixolydian"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
});

static constexpr auto locrian_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C, MSC::NoteType::Flat, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::E, MSC::NoteType::Flat, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("f#"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A, MSC::NoteType::Flat, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output(KeyGen(MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("db"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::A_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::D_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{
            MSC::Key::generate_final_output(KeyGen(MSC::Tonic::G_SHARP, MSC::NoteType::Sharp, MSC::Key::locrian))},
        .scale_hash_ = MSC::generate_hash("locrian"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
});

static constexpr auto pentatonic_major_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::D, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::F_SHARP, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("f#"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::G, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::B_FLAT, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::E_FLAT, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::A_FLAT, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::D_FLAT, MSC::NoteType::Sharp, MSC::Key::major_pentatonic})},
        .scale_hash_ = MSC::generate_hash("major-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
});

static constexpr auto pentatonic_minor_keys = std::to_array<MSC::SearchTable>({
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::C, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("c"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::D, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("d"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::E, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("e"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::F, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("f"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::G, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("g"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::A, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("a"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::B, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("b"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::C_SHARP, MSC::NoteType::Sharp, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("c#"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::B_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("bb"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::E_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("eb"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::A_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("ab"),
    },
    {
        .final_buffer_{MSC::Key::generate_final_output<5, MSC::Key::pentatonic_chord>(
            KeyGen{MSC::Tonic::G_FLAT, MSC::NoteType::Flat, MSC::Key::minor_pentatonic})},
        .scale_hash_ = MSC::generate_hash("minor-pentatonic"),
        .tonic_hash_ = MSC::generate_hash("gb"),
    },
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

void MSC::list()
{
  static constexpr auto scale_strings = [](){
    enum class scale_names {
      Major,
      Minor,
      
      Phrygian,
      Lydian,
      Mixolydian,
      Aeolian,
      Locrian,

      Minor_Pentatonic,
      Major_Pentatonic,
    };
    const auto scale_size{std::meta::enumerators_of(^^scale_names).size()};
    
    std::array<std::array<char, 32>, scale_size> scale_buffers {};
    
    std::size_t index{0};
    template for (constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^scale_names)))
    {
      std::string enum_res {std::meta::identifier_of(e)};
      std::ranges::copy(enum_res, std::ranges::begin(scale_buffers.at(index)));
      index++;
    }

    // Make strings lowercase and replace underscores with spaces.
    for(auto &str: scale_buffers)
    {
      for(auto &c : str)
      {
        // Convert to lowercase:
        if(c >= 'A' && c <= 'Z' )
        {
          c = c + 32;
        }

        if (c == '_') c = '-';
      }
    }

    return scale_buffers;
  }();

  for(const auto &str : scale_strings)
    std::println(stdout, "{:s}", str);
}
