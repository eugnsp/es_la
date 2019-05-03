#pragma once
#include <es_la/tags.hpp>

#include <mkl_types.h>

namespace es_la
{
template<class Symmetry_tag = Not_symmetric, typename Index = MKL_UINT>
class Csr_pattern;

template<typename Value, class Symmetry_tag = Not_symmetric, typename Index = MKL_UINT>
class Csr_matrix;

template<class Matrix_tag, class Access_tag>
class Mkl_sparse_matrix;
}
