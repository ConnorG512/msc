#pragma once

#include <array>
#include <string_view>

namespace MSC::ChromaticScales
{
constexpr inline auto standard_sharp =
    std::to_array<std::string_view>({"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"});
constexpr inline auto standard_flat =
    std::to_array<std::string_view>({"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"});
} // namespace MSC::ChromaticScales
