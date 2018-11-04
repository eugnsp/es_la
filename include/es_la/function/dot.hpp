#pragma once
#include "../config.hpp"
#include "../base/forward.hpp"

namespace la
{
// TODO : static_asserts
template<class Left, class Right>
auto dot(const Expression<Left>& left, const Expression<Right>& right)
{
	MATHLA_ASSERT(left.rows() == right.rows());

	double result = 0;
	for (std::size_t i = 0; i < left.rows(); ++i)
		result += left[i] * right[i];

	return result;
}
}