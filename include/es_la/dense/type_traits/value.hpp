#pragma once
#include <es_la/core/type_traits/value.hpp>
#include <es_la/dense/forward.hpp>

#include <type_traits>

namespace es_la::internal
{
template<typename Value, auto ct_rows, auto ct_cols, class Layout>
struct Value_trait_impl<Matrix<Value, ct_rows, ct_cols, Layout>>
{
	using Type = Value;
};

template<class Expr, class Rows, class Cols, class Category>
struct Value_trait_impl<View<Expr, Rows, Cols, Category>> : Value_trait<Expr>
{};

template<class Expr, class Category>
struct Value_trait_impl<Transposed_view<Expr, Category>> : Value_trait<Expr>
{};

template<class Expr1, class Expr2, template<class, class> class Fn>
struct Value_trait_impl<Binary_expr<Expr1, Expr2, Fn>>
{
	using Type = typename Fn<Expr1, Expr2>::Value;
};

template<class Expr, typename Scalar, class Fn>
struct Value_trait_impl<Scalar_expr<Expr, Scalar, Fn>>
{
	using Type = typename Fn::Value;
};

template<class Random_distribution, class Random_generator>
struct Value_trait_impl<Random_matrix<Random_distribution, Random_generator>>
{
	using Type = typename Random_distribution::result_type;
};
}
