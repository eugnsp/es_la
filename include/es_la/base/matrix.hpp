#pragma once
#include "../config.hpp"
#include "matrix_base_static.hpp"
#include "matrix_base_dynamic.hpp"
#include <es_util/type_traits.hpp>
#include <tuple>
#include <type_traits>

namespace la
{
namespace internal
{

class Static_matrix
{};

class Dynamic_matrix
{};
} // namespace internal

template<typename T_Value, size_t t_rows, size_t t_cols, class Layout>
class Matrix :
	public internal::Matrix_base<t_rows, t_cols, Matrix<T_Value, t_rows, t_cols, Layout>, Layout>
{
	static_assert(!std::is_const_v<T_Value>);
	static_assert(!std::is_reference_v<T_Value>);
	// static_assert(std::is_trivially_copyable_v<T_Value>);

public:
	static constexpr std::size_t static_rows = t_rows;
	static constexpr std::size_t static_cols = t_cols;

private:
	using Base = internal::Matrix_base<t_rows, t_cols, Matrix, Layout>;

public:
	using Base::Base;

	Matrix() = default;
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	template<class Expr>
	Matrix(const Expression<Expr>& expr) : Base(expr)
	{}

	template<class Expr>
	Matrix& operator=(const Expression<Expr>& expr)
	{
		this->assign(expr);
		return *this;
	}

	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;

	using Base::cols;
	using Base::rows;

	T_Value* data() noexcept MATHLA_ALIGNED_ATTR_S
	{
		return data_.data();
	}

	const T_Value* data() const noexcept MATHLA_ALIGNED_ATTR_S
	{
		return data_.data();
	}

	std::size_t lead_dim() const
	{
		return rows();
	}

private:
	using Base::data_;
};

namespace internal
{
// TODO : move to util::
template<class Func, std::size_t... ii>
constexpr auto make_array_of_func_values_impl(Func func, std::index_sequence<ii...>)
{
	using Result = std::invoke_result_t<Func, std::size_t>;
	return std::array<Result, sizeof...(ii)>{func(ii)...};
}

template<std::size_t size, class Func>
constexpr auto make_array_of_func_values(Func func)
{
	return make_array_of_func_values_impl(func, std::make_index_sequence<size>{});
}

template<typename Rows, typename Cols, auto stride, class Func, std::size_t... ii>
constexpr auto make_array_of_2d_func_values_impl(Func func, std::index_sequence<ii...>)
{
	using Result = std::invoke_result_t<Func, Rows, Cols>;
	return std::array<Result, sizeof...(ii)>{
		func(static_cast<Rows>(ii % stride), static_cast<Cols>(ii / stride))...};
}

template<auto rows, auto cols, class Func>
constexpr auto make_array_of_2d_func_values(Func func)
{
	return make_array_of_2d_func_values_impl<decltype(rows), decltype(cols), rows>(
		func, std::make_index_sequence<rows * cols>{});
}
} // namespace internal

template<std::size_t size, class Func>
constexpr auto make_vector(Func func)
{
	using Value = std::invoke_result_t<Func, std::size_t>;
	return Vector<Value, size>(internal::make_array_of_func_values<size>(func));
}

template<auto rows, auto cols, class Func>
constexpr auto make_matrix(Func func)
{
	using Value = std::invoke_result_t<Func, decltype(rows), decltype(cols)>;
	return Matrix<Value, rows, cols>(internal::make_array_of_2d_func_values<rows, cols>(func));
}

// TODO : move to another header / combine headers
template<typename T>
T det(Matrix<T, 2, 2>& m)
{
	return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
}

template<typename T>
void invert(Matrix<T, 2, 2>& m)
{
	const auto d = det(m);

	std::swap(m(0, 0), m(1, 1));
	m(0, 0) /= d;
	m(1, 1) /= d;
	m(1, 0) /= -d;
	m(0, 1) /= -d;
}

template<typename T>
void invert_transpose(Matrix<T, 2, 2>& m)
{
	const auto d = det(m);
	const auto m00 = m(0, 0);
	const auto m01 = m(0, 1);

	m(0, 0) = m(1, 1) / d;
	m(1, 1) = m00 / d;
	m(0, 1) = -m(1, 0) / d;
	m(1, 0) = -m01 / d;
}
} // namespace la
