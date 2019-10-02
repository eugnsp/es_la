#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/tags.hpp>

#include <cstddef>
#include <utility>
#include <type_traits>

namespace es_la
{
template<class Fn>
class Fn_matrix : public Dense<Fn_matrix<Fn>, Rvalue>
{
public:
	using Value = std::invoke_result_t<Fn, std::size_t, std::size_t>;

public:
	Fn_matrix(std::size_t rows, std::size_t cols, Fn fn) : rows_(rows), cols_(cols), fn_(std::move(fn))
	{}

	std::size_t rows() const
	{
		return rows_;
	}

	std::size_t cols() const
	{
		return cols_;
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		return fn_(row, col);
	}

private:
	const std::size_t rows_;
	const std::size_t cols_;
	
	const Fn fn_;
};
} // namespace es_la
