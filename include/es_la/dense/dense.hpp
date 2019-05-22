#pragma once
#include <es_la/core/expression.hpp>
#include <es_la/dense/expr.hpp>
#include <es_la/dense/forward.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/view/range.hpp>
#include <es_la/dense/view/slice.hpp>

#include <es_la/dense/expr/add.hpp>

#include <array>
#include <cstddef>
#include <type_traits>

namespace es_la
{
template<class Expr, class Category>
class Dense : public Expression<Expr>
{
	// static_assert(std::is_same_v<Category_type<Expr>, Category>);

private:
	using Base = Expression<Expr>;

public:
	using typename Base::Value;

public:
	using Base::cols;
	using Base::rows;
	using Base::self;

	template<class Scalar>
	void assign_scalar(const Scalar& scalar)
	{
		static_assert(std::is_same_v<Category, Lvalue>, "Expression should be an l-value");
		static_assert(std::is_convertible_v<Scalar, Value>, "Inconsistent data types");

		internal::Assign_scalar_op_type<Expr, Scalar>::run(self(), scalar);
	}

	template<class Expr2>
	void assign_expr(const Expression<Expr2>& expr)
	{
		static_assert(std::is_same_v<Category, Lvalue>, "Expression should be an l-value");
		static_assert(std::is_convertible_v<Value_type<Expr2>, Value>, "Inconsistent data types");

		internal::Assign_expr_op_type<Expr, Expr2>::run(self(), expr.self());
	}

	template<class Scalar, typename = std::enable_if_t<std::is_convertible_v<Scalar, Value>>>
	Dense& operator=(const Scalar& scalar)
	{
		assign_scalar(scalar);
		return *this;
	}

	template<class Expr2>
	Dense& operator=(const Expression<Expr2>& expr)
	{
		assign_expr(expr);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////
	//* Element access */

	decltype(auto) operator()(std::size_t row, std::size_t col)
	{
		return self()(row, col);
	}

	decltype(auto) operator()(std::size_t row, std::size_t col) const
	{
		return self()(row, col);
	}

	decltype(auto) operator[](std::size_t index)
	{
		static_assert(internal::is_vector_expr<Expr>, "Expression should be a vector");
		return self()(index, 0);
	}

	decltype(auto) operator[](std::size_t index) const
	{
		static_assert(internal::is_vector_expr<Expr>, "Expression should be a vector");
		return self()(index, 0);
	}

	auto eval() const
	{
		constexpr auto rows = ct_rows_value<Expr>;
		constexpr auto cols = ct_cols_value<Expr>;

		Matrix<Value, rows, cols> matrix{self()};
		return matrix;
	}

	// 	template<class Other>
	// 	bool operator==(const Expr<Other>& other) const
	// 	{
	// 		if (!ct_size_equal_v<ct_rows, ct_rows_v<Other>> ||
	// 			!ct_size_equal_v<ct_cols, ct_cols_v<Other>> ||
	// 			n_rows() != other.n_rows() ||
	// 			n_cols() != other.n_cols())
	// 		{
	// 			return false;
	// 		}
	//
	// 		for (std::size_t col = 0; col < other.n_cols(); ++col)
	// 			for (std::size_t row = 0; row < other.n_rows(); ++row)
	// 				if ((*this)(row, col) != other.self()(row, col))
	// 					return false;
	//
	// 		return true;
	// 	}
	//
	// 	template<class Other>
	// 	bool operator!=(const Expr<Other>& other) const
	// 	{
	// 		return !(*this == other);
	// 	}

	template<class Expr2>
	Dense& operator+=(const Expr2& expr)
	{
		internal::Add_equal<Expr, Expr2>::run(self(), expr);
		//	internal::add(*this, expr);
		return *this;
	}

	// template<class Expr2>
	// Dense& operator-=(const Expr2& expr)
	// {
	// 	internal::sub(*this, expr);
	// 	return *this;
	// }

	template<class Expr2>
	Dense& operator*=(const Expr2& expr)
	{
		internal::mul(*this, expr);
		return *this;
	}

	// template<class Expr2>
	// Dense& operator/=(const Expr2& expr)
	// {
	// 	internal::div(*this, expr);
	// 	return *this;
	// }

	//////////////////////////////////////////////////////////////////////////
	/** Block views */

	template<std::size_t ct_start_row, std::size_t ct_rows, std::size_t ct_start_col, std::size_t ct_cols>
	auto view()
	{
		using Rows = internal::Range<ct_start_row, ct_rows>;
		using Cols = internal::Range<ct_start_col, ct_cols>;
		return view_impl(Rows{}, Cols{});
	}

	template<std::size_t ct_start_row, std::size_t ct_rows, std::size_t ct_start_col, std::size_t ct_cols>
	auto view() const
	{
		using Rows = internal::Range<ct_start_row, ct_rows>;
		using Cols = internal::Range<ct_start_col, ct_cols>;
		return view_impl(Rows{}, Cols{});
	}

	template<std::size_t ct_start_row, std::size_t ct_rows, std::size_t ct_start_col, std::size_t ct_cols>
	auto cview() const
	{
		return view<ct_start_row, ct_rows, ct_start_col, ct_cols>();
	}

	///////////////////////////////////////////////////////////////////////

	auto view(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols)
	{
		using Range = internal::Range<dynamic, dynamic>;
		return view_impl(Range{start_row, rows}, Range{start_col, cols});
	}

	auto view(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols) const
	{
		using Range = internal::Range<dynamic, dynamic>;
		return view_impl(Range{start_row, rows}, Range{start_col, cols});
	}

	auto cview(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols) const
	{
		return view(start_row, rows, start_col, cols);
	}

	///////////////////////////////////////////////////////////////////////
	//* Row views */

	template<std::size_t ct_index>
	auto row_view()
	{
		using Rows = internal::Range<ct_index, std::size_t{1}>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{}, Cols{0, cols()});
	}

