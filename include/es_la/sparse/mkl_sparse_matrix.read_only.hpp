#pragma once
#include <es_la/sparse/forward.hpp>
#include <es_la/sparse/helpers.hpp>
#include <es_la/tags.hpp>
#include <es_la/type_traits.hpp>

#include <mkl_spblas.h>

#include <cassert>
#include <utility>

namespace es_la
{
template<class Matrix_tag>
class Mkl_sparse_matrix<Matrix_tag, Read_only>
{
public:
	using Index = typename Matrix_tag::Index;
	using Value = typename Matrix_tag::Value;

	static_assert(sizeof(Index) == sizeof(MKL_INT));
	static_assert(internal::is_real_or_complex_float_or_double<Value>);

public:
	Mkl_sparse_matrix(const Mkl_sparse_matrix&) = delete;
	Mkl_sparse_matrix& operator=(const Mkl_sparse_matrix&) = delete;

	Mkl_sparse_matrix(Mkl_sparse_matrix&& other)
	{
		std::swap(handle_, other.handle_);
	}

	Mkl_sparse_matrix& operator=(Mkl_sparse_matrix&& other)
	{
		std::swap(handle_, other.handle_);
		return *this;
	}

	~Mkl_sparse_matrix()
	{
		if (handle_ != nullptr)
		{
			[[maybe_unused]] const auto status = ::mkl_sparse_destroy(handle_);
			assert(status == ::SPARSE_STATUS_SUCCESS);
		}
	}

	::sparse_matrix_t handle()
	{
		return handle_;
	}

protected:
	Mkl_sparse_matrix() = default;

protected:
	::sparse_matrix_t handle_ = nullptr;
};
} // namespace es_la
