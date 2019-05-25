#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility.hpp>

#include <cmath>
#include <cstddef>
#include <type_traits>

namespace es_la
{
template<typename T, typename = std::enable_if_t<is_scalar<T>>>
auto norm_sup(T v)
{
	return std::abs(v);
}

template<class Expr, class Category>
auto norm_sup(const Dense<Expr, Category>& expr)
{
	static_assert(internal::is_vector_expr<Expr>, "Expression should be a vector");

	using R = decltype(std::abs(expr[0]));
	R nrm_sup{};

	for (std::size_t i = 0; i < expr.size(); ++i)
		if (nrm_sup < std::abs(expr[i]))
			nrm_sup = std::abs(expr[i]);

	return nrm_sup;
}
} // namespace es_la
