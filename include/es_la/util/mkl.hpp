#pragma once

#ifdef ES_LA_USE_MKL
#	if ES_LA_USE_MKL
#		if !__has_include(<mkl.h>)
#			error MKL not found
#		endif
#		include <complex>
#		define MKL_Complex8 std::complex<float>
#		define MKL_Complex16 std::complex<double>
#		include <mkl.h>
#	endif
#else
#	if __has_include(<mkl.h>)
#		define ES_LA_USE_MKL 1
#		include <complex>
#		define MKL_Complex8 std::complex<float>
#		define MKL_Complex16 std::complex<double>
#		include <mkl.h>
#	else
#		define ES_LA_USE_MKL 0
#	endif
#endif

#if ES_LA_USE_MKL
namespace es_la::internal
{
enum class Mkl_blas_layout : std::underlying_type_t<::CBLAS_LAYOUT>
{
	ROW_MAJOR = ::CblasRowMajor,
	COL_MAJOR = ::CblasColMajor
};

enum class Mkl_blas_transpose : std::underlying_type_t<::CBLAS_TRANSPOSE>
{
	NO_TRANS = ::CblasNoTrans,
	TRANS = ::CblasTrans,
	CONJ_TRANS = ::CblasConjTrans
};

inline void mkl_blas_gemm(
	Mkl_blas_layout layout,
	Mkl_blas_transpose trans_a,
	Mkl_blas_transpose trans_b,
	MKL_INT m,
	MKL_INT n,
	MKL_INT k,
	float alpha,
	const float* a,
	MKL_INT lead_dim_a,
	const float* b,
	MKL_INT lead_dim_b,
	float beta,
	float* c,
	const MKL_INT lead_dim_c)
{
	::cblas_sgemm(
		static_cast<::CBLAS_LAYOUT>(layout), static_cast<::CBLAS_TRANSPOSE>(trans_a),
		static_cast<::CBLAS_TRANSPOSE>(trans_b), m, n, k, alpha, a, lead_dim_a, b, lead_dim_b, beta,
		c, lead_dim_c);
}

inline void mkl_blas_gemm(
	Mkl_blas_layout layout,
	Mkl_blas_transpose trans_a,
	Mkl_blas_transpose trans_b,
	MKL_INT m,
	MKL_INT n,
	MKL_INT k,
	double alpha,
	const double* a,
	MKL_INT lead_dim_a,
	const double* b,
	MKL_INT lead_dim_b,
	double beta,
	double* c,
	const MKL_INT lead_dim_c)
{
	::cblas_dgemm(
		static_cast<::CBLAS_LAYOUT>(layout), static_cast<::CBLAS_TRANSPOSE>(trans_a),
		static_cast<::CBLAS_TRANSPOSE>(trans_b), m, n, k, alpha, a, lead_dim_a, b, lead_dim_b, beta,
		c, lead_dim_c);
}

inline void mkl_blas_gemm(
	Mkl_blas_layout layout,
	Mkl_blas_transpose trans_a,
	Mkl_blas_transpose trans_b,
	MKL_INT m,
	MKL_INT n,
	MKL_INT k,
	std::complex<float> alpha,
	const std::complex<float>* a,
	MKL_INT lead_dim_a,
	const std::complex<float>* b,
	MKL_INT lead_dim_b,
	std::complex<float> beta,
	std::complex<float>* c,
	const MKL_INT lead_dim_c)
{
	::cblas_cgemm(
		static_cast<::CBLAS_LAYOUT>(layout), static_cast<::CBLAS_TRANSPOSE>(trans_a),
		static_cast<::CBLAS_TRANSPOSE>(trans_b), m, n, k, &alpha, a, lead_dim_a, b, lead_dim_b,
		&beta, c, lead_dim_c);
}

inline void mkl_blas_gemm(
	Mkl_blas_layout layout,
	Mkl_blas_transpose trans_a,
	Mkl_blas_transpose trans_b,
	MKL_INT m,
	MKL_INT n,
	MKL_INT k,
	std::complex<double> alpha,
	const std::complex<double>* a,
	MKL_INT lead_dim_a,
	const std::complex<double>* b,
	MKL_INT lead_dim_b,
	std::complex<double> beta,
	std::complex<double>* c,
	const MKL_INT lead_dim_c)
{
	::cblas_zgemm(
		static_cast<::CBLAS_LAYOUT>(layout), static_cast<::CBLAS_TRANSPOSE>(trans_a),
		static_cast<::CBLAS_TRANSPOSE>(trans_b), m, n, k, &alpha, a, lead_dim_a, b, lead_dim_b,
		&beta, c, lead_dim_c);
}
} // namespace la::internal
#endif
