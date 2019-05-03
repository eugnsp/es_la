#pragma once
#include <es_la/base/forward.hpp>
#include <type_traits>

namespace es_la::internal
{
template<std::size_t static_rows, std::size_t static_cols>
struct Ct_shape
{
	static constexpr auto rows = static_rows;
	static constexpr auto cols = static_cols;

	static constexpr bool has_dynamic_rows = (rows == dynamic && cols != dynamic);
	static constexpr bool has_dynamic_cols = (rows != dynamic && cols == dynamic);
	static constexpr bool has_dynamic_size = (cols == dynamic && rows == dynamic);
	static constexpr bool has_static_size = (cols != dynamic && rows != dynamic);
};
} // namespace la::internal
