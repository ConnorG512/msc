#pragma once

#include "fnv1a.hpp"
#include <utility>

template <MSC::Hash auto hash> inline constexpr auto MSC::generate_hash(const std::string_view str)
{
  using hash_t = decltype(hash);

  const auto [offset, prime] = []()
  {
    if constexpr (std::is_same_v<hash_t, std::uint64_t>)
    {
      return std::pair<std::uint64_t, std::uint64_t>{0xcbf29ce484222325, 1099511628211};
    }
    else
    {
      return std::pair<std::uint32_t, std::uint32_t>{0x811c9dc5, 16777619};
    }
  }();

  hash_t hash_output{(hash == 0) ? offset : hash};

  for (const auto &c : str)
  {
    hash_output ^= static_cast<hash_t>(c);
    hash_output *= prime;
  }

  return hash_output;
}
