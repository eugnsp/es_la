#pragma once
#include <es_la/dense/matrix_base.dynamic.hpp>
#include <es_la/dense/matrix_base.static.hpp>
#include <es_la/dense/utility.hpp>

#include <es_util/type_traits.hpp>

#include <array>
#include <tuple>
#include <type_traits>

namespace es_la
{
template<typename Value, auto t_rows, auto t_cols, class Layout>
class Matrix :
	public internal::Matrix_base<internal::ct_extent_dynamic_or_size_t(t_rows),
		internal::ct_extent_dynamic_or_size_t(t_cols), Matrix<Value, t_rows, t_cols, Layout>, Layout>
{
	static_assert(!std::is_const_v<Value>);
	static_assert(!std::is_reference_v<Value>);
	//static_assert(std::is_trivial_v<Value>);
	static_assert(std::is_trivially_destructible_v<Value>);

private:
	using Base = internal::Matrix_base<internal::ct_extent_dynamic_or_size_t(t_rows),
		internal::ct_extent_dynamic_or_size_t(t_cols), Matrix<Value, t_rows, t_cols, Layout>, Layout>;

public:
	///////////////////////////////////////////////////////////////////////
	//* Constructors */

	using Base::Base;

	Matrix() = default;
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	// template<class Expr>
	// Matrix(const Expression<Expr>& expr)
	// {
	// 	Base::assign_expr(expr);
	// }

	///////////////////////////////////////////////////////////////////////
	//* Assignments */

	using Base::operator=;

	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;

	//////////////////////////////////////////////////////////////////////
	//* Extents */

	using Base::cols;
	using Base::rows;

	std::size_t l_dim() const
	{
		return is_col_major<Matrix> ? rows() : cols();
	}

	std::size_t row_inc() const
	{
		return is_col_major<Matrix> ? 1 : l_dim();
	}

	std::size_t col_inc() const
	{
		return is_col_major<Matrix> ? l_dim() : 1;
	}

	std::size_t memory_size() const
	{
		return Base::capacity() * sizeof(Value);
	}

	//////////////////////////////////////////////////////////////////////
	//* Element access */

	Value* data()
	{
		return data_.data();
	}

	const Value* data() const
	{
		return data_.data();
	}

private:
	using Base::data_;
};

template<class Expr>
Matrix(const Expression<Expr>&) -> Matrix<Value_type<Expr>, ct_rows_value<Expr>, ct_cols_value<Expr>>;
} // namespace es_la
