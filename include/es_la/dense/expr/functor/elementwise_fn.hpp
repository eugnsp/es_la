#pragma once
#include <es_la/dense/utility.hpp>
#include <es_la/dense/type_traits.hpp>

#include <cassert>
#include <cstddef>

namespace es_la::internal
{
template<class Expr1, class Expr2>
class Elementwise_fn
{
public:
	static_assert(is_ct_extent_dynamic_or_eq(ct_rows_value<Expr1>, ct_rows_value<Expr2>), "Incompatible extents");
	static_assert(is_ct_extent_dynamic_or_eq(ct_cols_value<Expr1>, ct_cols_value<Expr2>), "Incompatible extents");

	static constexpr auto ct_rows = ct_extent_static(ct_rows_value<Expr1>, ct_rows_value<Expr2>);
	static constexpr auto ct_cols = ct_extent_static(ct_cols_value<Expr1>, ct_cols_value<Expr2>);

public:
	static void check_sizes([[maybe_unused]] const Expr1& expr1, [[maybe_unused]] const Expr2& expr2)
	{
		assert(expr1.rows() == expr2.rows());
		assert(expr1.cols() == expr2.cols());
	}

	static std::size_t rows(const Expr1& expr1, const Expr2&)
	{
		return expr1.rows();
	}

	static std::size_t cols(const Expr1& expr1, const Expr2&)
	{
		return expr1.cols();
	}
};
} // namespace es_la::internal
