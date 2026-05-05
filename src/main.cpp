#include "music.hpp"

#include <print>

int main()
{
  static constexpr auto c_major {Music::Key<>{}};
  std::println("{} {}", c_major.get_tonic_note(), c_major.scale_name);
  std::println("{:s}", c_major.generate_key());

  return 0;
}
