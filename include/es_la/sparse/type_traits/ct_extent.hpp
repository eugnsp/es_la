#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>
#include <es_la/sparse/forward.hpp>

namespace es_la
{
template<class Matrix>
struct Ct_rows_trait<Mkl_sparse_matrix<Matrix>> : es_util::Std_integral_constant<dynamic>
{};

template<class Matrix>
struct Ct_cols_trait<Mkl_sparse_matrix<Matrix>> : es_util::Std_integral_constant<dynamic>
{};
} // namespace es_la
