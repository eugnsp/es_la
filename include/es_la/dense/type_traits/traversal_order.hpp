#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits/is_row_col_major.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace traits
{
template<class Expr>
struct Traversal_order;
}

namespace internal
{
template<class... Ts>
struct Common_traversal_order_tag
{
	using Type = Col_major;
};

template<class... Ts>
struct Common_traversal_order_tag<Any_order, Ts...> : Common_traversal_order_tag<Ts...>
{};
} // namespace internal

// Returns the traversal order tag of an expression, possibly cv-ref qualified
template<class Expr>
using Traversal_order_tag = typename traits::Traversal_order<es_util::Remove_cv_ref<Expr>>::Type;

// Returns the common traversal order tag of expressions, possibly cv-ref qualified
// (the common traversal order tag is the first tag that is not `Any_order`)
template<class... Exprs>
using Common_traversal_order_tag = typename internal::Common_traversal_order_tag<Traversal_order_tag<Exprs>...>::Type;

template<class Expr>
inline constexpr bool is_row_major_traversal = is_row_major<Traversal_order_tag<Expr>>;

template<class Expr>
inline constexpr bool is_col_major_traversal = is_col_major<Traversal_order_tag<Expr>>;

template<class Expr>
inline constexpr bool is_any_traversal = std::is_same_v<Traversal_order_tag<Expr>, Any_order>;
} // namespace es_la
