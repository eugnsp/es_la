#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace traits
{
template<class Expr>
struct Layout;
}

namespace internal
{
template<class Layout>
struct Transpose_layout_tag;

template<>
struct Transpose_layout_tag<void>
{
	using Type = void;
};

template<>
struct Transpose_layout_tag<Col_major>
{
	using Type = Row_major;
};

template<>
struct Transpose_layout_tag<Row_major>
{
	using Type = Col_major;
};
}

///////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////

namespace internal
{
template<class Expr1, class Expr2>
inline constexpr bool have_same_layout = std::is_same_v<Layout_tag<Expr1>, Layout_tag<Expr2>>;
}
} // namespace es_la
