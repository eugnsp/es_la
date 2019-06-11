#pragma once
#include <es_la/dense/type_traits/mkl_decay.hpp>
#include <es_la/sparse/tags.hpp>
#include <es_la/sparse/forward.hpp>

namespace es_la::internal
{
template<class Matrix>
struct Mkl_expr_decay_trait_impl<Mkl_sparse_matrix<Matrix>>
{
	using Type = Mkl_sparse_matrix_t<typename Matrix::Value>;
};
}
