#pragma once
#include <es_la/core/expression.hpp>
#include <es_la/dense/expr/functor.hpp>
#include <es_la/dense/forward.hpp>

namespace es_la
{
template<class Expr1, class Expr2>
Binary_expr<Expr1, Expr2, internal::Add_fn> operator+(const Expression<Expr1>& expr1, const Expression<Expr2>& expr2)
{
	return {expr1.self(), expr2.self()};
}

template<class Expr1, class Expr2>
Binary_expr<Expr1, Expr2, internal::Sub_fn> operator-(const Expression<Expr1>& expr1, const Expression<Expr2>& expr2)
{
	return {expr1.self(), expr2.self()};
}

template<class Expr1, class Expr2>
Binary_expr<Expr1, Expr2, internal::Mul_fn> operator*(const Expression<Expr1>& expr1, const Expression<Expr2>& expr2)
{
	return {expr1.self(), expr2.self()};
}
} // namespace es_la
