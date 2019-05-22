#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
struct Is_view_trait_impl : std::false_type
{};

template<class Expr, class Rows, class Cols, class Category>
struct Is_view_trait_impl<View<Expr, Rows, Cols, Category>> : std::true_type
{};

template<class Expr>
struct Is_view_trait : Is_view_trait_impl<es_util::Remove_cv_ref<Expr>>
{};

template<class Expr>
inline constexpr bool is_view = Is_view_trait<Expr>::value;
} // namespace es_la::internal
