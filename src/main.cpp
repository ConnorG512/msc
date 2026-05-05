#include <array>
#include <cstdint>
#include <print>
#include <string>
#include <utility>

namespace Music
{
enum class Tonic
{
  C = 0,
  D = 2,
  E = 4,
  F = 5,
  G = 7,
  A = 9,
  B = 11,

  C_SHARP = 1,
  D_SHARP = 3,
  E_SHARP = 5,
  F_SHARP = 6,
  G_SHARP = 8,
  A_SHARP = 10,
  B_SHARP = 0,

  C_FLAT = 11,
  D_FLAT = 1,
  E_FLAT = 3,
  F_FLAT = 4,
  G_FLAT = 6,
  A_FLAT = 8,
  B_FLAT = 10,
};

consteval auto calculate_key(const Tonic starting_interval,
                             const std::array<std::uint8_t, 7> intervals = {2, 2, 1, 2, 2, 2, 1},
                             const std::array<std::array<char, 4>, 12> chromatic_scale = {
                                 {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}})
{
  std::string output{};

  auto current_interval{std::to_underlying(starting_interval)};
  for (auto interval : intervals)
  {
    output.append(chromatic_scale.at(current_interval % chromatic_scale.size()).data());
    output.push_back(' ');
    current_interval += interval;
  }
  output.append(chromatic_scale.at(std::to_underlying(starting_interval)).data());

  std::array<char, 32> final_buffer{};
  if (output.size() >= final_buffer.size())
    throw "Output is too big for the final buffer, increase buffer size!";

  const auto copy_tail = std::ranges::copy(output, std::ranges::begin(final_buffer)).out;
  *copy_tail = '\0';
  return final_buffer;
}

consteval std::array<std::array<char, 32>, 12> create_circle_of_fiths()
{
  return std::to_array({
      calculate_key(Music::Tonic::C),
      calculate_key(Music::Tonic::G),
      calculate_key(Music::Tonic::D),
      calculate_key(Music::Tonic::A),
      calculate_key(Music::Tonic::E),
      calculate_key(Music::Tonic::B),
      calculate_key(Music::Tonic::F_SHARP, {2,2,1,2,2,2,1}, {"C", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}),
      calculate_key(Music::Tonic::C_SHARP, {2,2,1,2,2,2,1}, {"C", "C#", "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B"}),
      calculate_key(Music::Tonic::F),
      calculate_key(Music::Tonic::B_FLAT),
      calculate_key(Music::Tonic::E_FLAT),
      calculate_key(Music::Tonic::A_FLAT),
  });
}
} // namespace Music

int main()
{
  for (const auto &key : Music::create_circle_of_fiths())
    std::println("{:s}", key);

  return 0;
}
