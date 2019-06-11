#pragma once
#include <es_la/dense/tags.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Category>
inline constexpr bool is_lvalue = std::is_same_v<Category, Lvalue>;
}
