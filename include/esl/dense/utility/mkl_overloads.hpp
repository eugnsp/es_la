#pragma once
#include <esl/dense/tags.hpp>
#include <esl/dense/type_traits.hpp>
#include <esl/dense/utility/mkl_helpers.hpp>

#include <mkl_cblas.h>

#include <complex>
#include <cstddef>

namespace esl::internal
{
//////////////////////////////////////////////////////////////////////
//> BLAS level 1

#define ES_LA_MKL_AXPY(T) void mkl_axpy(std::size_t n, T a, const T* x, std::size_t inc_x, T* y, std::size_t inc_y);

ES_LA_MKL_AXPY(float)
ES_LA_MKL_AXPY(double)
ES_LA_MKL_AXPY(std::complex<float>)
ES_LA_MKL_AXPY(std::complex<double>)

///////////////////////////////////////////////////////////////////////

#define ES_LA_MKL_DOT(T) T mkl_dot(std::size_t n, const T* x, std::size_t inc_x, const T* y, std::size_t inc_y);

ES_LA_MKL_DOT(float)
ES_LA_MKL_DOT(double)

///////////////////////////////////////////////////////////////////////

#define ES_LA_MKL_NRM2(T) Remove_complex<T> mkl_nrm2(std::size_t n, const T* data, std::size_t inc);

ES_LA_MKL_NRM2(float)
ES_LA_MKL_NRM2(double)
ES_LA_MKL_NRM2(std::complex<float>)
ES_LA_MKL_NRM2(std::complex<double>)

//////////////////////////////////////////////////////////////////////
//> BLAS levels 2 and 3

#define ES_LA_MKL_GEMV(T)                                                                                              \
	void mkl_gemv(CBLAS_LAYOUT, CBLAS_TRANSPOSE, std::size_t m, std::size_t n, T alpha, const T* data_a,               \
		std::size_t lead_dim_a, const T* data_x, std::size_t inc_x, T beta, T* data_y, std::size_t inc_y);             \
                                                                                                                       \
	template<class Layout_tag, class Transp_tag>                                                                       \
	void mkl_gemv(std::size_t m, std::size_t n, T alpha, const T* data_a, std::size_t lead_dim_a, const T* data_x,     \
		std::size_t inc_x, T beta, T* data_y, std::size_t inc_y)                                                       \
	{                                                                                                                  \
		constexpr auto layout = layout_as_mkl_enum(Layout_tag{});                                                      \
		constexpr auto transp = transp_op_as_mkl_enum(Transp_tag{});                                                   \
		mkl_gemv(layout, transp, m, n, alpha, data_a, lead_dim_a, data_x, inc_x, beta, data_y, inc_y);                 \
	}

ES_LA_MKL_GEMV(float)
ES_LA_MKL_GEMV(double)
ES_LA_MKL_GEMV(std::complex<float>)
ES_LA_MKL_GEMV(std::complex<double>)

//////////////////////////////////////////////////////////////////////

#define ES_LA_MKL_GEMM(T)                                                                                              \
	void mkl_gemm(CBLAS_LAYOUT, CBLAS_TRANSPOSE transp_a, CBLAS_TRANSPOSE transp_b, std::size_t m, std::size_t n,      \
		std::size_t k, T alpha, const T* data_a, std::size_t lead_dim_a, const T* data_b, std::size_t lead_dim_b,      \
		T beta, T* data_c, std::size_t lead_dim_c);                                                                    \
                                                                                                                       \
	template<class Layout_tag, class Transp_a_tag, class Transp_b_tag>                                                 \
	void mkl_gemm(std::size_t m, std::size_t n, std::size_t k, T alpha, const T* data_a, std::size_t lead_dim_a,       \
		const T* data_b, std::size_t lead_dim_b, T beta, T* data_c, std::size_t lead_dim_c)                            \
	{                                                                                                                  \
		constexpr auto layout = layout_as_mkl_enum(Layout_tag{});                                                      \
		constexpr auto transp_a = transp_op_as_mkl_enum(Transp_a_tag{});                                               \
		constexpr auto transp_b = transp_op_as_mkl_enum(Transp_b_tag{});                                               \
		mkl_gemm(layout, transp_a, transp_b, m, n, k, alpha, data_a, lead_dim_a, data_b, lead_dim_b, beta, data_c,     \
			lead_dim_c);                                                                                               \
	}

ES_LA_MKL_GEMM(float)
ES_LA_MKL_GEMM(double)
ES_LA_MKL_GEMM(std::complex<float>)
ES_LA_MKL_GEMM(std::complex<double>)

///////////////////////////////////////////////////////////////////////
//> BLAS-like extensions

#define ES_LA_MKL_OMATCOPY(T)                                                                                          \
	void mkl_omatcopy(char layout, char trans, std::size_t rows, std::size_t cols, T alpha, const T* data_a,           \
		std::size_t lead_dim_a, T* data_b, std::size_t lead_dim_b);                                                    \
                                                                                                                       \
	template<class Layout_tag, class Transp_tag>                                                                       \
	void mkl_omatcopy(std::size_t rows, std::size_t cols, T alpha, const T* data_a, std::size_t lead_dim_a, T* data_b, \
		std::size_t lead_dim_b)                                                                                        \
	{                                                                                                                  \
		constexpr auto layout = layout_as_mkl_char(Layout_tag{});                                                      \
		constexpr auto trans = transp_op_as_mkl_char(Transp_tag{});                                                    \
		mkl_omatcopy(layout, trans, rows, cols, alpha, data_a, lead_dim_a, data_b, lead_dim_b);                        \
	}

ES_LA_MKL_OMATCOPY(float)
ES_LA_MKL_OMATCOPY(double)
ES_LA_MKL_OMATCOPY(std::complex<float>)
ES_LA_MKL_OMATCOPY(std::complex<double>)

///////////////////////////////////////////////////////////////////////
//> LAPACK

#define ES_LA_MKL_LAPACK_SYTRD(T)                                                                                      \
	void mkl_lapack_sytrd(                                                                                             \
		int layout, char up_lo, std::size_t n, T* data_a, std::size_t lead_dim_a, T* data_d, T* data_e, T* data_tau);  \
                                                                                                                       \
	template<class Layout_tag, class Symmetry_tag = Symmetric_upper>                                                   \
	void mkl_lapack_sytrd(std::size_t n, T* data_a, std::size_t lead_dim_a, T* data_d, T* data_e, T* data_tau)         \
	{                                                                                                                  \
		constexpr auto layout = layout_as_mkl_lapack(Layout_tag{});                                                    \
		constexpr auto symm = symmetry_as_mkl_char(Symmetry_tag{});                                                    \
		mkl_lapack_sytrd(layout, symm, n, data_a, lead_dim_a, data_d, data_e, data_tau);                               \
	}

ES_LA_MKL_LAPACK_SYTRD(float)
ES_LA_MKL_LAPACK_SYTRD(double)

///////////////////////////////////////////////////////////////////////

#define ES_LA_MKL_LAPACK_STERF(T) void mkl_lapack_sterf(std::size_t n, T* data_d, T* data_e);

ES_LA_MKL_LAPACK_STERF(float)
ES_LA_MKL_LAPACK_STERF(double)

} // namespace esl::internal
