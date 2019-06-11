#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/matrix_base.static.hpp>
#include <es_la/dense/matrix_dynamic_base.hpp>
#include <es_la/dense/shape.hpp>
#include <es_la/dense/storage/storage.hpp>
#include <es_la/dense/type_traits.hpp>

#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace es_la::internal
{
template<std::size_t ct_rows, class Derived, class Layout>
class Matrix_base<ct_rows, dynamic, Derived, Layout> : public Matrix_dynamic_base<ct_rows, dynamic, Derived, Layout>
{
private:
	using Base = Matrix_dynamic_base<ct_rows, dynamic, Derived, Layout>;

public:
	using Value = Value_type<Derived>;

public:
	using Base::Base;

	explicit Matrix_base(std::size_t cols) : Base(Internal{}, ct_rows, cols)
	{}

	Matrix_base(std::size_t cols, const Value& value) : Matrix_base(Internal{}, ct_rows, cols, value)
	{}

	Matrix_base(std::size_t cols, std::initializer_list<Value> values) : Matrix_base(Internal{}, ct_rows, cols, values)
	{}

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

template<std::size_t t_cols, class Derived, class Layout>
class Matrix_base<dynamic, t_cols, Derived, Layout> : public Matrix_dynamic_base<dynamic, t_cols, Derived, Layout>
{
private:
	using Base = Matrix_dynamic_base<dynamic, t_cols, Derived, Layout>;

public:
	using Value = Value_type<Derived>;

public:
	using Base::Base;

	explicit Matrix_base(std::size_t rows = 0) : Base(Internal{}, rows, t_cols)
	{}

	Matrix_base(std::size_t rows, const Value& value) : Base(Internal{}, rows, t_cols, value)
	{}

	Matrix_base(std::size_t rows, std::initializer_list<Value> values) : Base(Internal{}, rows, t_cols, values)
	{}

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

	Matrix_base(std::size_t rows, std::size_t cols) : Base(Internal{}, rows, cols)
	{}

	Matrix_base() : Matrix_base(0, 0)
	{}

	Matrix_base(std::size_t rows, std::size_t cols, const Value& value) : Base(Internal{}, rows, cols, value)
	{}

	Matrix_base(std::size_t rows, std::size_t cols, std::initializer_list<Value> values) : Base(Internal{}, rows, cols, values)
	{}

	using Base::operator=;

	void resize(std::size_t rows, std::size_t cols, bool preserve_data = false)
	{
		Base::resize(rows, cols, preserve_data);
	}

protected:
	using Base::data_;
};
} // namespace es_la::internal
