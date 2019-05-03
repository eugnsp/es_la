#pragma once
#include <es_la/base/type_traits.hpp>
#include <es_la/expr/functor/elementwise_func.hpp>
#include <utility>

namespace es_la::internal
{
template<class Left, class Right>
struct Mul_func
{
	using Value = decltype(std::declval<Value_t<Left>>() * std::declval<Value_t<Right>>());

	static constexpr std::size_t ct_rows = rows_v<Left>;
	static constexpr std::size_t ct_cols = cols_v<Right>;

	static void check_sizes(const Left& left, const Right& right)
	{
		static_assert(ct_equal(cols_v<Left>, rows_v<Right>), "Incompatible operand sizes");
		MATHLA_ASSERT(left.cols() == right.rows());
	}

	static std::size_t rows(const Left& left, const Right&)
	{
		return left.rows();
	}

	static std::size_t cols(const Left&, const Right& right)
	{
		return right.cols();
	}

	static Value element(const Left& left, const Right& right, std::size_t row, std::size_t col)
	{
		auto result = Value{};
		for (std::size_t i = 0; i < left.cols(); ++i)
			result += left(row, i) * right(i, col);

		return result;
	}
};
} // namespace la::internal
