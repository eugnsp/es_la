#pragma once
#include <es_la/dense/expr/functor.hpp>
#include <es_la/dense/expression.hpp>
#include <es_la/dense/forward.hpp>
#include <es_la/dense/type_traits.hpp>

#include <type_traits>

namespace es_la
{
template<class Expr, typename Scalar, typename = std::enable_if_t<!is_expression<Scalar>>>
Scalar_expr<Expr, Scalar, internal::Scalar_mul_left_fn> operator*(const Scalar& scalar, const Expression<Expr>& expr)
{
	return {expr.self(), scalar};
}

template<class Expr, typename Scalar, typename = std::enable_if_t<!is_expression<Scalar>>>
Scalar_expr<Expr, Scalar, internal::Scalar_mul_right_fn> operator*(const Expression<Expr>& expr, const Scalar& scalar)
{
	return {expr.self(), scalar};
}

template<class Expr, typename Scalar, typename = std::enable_if_t<!is_expression<Scalar>>>
auto operator/(const Expression<Expr>& expr, const Scalar& scalar)
{
	return Scalar_expr<Expr, Scalar, internal::Scalar_div_fn>{expr.self(), scalar};
}
} // namespace es_la
