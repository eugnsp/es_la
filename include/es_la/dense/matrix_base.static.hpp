#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/shape.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/storage/storage.hpp>

#include <es_util/array.hpp>

#include <array>
#include <cstddef>

namespace es_la::internal
{
template<auto ct_rows, auto ct_cols, class Expr, class Layout>
class Matrix_base;

template<std::size_t ct_rows, std::size_t ct_cols, class Expr, class Layout>
class Matrix_base<ct_rows, ct_cols, Expr, Layout> : public Dense<Expr, Lvalue>, public Shape<ct_rows, ct_cols, Layout>
{
private:
	using Dense_base = Dense<Expr, Lvalue>;
	using Shape_base = Shape<ct_rows, ct_cols, Layout>;

public:
	using Value = Value_type<Expr>;

public:
	//////////////////////////////////////////////////////////////////////
	//* Constructors */

	Matrix_base() = default;
	Matrix_base(const Matrix_base&) = default;
	Matrix_base(Matrix_base&&) = default;

	explicit Matrix_base(const Value& value)
	{
		Dense_base::assign_scalar(value);
	}

	explicit constexpr Matrix_base(const std::array<Value, ct_rows * ct_cols>& values) : data_{values}
	{}

	//explicit constexpr Matrix_base(const Value (&values)[ct_rows * ct_cols]) : Matrix_base(es_util::to_array(values))
	//{}

	template<class Expr2>
	explicit Matrix_base(const Expression<Expr2>& expr)
	{
		Dense_base::assign_expr(expr);
	}

	///////////////////////////////////////////////////////////////////////
	//* Assignments */

	using Dense_base::operator=;

	Matrix_base& operator=(const Matrix_base&) = default;
	Matrix_base& operator=(Matrix_base&&) = default;

	////////////////////////////////////////////////////////////////////////
	//* Extents */

	using Shape_base::cols;
	using Shape_base::rows;

	static constexpr std::size_t size()
	{
		return rows() * cols();
	}

	static constexpr std::size_t capacity()
	{
		return size();
	}

	///////////////////////////////////////////////////////////////////////
	//* Element access */

	constexpr Value& operator()(std::size_t row, std::size_t col)
	{
		return data_[this->linear_index(row, col)];
	}

	constexpr const Value& operator()(std::size_t row, std::size_t col) const
	{
		return data_[this->linear_index(row, col)];
	}

	constexpr Value& operator[](std::size_t index)
	{
		static_assert(internal::is_vector_expr<Expr>, "Expression should be a vector");
		return (*this)(index, 0);
	}

	constexpr const Value& operator[](std::size_t index) const
	{
		static_assert(internal::is_vector_expr<Expr>, "Expression should be a vector");
		return (*this)(index, 0);
	}

protected:
	Storage<Value, ct_rows * ct_cols> data_;
};
} // namespace es_la::internal
