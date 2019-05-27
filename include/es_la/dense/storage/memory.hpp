#pragma once
#include <es_la/dense/storage/memory.hpp>

#include <mkl_service.h>
#include <mkl_version.h>

#include <cassert>
#include <cstddef>
#include <cstdint>

#if INTEL_MKL_VERSION < 110301
	#error MKL 2011.3.1 or later is required for alignment-preserving mkl_realloc()
#endif

namespace es_la::internal
{
[[nodiscard]] inline void* mem_alloc(std::size_t size, std::size_t alignment)
{
	return ::mkl_malloc(size, static_cast<int>(alignment));
}

[[nodiscard]] inline void* mem_realloc(void* ptr, std::size_t size, std::size_t alignment)
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
