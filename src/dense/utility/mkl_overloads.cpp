#include <es_la/core/type_traits.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <mkl_cblas.h>
#include <mkl_types.h>

#include <complex>
#include <cstddef>

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
} // namespace es_la::internal
