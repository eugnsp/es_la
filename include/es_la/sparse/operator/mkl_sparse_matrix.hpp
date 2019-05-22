#pragma once
#include <es_la/dense/type_traits.hpp>
#include <es_la/sparse/utility.hpp>

#include <mkl_spblas.h>

#include <cassert>
#include <type_traits>

namespace es_la::internal
{

template<class Expr1, class Matrix, class Expr2>
struct Mkl_sparse_matrix_mul_op
{
	static_assert(std::is_same_v<Value_type<Expr1>, Value_type<Matrix>>, "Incompatible data types");
	static_assert(std::is_same_v<Value_type<Expr2>, Value_type<Matrix>>, "Incompatible data types");
	static_assert(std::is_same_v<Layout_tag<Expr1>, Layout_tag<Expr2>>, "Incompatible layouts");
	static_assert(is_lvalue_block<Expr1>, "Expression should be an l-value block");
	static_assert(is_lvalue_block<Expr2>, "Expression should be an l-value block");

	template<class Expr1p, class Expr2p>
	static void run(Expr1p& expr1, const Expr2p& expr2)
	{
		const auto descr = mkl_matrix_descr<Matrix>();

		const auto x = expr2.expr2().data();
		const auto cols = expr2.expr2().cols();
		const auto ldx = expr2.expr2().l_dim();

		const auto y = expr1.data();
		const auto ldy = expr1.l_dim();

		const auto handle = expr2.expr1().handle();
		constexpr auto layout = mkl_sparse_dense_layout<Expr1>();

		mkl_sparse_mm(SPARSE_OPERATION_NON_TRANSPOSE, 1., handle, descr, layout, x, cols, ldx, 0., y, ldy);
	}
};
} // namespace es_la::internal
