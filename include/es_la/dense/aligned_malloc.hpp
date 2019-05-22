#pragma once
#include <cstddef>

// #ifdef __has_include<mkl_service2.h>
// #include <mkl_service.h>
//
// namespace la::internal
// {
// inline void* aligned_malloc(std::size_t size, std::size_t alignment)
// {
// 	return ::mkl_malloc(size, static_cast<int>(alignment));
// }
// }
//
// #else

#ifdef _MSC_VER

	#include <malloc.h>

namespace la::internal
{
inline void* aligned_malloc(std::size_t size, std::size_t alignment)
{
	return ::_aligned_malloc(size, alignment);
}

inline void* aligned_realloc(void* ptr, std::size_t size, std::size_t alignment)
{
	return ::_aligned_realloc(ptr, size, alignment);
}

inline void aligned_free(void* ptr)
{
	_aligned_free(ptr);
}
} // namespace la::internal

#else

	#include <cstdlib>

namespace es_la::internal
{
inline void* aligned_malloc(std::size_t size, std::size_t alignment)
{
	return std::aligned_alloc(alignment, size);
}

inline void* aligned_realloc(void* ptr, std::size_t size, std::size_t alignment)
{
	return ::_aligned_realloc(ptr, size, alignment);
}

inline void aligned_free(void* ptr)
{
	_aligned_free(ptr);
}
} // namespace es_la::internal

#endif

//#endif

#define MATHLA_ALIGNED_MALLOC_H <mkl_service.h>
#define MATHLA_ALIGNED_MALLOC(size) mkl_malloc(size, MATHLA_ALIGNMENT)
#define MATHLA_ALIGNED_REALLOC(ptr, size) mkl_realloc(ptr, size)
#define MATHLA_ALIGNED_FREE(ptr) mkl_free(ptr)
#else
	#define MATHLA_ALIGNED_MALLOC_H
	#define MATHLA_ALIGNED_MALLOC(size) aligned_alloc(MATHLA_ALIGNMENT, size)
	#define MATHLA_ALIGNED_REALLOC(ptr, size) realloc(ptr, size)
	#define MATHLA_ALIGNED_FREE(ptr) free(ptr)
