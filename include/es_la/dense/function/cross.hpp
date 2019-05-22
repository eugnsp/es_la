#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility.hpp>

#include <es_util/numeric/det.hpp>

namespace es_la
{
template<class Expr1, class Value_category1, class Expr2, class Value_category2>
auto cross(const Dense<Expr1, Value_category1>& expr1, const Dense<Expr2, Value_category2>& expr2)
{
	static_assert(internal::is_vector_expr<Expr1> && internal::is_vector_expr<Expr2> &&
				  internal::is_ct_extent_static_and_eq(ct_rows_value<Expr1>, 2) &&
				  internal::is_ct_extent_static_and_eq(ct_rows_value<Expr2>, 2),
		"Expressions should be vectors of size 2");

	return es_util::det(expr1[0], expr1[1], expr2[0], expr2[1]);
}
} // namespace es_la
