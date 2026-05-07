#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace MSC
{

template <typename T>
concept Hash = std::is_same_v<T, std::size_t> || std::is_same_v<T, std::uint32_t>;

template <Hash auto hash = 0UL> inline constexpr auto generate_hash(const std::string_view str);
} // namespace MSC

#include "fnv1a.ipp"
