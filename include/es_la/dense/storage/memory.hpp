#pragma once
#include <mkl_service.h>
#include <mkl_version.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if INTEL_MKL_VERSION < 110301
	#error MKL 2011.3.1 or later is required for alignment-preserving mkl_realloc()
#endif

namespace es_la::internal
{
template<typename T>
constexpr std::size_t get_alignment()
{
	constexpr std::size_t min_arithmetic_alignment = 64;
	return (std::is_arithmetic_v<T> && alignof(T) < min_arithmetic_alignment) ? min_arithmetic_alignment : alignof(T);
}

[[nodiscard, gnu::malloc, gnu::alloc_size(1)]] inline void* mem_alloc(std::size_t size, std::size_t alignment)
{
	return ::mkl_malloc(size, static_cast<int>(alignment));
}

[[nodiscard, gnu::alloc_size(2)]] inline void* mem_realloc(void* ptr, std::size_t size, std::size_t alignment)
{
	const auto new_ptr = ::mkl_realloc(ptr, size);

	// mkl_realloc() in MKL 2011.3.1 and later preserves the buffer alignment
	assert(reinterpret_cast<std::uintptr_t>(new_ptr) % alignment == 0);
	return new_ptr;
}

inline void mem_free(void* ptr) noexcept
{
	::mkl_free(ptr);
}
} // namespace es_la::internal
