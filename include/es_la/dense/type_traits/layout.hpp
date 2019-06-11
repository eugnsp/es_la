#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Layout>
struct Transpose_layout_impl;

template<>
struct Transpose_layout_impl<Col_major>
{
	using Type = Row_major;
};

template<>
struct Transpose_layout_impl<Row_major>
{
	using Type = Col_major;
};

template<class Layout>
using Transpose_layout = typename Transpose_layout_impl<Layout>::Type;

///////////////////////////////////////////////////////////////////////

template<class Expr>
struct Layout_trait_impl
{};

template<class Expr>
struct Layout_trait : Layout_trait_impl<es_util::Remove_cv_ref<Expr>>
{};
}

template<class Expr>
using Layout_tag = typename internal::Layout_trait<Expr>::Type;

//////////////////////////////////////////////////////////////////////
namespace internal
{
template<typename Value, auto ct_rows, auto ct_cols, class Layout>
struct Layout_trait_impl<Matrix<Value, ct_rows, ct_cols, Layout>>
{
	using Type = Layout;
};

template<class Expr, class Rows, class Cols, class Category>
struct Layout_trait_impl<View<Expr, Rows, Cols, Category>> : Layout_trait<Expr>
{};

template<class Expr, class Category>
struct Layout_trait_impl<Transposed_view<Expr, Category>>
{
	using Type = Transpose_layout<Layout_tag<Expr>>;
};

template<class Expr, class Category>
struct Layout_trait_impl<Diag_view<Expr, Category>>
{
	using Type = Row_major;
};

//////////////////////////////////////////////////////////////////////

template<class Expr1, class Expr2>
inline constexpr bool have_same_layout = std::is_same_v<Layout_tag<Expr1>, Layout_tag<Expr2>>;
}
} // namespace es_la
