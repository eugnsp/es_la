#pragma once
#include <es_la/base/forward.hpp>
#include <es_la/util/macros.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace la::internal
{
template<std::size_t ct_rows, std::size_t ct_cols>
class Shape_base
{
public:
	static constexpr std::size_t rows() noexcept
	{
		return rows_;
	}

	static constexpr std::size_t cols() noexcept
	{
		return cols_;
	}

	static constexpr std::size_t size() noexcept
	{
		return rows_ * cols_;
	}

protected:
	constexpr Shape_base() = default;

private:
	static constexpr std::size_t rows_ = ct_rows;
	static constexpr std::size_t cols_ = ct_cols;
};

template<std::size_t ct_rows>
class Shape_base<ct_rows, dynamic>
{
public:
	static constexpr std::size_t rows() noexcept
	{
		return rows_;
	}

	constexpr std::size_t cols() const noexcept
	{
		return cols_;
	}

	constexpr std::size_t size() const noexcept
	{
		return rows_ * cols_;
	}

protected:
	constexpr Shape_base(std::size_t rows, std::size_t cols) noexcept : cols_(cols)
	{
		ES_LA_ASSERT(rows == rows_);
	}

	void set_size(std::size_t cols) noexcept
	{
		cols_ = cols;
	}

	void swap(Shape_base& other) noexcept
	{
		std::swap(cols_, other.cols_);
	}

private:
	static constexpr std::size_t rows_ = ct_rows;
	std::size_t cols_;
};

template<std::size_t ct_cols>
class Shape_base<dynamic, ct_cols>
{
public:
	constexpr std::size_t rows() const noexcept
	{
		return rows_;
	}

	static constexpr std::size_t cols() noexcept
	{
		return cols_;
	}

	constexpr std::size_t size() const noexcept
	{
		return rows_ * cols_;
	}

protected:
	constexpr Shape_base(std::size_t rows, std::size_t cols) noexcept : rows_(rows)
	{
		ES_LA_ASSERT(cols == cols_);
	}

	void set_size(std::size_t rows) noexcept
	{
		rows_ = rows;
	}

	void swap(Shape_base& other) noexcept
	{
		std::swap(rows_, other.rows_);
	}

private:
	std::size_t rows_;
	static constexpr std::size_t cols_ = ct_cols;
};

template<>
class Shape_base<dynamic, dynamic>
{
public:
	constexpr std::size_t rows() const noexcept
	{
		return rows_;
	}

	constexpr std::size_t cols() const noexcept
	{
		return cols_;
	}

	constexpr std::size_t size() const noexcept
	{
		return rows_ * cols_;
	}

protected:
	constexpr Shape_base(std::size_t rows, std::size_t cols) noexcept : rows_(rows), cols_(cols)
	{}

	void set_size(std::size_t rows, std::size_t cols) noexcept
	{
		rows_ = rows;
		cols_ = cols;
	}

	void swap(Shape_base& other) noexcept
	{
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
	}

private:
	std::size_t rows_;
	std::size_t cols_;
};

template<std::size_t ct_rows, std::size_t ct_cols, class Layout>
class Shape : public Shape_base<ct_rows, ct_cols>
{
private:
	using Base = Shape_base<ct_rows, ct_cols>;

public:
	using Base::cols;
	using Base::rows;

	// Leading dimension
	constexpr std::size_t ldim() const noexcept
	{
		if constexpr (is_col_major<Layout>)
			return rows();
		else if constexpr (is_row_major<Layout>)
			return cols();
	}

protected:
	using Base::Base;

	constexpr std::size_t linear_index(std::size_t row, std::size_t col) const noexcept
	{
		MATHLA_ASSERT(row < rows());
		MATHLA_ASSERT(col < cols());

		if constexpr (is_col_major<Layout>)
			return row + col * ldim();
		else if constexpr (is_row_major<Layout>)
			return col + row * ldim();
	}
};
} // namespace la::internal