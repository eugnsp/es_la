#pragma once
#include <es_la/dense/forward.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/utility/ct_extent.hpp>

#include <es_util/type_traits.hpp>

#include <algorithm>
#include <cstddef>

namespace es_la
{
template<class Expr>
struct Ct_rows_trait;

template<class Expr>
struct Ct_cols_trait;

template<class Expr>
struct Ct_size_trait;

template<class Expr>
inline constexpr auto ct_rows_value = Ct_rows_trait<Expr>::value;

template<class Expr>
inline constexpr auto ct_cols_value = Ct_cols_trait<Expr>::value;

template<class Expr>
inline constexpr auto ct_size_value = Ct_size_trait<Expr>::value;

namespace internal
{
template<class Expr>
inline constexpr bool is_row_dynamic = (ct_rows_value<Expr> == dynamic);

template<class Expr>
inline constexpr bool is_col_dynamic = (ct_cols_value<Expr> == dynamic);

template<class Expr>
inline constexpr bool is_rc_dynamic = is_row_dynamic<Expr>&& is_col_dynamic<Expr>;

template<class Expr>
inline constexpr bool is_dynamic = is_row_dynamic<Expr> || is_col_dynamic<Expr>;

template<class Expr>
inline constexpr bool is_vector = (ct_cols_value<Expr> == 1);
}

//////////////////////////////////////////////////////////////////////

template<typename T, std::size_t ct_rows, std::size_t ct_cols, class Layout>
struct Ct_rows_trait<Matrix<T, ct_rows, ct_cols, Layout>> : std::integral_constant<std::size_t, ct_rows>
{};

template<typename T, std::size_t ct_rows, std::size_t ct_cols, class Layout>
struct Ct_cols_trait<Matrix<T, ct_rows, ct_cols, Layout>> : std::integral_constant<std::size_t, ct_cols>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr, class Rows, class Cols, class Category>
struct Ct_rows_trait<View<Expr, Rows, Cols, Category>> : Ct_size_trait<Rows>
{};

template<class Expr, class Rows, class Cols, class Category>
struct Ct_cols_trait<View<Expr, Rows, Cols, Category>> : Ct_size_trait<Cols>
{};

//////////////////////////////////////////////////////////////////////

template<class Expr, class Category>
struct Ct_rows_trait<Transposed_view<Expr, Category>> : Ct_cols_trait<Expr>
{};

template<class Expr, class Category>
struct Ct_cols_trait<Transposed_view<Expr, Category>> : Ct_rows_trait<Expr>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr, class Category>
struct Ct_rows_trait<Diag_view<Expr, Category>> :
	std::integral_constant<std::size_t, std::min(ct_rows_value<Expr>, ct_cols_value<Expr>)>
{};

template<class Expr, class Category>
struct Ct_cols_trait<Diag_view<Expr, Category>> : std::integral_constant<std::size_t, 1>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr, typename Scalar, template<class, typename> class Fn>
struct Ct_rows_trait<Scalar_expr<Expr, Scalar, Fn>> : Ct_rows_trait<Expr>
{};

template<class Expr, typename Scalar, template<class, typename> class Fn>
struct Ct_cols_trait<Scalar_expr<Expr, Scalar, Fn>> : Ct_cols_trait<Expr>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr_l, class Expr_r, template<class, class> class Fn>
struct Ct_rows_trait<Binary_expr<Expr_l, Expr_r, Fn>> : std::integral_constant<std::size_t, Fn<Expr_l, Expr_r>::ct_rows>
{};

template<class Expr_l, class Expr_r, template<class, class> class Fn>
struct Ct_cols_trait<Binary_expr<Expr_l, Expr_r, Fn>> : std::integral_constant<std::size_t, Fn<Expr_l, Expr_r>::ct_cols>
{};

///////////////////////////////////////////////////////////////////////

template<class Random_distribution, class Random_generator>
struct Ct_rows_trait<Random_matrix<Random_distribution, Random_generator>> : internal::Dynamic
{};

template<class Random_distribution, class Random_generator>
struct Ct_cols_trait<Random_matrix<Random_distribution, Random_generator>> : internal::Dynamic
{};

///////////////////////////////////////////////////////////////////////

template<std::size_t ct_begin, std::size_t ct_size>
struct Ct_size_trait<internal::Range<ct_begin, ct_size>> : std::integral_constant<std::size_t, ct_size>
{};

template<std::size_t ct_size>
struct Ct_size_trait<internal::Slice<ct_size>> : std::integral_constant<std::size_t, ct_size>
{};
} // namespace es_la
