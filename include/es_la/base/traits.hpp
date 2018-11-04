#pragma once
#include "forward.hpp"
#include <complex>
#include <type_traits>

namespace la::internal
{
struct Read_only_tag { };
struct Read_write_tag { };

template<class T>
using Tag_by_constness = std::conditional_t<std::is_const_v<T>, Read_only_tag, Read_write_tag>;

//////////////////////////////////////////////////////////////////////////

template<class T>
struct Is_expr_impl : std::is_base_of<Expression<T>, T> { };

template<class T>
struct Is_expr : Is_expr_impl<std::remove_cv_t<T>> { };

template<class T>
struct Is_matrix_impl : std::false_type { };

template<typename T, std::size_t rows, std::size_t cols, class Layout>
struct Is_matrix_impl<Matrix<T, rows, cols, Layout>> : std::true_type { };

template<class T>
struct Is_matrix : Is_matrix_impl<std::remove_cv_t<T>> { };

template<class T>
constexpr bool is_matrix = Is_matrix<T>::value;

template<class T>
struct Is_any_expr : std::bool_constant<Is_expr<T>::value || is_matrix<T>> { };

template<class T>
constexpr bool is_expr = Is_expr<T>::value;

template<class T>
constexpr bool is_any_expr = Is_any_expr<T>::value;

//////////////////////////////////////////////////////////////////////////

template<class Ex, class Rows, class Cols>
using Sub_expr_t = Sub_expr<Ex, Rows, Cols,	Tag_by_constness<Ex>>;

template<class T>
using Expr_storage_t = std::conditional_t<is_matrix<T>, T&, T>;

//////////////////////////////////////////////////////////////////////////

template<class>
struct Traits_impl { };

template<class T>
struct Traits : Traits_impl<std::remove_cv_t<T>> { };

template<class T>
using Value_t = typename Traits<T>::Value;

template<class T>
constexpr std::size_t size_v = Traits<T>::size;

template<class T>
constexpr std::size_t rows_v = Traits<T>::rows;

template<class T>
constexpr std::size_t cols_v = Traits<T>::cols;

/************************************************************************/

template<typename T_Value, std::size_t t_rows, std::size_t t_cols, class Layout>
struct Traits_impl<Matrix<T_Value, t_rows, t_cols, Layout>>
{
	using Value = T_Value;
	using Access_tag = Read_write_tag;

	static constexpr std::size_t rows = t_rows;
	static constexpr std::size_t cols = t_cols;
};

/************************************************************************/

template<class TExpr, class TRows, class TCols, class TAccess_tag>
struct Traits_impl<Sub_expr<TExpr, TRows, TCols, TAccess_tag>>
{
	using Value = Value_t<TExpr>;
	using Access_tag = std::conditional_t<std::is_same_v<TAccess_tag, Read_only_tag>,
		Read_only_tag, typename Traits<TExpr>::Access_tag>;

	static constexpr std::size_t rows = size_v<TRows>;
	static constexpr std::size_t cols = size_v<TCols>;
};

template<std::size_t t_begin, std::size_t t_size>
struct Traits_impl<Range<t_begin, t_size>>
{
	static constexpr std::size_t size = t_size;
};

template<std::size_t t_size>
struct Traits_impl<Slice<t_size>>
{
	static constexpr std::size_t size = t_size;
};

/************************************************************************/

template<class TExpr, typename TScalar, class TFunc>
struct Traits_impl<Unary_expr<TExpr, TScalar, TFunc>>
{
	using Value = typename TFunc::Value;
	using Access_tag = Read_only_tag;

	static constexpr std::size_t rows = rows_v<TExpr>;
	static constexpr std::size_t cols = cols_v<TExpr>;
};

template<class Left, class Right, template<class, class> class Func>
struct Traits_impl<Bin_expr<Left, Right, Func>>
{
	using Value = typename Func<Left, Right>::Value;
	using Access_tag = Read_only_tag;

