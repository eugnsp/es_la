#pragma once
#include <es_la/dense/expression.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <cmath>
#include <complex>
#include <cstddef>
#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Expr, class Mkl_tag, typename = void>
class Norm2_impl
{
public:
	auto operator()(const Expr& expr) const
	{
		using Ret = decltype(std::norm(expr[0]));
		Ret nrm_sq{};

		for (std::size_t i = 0; i < expr.size(); ++i)
			nrm_sq += std::norm(expr[i]);

		return std::sqrt(nrm_sq);
	}
};

template<class Expr, typename Value>
class Norm2_impl<Expr, Lvalue_block_t<Value>, std::enable_if_t<is_fd_or_cfd<Value> && is_dynamic<Expr>>>
{
public:
	auto operator()(const Expr& expr) const
	{
		return internal::mkl_nrm2(expr.size(), expr.data(), expr.row_stride());
	}
};
} // namespace internal

template<typename T>
auto norm2(T v) -> decltype(std::abs(T{}))
{
	return std::abs(v);
}

template<class Expr>
auto norm2(const Expression<Expr>& expr)
{
	static_assert(internal::is_vector<Expr>);
	return internal::Norm2_impl<Expr, internal::Mkl_expr_decay<Expr>>{}(expr);
}
} // namespace es_la
