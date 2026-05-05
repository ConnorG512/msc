#include "music.hpp"

#include <print>

int main()
{
  for (const auto &key : Music::create_circle_of_fiths())
    std::println("{:s}", key);

  return 0;
}
