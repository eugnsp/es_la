#pragma once
#include "forward.hpp"
#include "traits.hpp"
#include "base.hpp"
#include "range_slice.hpp"
#include "assign.hpp"
#include <array>
#include <cstddef>
#include <type_traits>

namespace la::internal
{
template<class T_Derived, class TAccess_tag>
class Expr_base;

template<class T_Derived>
class Expr_base<T_Derived, Read_only_tag> : public Base<T_Derived>
{
private:
	// TODO
	using Base1 = Base<T_Derived>;

public:
	using Base1::cols;
	using Base1::rows;
	using Base1::self;

	typename Base1::Value operator()(std::size_t row, std::size_t col) const
	{
		return self()(row, col);
	}

	template<bool is_vector = is_vector_expr_v<T_Derived>, typename = std::enable_if_t<is_vector>>
	typename Base1::Value operator[](std::size_t index) const
	{
		return self()(index, 0);
	}

	auto eval() const
	{
		using Value = internal::Value_t<T_Derived>;
		constexpr auto rows = internal::rows_v<T_Derived>;
		constexpr auto cols = internal::cols_v<T_Derived>;

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

	//////////////////////////////////////////////////////////////////////////
	/** Views */

	// Block views
	template<
		class Rows,
		class Cols,
		typename = std::enable_if_t<is_indexer_v<Rows> && is_indexer_v<Cols>>>
	auto view(Rows rows, Cols cols) const
	{
		return Sub_expr_t<const T_Derived, Rows, Cols>{self(), std::move(rows), std::move(cols)};
	}

	template<
		std::size_t t_start_row,
		std::size_t t_rows,
		std::size_t t_start_col,
		std::size_t t_cols>
	auto view() const
	{
		return view(Range<t_start_row, t_rows>{}, Range<t_start_col, t_cols>{});
	}

	auto view(
		std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols) const
	{
		return view(Range<0, 0>{start_row, rows}, Range<0, 0>{start_col, cols});
	}

	// 	template<std::size_t rows, std::size_t cols>
	// 	auto view(Matrix<std::size_t, rows, cols> indices)
	// 	{
	// 		//return col(Matrix_slice<rows, cols>{std::move(indices)});
	// 	}

	template<
		class Rows,
		class Cols,
		typename = std::enable_if_t<is_indexer_v<Rows> && is_indexer_v<Cols>>>
	auto cview(Rows rows, Cols cols) const
	{
		return view(std::move(rows), std::move(cols));
	}

	template<
		std::size_t t_start_row,
		std::size_t t_rows,
		std::size_t t_start_col,
		std::size_t t_cols>
	auto cview() const
	{
		return view<t_start_row, t_rows, t_start_col, t_cols>();
	}

	auto cview(
		std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols) const
	{
		return view(start_row, rows, start_col, cols);
	}

	// Column views
	template<class TCols, typename = std::enable_if_t<is_indexer_v<TCols>>>
	auto col(TCols cols) const
	{
		return view(Range<0, rows_v<T_Derived>>{0, rows()}, std::move(cols));
	}

	template<std::size_t t_size>
	auto col(Vector<std::size_t, t_size> indices) const
	{
		return col(Slice<t_size>{std::move(indices)});
	}

	template<std::size_t t_index>
	auto col() const
	{
		return col(Range<t_index, 1>{});
	}

	auto col(std::size_t index) const
	{
		return col(Vector<std::size_t, 1>{index});
	}

	template<class TCols, typename = std::enable_if_t<is_indexer_v<TCols>>>
	auto ccol(TCols cols) const
	{
		return col(std::move(cols));
	}

	template<std::size_t t_size>
	auto ccol(Vector<std::size_t, t_size> indices) const
	{
		return col(std::move(indices));
	}

	template<std::size_t t_index>
	auto ccol() const
	{
		return col<t_index>();
	}

	auto ccol(std::size_t index) const
	{
		return col(index);
	}

	// Row views
	template<class TRows, typename = std::enable_if_t<is_indexer_v<TRows>>>
	auto row(TRows rows) const
	{
		return view(std::move(rows), Range<0, cols_v<T_Derived>>{0, cols()});
	}

	template<std::size_t t_size>
	auto row(Vector<std::size_t, t_size> indices) const
	{
		return row(Slice<t_size>{std::move(indices)});
	}

	template<std::size_t t_index>
	auto row() const
	{
		return row(Range<t_index, 1>{});
	}

	auto row(std::size_t index) const
	{
		return row(Vector<std::size_t, 1>{index});
	}

	template<class TRows, typename = std::enable_if_t<is_indexer_v<TRows>>>
	auto crow(TRows rows) const
	{
		return row(std::move(rows));
	}

	template<std::size_t t_size>
	auto crow(Vector<std::size_t, t_size> indices) const
	{
		return row(std::move(indices));
	}

	template<std::size_t t_index>
	auto crow() const
	{
		return row<t_index>();
	}

	auto crow(std::size_t index) const
	{
		return row(index);
	}
};

//////////////////////////////////////////////////////////////////////////

template<class T_Derived>
class Expr_base<T_Derived, Read_write_tag> : public Expr_base<T_Derived, Read_only_tag>
{
	static_assert(!std::is_const_v<T_Derived>, "");

private:
	using Base = Expr_base<T_Derived, Read_only_tag>;

public:
	using typename Base::Value;

public:
	using Base::cols;
	using Base::rows;
	using Base::self;

