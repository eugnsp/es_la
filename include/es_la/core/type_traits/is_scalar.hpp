#pragma once
#include <es_la/core/type_traits/is_expression.hpp>

#include <type_traits>

namespace es_la
{
template<typename Expr>
inline constexpr bool is_scalar = !is_expression<Expr>;
} // namespace es_la
