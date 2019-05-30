#pragma once
#include <es_la/core/tags.hpp>

#include <type_traits>

namespace es_la
{
template<class Expr>
struct Ct_rows_trait;

template<class Expr>
struct Ct_cols_trait;

template<class Expr>
struct Ct_size_trait;

template<class Expr>
inline constexpr auto ct_rows_value = Ct_rows_trait<Expr>::value;

template<class Expr>
inline constexpr auto ct_cols_value = Ct_cols_trait<Expr>::value;

template<class Expr>
inline constexpr auto ct_size_value = Ct_size_trait<Expr>::value;
} // namespace es_la
