#pragma once
#include "../config.hpp"
#include "../base/forward.hpp"
#include <es/math/function.hpp>

namespace la
{
// TODO : static_asserts
template<class Left, class Right>
auto cross2(const Expression<Left>& left, const Expression<Right>& right)
{
	MATHLA_ASSERT(left.rows() == 2);
	MATHLA_ASSERT(right.rows() == 2);

	return math::det(left[0], left[1], right[0], right[1]);
}
}