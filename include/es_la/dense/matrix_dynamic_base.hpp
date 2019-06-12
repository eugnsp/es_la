#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/dense.hpp>
#include <es_la/dense/matrix_base.static.hpp>
#include <es_la/dense/shape.hpp>
#include <es_la/dense/storage/storage.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace es_la::internal
{
template<std::size_t ct_rows, std::size_t ct_cols, class Expr, class Layout>
class Matrix_dynamic_base : public Dense<Expr, Lvalue>, public Shape<ct_rows, ct_cols, Layout>
{
private:
	using Dense_base = Dense<Expr, Lvalue>;
	using Shape_base = Shape<ct_rows, ct_cols, Layout>;

public:
	using Value = typename Dense_base::Value;

public:
	//////////////////////////////////////////////////////////////////////
	//* Constructor */

	Matrix_dynamic_base() :
		Matrix_dynamic_base(Internal{}, extent_static_or_zero(ct_rows), extent_static_or_zero(ct_cols))
	{}

	Matrix_dynamic_base(const Matrix_dynamic_base& matrix) :
		Matrix_dynamic_base(Internal{}, matrix.rows(), matrix.cols())
	{
		this->assign_expr(matrix);
	}

	Matrix_dynamic_base(Matrix_dynamic_base&& matrix) noexcept : Matrix_dynamic_base()
	{
		swap(matrix);
	}

	template<class Expr2>
	Matrix_dynamic_base(const Expression<Expr2>& expr) : Matrix_dynamic_base(Internal{}, expr.rows(), expr.cols())
	{
		this->assign_expr(expr);
	}

	~Matrix_dynamic_base()
	{
		std::destroy_n(data_.data(), this->size());
	}

	///////////////////////////////////////////////////////////////////////
	//* Assignments */

	using Dense_base::operator=;

	Matrix_dynamic_base& operator=(const Matrix_dynamic_base& matrix)
	{
		assert(rows() == 0 || rows() == matrix.rows());
		assert(cols() == 0 || cols() == matrix.cols());

		resize(matrix.rows(), matrix.cols());
		this->assign_expr(matrix);
		return *this;
	}

	Matrix_dynamic_base& operator=(Matrix_dynamic_base&& matrix)
	{
		assert(rows() == 0 || rows() == matrix.rows());
		assert(cols() == 0 || cols() == matrix.cols());

		swap(matrix);
		return *this;
	}

	template<class Expr2>
	Matrix_dynamic_base& operator=(const Expression<Expr2>& expr)
	{
		assert(rows() == 0 || rows() == expr.rows());
		assert(cols() == 0 || cols() == expr.cols());

		if (rows() != expr.rows() || cols() != expr.cols())
			resize(expr.rows(), expr.cols());

		Dense_base::assign_expr(expr);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////
	//* Extents */

	using Shape_base::cols;
	using Shape_base::rows;

	std::size_t capacity() const
	{
		return data_.capacity();
	}

	///////////////////////////////////////////////////////////////////////
	//* Element access */

	Value& operator()(std::size_t row, std::size_t col)
	{
		return data_[linear_index(row, col)];
	}

	const Value& operator()(std::size_t row, std::size_t col) const
	{
		return data_[linear_index(row, col)];
	}

	///////////////////////////////////////////////////////////////////////
	//* Modifiers */

	void swap(Matrix_dynamic_base& other) noexcept
	{
		Shape_base::swap(other);
		data_.swap(other.data_);
	}

protected:
	//////////////////////////////////////////////////////////////////////
	//* Constructor */

	Matrix_dynamic_base(Internal, std::size_t rows, std::size_t cols) : Shape_base(rows, cols), data_(rows * cols)
	{
		std::uninitialized_default_construct_n(data_.data(), this->size());
	}

	Matrix_dynamic_base(Internal, std::size_t rows, std::size_t cols, const Value& value) :
		Shape_base(rows, cols), data_(rows * cols)
	{
		std::uninitialized_fill_n(data_.data(), this->size(), value);
	}

	Matrix_dynamic_base(Internal, std::size_t rows, std::size_t cols, std::initializer_list<Value> values) :
		Shape_base(rows, cols), data_(rows * cols)
	{
		assert(values.size() == this->size());
		std::uninitialized_copy_n(values.begin(), this->size(), data_.data());
	}

	///////////////////////////////////////////////////////////////////////
	//* Modifiers */

	void resize(std::size_t n_rows, std::size_t n_cols, bool preserve_data = false)
	{
		// TODO
		assert(!preserve_data);
		(void)preserve_data;

		if (rows() == n_rows && cols() == n_cols)
			return;

		Shape_base::set(n_rows, n_cols);
		data_.resize(n_rows * n_cols);
	}

protected:
	Storage<Value_type<Expr>, 0> data_;

private:
	using Shape_base::linear_index;
};
} // namespace es_la::internal
