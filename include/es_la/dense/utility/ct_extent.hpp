#pragma once
#include <es_la/dense/tags.hpp>

#include <cstddef>
#include <type_traits>

namespace es_la::internal
{
template<class Ext1, class Ext2>
constexpr bool is_ct_extent_dynamic_or_eq([[maybe_unused]] Ext1 ext1, [[maybe_unused]] Ext2 ext2)
{
	if constexpr (std::is_same_v<Ext1, Dynamic_extent> || std::is_same_v<Ext2, Dynamic_extent>)
		return true;
	else
		return static_cast<std::size_t>(ext1) == static_cast<std::size_t>(ext2);
}

template<class Ext1, class Ext2>
constexpr bool is_ct_extent_dynamic_or_less([[maybe_unused]] Ext1 ext1, [[maybe_unused]] Ext2 y)
{
	if constexpr (std::is_same_v<Ext1, Dynamic_extent> || std::is_same_v<Ext2, Dynamic_extent>)
		return true;
	else
		return static_cast<std::size_t>(ext1) < static_cast<std::size_t>(y);
}

template<class Ext1, class Ext2>
constexpr bool is_ct_extent_dynamic_or_less_equal(Ext1 ext1, Ext2 ext2)
{
	return is_ct_extent_dynamic_or_eq(ext1, ext2) || is_ct_extent_dynamic_or_less(ext1, ext2);
}

template<class Ext>
constexpr bool is_ct_extent_static_and_eq([[maybe_unused]] Ext ext1, std::size_t ext2)
{
	if constexpr (std::is_same_v<Ext, Dynamic_extent>)
		return false;
	else
		return static_cast<std::size_t>(ext1) == ext2;
}

///////////////////////////////////////////////////////////////////////

template<class Ext>
constexpr std::size_t ct_extent_static_or_zero([[maybe_unused]] Ext ext)
{
	if constexpr (std::is_same_v<Ext, Dynamic_extent>)
		return 0;
	else
		return static_cast<std::size_t>(ext);
}

template<class Ext>
constexpr auto ct_extent_dynamic_or_size_t([[maybe_unused]] Ext ext)
{
	if constexpr (std::is_same_v<Ext, Dynamic_extent>)
		return dynamic;
	else
		return static_cast<std::size_t>(ext);
}

template<class Ext1, class Ext2>
constexpr auto ct_extent_static([[maybe_unused]] Ext1 ext1, [[maybe_unused]] Ext2 ext2)
{
	if constexpr (!std::is_same_v<Ext1, Dynamic_extent>)
		return ext1;
	else
		return ext2;
}

template<class Ext1, class Ext2>
constexpr auto ct_extent_mul([[maybe_unused]] Ext1 ext1, [[maybe_unused]] Ext2 ext2)
{
	if constexpr (std::is_same_v<Ext1, Dynamic_extent> || std::is_same_v<Ext2, Dynamic_extent>)
		return dynamic;
	else
		return ext1 * ext2;
}
} // namespace es_la::internal
