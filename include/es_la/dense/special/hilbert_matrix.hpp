#pragma once
#include <es_la/dense/function.hpp>
#include <es_la/dense/tags.hpp>

#include <cstddef>

namespace es_la
{
// Returns the Hilbert matrix
template<typename T, class Layout = Col_major>
constexpr auto hilbert_matrix(const std::size_t size)
{
	return make_matrix<Layout>(size, size, [](auto row, auto col) { return static_cast<T>(T{1} / (1 + row + col)); });
}

// Returns the Hilbert matrix
template<typename T, std::size_t size, class Layout = Col_major>
constexpr auto hilbert_matrix()
{
	return make_matrix<size, size, Layout>([](auto row, auto col) { return static_cast<T>(T{1} / (1 + row + col)); });
}
} // namespace es_la
