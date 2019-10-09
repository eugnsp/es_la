#pragma once
#include <esl/dense/forward.hpp>
#include <esl/dense/tags.hpp>
#include <esl/dense/utility/layout.hpp>

#include <esu/type_traits.hpp>

#include <type_traits>

namespace esl
{
template<class Expr>
using Layout_tag = typename Traits<esu::Remove_cv_ref<Expr>>::Layout;

template<class... Exprs>
using Common_layout_tag = typename internal::Common_layout<Layout_tag<Exprs>...>::Type;

template<class T>
inline constexpr bool is_row_major = std::is_same_v<Layout_tag<T>, Row_major>;

template<>
inline constexpr bool is_row_major<Row_major> = true;

template<>
inline constexpr bool is_row_major<Col_major> = false;

template<class T>
inline constexpr bool is_col_major = std::is_same_v<Layout_tag<T>, Col_major>;

template<>
inline constexpr bool is_col_major<Row_major> = false;

template<>
inline constexpr bool is_col_major<Col_major> = true;

namespace internal
{
template<class... Exprs>
inline constexpr bool have_same_layouts = esu::are_same<Layout_tag<Exprs>...>;
}
} // namespace esl
