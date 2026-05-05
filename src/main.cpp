#include "music.hpp"

#include <print>

int main()
{
  // for (const auto &key : Music::create_circle_of_fiths())
  //   std::println("{:s}", key);

  static constexpr auto c_major{
      Music::prepend_title_to_key(Music::calculate_key(Music::Tonic::C), Music::Tonic::C, Music::Scale::MAJOR)};
  std::println("{:s}", c_major);
  return 0;
}
