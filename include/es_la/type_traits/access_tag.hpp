#pragma once
#include <es_la/tags.hpp>

#include <type_traits>

namespace es_la::internal
{
// It the given type is const or const-ref, returns the Read_only tag,
// otherwise returns the Read_write tag
template<class T>
using Access_tag_by_constness =
	std::conditional_t<std::is_const_v<std::remove_reference_t<T>>, Read_only, Read_write>;
}
