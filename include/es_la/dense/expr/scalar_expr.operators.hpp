#pragma once
#include <es_la/core/expression.hpp>
#include <es_la/dense/expr/functor.hpp>
#include <es_la/dense/forward.hpp>

#include <type_traits>

namespace es_la
{
template<class Expr, typename Scalar, typename = std::enable_if_t<is_scalar<Scalar>>>
Scalar_expr<Expr, Scalar, internal::Scalar_mul_left_fn<Expr, Scalar>> operator*(
	const Scalar& scalar, const Expression<Expr>& expr)
{
	return {expr.self(), scalar};
}

template<class Expr, typename Scalar, typename = std::enable_if_t<is_scalar<Scalar>>>
Scalar_expr<Expr, Scalar, internal::Scalar_mul_right_fn<Expr, Scalar>> operator*(
	const Expression<Expr>& expr, const Scalar& scalar)
{
	return {expr.self(), scalar};
}

template<class Expr, typename Scalar, typename = std::enable_if_t<is_scalar<Scalar>>>
auto operator/(const Expression<Expr>& expr, const Scalar& scalar)
{
	return Scalar_expr<Expr, Scalar, internal::Scalar_div_fn<Expr, Scalar>>{expr.self(), scalar};
}
} // namespace es_la
