#pragma once
#include "../config.hpp"
#include "base.hpp"
#include <es_la/base/type_traits.hpp>
#include "expression.hpp"
//#include "extended.hpp"
#include <es_la/storage/storage.hpp>
#include <es_la/base/ct_shape.hpp>
#include <es_la/base/shape.hpp>

#include <es_util/array.hpp>

#include <array>
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <type_traits>

namespace es_la::internal
{
template<size_t t_rows, size_t t_cols, class T_Derived, class Layout>
class Matrix_base : public Expression<T_Derived>, public Shape<t_rows, t_cols, Layout>
{
private:
	using Base = Expression<T_Derived>;
	using Shape_base = Shape<t_rows, t_cols, Layout>;

public:
	using Value = Value_t<T_Derived>;

public:
	Matrix_base()
	{}

	Matrix_base(const Matrix_base&) = default;
	Matrix_base(Matrix_base&&) = default;

	template<class TExpr>
	Matrix_base(const Expression<TExpr>& expr)
	{
		Base::assign(expr);
	}

	using Base::operator=;

	Matrix_base& operator=(const Matrix_base&) = default;
	Matrix_base& operator=(Matrix_base&&) = default;

	constexpr Matrix_base(const std::array<Value, t_rows * t_cols>& values) : data_{values}
	{}

	template<std::size_t t_size>
	constexpr Matrix_base(const Value (&values)[t_size]) : Matrix_base(es_util::to_array(values))
	{
		static_assert(t_size == t_rows * t_cols);
	}

	Matrix_base(const Value& value)
	{
		std::fill(data_.data(), data_.data() + this->size(), value);
	}

	using Shape_base::cols;
	using Shape_base::rows;
	using Shape_base::size;

	constexpr Value& operator[](std::size_t index)
	{
		static_assert(t_cols == 1);
		return (*this)(index, 0);
	}

	constexpr const Value& operator[](std::size_t index) const
	{
		static_assert(t_cols == 1);
		return (*this)(index, 0);
	}

	constexpr Value& operator()(std::size_t row, std::size_t col)
	{
		return data_[linear_index(row, col)];
	}

	constexpr const Value& operator()(std::size_t row, std::size_t col) const
	{
		return data_[linear_index(row, col)];
	}

protected:
	Storage<Value, t_rows * t_cols> data_;

private:
	using Shape_base::linear_index;
};
} // namespace la::internal
