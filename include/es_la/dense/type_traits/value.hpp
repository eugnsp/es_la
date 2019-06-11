#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <cstddef>
#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Expr>
struct Value_trait_impl;

template<class Expr>
struct Value_trait : internal::Value_trait_impl<es_util::Remove_cv_ref<Expr>>
{};

template<typename Value, std::size_t rows, std::size_t cols, class Layout>
struct Value_trait_impl<Matrix<Value, rows, cols, Layout>>
{
	using Type = Value;
};

template<class Expr, class Rows, class Cols, class Category>
struct Value_trait_impl<View<Expr, Rows, Cols, Category>> : Value_trait<Expr>
{};

template<class Expr, class Category>
struct Value_trait_impl<Transposed_view<Expr, Category>> : Value_trait<Expr>
{};

template<class Expr, class Category>
struct Value_trait_impl<Diag_view<Expr, Category>> : Value_trait<Expr>
{};

template<class Expr1, class Expr2, template<class, class> class Fn>
struct Value_trait_impl<Binary_expr<Expr1, Expr2, Fn>>
{
	using Type = typename Fn<Expr1, Expr2>::Value;
};

template<class Expr, typename Scalar, template<class, typename> class Fn>
struct Value_trait_impl<Scalar_expr<Expr, Scalar, Fn>>
{
	using Type = typename Fn<Expr, Scalar>::Value;
};

template<class Random_distribution, class Random_generator>
struct Value_trait_impl<Random_matrix<Random_distribution, Random_generator>>
{
	using Type = typename Random_distribution::result_type;
};
} // namespace internal

template<class Expr>
using Value_type = typename internal::Value_trait<Expr>::Type;

namespace internal
{
template<class Expr1, class Expr2>
inline constexpr bool have_same_value_type = std::is_same_v<Value_type<Expr1>, Value_type<Expr2>>;
}
} // namespace es_la
