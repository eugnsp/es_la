#pragma once
#include <es_la/config.hpp>

#include <cstddef>
#include <type_traits>

namespace es_la
{
struct Read_only
{};

struct Read_write
{};

#ifdef LA_USE_AUTO_EXTENT
namespace internal
{
enum class Dynamic_extent
{
};
}

inline constexpr auto dynamic = impl::Dynamic_extent{};
#else
inline constexpr auto dynamic = static_cast<std::size_t>(-1);
#endif

// Dense matrix storage format tags
struct Col_major
{
	static constexpr auto is_col_major = true;
	static constexpr auto is_row_major = false;
};

struct Row_major
{
	static constexpr auto is_col_major = false;
	static constexpr auto is_row_major = true;
};

// Symmetry tags
struct Not_symmetric
{};
struct Structural_symmetric
{};
struct Symmetric_upper
{};
struct Symmetric_lower
{};
// struct Hermitian
// {};
} // namespace es_la
