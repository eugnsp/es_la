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
constexpr auto make_vector_impl(Fn fn, std::index_sequence<ii...>)
{
	using Value = std::invoke_result_t<Fn, std::size_t>;
	return Vector<Value, sizeof...(ii)>{fn(ii)...};
}

template<std::size_t rows, std::size_t cols, class Layout, class Fn, std::size_t... ii>
constexpr auto make_matrix_impl(Fn fn, std::index_sequence<ii...>)
{
	using Value = std::invoke_result_t<Fn, std::size_t, std::size_t>;
	constexpr auto stride = is_col_major<Layout> ? rows : cols;
	return Matrix<Value, rows, cols, Layout>{fn(ii % stride, ii / stride)...};
}
} // namespace internal

template<std::size_t size, class Fn>
constexpr auto make_vector(Fn fn)
{
	return internal::make_vector_impl(fn, std::make_index_sequence<size>{});
}

template<std::size_t rows, std::size_t cols, class Layout = Col_major, class Fn>
constexpr auto make_matrix(Fn fn)
{
	return internal::make_matrix_impl<rows, cols, Layout>(fn, std::make_index_sequence<rows * cols>{});
}
} // namespace es_la
