#pragma once
#include <es_la/sparse/csr_matrix.hpp>
#include <es_la/sparse/helpers.hpp>
#include <es_la/sparse/type_traits.hpp>

#include <mkl_spblas.h>

#include <cassert>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace es_la
{
template<class Value_or_matrix>
class Sparse_matrix
{
	static_assert(
		std::is_same_v<Value_or_matrix, float> || std::is_same_v<Value_or_matrix, double>);

public:
	using Value = Value_or_matrix;
	using Index = MKL_UINT;

public:
	Sparse_matrix(const Sparse_matrix&) = delete;
	Sparse_matrix& operator=(const Sparse_matrix&) = delete;

	Sparse_matrix(Sparse_matrix&& other)
	{
		std::swap(handle_, other.handle_);
	}

	Sparse_matrix& operator=(Sparse_matrix&& other)
	{
		std::swap(handle_, other.handle_);
		return *this;
	}

	~Sparse_matrix()
	{
		destroy();
	}

	::sparse_matrix_t handle()
	{
		return handle_;
	}

	void set(Index row, Index col, Value value)
	{
		::sparse_status_t status;
		if constexpr (std::is_same_v<Value, float>)
			status = ::mkl_sparse_s_set_value(&handle_, row, col, value);
		else if constexpr (std::is_same_v<Value, double>)
			status = ::mkl_sparse_d_set_value(&handle_, row, col, value);

		if (status != ::sparse_status_t::SPARSE_STATUS_SUCCESS)
			throw std::runtime_error(internal::mkl_sparse_status_string(status));
	}

protected:
	Sparse_matrix() = default;

	void destroy()
	{
		if (handle_ != nullptr)
		{
			[[maybe_unused]] const auto status = ::mkl_sparse_destroy(handle_);
			assert(status == ::SPARSE_STATUS_SUCCESS);
			handle_ = nullptr;
		}
	}

protected:
	::sparse_matrix_t handle_ = nullptr;
};

template<typename Value, class Symmetry_tag, typename Index_>
class Sparse_matrix<Csr_matrix<Value, Symmetry_tag, Index_>> : public Sparse_matrix<Value>
{
private:
	using Base = Sparse_matrix<Value>;
	using Matrix = Csr_matrix<Value, Symmetry_tag, Index_>;

public:
	using typename Base::Index;

public:
	Sparse_matrix(Matrix matrix) : matrix_(std::move(matrix))
	{
		static_assert(sizeof(Index_) == sizeof(Index));

		const auto rows = static_cast<MKL_INT>(matrix_.rows());
		const auto cols = static_cast<MKL_INT>(matrix_.rows());
		const auto row_indices =
			reinterpret_cast<MKL_INT*>(const_cast<Index*>(matrix_.row_indices()));
		const auto col_indices =
			reinterpret_cast<MKL_INT*>(const_cast<Index*>(matrix_.col_indices()));
		const auto values = const_cast<Value*>(matrix_.values());

		::sparse_status_t status;
		if constexpr (std::is_same_v<Value, float>)
			status =
				::mkl_sparse_s_create_csr(&handle_, ::sparse_index_base_t::SPARSE_INDEX_BASE_ZERO,
					rows, cols, row_indices, row_indices + 1, col_indices, values);
		else if constexpr (std::is_same_v<Value, double>)
			status =
				::mkl_sparse_d_create_csr(&handle_, ::sparse_index_base_t::SPARSE_INDEX_BASE_ZERO,
					rows, cols, row_indices, row_indices + 1, col_indices, values);

		if (status != ::sparse_status_t::SPARSE_STATUS_SUCCESS)
			throw std::runtime_error(internal::mkl_sparse_status_string(status));
	}

	Matrix release()
	{
		this->destroy();
		return std::move(matrix_);
	}

private:
	using Base::handle_;
	Matrix matrix_;
};

template<typename Value, class Symmetry_tag, typename Index>
Sparse_matrix(Csr_matrix<Value, Symmetry_tag, Index>)
	-> Sparse_matrix<Csr_matrix<Value, Symmetry_tag, Index>>;
} // namespace es_la
