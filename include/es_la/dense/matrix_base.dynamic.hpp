#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/matrix_base.static.hpp>
#include <es_la/dense/matrix_dynamic_base.hpp>
#include <es_la/dense/shape.hpp>
#include <es_la/dense/storage/storage.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace es_la::internal
{
template<auto ct_rows, class Derived, class Layout>
class Matrix_base<ct_rows, dynamic, Derived, Layout> : public Matrix_dynamic_base<ct_rows, dynamic, Derived, Layout>
{
private:
	using Base = Matrix_dynamic_base<ct_rows, dynamic, Derived, Layout>;

public:
	using Value = Value_type<Derived>;

public:
	using Base::Base;

	explicit Matrix_base(std::size_t cols) : Base(ct_rows, cols, Internal{})
	{}

	Matrix_base(std::size_t cols, const Value& value) : Matrix_base(cols)
	{
		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	Matrix_base(std::size_t cols, std::initializer_list<Value> values) : Matrix_base(cols)
	{
		assert(values.size() == this->size());
		std::copy(values.begin(), values.end(), data_.data());
	}

	Matrix_base(std::initializer_list<Value> values) : Matrix_base(values.size() / ct_rows, values)
	{
		assert(values.size() % ct_rows == 0);
	}

	template<class Expr, class Value_category>
	Matrix_base(const Dense<Expr, Value_category>& expr) : Base(expr)
	{}

	using Base::operator=;

	void resize(std::size_t cols, bool preserve_data = false)
	{
		Base::resize(ct_rows, cols, preserve_data);
	}

protected:
	using Base::data_;
};

template<auto t_cols, class Derived, class Layout>
class Matrix_base<dynamic, t_cols, Derived, Layout> : public Matrix_dynamic_base<dynamic, t_cols, Derived, Layout>
{
private:
	using Base = Matrix_dynamic_base<dynamic, t_cols, Derived, Layout>;

public:
	using Value = Value_type<Derived>;

public:
	using Base::Base;

	explicit Matrix_base(std::size_t rows = 0) : Base(rows, t_cols, Internal{})
	{}

	Matrix_base(std::size_t rows, const Value& value) : Matrix_base(rows)
	{
		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	Matrix_base(std::size_t rows, std::initializer_list<Value> values) : Matrix_base(rows)
	{
		assert(values.size() == this->size());
		std::copy(values.begin(), values.end(), data_.data());
	}

	Matrix_base(std::initializer_list<Value> values) : Matrix_base(values.size() / t_cols, values)
	{
		assert(values.size() % t_cols == 0);
	}

	template<class Expr, class Value_category>
	Matrix_base(const Dense<Expr, Value_category>& expr) : Base(expr)
	{}

	using Base::operator=;

	void resize(std::size_t rows, bool preserve_data = false)
	{
		Base::resize(rows, t_cols, preserve_data);
	}

protected:
	using Base::data_;
};

template<class Derived, class Layout>
class Matrix_base<dynamic, dynamic, Derived, Layout> : public Matrix_dynamic_base<dynamic, dynamic, Derived, Layout>
{
private:
	using Base = Matrix_dynamic_base<dynamic, dynamic, Derived, Layout>;

public:
	using Value = Value_type<Derived>;

public:
	using Base::Base;

	Matrix_base(std::size_t rows, std::size_t cols) : Base(rows, cols, Internal{})
	{}

	Matrix_base() : Matrix_base(0, 0)
	{}

	Matrix_base(std::size_t rows, std::size_t cols, const Value& value) : Matrix_base(rows, cols)
	{
		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	Matrix_base(std::size_t rows, std::size_t cols, std::initializer_list<Value> values) : Matrix_base(rows, cols)
	{
		assert(values.size() == this->size());
		std::copy(values.begin(), values.end(), data_.data());
	}

	using Base::operator=;

	void resize(std::size_t rows, std::size_t cols, bool preserve_data = false)
	{
		Base::resize(rows, cols, preserve_data);
	}

protected:
	using Base::data_;
};
} // namespace es_la::internal
