#pragma once
#include <es_la/core/type_traits/operator.hpp>
#include <es_la/dense/forward.hpp>

namespace es_la::internal
{
template<class Expr1, class Expr2>
struct Assign_scalar_op_trait<Expr1, Expr2, void>
{
	using Type = Default_assign_scalar_op<Expr1, Expr2>;
};

template<class Expr1, class Expr2>
struct Assign_expr_op_trait<Expr1, Expr2, void>
{
	using Type = Default_assign_expr_op<Expr1, Expr2>;
};
}
