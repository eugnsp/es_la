#pragma once
#include <es_la/core/type_traits/value.hpp>
#include <es_la/sparse/forward.hpp>

namespace es_la::internal
{
template<typename Value, class Symmetry, typename Index>
struct Value_trait_impl<Csr_matrix<Value, Symmetry, Index>>
{
	using Type = Value;
};

template<typename Matrix>
struct Value_trait_impl<Mkl_sparse_matrix<Matrix>> : Value_trait<Matrix>
{};
} // namespace es_la::internal
