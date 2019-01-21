#pragma once
#include <cassert>

#ifdef _DEBUG
#	define ES_LA_VISUALIZE 1
#else
#	define ES_LA_VISUALIZE 0
#endif

//////////////////////////////////////////////////////////////////////////

#define ES_LA_USE_MKL 1

#ifndef ES_LA_USE_MKL
#	define ES_LA_USE_MKL 0
#endif

//////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
#	define ES_LA_LIKELY(x) __builtin_expect(!!(x), 1)
#else
#	define ES_LA_LIKELY(x) (!!(x))
#endif

#ifdef NDEBUG
#	ifdef __GNUC__
#		define ES_LA_ASSERT(x) (void(0))
#	else
#		define ES_LA_ASSERT(x) (__assume(!!(x)))
#	endif
#else
#	define ES_LA_ASSERT(x) (ES_LA_LIKELY(x) ? void(0) : [] { assert(!#x); }())
#endif
