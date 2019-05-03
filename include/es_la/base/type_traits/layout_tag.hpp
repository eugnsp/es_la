#pragma once
#include <es_la/base/forward.hpp>
#include <es_la/tags.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace internal
{
template<class T>
inline constexpr bool is_layout_tag = es_util::is_one_of<T, Row_major, Col_major>;
}

template<class T, typename = void>
struct Is_row_major;

template<class T>
struct Is_row_major<T, std::enable_if_t<internal::is_layout_tag<T>>> : std::is_same<T, Row_major>
{};

template<typename Value, std::size_t ct_rows, std::size_t ct_cols, class Layout_tag>
struct Is_row_major<Matrix<Value, ct_rows, ct_cols, Layout_tag>> :
	std::is_same<Layout_tag, Row_major>
{};

template<class T>
inline constexpr bool is_row_major = Is_row_major<T>::value;

template<class T, typename = void>
struct Is_col_major;

template<class T>
struct Is_col_major<T, std::enable_if_t<internal::is_layout_tag<T>>> : std::is_same<T, Col_major>
{};

template<typename Value, std::size_t ct_rows, std::size_t ct_cols, class Layout_tag>
struct Is_col_major<Matrix<Value, ct_rows, ct_cols, Layout_tag>> :
	std::is_same<Layout_tag, Col_major>
{};

template<class T>
inline constexpr bool is_col_major = Is_col_major<T>::value;
} // namespace es_la
