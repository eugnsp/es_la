#pragma once
#include "../config.hpp"
#include "../base/forward.hpp"
//#include <mkl_cblas.h>

namespace la
{
#ifdef ESLA_USE_MKL
// template<std::size_t t_size>
// double norm2(const Vector<double, t_size>& vec)
//{
//	return cblas_dnrm2(vec.size(), vec.data(), 1);
//}
#endif
} // namespace la