	static constexpr std::size_t rows = Func<Left, Right>::ct_rows;
	static constexpr std::size_t cols = Func<Left, Right>::ct_cols;
};

//////////////////////////////////////////////////////////////////////////

template<class Ex>
struct Is_dynamic_expr : std::bool_constant<(Traits<Ex>::rows == dynamic || Traits<Ex>::cols == dynamic)> { };

template<class Ex>
struct Is_dynamic_matrix : std::conjunction<Is_matrix<Ex>, Is_dynamic_expr<Ex>> { };
	
//////////////////////////////////////////////////////////////////////////

template<class T>
struct Is_range : std::false_type { };

template<std::size_t begin, std::size_t size>
struct Is_range<Range<begin, size>> : std::true_type { };

template<class T>
constexpr bool is_range = Is_range<T>::value;

template<class>
struct Is_indexer_impl : std::false_type { };

template<class T>
struct Is_indexer : Is_indexer_impl<std::remove_cv_t<T>> { };

template<std::size_t t_begin, std::size_t t_size>
struct Is_indexer_impl<Range<t_begin, t_size>> : std::true_type { };

template<std::size_t t_size>
struct Is_indexer_impl<Slice<t_size>> : std::true_type { };

template<class T>
constexpr bool is_indexer_v = Is_indexer<T>::value;

template<template<class> class Func, class T>
struct Is_matrix_block_impl_func : std::false_type { };

template<template<class> class Func, class Ex, class Rows, class Cols, class Access_tag>
struct Is_matrix_block_impl_func<Func, Sub_expr<Ex, Rows, Cols, Access_tag>>
	: std::conjunction<Func<Ex>, Is_range<Rows>, Is_range<Cols>> { };

template<template<class> class Func, class T>
struct Is_matrix_block_func : Is_matrix_block_impl_func<Func, std::remove_cv_t<T>> { };

template<class T>
struct Is_matrix_block : Is_matrix_block_func<Is_matrix, std::remove_cv_t<T>> { };

template<class T>
constexpr bool is_matrix_block = Is_matrix_block<T>::value;

template<template<class> class Func, class T>
struct Is_matrix_or_matrix_block_func
	: std::disjunction<Func<T>, Is_matrix_block_func<Func, T>> { };

template<class T>
struct Is_matrix_or_matrix_block : Is_matrix_or_matrix_block_func<Is_matrix, T> { };

template<class T>
constexpr bool is_matrix_or_matrix_block = Is_matrix_or_matrix_block<T>::value;

template<class T>
struct Is_dyn_matrix_or_dyn_matrix_block
	: Is_matrix_or_matrix_block_func<Is_dynamic_matrix, T> { };

template<class T>
constexpr bool is_dyn_matrix_or_dyn_matrix_block = Is_dyn_matrix_or_dyn_matrix_block<T>::value;

//////////////////////////////////////////////////////////////////////////

template<class T>
constexpr bool is_vector = is_matrix<T> && Traits<T>::cols == 1;

//////////////////////////////////////////////////////////////////////////

template<class T>
struct Is_vector_expr : std::bool_constant<cols_v<T> == 1> { };

template<class T>
constexpr bool is_vector_expr_v = Is_vector_expr<T>::value;

//////////////////////////////////////////////////////////////////////////

template<class T>
struct Has_fd_or_complex_fd_element
	: std::disjunction<std::is_same<double, Value_t<T>>, std::is_same<float, Value_t<T>>,
	std::is_same<std::complex<double>, Value_t<T>>, std::is_same<std::complex<float>, Value_t<T>>> { };

template<class T>
constexpr bool has_fd_or_complex_fd_element = Has_fd_or_complex_fd_element<T>::value;

//////////////////////////////////////////////////////////////////////////

template<class T>
struct Is_product_expr_impl : std::false_type { };

template<class Left, class Right>
struct Is_product_expr_impl<Bin_expr<Left, Right, Mul_func>> : std::true_type { };

template<class T>
struct Is_product_expr : Is_product_expr_impl<std::remove_cv_t<T>> { };

template<class T>
constexpr bool is_product_expr = Is_product_expr<T>::value;

//////////////////////////////////////////////////////////////////////////

template<class Layout>
inline constexpr bool is_row_major = std::is_same_v<Layout, Row_major>;

template<class Layout>
inline constexpr bool is_col_major = std::is_same_v<Layout, Col_major>;

}
