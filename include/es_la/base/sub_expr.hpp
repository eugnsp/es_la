#pragma once
#include "forward.hpp"
#include "expression.hpp"
#include "helper.hpp"
#include <cstddef>
#include <cassert>

template<class T>
class TD;

namespace la::internal
{
template<class Ex, class Rows, class Cols>
class Sub_expr<Ex, Rows, Cols, Read_only_tag> : public Expression<Sub_expr_t<Ex, Rows, Cols>>
{
private:
	using Base = Expression<Sub_expr_t<Ex, Rows, Cols>>;

public:
	using Value = typename Base::Value;

public:
	Sub_expr(Ex& expr, const Rows& rows, const Cols& cols)
		: expr_(expr), rows_(rows), cols_(cols)
	{
		static_assert(ct_greater_equal(rows_v<Ex>, size_v<Rows>),
			"Too many rows in the sub-matrix");
		// HACK
// 		static_assert(ct_greater_equal(cols_v<Ex>, size_v<Cols>),
// 			"Too many columns in the sub-matrix");

		MATHLA_ASSERT(rows.are_all_less(expr.rows()));
		MATHLA_ASSERT(cols.are_all_less(expr.cols()));
	}

	Sub_expr(const Sub_expr&) = default;

	Sub_expr& operator=(const Sub_expr&) = delete;

	std::size_t rows() const
	{
		return rows_.size();
	}

	std::size_t cols() const
	{
		return cols_.size();
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		return expr_(rows_[row], cols_[col]);
	}

	const Value* data() const
	{
		static_assert(is_matrix_block<std::decay_t<decltype(*this)>>,
			"Sub-expression should be an l-value matrix block");

		return expr_.data() + cols_.begin() * lead_dim() + rows_.begin();
	}

	std::size_t lead_dim() const
	{
		static_assert(is_matrix_block<std::decay_t<decltype(*this)>>,
			"Sub-expression should be an l-value matrix block");

		return expr_.rows();
	}

protected:
	Expr_storage_t<Ex> expr_;

	const Rows rows_;
	const Cols cols_;
};

template<class Ex, class Rows, class Cols>
class Sub_expr<Ex, Rows, Cols, Read_write_tag> : public Sub_expr<Ex, Rows, Cols, Read_only_tag>
{
private:
	using Base = Sub_expr<Ex, Rows, Cols, Read_only_tag>;

public:
	using Base::Base;

	Sub_expr& operator=(const Sub_expr& other)
	{
		this->assign(other);
		return *this;
	}

	template<class Other>
	Sub_expr& operator=(const Expression<Other>& other)
	{
		this->assign(other);
		return *this;
	}

	using Base::operator();

	typename Base::Value& operator()(std::size_t row, std::size_t col)
	{
		return expr_(rows_[row], cols_[col]);
	}

	using Base::data;

	typename Base::Value* data()
	{
		static_assert(is_matrix_block<std::decay_t<decltype(*this)>>,
			"Sub-expression should be an l-value matrix block");

		return expr_.data() + cols_.begin() * this->lead_dim() + rows_.begin();
	}

private:
	using Base::expr_;
	using Base::rows_;
	using Base::cols_;
};

// template<typename Value, std::size_t ct_rows, std::size_t ct_cols, 
// 	std::size_t rows_begin, std::size_t rows_size,
// 	std::size_t cols_begin, std::size_t cols_size, class Access_tag>
// class Sub<Matrix<Value, ct_rows, ct_cols>, Range<>, Range<>, Access_tag> : 
// 	Sub_expr<Matrix<>, Range<>, Range<>, Access_tag>,
// 	Special_int
// { };


}
