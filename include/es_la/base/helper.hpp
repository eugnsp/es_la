#pragma once
#include <es_la/base/type_traits.hpp>

namespace es_la::internal
{
// Compile-time size checks
static constexpr bool ct_equal(std::size_t x, std::size_t y)
{
	return x == 0 || y == 0 || x == y;
}

static constexpr bool ct_greater(std::size_t x, std::size_t y)
{
	return x == 0 || y == 0 || x > y;
}

static constexpr bool ct_greater_equal(std::size_t x, std::size_t y)
{
	return ct_equal(x, y) || ct_greater(x, y);
}
} // namespace la::internal
