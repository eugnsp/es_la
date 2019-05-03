#pragma once
#include <es_la/sparse/helpers.hpp>
#include <es_la/type_traits.hpp>

#include <es_util/type_traits.hpp>

#include <mkl_spblas.h>

#include <stdexcept>
#include <utility>

namespace es_la
{
template<class Matrix>
class Mkl_sparse_matrix_ext :
	public Mkl_sparse_matrix<es_util::Remove_cvref<Matrix>,
		internal::Access_tag_by_constness<Matrix>>
{
private:
	using Base =
		Mkl_sparse_matrix<es_util::Remove_cvref<Matrix>, internal::Access_tag_by_constness<Matrix>>;

public:
	template<class M>
	Mkl_sparse_matrix_ext(M&& matrix) : matrix_(std::forward<M>(matrix))
	{
		const auto status = internal::mkl_sparse_create(handle_, matrix_);
		if (status != ::sparse_status_t::SPARSE_STATUS_SUCCESS)
			throw std::runtime_error(internal::mkl_sparse_status_string(status));
	}

private:
	using Base::handle_;
	Matrix matrix_;
};

template<class Matrix>
Mkl_sparse_matrix_ext(Matrix&&) -> Mkl_sparse_matrix_ext<Matrix>;
} // namespace es_la
