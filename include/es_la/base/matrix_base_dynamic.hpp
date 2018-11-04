#pragma once
#include "../config.hpp"
#include "base.hpp"
#include "traits.hpp"
#include "expression.hpp"
//#include "extended.hpp"
#include <es_la/base/ct_shape.hpp>
#include <es_la/base/shape.hpp>
#include <es_la/storage/storage.hpp>
#include "matrix_base_static.hpp"
#include <array>
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <type_traits>
#include <cassert>

namespace la::internal
{
constexpr std::size_t zero_or_static_size(std::size_t size)
{
	return size == dynamic ? 0 : size;
}

template<std::size_t ct_rows, std::size_t ct_cols, class Derived, class Layout>
class Matrix_base_dynamic : public Expression<Derived>, public Shape<ct_rows, ct_cols, Layout>
{
private:
	using Base = Expression<Derived>;
	using Shape_base = Shape<ct_rows, ct_cols, Layout>;

public:
	using Value = Value_t<Derived>;

public:
	Matrix_base_dynamic()
		: Matrix_base_dynamic(zero_or_static_size(ct_rows), zero_or_static_size(ct_cols))
	{ }

	Matrix_base_dynamic(std::size_t rows, std::size_t cols)
		: Shape_base(rows, cols), data_(rows * cols)
	{ }

	Matrix_base_dynamic(const Matrix_base_dynamic& other)
		: Matrix_base_dynamic(other.rows(), other.cols())
	{
		this->assign(other);
	}

	Matrix_base_dynamic(Matrix_base_dynamic&& other) noexcept
		: Matrix_base_dynamic()
	{
		swap(other);
	}

	template<class Expr>
	Matrix_base_dynamic(const Expression<Expr>& expr)
		: Matrix_base_dynamic(expr.rows(), expr.cols())
	{
		this->assign(expr);
	}

	using Shape_base::rows;
	using Shape_base::cols;
	using Shape_base::size;

	Matrix_base_dynamic& operator=(const Matrix_base_dynamic& other)
	{
		assert(rows() == other.rows() && cols() == other.cols());
		this->assign(other);
		return *this;
	}

	Matrix_base_dynamic& operator=(Matrix_base_dynamic&& other)
	{
		assert(rows() == other.rows() && cols() == other.cols());
		swap(other);
		return *this;
	}

	template<bool is_vector = (ct_cols == 1), typename = std::enable_if_t<is_vector>>
	Value& operator[](std::size_t);

	template<bool is_vector = (ct_cols == 1), typename = std::enable_if_t<is_vector>>
	Value operator[](std::size_t) const;

	Value& operator()(std::size_t row, std::size_t col)
	{
		MATHLA_ASSERT(row < rows());
		MATHLA_ASSERT(col < cols());
		return data_[linear_index(row, col)];
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		MATHLA_ASSERT(row < rows());
		MATHLA_ASSERT(col < cols());
		return data_[linear_index(row, col)];
	}

