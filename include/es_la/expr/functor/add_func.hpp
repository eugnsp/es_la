#pragma once
#include <es_la/base/type_traits.hpp>
#include <es_la/expr/functor/elementwise_func.hpp>

#include <utility>

namespace es_la::internal
{
template<class Left, class Right>
struct Add_func : public Elementwise_func<Left, Right>
{
	using Value = decltype(std::declval<Value_t<Left>>() + std::declval<Value_t<Right>>());

	static Value element(const Left& left, const Right& right, std::size_t row, std::size_t col)
	{
		return left(row, col) + right(row, col);
	}
};
} // namespace la::internal
