#pragma once
#include <es_la/dense/functor/type_traits/fn_expr_trait.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits/layout.hpp>
#include <es_la/dense/type_traits/numeric.hpp>
#include <es_la/sparse/functor/fn_expr_mkl_sparse_mat_mul.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr1, class Expr2, typename Value>
struct Fn_expr_assign_trait<Expr1, Expr2, Lvalue_block_t<Value>,
	Binary_expr_t<Mkl_sparse_matrix_t<Value>, Lvalue_block_t<Value>, Mul_t>, std::enable_if_t<is_fd_or_cfd<Value>>>
{
	using Type = Fn_expr_mkl_sparse_mat_mul;
};
} // namespace es_la::internal
