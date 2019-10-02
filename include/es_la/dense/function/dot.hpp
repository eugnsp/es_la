#pragma once
#include <es_la/dense/expression.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Expr1, class Expr2, class Mkl_tag1, class Mkl_tag2, typename = void>
class Dot_impl
{
public:
	auto operator()(const Expr1& expr1, const Expr2& expr2) const
	{
		using Ret = decltype(expr1(0, 0) * expr2(0, 0));
		Ret dot{};

		for (std::size_t col = 0; col < expr1.cols(); ++col)
			for (std::size_t row = 0; row < expr1.rows(); ++row)
				dot += expr1(row, col) * expr2(row, col);

		return dot;
	}
};

// template<class Expr1, class Expr2, typename Value>
// class Dot_impl<Expr1, Expr2, Lvalue_block_tag<Value>, Lvalue_block_tag<Value>,
// 	std::enable_if_t<is_fd<Value> && is_dynamic<Expr1> && is_dynamic<Expr2>>>
// {
// public:
// 	auto operator()(const Expr1& expr1, const Expr2& expr2) const
// 	{
// 		// TO DO : check row_stride
// 		return internal::mkl_dot(expr1.size(), expr1.data(), expr1.row_stride(), expr2.data(), expr2.row_stride());
// 	}
// };
} // namespace internal

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
auto dot(T v1, T v2)
{
	return v1 * v2;
}

template<class Expr1, class Category1, class Expr2, class Category2>
auto dot(const Dense<Expr1, Category1>& expr1, const Dense<Expr2, Category2>& expr2)
{
	static_assert(internal::is_extent_dynamic_or_eq(ct_rows_value<Expr1>, ct_rows_value<Expr2>));
	static_assert(internal::is_extent_dynamic_or_eq(ct_cols_value<Expr1>, ct_cols_value<Expr2>));
	assert(expr1.rows() == expr2.rows());
	assert(expr1.cols() == expr2.cols());

	return internal::Dot_impl<Expr1, Expr2, internal::Mkl_expr_decay<Expr1>, internal::Mkl_expr_decay<Expr2>>{}(
		expr1.self(), expr2.self());
}
} // namespace es_la
