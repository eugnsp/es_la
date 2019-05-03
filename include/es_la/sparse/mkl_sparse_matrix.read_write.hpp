#pragma once
#include <es_la/sparse/forward.hpp>
#include <es_la/sparse/helpers.hpp>
#include <es_la/sparse/mkl_sparse_matrix.read_only.hpp>
#include <es_la/sparse/type_traits.hpp>
#include <es_la/tags.hpp>

#include <mkl_spblas.h>

#include <stdexcept>

namespace es_la
{
template<class Matrix_tag>
class Mkl_sparse_matrix<Matrix_tag, Read_write> : public Mkl_sparse_matrix<Matrix_tag, Read_only>
{
private:
	using Base = Mkl_sparse_matrix<Matrix_tag, Read_only>;

public:
	using Index = typename Base::Index;
	using Value = typename Base::Value;

public:
	void set(const Index row, const Index col, const Value value)
	{
		const auto status = internal::mkl_sparse_set_value(handle_, row, col, value);
		if (status != ::sparse_status_t::SPARSE_STATUS_SUCCESS)
			throw std::runtime_error(internal::mkl_sparse_status_string(status));
	}

	void order()
	{
		static_assert(internal::is_csr_matrix<Matrix_tag>);

		const auto status = ::mkl_sparse_order(handle_);
		if (status != ::sparse_status_t::SPARSE_STATUS_SUCCESS)
			throw std::runtime_error(internal::mkl_sparse_status_string(status));
	}

protected:
	using Base::handle_;
};
} // namespace es_la
