#pragma once
#include <es_la/core/type_traits/numeric.hpp>
#include <es_la/core/type_traits/operator.hpp>
#include <es_la/dense/forward.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>
#include <es_la/dense/type_traits/is_lvalue_block.hpp>
#include <es_la/dense/type_traits/value.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr1, class Expr2, typename>
struct Assign_scalar_op_trait
{
	using Type = Default_assign_scalar_op;
};

template<class Expr1, class Expr2, typename>
struct Assign_expr_op_trait
{
	using Type = Default_assign_expr_op;
};

//////////////////////////////////////////////////////////////////////

template<class Expr1, class Expr2>
struct Assign_expr_op_trait<Expr1, Expr2,
	std::enable_if_t<is_lvalue_block<Expr1> && is_lvalue_block<Expr2> && is_fd_cfd<Value_type<Expr1>> &&
					 std::is_same_v<Value_type<Expr1>, Value_type<Expr2>> && ct_rows_value<Expr1> == dynamic &&
					 ct_cols_value<Expr1> == dynamic && ct_rows_value<Expr2> == dynamic &&
					 ct_cols_value<Expr2> == dynamic>>
{
	using Type = Mkl_matrix_assign_op;
};

template<class Expr1, class Expr2, typename Scalar>
struct Assign_expr_op_trait<Expr1, Scalar_expr<Expr2, Scalar, Scalar_mul_left_fn<Expr2, Scalar>>,
	std::enable_if_t<is_lvalue_block<Expr1> && is_lvalue_block<Expr2> && is_fd_cfd<Value_type<Expr1>> &&
					 std::is_same_v<Value_type<Expr1>, Value_type<Expr2>> &&
					 std::is_convertible_v<Scalar, Value_type<Expr1>> && ct_rows_value<Expr1> == dynamic &&
					 ct_cols_value<Expr1> == dynamic && ct_rows_value<Expr2> == dynamic &&
					 ct_cols_value<Expr2> == dynamic>>
{
	using Type = Mkl_matrix_assign_op2;
};
} // namespace es_la::internal
