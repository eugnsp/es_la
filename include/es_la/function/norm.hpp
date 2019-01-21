#pragma once
#include <es_la/util/mkl.hpp>
#include <cmath>

namespace la
{
template<class TExpr>
double norm2(const Expression<TExpr>& vec)
{
	double nrm = 0;
	for (std::size_t i = 0; i < vec.size(); ++i)
		nrm += vec[i] * vec[i];

	return std::sqrt(nrm);
}

#if ES_LA_USE_MKL
template<std::size_t size>
double norm2(const Vector<double, size>& vec)
{
	return ::cblas_dnrm2(vec.size(), vec.data(), 1);
}
#else
template<std::size_t size>
double norm2(const Vector<double, size>& vec)
{
	double norm = 0;
	for (std::size_t i = 0; i < vec.size(); ++i)
		norm += vec[i] * vec[i];
	return std::sqrt(norm);
}
#endif

template<std::size_t rows, std::size_t cols>
double norm_f(const Matrix<double, rows, cols>& mat)
{
	double s = 0;
	for (std::size_t c = 0; c < mat.cols(); ++c)
		for (std::size_t r = 0; r < mat.rows(); ++r)
		{
			const auto m = mat(r, c);
			s += std::abs(m * m);
		}

	return std::sqrt(s);
}
} // namespace la
