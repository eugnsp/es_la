#include <esl/dense/type_traits.hpp>
#include <esl/dense/utility/mkl_overloads.hpp>

#include <mkl_cblas.h>
#include <mkl_lapacke.h>
#include <mkl_trans.h>
#include <mkl_types.h>

#include <complex>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>

namespace esl::internal
{
//////////////////////////////////////////////////////////////////////
//> BLAS level 1

#define ES_LA_IMPL_MKL_BLAS_AXPY_R(fn, T)                                                                              \
	void mkl_axpy(std::size_t n, T a, const T* data_x, std::size_t inc_x, T* data_y, std::size_t inc_y)                \
	{                                                                                                                  \
		::fn(static_cast<MKL_INT>(n), a, data_x, static_cast<MKL_INT>(inc_x), data_y, static_cast<MKL_INT>(inc_y));    \
	}

#define ES_LA_IMPL_MKL_BLAS_AXPY_C(fn, T)                                                                              \
	void mkl_axpy(std::size_t n, T a, const T* data_x, std::size_t inc_x, T* data_y, std::size_t inc_y)                \
	{                                                                                                                  \
		::fn(static_cast<MKL_INT>(n), &a, data_x, static_cast<MKL_INT>(inc_x), data_y, static_cast<MKL_INT>(inc_y));   \
	}

ES_LA_IMPL_MKL_BLAS_AXPY_R(cblas_saxpy, float)
ES_LA_IMPL_MKL_BLAS_AXPY_R(cblas_daxpy, double)
ES_LA_IMPL_MKL_BLAS_AXPY_C(cblas_caxpy, std::complex<float>)
ES_LA_IMPL_MKL_BLAS_AXPY_C(cblas_zaxpy, std::complex<double>)

///////////////////////////////////////////////////////////////////////

#define ES_LA_IMPL_MKL_BLAS_DOT(fn, T)                                                                                 \
	T mkl_dot(std::size_t n, const T* data_x, std::size_t inc_x, const T* data_y, std::size_t inc_y)                   \
	{                                                                                                                  \
		return ::fn(                                                                                                   \
			static_cast<MKL_INT>(n), data_x, static_cast<MKL_INT>(inc_x), data_y, static_cast<MKL_INT>(inc_y));        \
	}

ES_LA_IMPL_MKL_BLAS_DOT(cblas_sdot, float)
ES_LA_IMPL_MKL_BLAS_DOT(cblas_ddot, double)

///////////////////////////////////////////////////////////////////////

#define ES_LA_IMPL_MKL_BLAS_NRM2(fn, T)                                                                                \
	Remove_complex<T> mkl_nrm2(std::size_t n, const T* data, std::size_t inc)                                          \
	{                                                                                                                  \
		return ::fn(static_cast<MKL_INT>(n), data, static_cast<MKL_INT>(inc));                                         \
	}

ES_LA_IMPL_MKL_BLAS_NRM2(cblas_snrm2, float)
ES_LA_IMPL_MKL_BLAS_NRM2(cblas_dnrm2, double)
ES_LA_IMPL_MKL_BLAS_NRM2(cblas_scnrm2, std::complex<float>)
ES_LA_IMPL_MKL_BLAS_NRM2(cblas_dznrm2, std::complex<double>)

//////////////////////////////////////////////////////////////////////
//> BLAS levels 2 and 3

#define ES_LA_IMPL_MKL_GEMV_R(fn, T)                                                                                   \
	void mkl_gemv(CBLAS_LAYOUT layout, CBLAS_TRANSPOSE transp, std::size_t m, std::size_t n, T alpha, const T* data_a, \
		std::size_t lead_dim_a, const T* data_x, std::size_t inc_x, T beta, T* data_y, std::size_t inc_y)              \
	{                                                                                                                  \
		::fn(layout, transp, static_cast<MKL_INT>(m), static_cast<MKL_INT>(n), alpha, data_a, lead_dim_a, data_x,      \
			inc_x, beta, data_y, inc_y);                                                                               \
	}

#define ES_LA_IMPL_MKL_GEMV_C(fn, T)                                                                                   \
	void mkl_gemv(CBLAS_LAYOUT layout, CBLAS_TRANSPOSE transp, std::size_t m, std::size_t n, T alpha, const T* data_a, \
		std::size_t lead_dim_a, const T* data_x, std::size_t inc_x, T beta, T* data_y, std::size_t inc_y)              \
	{                                                                                                                  \
		::fn(layout, transp, static_cast<MKL_INT>(m), static_cast<MKL_INT>(n), &alpha, data_a, lead_dim_a, data_x,     \
			inc_x, &beta, data_y, inc_y);                                                                              \
	}

ES_LA_IMPL_MKL_GEMV_R(cblas_sgemv, float)
ES_LA_IMPL_MKL_GEMV_R(cblas_dgemv, double)
ES_LA_IMPL_MKL_GEMV_C(cblas_cgemv, std::complex<float>)
ES_LA_IMPL_MKL_GEMV_C(cblas_zgemv, std::complex<double>)

//////////////////////////////////////////////////////////////////////

#define ES_LA_IMPL_MKL_GEMM_R(fn, T)                                                                                   \
	void mkl_gemm(CBLAS_LAYOUT layout, CBLAS_TRANSPOSE transp_a, CBLAS_TRANSPOSE transp_b, std::size_t m,              \
		std::size_t n, std::size_t k, T alpha, const T* data_a, std::size_t lead_dim_a, const T* data_b,               \
		std::size_t lead_dim_b, T beta, T* data_c, std::size_t lead_dim_c)                                             \
	{                                                                                                                  \
		::fn(layout, transp_a, transp_b, static_cast<MKL_INT>(m), static_cast<MKL_INT>(n), static_cast<MKL_INT>(k),    \
			alpha, data_a, lead_dim_a, data_b, lead_dim_b, beta, data_c, lead_dim_c);                                  \
	}

#define ES_LA_IMPL_MKL_GEMM_C(fn, T)                                                                                   \
	void mkl_gemm(CBLAS_LAYOUT layout, CBLAS_TRANSPOSE transp_a, CBLAS_TRANSPOSE transp_b, std::size_t m,              \
		std::size_t n, std::size_t k, T alpha, const T* data_a, std::size_t lead_dim_a, const T* data_b,               \
		std::size_t lead_dim_b, T beta, T* data_c, std::size_t lead_dim_c)                                             \
	{                                                                                                                  \
		::fn(layout, transp_a, transp_b, static_cast<MKL_INT>(m), static_cast<MKL_INT>(n), static_cast<MKL_INT>(k),    \
			&alpha, data_a, lead_dim_a, data_b, lead_dim_b, &beta, data_c, lead_dim_c);                                \
	}

ES_LA_IMPL_MKL_GEMM_R(cblas_sgemm, float)
ES_LA_IMPL_MKL_GEMM_R(cblas_dgemm, double)
ES_LA_IMPL_MKL_GEMM_C(cblas_cgemm3m, std::complex<float>)
ES_LA_IMPL_MKL_GEMM_C(cblas_zgemm3m, std::complex<double>)

///////////////////////////////////////////////////////////////////////
//> BLAS-like extensions

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

//////////////////////////////////////////////////////////////////////
//> LAPACK

#define ES_LA_IMPL_MKL_LAPACK_SYTRD(fn, T)                                                                             \
	void mkl_lapack_sytrd(                                                                                             \
		int layout, char up_lo, std::size_t n, T* data_a, std::size_t lead_dim_a, T* data_d, T* data_e, T* data_tau)   \
	{                                                                                                                  \
		const auto info = ::fn(layout, up_lo, static_cast<lapack_int>(n), data_a, static_cast<lapack_int>(lead_dim_a), \
			data_d, data_e, data_tau);                                                                                 \
		if (info != 0)                                                                                                 \
			throw std::runtime_error(                                                                                  \
				"Parameter " + std::to_string(-info) + " has an illegal value in " + std::string(__FUNCTION__));       \
	}

ES_LA_IMPL_MKL_LAPACK_SYTRD(LAPACKE_ssytrd, float)
ES_LA_IMPL_MKL_LAPACK_SYTRD(LAPACKE_dsytrd, double)

///////////////////////////////////////////////////////////////////////

#define ES_LA_IMPL_MKL_LAPACK_STERF(fn, T)                                                                             \
	void mkl_lapack_sterf(std::size_t n, T* data_d, T* data_e)                                                         \
	{                                                                                                                  \
		const auto info = ::fn(static_cast<lapack_int>(n), data_d, data_e);                                            \
		if (info > 0)                                                                                                  \
			throw std::runtime_error(std::to_string(info) + " off-diagonal elements have not converged to zero in " +  \
									 std::string(__FUNCTION__));                                                       \
		else if (info < 0)                                                                                             \
			throw std::runtime_error(                                                                                  \
				"Parameter " + std::to_string(-info) + " has an illegal value in " + std::string(__FUNCTION__));       \
	}

ES_LA_IMPL_MKL_LAPACK_STERF(LAPACKE_ssterf, float)
ES_LA_IMPL_MKL_LAPACK_STERF(LAPACKE_dsterf, double)

} // namespace esl::internal
