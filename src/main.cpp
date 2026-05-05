#include "music.hpp"

#include <print>

int main()
{
  static constexpr auto c_major{Music::Key<>{}};
  std::println("{:s}", Music::generate_title_and_notes(c_major));

  return 0;
}
