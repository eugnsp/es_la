#pragma once
#include <es_la/core/tags.hpp>
#include <es_la/core/type_traits/ct_extent.hpp>
#include <es_la/sparse/forward.hpp>

#include <es_util/type_traits.hpp>

namespace es_la
{
template<class Matrix>
struct Ct_rows_trait<Mkl_sparse_matrix<Matrix>> : es_util::Std_integral_constant<dynamic>
{};

template<class Matrix>
struct Ct_cols_trait<Mkl_sparse_matrix<Matrix>> : es_util::Std_integral_constant<dynamic>
{};
} // namespace es_la
