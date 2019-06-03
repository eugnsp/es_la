#pragma once
#include <es_la/core/type_traits.hpp>

#include <complex>
#include <cstddef>

namespace es_la::internal
{
#define ES_LA_MKL_BLAS_DOT(T)                                                                                          \
	T mkl_blas_dot(std::size_t n, const T* x, std::size_t inc_x, const T* y, std::size_t inc_y);

ES_LA_MKL_BLAS_DOT(float)
ES_LA_MKL_BLAS_DOT(double)

///////////////////////////////////////////////////////////////////////

#define ES_LA_MKL_BLAS_NRM2(T) Remove_complex<T> mkl_blas_nrm2(std::size_t n, const T* data, std::size_t inc);

ES_LA_MKL_BLAS_NRM2(float)
ES_LA_MKL_BLAS_NRM2(double)
ES_LA_MKL_BLAS_NRM2(std::complex<float>)
ES_LA_MKL_BLAS_NRM2(std::complex<double>)

///////////////////////////////////////////////////////////////////////

#define ES_LA_MKL_OMATCOPY(T)                                                                                          \
	void mkl_omatcopy(char layout, char trans, std::size_t rows, std::size_t cols, T alpha, const T* data_a,           \
		std::size_t l_dim_a, T* data_b, std::size_t l_dim_b);

ES_LA_MKL_OMATCOPY(float)
ES_LA_MKL_OMATCOPY(double)
ES_LA_MKL_OMATCOPY(std::complex<float>)
ES_LA_MKL_OMATCOPY(std::complex<double>)
} // namespace es_la::internal
