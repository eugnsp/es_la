#pragma once
#include <es_la/dense/tags.hpp>

#include <mkl_cblas.h>

namespace es_la::internal
{
//////////////////////////////////////////////////////////////////////
//* Matrix memory layouts */

inline constexpr ::CBLAS_LAYOUT layout_as_mkl_enum(Col_major)
{
	return ::CBLAS_LAYOUT::CblasColMajor;
}

inline constexpr ::CBLAS_LAYOUT layout_as_mkl_enum(Row_major)
{
	return ::CBLAS_LAYOUT::CblasRowMajor;
}

inline constexpr char layout_as_mkl_char(Col_major)
{
	return 'C';
}

inline constexpr char layout_as_mkl_char(Row_major)
{
	return 'R';
}

///////////////////////////////////////////////////////////////////////
//* Matrix operations */

inline constexpr ::CBLAS_TRANSPOSE transp_op_as_mkl_enum(No_transpose)
{
	return ::CBLAS_TRANSPOSE::CblasNoTrans;
}

inline constexpr ::CBLAS_TRANSPOSE transp_op_as_mkl_enum(Transpose)
{
	return ::CBLAS_TRANSPOSE::CblasTrans;
}

inline constexpr ::CBLAS_TRANSPOSE transp_op_as_mkl_enum(Conj_transpose)
{
	return ::CBLAS_TRANSPOSE::CblasConjTrans;
}

inline constexpr char transp_op_as_mkl_char(No_transpose)
{
	return 'N';
}

inline constexpr char transp_op_as_mkl_char(Transpose)
{
	return 'T';
}

inline constexpr char transp_op_as_mkl_char(Conj_transpose)
{
	return 'C';
}
}
