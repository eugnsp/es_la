#pragma once
#include <es_la/dense/expression.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility/ct_extent.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Expr, class Mkl_tag, typename = void>
class Sum_impl
{
public:
	auto operator()(const Expr& expr) const
	{
		Value_type<Expr> sum{};

		for (std::size_t i = 0; i < expr.size(); ++i)
			sum += expr[i];

		return sum;
	}
};
} // namespace internal

template<class Expr, class Category>
auto sum(const Dense<Expr, Category>& expr)
{
	static_assert(internal::is_vector<Expr>);

	return internal::Sum_impl<Expr, internal::Mkl_expr_decay<Expr>>{}(expr.self());
}
} // namespace es_la
