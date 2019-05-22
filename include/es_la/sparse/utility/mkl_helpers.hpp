#pragma once
#include <es_la/dense/type_traits.hpp>
#include <es_la/sparse/csr_matrix.hpp>
#include <es_la/sparse/utility/mkl_overloads.hpp>
#include <es_la/sparse/type_traits.hpp>

#include <mkl_spblas.h>
#include <mkl_types.h>

#include <string>

namespace es_la::internal
{
template<class Matrix>
constexpr ::sparse_layout_t mkl_sparse_dense_layout()
{
	return is_col_major<Matrix> ? ::sparse_layout_t::SPARSE_LAYOUT_COLUMN_MAJOR
								: ::sparse_layout_t::SPARSE_LAYOUT_ROW_MAJOR;
}

template<class Matrix>
::matrix_descr mkl_matrix_descr()
{
	::matrix_descr descr;
	descr.diag = SPARSE_DIAG_NON_UNIT;
	if constexpr (is_symmetric_upper<Matrix>)
	{
		descr.type = SPARSE_MATRIX_TYPE_SYMMETRIC;
		descr.mode = SPARSE_FILL_MODE_UPPER;
	}
	else if constexpr (is_symmetric_lower<Matrix>)
	{
		descr.type = SPARSE_MATRIX_TYPE_SYMMETRIC;
		descr.mode = SPARSE_FILL_MODE_LOWER;
	}
	else
		descr.type = SPARSE_MATRIX_TYPE_GENERAL;

	return descr;
}

template<typename Value, class Symmetry, typename Index>
::sparse_status_t mkl_sparse_create(::sparse_matrix_t& handle, const Csr_matrix<Value, Symmetry, Index>& matrix)
{
	static_assert(sizeof(Index) == sizeof(MKL_UINT));

	const auto row_indices = reinterpret_cast<MKL_UINT*>(const_cast<Index*>(matrix.row_indices()));
	const auto col_indices = reinterpret_cast<MKL_UINT*>(const_cast<Index*>(matrix.col_indices()));
	const auto values = const_cast<Value*>(matrix.values());

	return mkl_sparse_create_csr(
		handle, matrix.rows(), matrix.cols(), row_indices, row_indices + 1, col_indices, values);
}

std::string mkl_sparse_status_string(::sparse_status_t);
} // namespace es_la::internal
