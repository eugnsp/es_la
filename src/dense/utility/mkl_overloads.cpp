#include <es_la/core/type_traits.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <mkl_cblas.h>
#include <mkl_trans.h>
#include <mkl_types.h>

#include <complex>
#include <cstddef>
#include <cstring>

namespace es_la::internal
{
#define ES_LA_IMPL_MKL_BLAS_DOT(fn, T)                                                                                 \
	T mkl_blas_dot(std::size_t n, const T* x, std::size_t inc_x, const T* y, std::size_t inc_y)                        \
	{                                                                                                                  \
		return ::fn(static_cast<MKL_INT>(n), x, static_cast<MKL_INT>(inc_x), y, static_cast<MKL_INT>(inc_y));          \
	}

ES_LA_IMPL_MKL_BLAS_DOT(cblas_sdot, float)
ES_LA_IMPL_MKL_BLAS_DOT(cblas_ddot, double)

///////////////////////////////////////////////////////////////////////

#define ES_LA_IMPL_MKL_BLAS_NRM2(fn, T)                                                                                \
	Remove_complex<T> mkl_blas_nrm2(std::size_t n, const T* data, std::size_t inc)                                     \
	{                                                                                                                  \
		return ::fn(static_cast<MKL_INT>(n), data, static_cast<MKL_INT>(inc));                                         \
	}

ES_LA_IMPL_MKL_BLAS_NRM2(cblas_snrm2, float)
ES_LA_IMPL_MKL_BLAS_NRM2(cblas_dnrm2, double)
ES_LA_IMPL_MKL_BLAS_NRM2(cblas_scnrm2, std::complex<float>)
ES_LA_IMPL_MKL_BLAS_NRM2(cblas_dznrm2, std::complex<double>)

//////////////////////////////////////////////////////////////////////

#define ES_LA_IMPL_MKL_OMATCOPY(fn, T)                                                                                 \
	void mkl_omatcopy(char layout, char trans, std::size_t rows, std::size_t cols, T alpha, const T* data_a,           \
		std::size_t l_dim_a, T* data_b, std::size_t l_dim_b)                                                           \
	{                                                                                                                  \
		Mkl_type<T> alpha_m;                                                                                           \
		std::memcpy(&alpha_m, &alpha, sizeof(T));                                                                      \
		::fn(layout, trans, rows, cols, alpha_m, reinterpret_cast<const Mkl_type<T>*>(data_a), l_dim_a,                \
			reinterpret_cast<Mkl_type<T>*>(data_b), l_dim_b);                                                          \
	}

ES_LA_IMPL_MKL_OMATCOPY(mkl_somatcopy, float)
ES_LA_IMPL_MKL_OMATCOPY(mkl_domatcopy, double)
ES_LA_IMPL_MKL_OMATCOPY(mkl_comatcopy, std::complex<float>)
ES_LA_IMPL_MKL_OMATCOPY(mkl_zomatcopy, std::complex<double>)
} // namespace es_la::internal
