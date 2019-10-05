#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/utility/layout.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
template<class Expr>
struct Traits;

//> Value

template<class Expr>
using Value_type = typename Traits<es_util::Remove_cv_ref<Expr>>::Value;

namespace internal
{
template<class Expr1, class Expr2>
inline constexpr bool have_same_value_type = std::is_same_v<Value_type<Expr1>, Value_type<Expr2>>;
}

//> Layout

template<class Expr>
using Layout_tag = typename Traits<es_util::Remove_cv_ref<Expr>>::Layout;

template<class... Exprs>
using Common_layout_tag = typename internal::Common_layout<Layout_tag<Exprs>...>::Type;

template<class T>
inline constexpr bool is_row_major = std::is_same_v<Layout_tag<T>, Row_major>;

template<>
inline constexpr bool is_row_major<Row_major> = true;

template<>
inline constexpr bool is_row_major<Col_major> = false;

template<class T>
inline constexpr bool is_col_major = std::is_same_v<Layout_tag<T>, Col_major>;

template<>
inline constexpr bool is_col_major<Row_major> = false;

template<>
inline constexpr bool is_col_major<Col_major> = true;

namespace internal
{
template<class Expr1, class Expr2>
inline constexpr bool have_same_layout = std::is_same_v<Layout_tag<Expr1>, Layout_tag<Expr2>>;
}

//> Compile-time extents

template<class Expr>
inline constexpr auto ct_rows_value = Traits<Expr>::rows;

template<class Expr>
inline constexpr auto ct_cols_value = Traits<Expr>::cols;

namespace internal
{
template<class Expr>
inline constexpr bool is_row_dynamic = (ct_rows_value<Expr> == dynamic);

template<class Expr>
inline constexpr bool is_col_dynamic = (ct_cols_value<Expr> == dynamic);

template<class Expr>
inline constexpr bool is_rc_dynamic = is_row_dynamic<Expr> && is_col_dynamic<Expr>;

template<class Expr>
inline constexpr bool is_dynamic = is_row_dynamic<Expr> || is_col_dynamic<Expr>;

template<class Expr>
inline constexpr bool is_vector = (ct_cols_value<Expr> == 1);
}

} // namespace es_la

#include <es_la/dense/type_traits/ct_extent.hpp>
#include <es_la/dense/type_traits/expr_storage.hpp>
#include <es_la/dense/type_traits/is_dense.hpp>
#include <es_la/dense/type_traits/is_expression.hpp>
#include <es_la/dense/type_traits/is_lvalue.hpp>
#include <es_la/dense/type_traits/is_lvalue_block.hpp>
#include <es_la/dense/type_traits/is_view.hpp>
#include <es_la/dense/type_traits/mkl_decay.hpp>
#include <es_la/dense/type_traits/mkl_type.hpp>
#include <es_la/dense/type_traits/numeric.hpp>