	template<std::size_t ct_index>
	auto row_view() const
	{
		using Rows = internal::Range<ct_index, std::size_t{1}>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{}, Cols{0, cols()});
	}

	template<std::size_t ct_index>
	auto row_cview() const
	{
		return row_view<ct_index>();
	}

	///////////////////////////////////////////////////////////////////////

	auto row_view(std::size_t index)
	{
		using Rows = internal::Range<dynamic, std::size_t{1}>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{index}, Cols{0, cols()});
	}

	auto row_view(std::size_t index) const
	{
		using Rows = internal::Range<dynamic, std::size_t{1}>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{index}, Cols{0, cols()});
	}

	auto row_cview(std::size_t index) const
	{
		return row_view(index);
	}

	///////////////////////////////////////////////////////////////////////

	template<std::size_t ct_start_row, std::size_t ct_rows>
	auto rows_view()
	{
		using Rows = internal::Range<ct_start_row, ct_rows>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{}, Cols{0, cols()});
	}

	template<std::size_t ct_start_row, std::size_t ct_rows>
	auto rows_view() const
	{
		using Rows = internal::Range<ct_start_row, ct_rows>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{}, Cols{0, cols()});
	}

	template<std::size_t ct_start_row, std::size_t ct_rows>
	auto rows_cview() const
	{
		return rows_view<ct_start_row, ct_rows>();
	}

	///////////////////////////////////////////////////////////////////////

	auto rows_view(std::size_t start_row, std::size_t rows)
	{
		using Rows = internal::Range<dynamic, dynamic>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{start_row, rows}, Cols{0, cols()});
	}

	auto rows_view(std::size_t start_row, std::size_t rows) const
	{
		using Rows = internal::Range<dynamic, dynamic>;
		using Cols = internal::Range<std::size_t{0}, ct_cols_value<Expr>>;
		return view_impl(Rows{start_row, rows}, Cols{0, cols()});
	}

	auto rows_cview(std::size_t start_row, std::size_t rows) const
	{
		return rows_view(start_row, rows);
	}

	///////////////////////////////////////////////////////////////////////
	//* Column views */

	template<std::size_t ct_index>
	auto col_view()
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<ct_index, std::size_t{1}>;
		return view_impl(Rows{0, rows()}, Cols{});
	}

	template<std::size_t ct_index>
	auto col_view() const
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<ct_index, std::size_t{1}>;
		return view_impl(Rows{0, rows()}, Cols{});
	}

	template<std::size_t ct_index>
	auto col_cview() const
	{
		return col_view<ct_index>();
	}

	///////////////////////////////////////////////////////////////////////

	auto col_view(std::size_t index)
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<dynamic, std::size_t{1}>;
		return view_impl(Rows{0, rows()}, Cols{index});
	}

	auto col_view(std::size_t index) const
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<dynamic, std::size_t{1}>;
		return view_impl(Rows{0, rows()}, Cols{index});
	}

	auto col_cview(std::size_t index) const
	{
		return col_view(index);
	}

	///////////////////////////////////////////////////////////////////////

	template<std::size_t ct_start_col, std::size_t ct_cols>
	auto cols_view()
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<ct_start_col, ct_cols>;
		return view_impl(Rows{0, rows()}, Cols{});
	}

	template<std::size_t ct_start_col, std::size_t ct_cols>
	auto cols_view() const
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<ct_start_col, ct_cols>;
		return view_impl(Rows{0, rows()}, Cols{});
	}

	template<std::size_t ct_start_col, std::size_t ct_cols>
	auto cols_cview() const
	{
		return cols_view<ct_start_col, ct_cols>();
	}

	///////////////////////////////////////////////////////////////////////

	auto cols_view(std::size_t start_col, std::size_t cols)
	{
		using Rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<dynamic, dynamic>;
		return view_impl(Rows{0, rows()}, Cols{start_col, cols});
	}

	auto cols_view(std::size_t start_col, std::size_t cols) const
	{
		using All_rows = internal::Range<std::size_t{0}, ct_rows_value<Expr>>;
		using Cols = internal::Range<dynamic, dynamic>;
		return view_impl(All_rows{0, rows()}, Cols{start_col, cols});
	}

	auto cols_cview(std::size_t start_col, std::size_t cols) const
	{
		return cols_view(start_col, cols);
	}

	// template<std::size_t t_size>
	// auto col(Vector<std::size_t, t_size> indices)
	// {
	// 	return col(internal::Slice<t_size>{std::move(indices)});
	// }

	// template<std::size_t t_size>
	// auto row(Vector<std::size_t, t_size> indices)
	// {
	// 	return row(internal::Slice<t_size>{std::move(indices)});
	// }

	// 	template<std::size_t rows, std::size_t cols>
	// 	auto view(Matrix<std::size_t, rows, cols> indices)
	// 	{
	// 		//return col(Matrix_slice<rows, cols>{std::move(indices)});
	// 	}

	// template<std::size_t t_size>
	// auto col(Vector<std::size_t, t_size> indices) const
	// {
	// 	return col(internal::Slice<t_size>{std::move(indices)});
	// }

	// template<std::size_t t_size>
	// auto ccol(Vector<std::size_t, t_size> indices) const
	// {
	// 	return col(std::move(indices));
	// }

	// Row views
	// template<class TRows, typename = std::enable_if_t<internal::is_indexer_v<TRows>>>
	// auto row(TRows rows) const
	// {
	// 	return view(std::move(rows), internal::Range<dynamic, ct_cols_value<Expr>>{0, cols()});
	// }

	// template<std::size_t t_size>
	// auto row(Vector<std::size_t, t_size> indices) const
	// {
	// 	return row(internal::Slice<t_size>{std::move(indices)});
	// }

	// template<std::size_t t_size>
	// auto crow(Vector<std::size_t, t_size> indices) const
	// {
	// 	return row(std::move(indices));
	// }

	// TODO
	// template<typename T_Value, typename = std::enable_if_t<!is_any_expr_v<T_Value>>>
	//                                                                           V !!!
	// template<typename T_Value, typename = std::void_t<decltype(std::declval<Value&>() += std::declval<T_Value&>())>>
	// Dense& operator+=(const T_Value& value)
	// {
	// 	for (std::size_t col = 0; col < cols(); ++col)
	// 		for (std::size_t row = 0; row < rows(); ++row)
	// 			self()(row, col) += value;
	// 	return *this;
	// }

	// template<typename T_Value, typename = std::void_t<decltype(std::declval<Value&>() -= std::declval<T_Value&>())>>
	// Dense& operator-=(const T_Value& value)
	// {
	// 	for (std::size_t col = 0; col < cols(); ++col)
	// 		for (std::size_t row = 0; row < rows(); ++row)
	// 			self()(row, col) -= value;
	// 	return *this;
	// }

	// template<class TExpr>
	// Dense& operator-=(const Dense<TExpr>& expr)
	// {
	// 	for (std::size_t col = 0; col < cols(); ++col)
	// 		for (std::size_t row = 0; row < rows(); ++row)
	// 			self()(row, col) -= expr(row, col);
	// 	return *this;
	// }

	// template<class T_Expr>
	// Dense& operator+=(const Dense<T_Expr>& expr)
	// {
	// 	for (std::size_t col = 0; col < cols(); ++col)
	// 		for (std::size_t row = 0; row < rows(); ++row)
	// 			self()(row, col) += expr(row, col);
	// 	return *this;
	// }

	// template<typename TAlpha>
	// Dense& operator*=(TAlpha alpha)
	// {
	// 	for (std::size_t col = 0; col < cols(); ++col)
	// 		for (std::size_t row = 0; row < rows(); ++row)
	// 			self()(row, col) *= alpha;
	// 	return *this;
	// }

	// template<typename TAlpha>
	// Dense& operator/=(TAlpha alpha)
	// {
	// 	for (std::size_t col = 0; col < cols(); ++col)
	// 		for (std::size_t row = 0; row < rows(); ++row)
	// 			self()(row, col) /= alpha;
	// 	return *this;
	// }

private:
	template<class Rows, class Cols>
	auto view_impl(Rows rows, Cols cols)
	{
		return View<Expr, Rows, Cols, Category>{self(), std::move(rows), std::move(cols)};
	}

	template<class Rows, class Cols>
	auto view_impl(Rows rows, Cols cols) const
	{
		return View<const Expr, Rows, Cols, Category>{self(), std::move(rows), std::move(cols)};
	}
};

} // namespace es_la
