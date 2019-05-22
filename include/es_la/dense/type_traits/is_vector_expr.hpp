#pragma once
#include <es_la/dense/utility.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
inline constexpr bool is_vector_expr = is_ct_extent_static_and_eq(ct_cols_value<Expr>, 1);
} // namespace es_la::internal
