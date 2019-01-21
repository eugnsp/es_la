#pragma once
#include <es_la/base/traits.hpp>
#include <utility>
#include <cassert>

// Binary functors
#include <es_la/expr/functor/elementwise_func.hpp>
#include <es_la/expr/functor/add_func.hpp>
#include <es_la/expr/functor/sub_func.hpp>
#include <es_la/expr/functor/mul_func.hpp>

namespace la::internal
{
//////////////////////////////////////////////////////////////////////////
/** Unary functors */

template<class TExpr, typename TScalar>
struct Scalar_mul_func
{
	using Value = decltype(std::declval<TScalar&>() * std::declval<Value_t<TExpr>&>());

	static Value element(const TExpr&, const TScalar&, std::size_t row, std::size_t col);
};

template<class TExpr, typename TScalar>
struct Scalar_div_func
{
	using Value = decltype(std::declval<Value_t<TExpr>&>() / std::declval<TScalar&>());

	static Value element(const TExpr&, const TScalar&, std::size_t row, std::size_t col);
};

/************************************************************************/
/* IMPLEMENTATION                                                       */
/************************************************************************/

template<class TExpr, typename TScalar>
inline auto Scalar_mul_func<TExpr, TScalar>::element(
	const TExpr& expr, const TScalar& scalar, std::size_t row, std::size_t col) -> Value
{
	return scalar * expr(row, col);
}

template<class TExpr, typename TScalar>
inline auto Scalar_div_func<TExpr, TScalar>::element(
	const TExpr& expr, const TScalar& scalar, std::size_t row, std::size_t col) -> Value
{
	return expr(row, col) / scalar;
}
} // namespace la::internal
