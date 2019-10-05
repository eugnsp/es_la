#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Fn, class Expr, class... Exprs>
void for_each_element_impl(Fn fn, Expr&& expr, Exprs&&... exprs)
{
	if constexpr (is_row_major_traversal<Expr>)
		for (std::size_t col = 0; col < expr.cols(); ++col)
			for (std::size_t row = 0; row < expr.rows(); ++row)
				fn(expr(row, col), exprs(row, col)...);
	else
		for (std::size_t row = 0; row < expr.rows(); ++row)
			for (std::size_t col = 0; col < expr.cols(); ++col)
				fn(expr(row, col), exprs(row, col)...);
}
} // namespace internal

template<class Fn, class Dense_expr, class... Dense_exprs,
	typename = std::enable_if_t<(is_dense<Dense_expr> && ... && is_dense<Dense_exprs>)>>
void for_each_element(Fn fn, Dense_expr&& expr, Dense_exprs&&... exprs)
{
	assert(((expr.rows() == exprs.rows()) && ...));
	assert(((expr.cols() == exprs.cols()) && ...));

	internal::for_each_element_impl(fn, expr.self(), exprs.self()...);
}
} // namespace es_la
