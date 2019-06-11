#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/forward.hpp>

#include <cstddef>
#include <type_traits>

namespace es_la::internal
{
template<class Expr>
struct Mkl_expr_decay_trait_impl
{
	using Type = Expr;
};

template<class Expr>
struct Mkl_expr_decay_trait : Mkl_expr_decay_trait_impl<std::remove_const_t<Expr>>
{};

template<class Expr>
using Mkl_expr_decay = typename Mkl_expr_decay_trait<Expr>::Type;

template<typename Value, std::size_t rows, std::size_t cols, class Layout>
struct Mkl_expr_decay_trait_impl<Matrix<Value, rows, cols, Layout>>
{
	using Type = Lvalue_block_t<Value>;
};

template<class Expr, auto begin1, auto size1, auto begin2, auto size2>
struct Mkl_expr_decay_trait_impl<View<Expr, Range<begin1, size1>, Range<begin2, size2>, Lvalue>> :
	Mkl_expr_decay_trait<Expr>
{};

template<class Expr>
struct Mkl_expr_decay_trait_impl<Diag_view<Expr, Lvalue>> : Mkl_expr_decay_trait<Expr>
{};

template<class Expr>
struct Mkl_expr_decay_trait_impl<Transposed_view<Expr, Lvalue>> : Mkl_expr_decay_trait<Expr>
{};

template<class Expr, typename Scalar>
struct Mkl_expr_decay_trait_impl<Scalar_expr<Expr, Scalar, Scalar_mul_left_fn>>
{
	using Type = Scalar_expr_t<Mkl_expr_decay<Expr>, Scalar, Mul_t>;
};

template<class Expr, typename Scalar>
struct Mkl_expr_decay_trait_impl<Scalar_expr<Expr, Scalar, Scalar_mul_right_fn>>
{
	using Type = Scalar_expr_t<Mkl_expr_decay<Expr>, Scalar, Mul_t>;
};

template<class Expr1, class Expr2>
struct Mkl_expr_decay_trait_impl<Binary_expr<Expr1, Expr2, Mul_fn>>
{
	using Type = Binary_expr_t<Mkl_expr_decay<Expr1>, Mkl_expr_decay<Expr2>, Mul_t>;
};
}