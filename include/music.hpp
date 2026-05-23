#pragma once

#include "key-properties.hpp"
#include "sharp-flat.hpp"
#include "tonic-offsets.hpp"
#include "chord-policies.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace MSC::Key
{
template <std::size_t interval_size> class Gen
{
public:
  // Constructors:
  consteval Gen(Tonic tonic, NoteType type, const MSC::Key::Properties<interval_size> &key_properties);

  // Functions:
  consteval std::array<char, 32> generate_key(std::string_view key_override = {}) const;
  consteval std::string_view get_tonic_note() const;
  consteval std::array<char, 64> get_jump_names() const;

  // Data:
  std::array<std::string_view, 12> chromatic_scale_{};
  std::array<std::int8_t, interval_size> intervals_{};
  std::string_view scale_name_{};
  std::int8_t starting_interval_{};
};

// User defined CTAD:
template <std::size_t interval_size>
Gen(Tonic, NoteType, const MSC::Key::Properties<interval_size> &) -> Gen<interval_size>;

// Outer Interface:
template <std::size_t interval_size> consteval std::array<char, 32> generate_title(const Gen<interval_size> &gen);

template <std::size_t interval_size, auto policy = MSC::Key::standard_chord>
consteval std::array<char, 512> generate_final_output(const Gen<interval_size> &gen,
                                                        std::string_view key_override = {});
template <auto policy = MSC::Key::standard_chord> 
consteval std::array<char, 256> get_chords(std::string_view key);
} // namespace MSC::Key

#include "music.ipp"
