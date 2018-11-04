#pragma once
#include <cassert>

#if __has_include(<mkl.h>)
#	ifndef MKL_ILP64
#		ifndef WIN32
#		define MKL_ILP64
#		endif
#	endif
#	define ESLA_USE_MKL
#endif

// #ifdef __GNUC__
// #define LA_USE_AUTO_EXTENT
// #endif

//////////////////////////////////////////////////////////////////////////
/** Memory alignment */

#if defined __AVX2__
#define MATHLA_ALIGNMENT 64
#elif defined __AVX__
#define MATHLA_ALIGNMENT 32
#else
#define MATHLA_ALIGNMENT 16
#endif

#if defined MATHLA_USE_MKL
#define MATHLA_ALIGNED_MALLOC_H <mkl_service.h>
#define MATHLA_ALIGNED_MALLOC(size) mkl_malloc(size, MATHLA_ALIGNMENT)
#define MATHLA_ALIGNED_REALLOC(ptr, size) mkl_realloc(ptr, size)
#define MATHLA_ALIGNED_FREE(ptr) mkl_free(ptr)
#elif defined _MSC_VER
#define MATHLA_ALIGNED_MALLOC_H <malloc.h>
#define MATHLA_ALIGNED_MALLOC(size) _aligned_malloc(size, MATHLA_ALIGNMENT)
#define MATHLA_ALIGNED_REALLOC(ptr, size) _aligned_realloc(ptr, size, MATHLA_ALIGNMENT)
#define MATHLA_ALIGNED_FREE(ptr) _aligned_free(ptr)
#else
#define MATHLA_ALIGNED_MALLOC_H <stdlib.h>
#define MATHLA_ALIGNED_MALLOC(size) aligned_alloc(MATHLA_ALIGNMENT, size)
#define MATHLA_ALIGNED_REALLOC(ptr, size) realloc(ptr, size)
#define MATHLA_ALIGNED_FREE(ptr) free(ptr)
#endif

#if defined __GNUC__
#define LA_ALIGNED(ptr, align) ptr = reinterpret_cast<decltype(ptr)>(__builtin_assume_aligned(ptr, align))
#define LA_RESTRICT restrict
#elif defined __INTEL_COMPILER
#define LA_ALIGNED(ptr, align) __assume_aligned(ptr, align)
#define LA_RESTRICT restrict
#else
#define LA_ALIGNED(ptr, align)
#define LA_RESTRICT __restrict
#endif

#ifdef __GNUG__
#define MATHLA_ALIGNED_ATTR(align) __attribute__((assume_aligned(align)))
#define MATHLA_ALIGNED_ATTR_S __attribute__((assume_aligned(MATHLA_ALIGNMENT)))
#else
#define MATHLA_ALIGNED_ATTR(align)
#define MATHLA_ALIGNED_ATTR_S
#endif

#if defined __GNUC__
#define MATHLA_LIKELY(x) __builtin_expect(!!(x), 1)
#else
#define MATHLA_LIKELY(x)  (!!(x))
#endif

#if defined NDEBUG
#define MATHLA_ASSERT(x) void(0)
#else
#define MATHLA_ASSERT(x) (MATHLA_LIKELY(x) ? void(0) : []{ assert(!#x); }())
#endif

#ifdef _MSC_VER
#define LA_RET_ALLOC __declspec(allocator) __declspec(restrict)
#else
#define LA_RET_ALLOC
#endif
