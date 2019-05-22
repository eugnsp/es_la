#pragma once
#include <es_la/dense/forward.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits.hpp>

#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace es_la
{
namespace internal
{
template<class Fn, std::size_t... ii>
constexpr auto make_array_of_func_values_impl(Fn fn, std::index_sequence<ii...>)
{
	using Result = std::invoke_result_t<Fn, std::size_t>;
	return std::array<Result, sizeof...(ii)>{fn(ii)...};
}

template<std::size_t size, class Fn>
constexpr auto make_array_of_func_values(Fn fn)
{
	return make_array_of_func_values_impl(fn, std::make_index_sequence<size>{});
}

template<std::size_t stride, class Fn, std::size_t... ii>
constexpr auto make_array_of_2d_func_values_impl(Fn fn, std::index_sequence<ii...>)
{
	using Result = std::invoke_result_t<Fn, std::size_t, std::size_t>;
	return std::array<Result, sizeof...(ii)>{fn(ii % stride, ii / stride)...};
}

template<std::size_t ct_rows, std::size_t ct_cols, class Layout, class Fn>
constexpr auto make_array_of_2d_func_values(Fn fn)
{
	constexpr auto stride = is_col_major<Layout> ? ct_rows : ct_cols;
	return make_array_of_2d_func_values_impl<stride>(fn, std::make_index_sequence<ct_rows * ct_cols>{});
}
} // namespace internal

template<std::size_t size, class Fn>
constexpr auto make_vector(Fn fn)
{
	using Value = std::invoke_result_t<Fn, std::size_t>;
	return Vector<Value, size>(internal::make_array_of_func_values<size>(fn));
}

template<std::size_t ct_rows, std::size_t ct_cols, class Layout = Col_major, class Fn>
constexpr auto make_matrix(Fn fn)
{
	using Value = std::invoke_result_t<Fn, std::size_t, std::size_t>;
	return Matrix<Value, ct_rows, ct_cols, Layout>(
		internal::make_array_of_2d_func_values<ct_rows, ct_cols, Layout>(fn));
}
} // namespace es_la
