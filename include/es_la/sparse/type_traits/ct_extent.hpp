#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>
#include <es_la/sparse/forward.hpp>

namespace es_la::internal
{
template<class Matrix>
struct Ct_rows_trait_impl<Mkl_sparse_matrix<Matrix>> : es_util::Std_integral_constant<dynamic>
{};

template<class Matrix>
struct Ct_cols_trait_impl<Mkl_sparse_matrix<Matrix>> : es_util::Std_integral_constant<dynamic>
{};
} // namespace es_la
