#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <cmath>
#include <complex>
#include <cstddef>
#include <type_traits>

namespace es_la
{
template<typename T>
auto norm2(T v) -> decltype(std::abs(T{}))
{
	return std::abs(v);
}

template<class Expr, class Category>
auto norm2(const Dense<Expr, Category>& expr)
{
	static_assert(internal::is_vector<Expr>, "Expression should be a vector");

	using Ret = decltype(std::norm(expr[0]));
	Ret nrm_sq{};

	for (std::size_t i = 0; i < expr.size(); ++i)
		nrm_sq += std::norm(expr[i]);

	return std::sqrt(nrm_sq);
}

template<class Expr,
	typename = std::enable_if_t<internal::is_fd_or_cfd<Value_type<Expr>> && internal::is_dynamic<Expr>>>
auto norm2(const Dense<Expr, Lvalue>& expr)
{
	static_assert(internal::is_vector<Expr>, "Expression should be a vector");

	return internal::mkl_blas_nrm2(expr.size(), expr.self().data(), expr.self().row_stride());
}
} // namespace es_la
