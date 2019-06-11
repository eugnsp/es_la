#pragma once
#include <es_la/dense/matrix_base.dynamic.hpp>
#include <es_la/dense/matrix_base.static.hpp>
#include <es_la/dense/type_traits.hpp>

#include <es_util/type_traits.hpp>

#include <array>
#include <cstddef>
#include <type_traits>

namespace es_la
{
template<typename Value, std::size_t ct_rows, std::size_t ct_cols, class Layout>
class Matrix : public internal::Matrix_base<ct_rows, ct_cols, Matrix<Value, ct_rows, ct_cols, Layout>, Layout>
{
	static_assert(!std::is_const_v<Value>);
	static_assert(!std::is_reference_v<Value>);

private:
	using Base = internal::Matrix_base<ct_rows, ct_cols, Matrix<Value, ct_rows, ct_cols, Layout>, Layout>;

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

	std::size_t lead_dim() const
	{
		return is_col_major<Matrix> ? col_stride() : row_stride();
	}

	std::size_t row_stride() const
	{
		return is_col_major<Matrix> ? 1 : cols();
	}

	std::size_t col_stride() const
	{
		return is_col_major<Matrix> ? rows() : 1;
	}

	std::size_t memory_size() const
	{
		return Base::capacity() * sizeof(Value);
	}

	//////////////////////////////////////////////////////////////////////
	//* Element access */

	Value* data() noexcept
	{
		return data_.data();
	}

	const Value* data() const noexcept
	{
		return data_.data();
	}

private:
	using Base::data_;
};

template<class Expr>
Matrix(const Expression<Expr>&) -> Matrix<Value_type<Expr>, ct_rows_value<Expr>, ct_cols_value<Expr>>;
} // namespace es_la
