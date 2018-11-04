#pragma once
#include <cassert>
#include <cstddef>

#if defined _MSC_VER

#include <malloc.h>

namespace la::internal
{
LA_RET_ALLOC inline void* mem_alloc(std::size_t size, std::size_t alignment)
{
	return ::_aligned_malloc(size, alignment);
}

LA_RET_ALLOC inline void* mem_realloc(void* ptr, std::size_t size, std::size_t alignment)
{
	return ::_aligned_realloc(ptr, size, alignment);
}

inline void mem_free(void* ptr) noexcept
{
	::_aligned_free(ptr);
}
}

#else

#include <mkl_version.h>
#include <mkl_service.h>

#if INTEL_MKL_VERSION < 110301
#error MKL 2011.3.1 or later is required for alignment-preserving mkl_realloc()
#endif

namespace la::internal
{
inline void* mem_alloc(std::size_t size, std::size_t alignment)
{
	return ::mkl_malloc(size, static_cast<int>(alignment));
}

inline void* mem_realloc(void* ptr, std::size_t size, std::size_t alignment)
{
	const auto new_ptr = ::mkl_realloc(ptr, size);

	// mkl_realloc() in MKL 2011.3.1 and later preserves the buffer alignment
	MATHLA_ASSERT(reinterpret_cast<std::size_t>(new_ptr) % alignment == 0);

	return new_ptr;
}

inline void mem_free(void* ptr) noexcept
{
	::mkl_free(ptr);
}
}

#endif
