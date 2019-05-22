#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Expr>
struct Layout_trait_impl;

template<class Expr>
struct Layout_trait : Layout_trait_impl<es_util::Remove_cv_ref<Expr>>
{};

//////////////////////////////////////////////////////////////////////

template<typename Value, auto ct_rows, auto ct_cols, class Layout>
struct Layout_trait_impl<Matrix<Value, ct_rows, ct_cols, Layout>>
{
	using Type = Layout;
};

template<class Expr, class Rows, class Cols, class Category>
struct Layout_trait_impl<View<Expr, Rows, Cols, Category>> : Layout_trait<Expr>
{};
}

template<class Expr>
using Layout_tag = typename internal::Layout_trait<Expr>::Type;
} // namespace es_la
