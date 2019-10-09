#pragma once
#include <esl/dense/forward.hpp>
#include <esl/dense/tags.hpp>
#include <esl/dense/utility/ct_extent.hpp>

#include <esu/type_traits.hpp>

#include <algorithm>
#include <cstddef>

namespace esl
{
namespace internal
{
template<class Expr>
struct Ct_size_trait_impl
{};
} // namespace internal

template<class Expr>
using Ct_size_trait = internal::Ct_size_trait_impl<esu::Remove_cv_ref<Expr>>;

namespace internal
{
template<std::size_t ct_begin, std::size_t ct_size>
struct Ct_size_trait_impl<internal::Range<ct_begin, ct_size>> : std::integral_constant<std::size_t, ct_size>
{};

template<std::size_t ct_size>
struct Ct_size_trait_impl<internal::Slice<ct_size>> : std::integral_constant<std::size_t, ct_size>
{};
} // namespace internal

template<class Expr>
inline constexpr auto ct_rows_value = Traits<esu::Remove_cv_ref<Expr>>::rows;

template<class Expr>
inline constexpr auto ct_cols_value = Traits<esu::Remove_cv_ref<Expr>>::cols;

template<class Expr>
inline constexpr auto ct_row_stride_value = Traits<esu::Remove_cv_ref<Expr>>::row_stride;

template<class Expr>
inline constexpr auto ct_col_stride_value = Traits<esu::Remove_cv_ref<Expr>>::col_stride;

namespace internal
{
template<class Expr>
inline constexpr bool is_row_dynamic = (ct_rows_value<Expr> == dynamic);

template<class Expr>
inline constexpr bool is_col_dynamic = (ct_cols_value<Expr> == dynamic);

template<class Expr>
inline constexpr bool is_rc_dynamic = is_row_dynamic<Expr> && is_col_dynamic<Expr>;

template<class Expr>
inline constexpr bool is_dynamic = is_row_dynamic<Expr> || is_col_dynamic<Expr>;

template<class Expr>
inline constexpr bool is_vector = (ct_cols_value<Expr> == 1);
}
} // namespace esl
