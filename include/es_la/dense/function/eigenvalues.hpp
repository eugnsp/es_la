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
template<class Expr>
void eigenvalues(Dense<Expr, Lvalue>& expr, Vector_x<Value_type<Expr>>& eigenvalues)
{
	assert(expr.rows() == expr.cols());

	eigenvalues.resize(expr.rows());
	es_la::Vector_x<Value_type<Expr>> tau(expr.rows());
	es_la::Vector_x<Value_type<Expr>> off_diag(expr.rows() - 1);

	// TO DO

	LAPACKE_dsytrd(LAPACK_COL_MAJOR, 'U', expr.rows(), expr.self().data(), expr.self().lead_dim(), eigenvalues.data(), off_diag.data(), tau.data());
	LAPACKE_dsterf(expr.rows(), eigenvalues.data(), off_diag.data());
}
} // namespace es_la
