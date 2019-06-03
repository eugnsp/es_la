#pragma once
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility.hpp>

#include <cassert>

namespace es_la::internal
{
struct Mkl_matrix_assign_op
{
	template<class Expr1, class Expr2>
	static void run(Expr1& expr1, const Expr2& expr2)
	{
		static_assert(is_lvalue_block<Expr1> && is_lvalue_block<Expr2>);
		static_assert(ct_rows_value<Expr1> == dynamic && ct_cols_value<Expr1> == dynamic);
		static_assert(ct_rows_value<Expr2> == dynamic && ct_cols_value<Expr2> == dynamic);
		assert(expr1.rows() == expr2.rows());
		assert(expr1.cols() == expr2.cols());

		constexpr bool transp = (is_col_major<Expr1> == is_col_major<Expr2>);
		constexpr auto layout = is_col_major<Expr1> ? 'C' : 'R';
		constexpr auto tr = transp ? 'N' : 'T';
		const auto rows = transp ? expr1.rows() : expr1.cols();
		const auto cols = transp ? expr1.cols() : expr1.rows();

		internal::mkl_omatcopy(layout, tr, rows, cols, 1, expr2.data(), expr2.l_dim(), expr1.data(), expr1.l_dim());
	}
};

struct Mkl_matrix_assign_op2
{
	template<class Expr1, class Expr2>
	static void run(Expr1& expr1, const Expr2& expr2)
	{
		static_assert(is_lvalue_block<Expr1> && is_lvalue_block<typename Expr2::Expr>);
		static_assert(ct_rows_value<Expr1> == dynamic && ct_cols_value<Expr1> == dynamic);
		static_assert(ct_rows_value<Expr2> == dynamic && ct_cols_value<Expr2> == dynamic);
		assert(expr1.rows() == expr2.rows());
		assert(expr1.cols() == expr2.cols());

		constexpr bool transp = (is_col_major<Expr1> == is_col_major<typename Expr2::Expr>);
		constexpr auto layout = is_col_major<Expr1> ? 'C' : 'R';
		constexpr auto tr = transp ? 'N' : 'T';
		const auto rows = transp ? expr1.rows() : expr1.cols();
		const auto cols = transp ? expr1.cols() : expr1.rows();

		internal::mkl_omatcopy(layout, tr, rows, cols, expr2.scalar(), expr2.expr().data(), expr2.expr().l_dim(),
			expr1.data(), expr1.l_dim());
	}
};
} // namespace es_la::internal
