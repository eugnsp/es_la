#pragma once
#include <es_la/core/tags.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
inline constexpr bool is_dynamic_expr = (ct_rows_value<Expr> == dynamic || ct_cols_value<Expr> == dynamic);
} // namespace es_la::internal
