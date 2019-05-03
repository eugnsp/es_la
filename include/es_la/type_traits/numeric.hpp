#pragma once
#include <es_util/type_traits.hpp>

#include <mkl_types.h>

#include <complex>

namespace es_la::internal
{
template<class T>
inline constexpr bool is_float_or_double = es_util::is_one_of<T, float, double>;

template<class T>
inline constexpr bool is_complex_float_or_double =
	es_util::is_one_of<T, std::complex<float>, std::complex<double>, MKL_Complex8, MKL_Complex16>;

template<class T>
inline constexpr bool is_real_or_complex_float_or_double =
	is_float_or_double<T> || is_complex_float_or_double<T>;

template<class T>
struct Add_complex_impl
{
	using Type = std::complex<T>;
};

template<class T>
struct Add_complex_impl<std::complex<T>>
{
	using Type = std::complex<T>;
};

template<class T>
using Add_complex = typename Add_complex_impl<T>::Type;

template<class T>
struct Mkl_type_impl;

template<>
struct Mkl_type_impl<float>
{
	using Type = float;
};

template<>
struct Mkl_type_impl<double>
{
	using Type = double;
};

template<>
struct Mkl_type_impl<std::complex<float>>
{
	using Type = MKL_Complex8;
};

template<>
struct Mkl_type_impl<std::complex<double>>
{
	using Type = MKL_Complex16;
};

template<class T>
using Mkl_type = typename Mkl_type_impl<T>::Type;
} // namespace es_la::internal
