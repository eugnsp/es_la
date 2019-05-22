#pragma once
#include <es_la/dense/type_traits/layout.hpp>
#include <es_la/dense/forward.hpp>
#include <es_la/dense/tags.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace internal
{
template<class T>
inline constexpr bool is_layout_tag = es_util::is_one_of<T, Row_major, Col_major>;

template<class T, typename = void>
struct Is_row_major_trait : std::is_same<Layout_tag<T>, Row_major>
{};

template<class T, typename = void>
struct Is_col_major_trait : std::is_same<Layout_tag<T>, Col_major>
{};

template<class T>
struct Is_row_major_trait<T, std::enable_if_t<is_layout_tag<T>>> : std::is_same<T, Row_major>
{};

template<class T>
struct Is_col_major_trait<T, std::enable_if_t<is_layout_tag<T>>> : std::is_same<T, Col_major>
{};
}

template<class T>
inline constexpr bool is_row_major = internal::Is_row_major_trait<T>::value;

template<class T>
inline constexpr bool is_col_major = internal::Is_col_major_trait<T>::value;
} // namespace es_la
