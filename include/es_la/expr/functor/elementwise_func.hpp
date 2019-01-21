#pragma once
#include <es_la/base/helper.hpp>
#include <es_la/base/traits.hpp>
#include <es_la/util/macros.hpp>

namespace la::internal
{
template<class Left, class Right>
struct Elementwise_func
{
	static constexpr std::size_t ct_rows = (rows_v<Left> != 0) ? rows_v<Left> : rows_v<Right>;
	static constexpr std::size_t ct_cols = (cols_v<Left> != 0) ? cols_v<Left> : cols_v<Right>;

	static void check_sizes(const Left& left, const Right& right)
	{
		static_assert(ct_equal(rows_v<Left>, rows_v<Right>), "Incompatible row sizes");
		static_assert(ct_equal(cols_v<Left>, cols_v<Right>), "Incompatible column sizes");
		MATHLA_ASSERT(left.rows() == right.rows() && left.cols() == right.cols());
	}

	static std::size_t rows(const Left& left, const Right&)
	{
		return left.rows();
	}

	static std::size_t cols(const Left& left, const Right&)
	{
		return left.cols();
	}
};
} // namespace la::internal