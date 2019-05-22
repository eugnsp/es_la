#pragma once
#include <es_la/dense/type_traits/ct_extent.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
inline constexpr bool is_dynamic_expr =
	is_dynamic_extent<ct_rows_value<Expr>> || is_dynamic_extent<ct_cols_value<Expr>>;
} // namespace es_la::internal
