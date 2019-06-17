#pragma once
#include <es_la/dense/forward.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>

#include <es_util/numeric/det.hpp>

#include <type_traits>

namespace es_la
{
// clang-format off
template<class Expr, class Category,
	std::enable_if_t<internal::is_extent_static_and_eq(ct_rows_value<Expr>, 2) &&
					 internal::is_extent_static_and_eq(ct_cols_value<Expr>, 2), int> = 0>
auto det(const Dense<Expr, Category>& expr)
{
	return es_util::det(
		expr(0, 0), expr(1, 0),
		expr(0, 1), expr(1, 1));
}

template<class Expr, class Category,
	std::enable_if_t<internal::is_extent_static_and_eq(ct_rows_value<Expr>, 3) &&
					 internal::is_extent_static_and_eq(ct_cols_value<Expr>, 3), int> = 0>
auto det(const Dense<Expr, Category>& expr)
{
	return es_util::det(
		expr(0, 0), expr(1, 0), expr(2, 0),
		expr(0, 1), expr(1, 1), expr(2, 1),
		expr(0, 2), expr(1, 2), expr(2, 2));
}
// clang-format on
} // namespace es_la
