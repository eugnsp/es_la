#pragma once
#include <es_la/tags.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
inline constexpr bool is_symmetric = es_util::is_one_of<typename Expr::Symmetry_tag, Symmetric_upper, Symmetric_lower>;

template<class Expr>
inline constexpr bool is_structural_symmetric = std::is_same_v<typename Expr::Symmetry_tag, Structural_symmetric>;
}
