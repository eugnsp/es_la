#pragma once
#include <es_la/sparse/csr_matrix.hpp>

#include <mkl_types.h>
#include <mkl_spblas.h>

#include <string>

namespace es_la::internal
{
::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t&, MKL_UINT rows, MKL_UINT cols,
	MKL_INT* rows_start, MKL_INT* rows_end, MKL_INT* col_indx, float*);

::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t&, MKL_UINT rows, MKL_UINT cols,
	MKL_INT* rows_start, MKL_INT* rows_end, MKL_INT* col_indx, double*);

::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t&, MKL_UINT rows, MKL_UINT cols,
	MKL_INT* rows_start, MKL_INT* rows_end, MKL_INT* col_indx, MKL_Complex8*);

::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t&, MKL_UINT rows, MKL_UINT cols,
	MKL_INT* rows_start, MKL_INT* rows_end, MKL_INT* col_indx, MKL_Complex16*);

::sparse_status_t mkl_sparse_set_value(::sparse_matrix_t, MKL_UINT row, MKL_UINT col, float);
::sparse_status_t mkl_sparse_set_value(::sparse_matrix_t, MKL_UINT row, MKL_UINT col, double);
::sparse_status_t mkl_sparse_set_value(::sparse_matrix_t, MKL_UINT row, MKL_UINT col, MKL_Complex8);
::sparse_status_t mkl_sparse_set_value(::sparse_matrix_t, MKL_UINT row, MKL_UINT col, MKL_Complex16);

std::string mkl_sparse_status_string(::sparse_status_t);

template<typename Value, class Symmetry_tag, typename Index>
::sparse_status_t mkl_sparse_create(
	::sparse_matrix_t& handle, const Csr_matrix<Value, Symmetry_tag, Index>& matrix)
{
	static_assert(sizeof(Index) == sizeof(MKL_INT));

	const auto row_indices =
		reinterpret_cast<MKL_INT*>(const_cast<Index*>(matrix.row_indices()));
	const auto col_indices =
		reinterpret_cast<MKL_INT*>(const_cast<Index*>(matrix.col_indices()));
	const auto values = const_cast<Value*>(matrix.values());

	return mkl_sparse_create_csr(
		handle, matrix.rows(), matrix.cols(), row_indices, row_indices + 1, col_indices, values);
}
} // namespace es_la::internal
