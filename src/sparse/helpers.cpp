#include <es_la/sparse/helpers.hpp>

#include <mkl_spblas.h>

namespace es_la::internal
{
::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t& handle, MKL_UINT rows, MKL_UINT cols,
	MKL_INT* rows_start, MKL_INT* rows_end, MKL_INT* col_indx, float* values)
{
	return mkl_sparse_s_create_csr(&handle, ::sparse_index_base_t::SPARSE_INDEX_BASE_ZERO,
		static_cast<MKL_INT>(rows), static_cast<MKL_INT>(cols), rows_start, rows_end, col_indx,
		values);
}

::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t& handle, MKL_UINT rows, MKL_UINT cols,
	MKL_INT* rows_start, MKL_INT* rows_end, MKL_INT* col_indx, double* values)
{
	return mkl_sparse_d_create_csr(&handle, ::sparse_index_base_t::SPARSE_INDEX_BASE_ZERO,
		static_cast<MKL_INT>(rows), static_cast<MKL_INT>(cols), rows_start, rows_end, col_indx,
		values);
}

::sparse_status_t mkl_sparse_set_value(
	::sparse_matrix_t handle, MKL_UINT row, MKL_UINT col, float value)
{
	return ::mkl_sparse_s_set_value(
		handle, static_cast<MKL_INT>(row), static_cast<MKL_INT>(col), value);
}

::sparse_status_t mkl_sparse_set_value(
	::sparse_matrix_t handle, MKL_UINT row, MKL_UINT col, double value)
{
	return ::mkl_sparse_d_set_value(
		handle, static_cast<MKL_INT>(row), static_cast<MKL_INT>(col), value);
}

std::string mkl_sparse_status_string(::sparse_status_t status)
{
	switch (status)
	{
	case ::sparse_status_t::SPARSE_STATUS_ALLOC_FAILED:
		return "Internal memory allocation failed";

	case ::sparse_status_t::SPARSE_STATUS_EXECUTION_FAILED:
		return "Execution failed";

	case ::sparse_status_t::SPARSE_STATUS_INTERNAL_ERROR:
		return "An error in algorithm implementation occurred";

	case ::sparse_status_t::SPARSE_STATUS_INVALID_VALUE:
		return "The input parameters contain an invalid value";

	case ::sparse_status_t::SPARSE_STATUS_NOT_INITIALIZED:
		return "The routine encountered an empty handle or matrix array";

	case ::sparse_status_t::SPARSE_STATUS_NOT_SUPPORTED:
		return "The requested operation is not supported";

	case ::sparse_status_t::SPARSE_STATUS_SUCCESS:
		return "The operation was successful";
	}

	return "Unknown error";
}
} // namespace es_la::internal
