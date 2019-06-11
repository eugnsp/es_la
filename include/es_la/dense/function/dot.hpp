#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace es_la
{
template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
auto dot(T v1, T v2)
{
	return v1 * v2;
}

template<class Expr1, class Category1, class Expr2, class Category2>
auto dot(const Dense<Expr1, Category1>& expr1, const Dense<Expr2, Category2>& expr2)
{
	static_assert(internal::is_vector<Expr1> && internal::is_vector<Expr2>, "Expressions should be vectors");
	static_assert(
		internal::is_ct_extent_dynamic_or_eq(ct_rows_value<Expr1>, ct_rows_value<Expr2>), "Incompatible extents");

	assert(expr1.size() == expr2.size());

	using Ret = decltype(expr1[0] * expr2[0]);
	Ret dot{};

	for (std::size_t i = 0; i < expr1.size(); ++i)
		dot += expr1[i] * expr2[i];

	return dot;
}

template<class Expr1, class Expr2,
	typename =
		std::enable_if_t<std::is_same_v<Value_type<Expr1>, Value_type<Expr2>> && internal::is_fd<Value_type<Expr1>> &&
						 internal::is_dynamic<Expr1> && internal::is_dynamic<Expr2>>>
auto dot(const Dense<Expr1, Lvalue>& expr1, const Dense<Expr2, Lvalue>& expr2)
{
	static_assert(internal::is_vector<Expr1> && internal::is_vector<Expr2>, "Expressions should be vectors");
	static_assert(
		internal::is_ct_extent_dynamic_or_eq(ct_rows_value<Expr1>, ct_rows_value<Expr2>), "Incompatible extents");

	assert(expr1.size() == expr2.size());

	return internal::mkl_blas_dot(
		expr1.size(), expr1.self().data(), expr1.self().col_inc(), expr2.self().data(), expr2.self().col_inc());
}
} // namespace es_la