	void swap(Matrix_base_dynamic& other) noexcept
	{
		Shape_base::swap(other);
		data_.swap(other.data_);
	}

protected:
	Storage<Value_t<Derived>, 0> data_;

private:
	using Shape_base::linear_index;
};

//////////////////////////////////////////////////////////////////////////

template<std::size_t ct_rows, std::size_t ct_cols, class Derived, class Layout>
template<bool is_vector, typename>
auto Matrix_base_dynamic<ct_rows, ct_cols, Derived, Layout>::operator[](std::size_t index) -> Value&
{
	return (*this)(index, 0);
}

template<std::size_t ct_rows, std::size_t ct_cols, class Derived, class Layout>
template<bool is_vector, typename>
auto Matrix_base_dynamic<ct_rows, ct_cols, Derived, Layout>::operator[](std::size_t index) const -> Value
{
	return (*this)(index, 0);
}

//////////////////////////////////////////////////////////////////////////

template<size_t t_rows, class Derived, class Layout>
class Matrix_base<t_rows, dynamic, Derived, Layout> 
	: public Matrix_base_dynamic<t_rows, dynamic, Derived, Layout>
{
private:
	using Base = Matrix_base_dynamic<t_rows, dynamic, Derived, Layout>;

public:
	using Value = Value_t<Derived>;

public:
	explicit Matrix_base(std::size_t cols = 0)
		: Base(t_rows, cols)
	{ }

	Matrix_base(std::size_t cols, const Value& value)
		: Matrix_base(cols)
	{
		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	Matrix_base(std::size_t cols, std::initializer_list<Value> values)
		: Matrix_base(cols)
	{
		assert(values.size() == this->size());
		std::copy(values.begin(), values.end(), data_.data());
	}

	Matrix_base(std::initializer_list<Value> values)
		: Matrix_base(values.size() / t_rows, values)
	{
		assert(values.size() % t_rows == 0);
	}

	template<class Expr>
	Matrix_base(const Expression<Expr>& expr)
		: Base(expr)
	{ }

	void resize(std::size_t cols, bool preserve_data = false)
	{
		data_.resize(t_rows * cols);
		if (preserve_data)
		{
			throw;
		}

		Base::set_size(cols);
	}

protected:
	using Base::data_;
};

template<size_t t_cols, class Derived, class Layout>
class Matrix_base<dynamic, t_cols, Derived, Layout> 
	: public Matrix_base_dynamic<dynamic, t_cols, Derived, Layout>
{
private:
	using Base = Matrix_base_dynamic<dynamic, t_cols, Derived, Layout>;

public:
	using Value = Value_t<Derived>;

public:
	explicit Matrix_base(std::size_t rows = 0)
		: Base(rows, t_cols)
	{ }

	Matrix_base(std::size_t rows, const Value& value)
		: Matrix_base(rows)
	{
		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	Matrix_base(std::size_t rows, std::initializer_list<Value> values)
		: Matrix_base(rows)
	{
		assert(values.size() == this->size());
		std::copy(values.begin(), values.end(), data_.data());
	}

	Matrix_base(std::initializer_list<Value> values)
		: Matrix_base(values.size() / t_cols, values)
	{
		assert(values.size() % t_cols == 0);
	}

	template<class Expr>
	Matrix_base(const Expression<Expr>& expr)
		: Base(expr)
	{ }

	void resize(std::size_t rows, bool preserve_data = false)
	{
		data_.resize(rows * t_cols);
		if (preserve_data)
		{
			throw;
		}

		Base::set_size(rows);
	}

protected:
	using Base::data_;
};

template<class Derived, class Layout>
class Matrix_base<dynamic, dynamic, Derived, Layout> 
	: public Matrix_base_dynamic<dynamic, dynamic, Derived, Layout>
{
private:
	using Base = Matrix_base_dynamic<dynamic, dynamic, Derived, Layout>;

public:
	using Value = Value_t<Derived>;

public:
	Matrix_base(std::size_t rows, std::size_t cols)
		: Base(rows, cols)
	{ }

	Matrix_base()
		: Matrix_base(0, 0)
	{ }

	Matrix_base(std::size_t rows, std::size_t cols, const Value& value)
		: Matrix_base(rows, cols)
	{
 		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	Matrix_base(std::size_t rows, std::size_t cols, std::initializer_list<Value> values)
		: Matrix_base(rows, cols)
	{
		MATHLA_ASSERT(values.size() == this->size());
		std::copy(values.begin(), values.end(), data_.data());
	}

	template<class Expr>
	Matrix_base(const Expression<Expr>& expr)
		: Base(expr)
	{ }

	void resize(std::size_t rows, std::size_t cols, bool preserve_data = false)
	{
		data_.resize(rows * cols);
		if (preserve_data)
		{
			throw;
		}

		Base::set_size(rows, cols);
	}

protected:
	using Base::data_;
};
}

