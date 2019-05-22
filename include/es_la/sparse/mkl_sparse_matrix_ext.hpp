#pragma once
#include <es_la/dense/type_traits.hpp>
#include <es_la/sparse/mkl_sparse_matrix.hpp>

#include <type_traits>
#include <utility>

namespace es_la
{
template<class Matrix>
class Mkl_sparse_matrix_ext : public Mkl_sparse_matrix<std::remove_reference_t<Matrix>>
{
private:
	using Base = Mkl_sparse_matrix<std::remove_reference_t<Matrix>>;

public:
	template<class Matrix_f>
	Mkl_sparse_matrix_ext(Matrix_f&& matrix) : matrix_(std::forward<Matrix_f>(matrix))
	{
		ES_LA_CALL_MKL_SPARSE(internal::mkl_sparse_create, handle_, matrix_);
	}

private:
	using Base::handle_;
	Matrix matrix_;
};

template<class Matrix>
Mkl_sparse_matrix_ext(Matrix&&) -> Mkl_sparse_matrix_ext<Matrix>;
} // namespace es_la
