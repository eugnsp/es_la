#pragma once
#include <es_la/dense/forward.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>

#include <cmath>
#include <cstddef>
#include <type_traits>

namespace es_la
{
template<typename T>
auto norm_sup(T v) -> decltype(std::abs(T{}))
{
	return std::abs(v);
}

template<class Expr, class Category>
auto norm_sup(const Dense<Expr, Category>& expr)
{
	using Ret = decltype(std::abs(expr(0, 0)));
	Ret nrm_sup{};

	for (std::size_t i = 0; i < expr.cols(); ++i)
		for (std::size_t j = 0; j < expr.rows(); ++j)
			if (nrm_sup < std::abs(expr(i, j)))
				nrm_sup = std::abs(expr(i, j));

	return nrm_sup;
}
} // namespace es_la
