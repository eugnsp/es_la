#pragma once
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility.hpp>

#include <cassert>

namespace es_la::internal
{
struct Default_assign_scalar_op
{
	template<class Expr1, typename Scalar>
	static void run(Expr1& expr, const Scalar& scalar)
	{
		if constexpr (is_col_major<Expr1>)
			for (std::size_t col = 0; col < expr.cols(); ++col)
				for (std::size_t row = 0; row < expr.rows(); ++row)
					expr(row, col) = scalar;
		else // constexpr (is_row_major<Expr1>)
			for (std::size_t row = 0; row < expr.rows(); ++row)
				for (std::size_t col = 0; col < expr.cols(); ++col)
					expr(row, col) = scalar;
	}
};

struct Default_assign_expr_op
{
	template<class Expr1, class Expr2>
	static void run(Expr1& expr1, const Expr2& expr2)
	{
		static_assert(is_ct_extent_dynamic_or_eq(ct_rows_value<Expr1>, ct_rows_value<Expr2>));
		static_assert(is_ct_extent_dynamic_or_eq(ct_cols_value<Expr1>, ct_cols_value<Expr2>));
		assert(expr1.rows() == expr2.rows());
		assert(expr1.cols() == expr2.cols());

		if constexpr (is_col_major<Expr1>)
			for (std::size_t col = 0; col < expr1.cols(); ++col)
				for (std::size_t row = 0; row < expr1.rows(); ++row)
					expr1(row, col) = expr2(row, col);
		else // constexpr (is_row_major<Expr1>)
			for (std::size_t row = 0; row < expr1.rows(); ++row)
				for (std::size_t col = 0; col < expr1.cols(); ++col)
					expr1(row, col) = expr2(row, col);
	}
};
} // namespace es_la::internal
