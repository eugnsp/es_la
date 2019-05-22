#pragma once
#include <es_la/core/type_traits/expr_storage.hpp>
#include <es_la/sparse/forward.hpp>

#include <type_traits>

namespace es_la::internal
{
template<typename Value, class Symmetry, typename Index>
struct Store_expr_as_reference_trait<Csr_matrix<Value, Symmetry, Index>> : std::true_type
{};

template<class Matrix>
struct Store_expr_as_reference_trait<Mkl_sparse_matrix<Matrix>> : std::true_type
{};
} // namespace es_la::internal
