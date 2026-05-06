#pragma once

#include <array>

namespace MSC::ChromaticScales
{
constexpr inline std::array<std::array<char, 4>, 12> standard_sharp{"C",  "C#", "D",  "D#", "E",  "F",
                                                                    "F#", "G",  "G#", "A",  "A#", "B"};
constexpr inline std::array<std::array<char, 4>, 12> standard_flat{"C",  "Db", "D",  "Eb", "E",  "F",
                                                                   "Gb", "G",  "Ab", "A",  "Bb", "B"};
} // namespace Music::ChromaticScales
