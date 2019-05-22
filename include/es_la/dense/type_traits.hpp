#pragma once
#include <es_la/core/type_traits.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>
#include <es_la/dense/type_traits/expr_storage.hpp>
#include <es_la/dense/type_traits/is_dense.hpp>
#include <es_la/dense/type_traits/is_dynamic_expr.hpp>
#include <es_la/dense/type_traits/is_lvalue_block.hpp>
#include <es_la/dense/type_traits/is_row_col_major.hpp>
#include <es_la/dense/type_traits/is_vector_expr.hpp>
#include <es_la/dense/type_traits/is_view.hpp>
#include <es_la/dense/type_traits/layout.hpp>
#include <es_la/dense/type_traits/operator.hpp>
#include <es_la/dense/type_traits/value.hpp>

#include <complex>
#include <type_traits>

namespace es_la::internal
{
template<class T>
struct Is_matrix_impl : std::false_type
{};

template<typename T, auto rows, auto cols, class Layout>
struct Is_matrix_impl<Matrix<T, rows, cols, Layout>> : std::true_type
{};

template<class T>
struct Is_matrix : Is_matrix_impl<std::remove_cv_t<T>>
{};

template<class T>
constexpr bool is_matrix = Is_matrix<T>::value;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

// template<class Ex>
// struct Is_dynamic_matrix : std::conjunction<Is_matrix<Ex>, Is_dynamic_expr<Ex>>
// {};

//////////////////////////////////////////////////////////////////////////

// template<template<class> class Func, class T>
// struct Is_matrix_block_impl_func : std::false_type
// {};

// template<template<class> class Func, class Ex, class Rows, class Cols>
// struct Is_matrix_block_impl_func<Func, View<Ex, Rows, Cols>> :
// 	std::conjunction<Func<Ex>, Is_range<Rows>, Is_range<Cols>>
// {};

// template<template<class> class Func, class T>
// struct Is_matrix_block_func : Is_matrix_block_impl_func<Func, std::remove_cv_t<T>>
// {};

// template<class T>
// struct Is_matrix_block : Is_matrix_block_func<Is_matrix, std::remove_cv_t<T>>
// {};

// template<class T>
// constexpr bool is_matrix_block = Is_matrix_block<T>::value;

// template<template<class> class Func, class T>
// struct Is_matrix_or_matrix_block_func : std::disjunction<Func<T>, Is_matrix_block_func<Func, T>>
// {};

// template<class T>
// struct Is_matrix_or_matrix_block : Is_matrix_or_matrix_block_func<Is_matrix, T>
// {};

// template<class T>
// constexpr bool is_matrix_or_matrix_block = Is_matrix_or_matrix_block<T>::value;

// template<class T>
// struct Is_dyn_matrix_or_dyn_matrix_block : Is_matrix_or_matrix_block_func<Is_dynamic_matrix, T>
// {};

// template<class T>
// constexpr bool is_dyn_matrix_or_dyn_matrix_block = Is_dyn_matrix_or_dyn_matrix_block<T>::value;

//////////////////////////////////////////////////////////////////////////

// template<class T>
// constexpr bool is_vector = is_matrix<T>&& Traits<T>::cols == 1;

//////////////////////////////////////////////////////////////////////////

template<class T>
struct Has_fd_or_complex_fd_element :
	std::disjunction<std::is_same<double, Value_type<T>>, std::is_same<float, Value_type<T>>,
		std::is_same<std::complex<double>, Value_type<T>>, std::is_same<std::complex<float>, Value_type<T>>>
{};

template<class T>
constexpr bool has_fd_or_complex_fd_element = Has_fd_or_complex_fd_element<T>::value;

//////////////////////////////////////////////////////////////////////////

template<class T>
struct Is_product_expr_impl : std::false_type
{};

template<class Left, class Right>
struct Is_product_expr_impl<Binary_expr<Left, Right, Mul_func>> : std::true_type
{};

template<class T>
struct Is_product_expr : Is_product_expr_impl<std::remove_cv_t<T>>
{};

template<class T>
constexpr bool is_product_expr = Is_product_expr<T>::value;
} // namespace es_la::internal