	template<class TExpr>
	void assign(const Expression<TExpr>& expr)
	{
		Assign<T_Derived, TExpr> assigner;
		assigner(this->self(), expr.self());
	}

	template<class T_Expr>
	Expr_base& operator=(const Expression<T_Expr>& expr)
	{
		assign(expr);
		return *this;
	}

	Value& operator()(std::size_t row, std::size_t col)
	{
		return self()(row, col);
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		return self()(row, col);
	}

	Value& operator[](std::size_t index)
	{
		static_assert(is_vector_expr_v<T_Derived>);
		return self()(index, 0);
	}

	Value operator[](std::size_t index) const
	{
		static_assert(is_vector_expr_v<T_Derived>);
		return self()(index, 0);
	}

	// TODO
	// template<typename T_Value, typename = std::enable_if_t<!is_any_expr_v<T_Value>>>
	//                                                                           V !!!
	template<
		typename T_Value,
		typename = std::void_t<decltype(std::declval<Value&>() += std::declval<T_Value&>())>>
	Expr_base& operator+=(const T_Value& value)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) += value;
		return *this;
	}

	template<
		typename T_Value,
		typename = std::void_t<decltype(std::declval<Value&>() -= std::declval<T_Value&>())>>
	Expr_base& operator-=(const T_Value& value)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) -= value;
		return *this;
	}

	template<class TExpr>
	Expr_base& operator-=(const Expression<TExpr>& expr)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) -= expr(row, col);
		return *this;
	}

	template<class T_Expr>
	Expr_base& operator+=(const Expression<T_Expr>& expr)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) += expr(row, col);
		return *this;
	}

	template<typename TAlpha>
	Expr_base& operator*=(TAlpha alpha)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) *= alpha;
		return *this;
	}

	template<typename TAlpha>
	Expr_base& operator/=(TAlpha alpha)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) /= alpha;
		return *this;
	}

	void set_all(const Value& value)
	{
		for (std::size_t col = 0; col < cols(); ++col)
			for (std::size_t row = 0; row < rows(); ++row)
				self()(row, col) = value;
	}

	void zero()
	{
		set_all(0);
	}

	//////////////////////////////////////////////////////////////////////////

	using Base::cview;
	using Base::view;

	template<
		class TRows,
		class TCols,
		typename = std::enable_if_t<is_indexer_v<TRows> && is_indexer_v<TCols>>>
	auto view(TRows rows, TCols cols)
	{
		return Sub_expr_t<T_Derived, TRows, TCols>{self(), std::move(rows), std::move(cols)};
	}

	template<
		std::size_t t_start_row,
		std::size_t t_rows,
		std::size_t t_start_col,
		std::size_t t_cols>
	auto view()
	{
		return view(Range<t_start_row, t_rows>{}, Range<t_start_col, t_cols>{});
	}

	auto view(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols)
	{
		return view(
			Range<la::dynamic, la::dynamic>{start_row, rows},
			Range<la::dynamic, la::dynamic>{start_col, cols});
	}

	// Column views
	using Base::ccol;
	using Base::col;

	template<class TCols, typename = std::enable_if_t<is_indexer_v<TCols>>>
	auto col(TCols cols)
	{
		return view(Range<0, rows_v<T_Derived>>{0, rows()}, std::move(cols));
	}

	template<std::size_t t_size>
	auto col(Vector<std::size_t, t_size> indices)
	{
		return col(Slice<t_size>{std::move(indices)});
	}

	template<std::size_t t_index>
	auto col()
	{
		return col(Range<t_index, 1>{});
	}

	auto col(std::size_t index)
	{
		return col(Vector<std::size_t, 1>{index});
	}

	// Row views
	using Base::crow;
	using Base::row;

	template<class TRows, typename = std::enable_if_t<is_indexer_v<TRows>>>
	auto row(TRows rows)
	{
		return view(std::move(rows), Range<0, cols_v<T_Derived>>{0, cols()});
	}

	template<std::size_t t_size>
	auto row(Vector<std::size_t, t_size> indices)
	{
		return row(Slice<t_size>{std::move(indices)});
	}

	template<std::size_t t_index>
	auto row()
	{
		return row(Range<t_index, 1>{});
	}

	auto row(std::size_t index)
	{
		return row(Vector<std::size_t, 1>{index});
	}
};
} // namespace la::internal
