#pragma once

namespace es_la::internal
{
template<class Expr1, class Expr2, typename = void>
struct Assign_scalar_op_trait;

template<class Expr1, class Expr2>
using Assign_scalar_op_type = typename Assign_scalar_op_trait<Expr1, Expr2>::Type;

template<class Expr1, class Expr2, typename = void>
struct Assign_expr_op_trait;

template<class Expr1, class Expr2>
using Assign_expr_op_type = typename Assign_expr_op_trait<Expr1, Expr2>::Type;
} // namespace es_la::internal
