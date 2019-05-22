#pragma once
#include <es_la/core/type_traits/operator.hpp>
#include <es_la/core/type_traits/numeric.hpp>
#include <es_la/dense/expr/binary_expr.hpp>
#include <es_la/dense/expr/functor/mul_fn.hpp>
#include <es_la/sparse/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr1, class Matrix, class Expr2>
struct Assign_expr_op_trait<Expr1, Binary_expr<Mkl_sparse_matrix<Matrix>, Expr2, Mul_fn>>
// ,

// 	std::enable_if_t<
// 	is_fd_cfd<Value_type<Expr2>>
	/*&&
					 es_util::are_same<Value_type<Expr1>, Value_type<Matrix>, Value_type<Expr2>>
*/
					//  >
{
	// using Type = Mkl_sparse_matrix_mul_op<Expr1, Binary_expr<Mkl_sparse_matrix<Matrix, Category>, Expr2, Mul_fn>>;
	using Type = Mkl_sparse_matrix_mul_op<Expr1, Mkl_sparse_matrix<Matrix>, Expr2>;
};
} // namespace es_la::internal
