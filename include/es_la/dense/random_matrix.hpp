#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits.hpp>

#include <cstddef>
#include <utility>

namespace es_la
{
template<class Random_distribution, class Random_generator>
class Random_matrix : public Dense<Random_matrix<Random_distribution, Random_generator>, Rvalue>
{
public:
	using Value = Value_type<Random_matrix>;

public:
	Random_matrix(std::size_t rows, std::size_t cols, Random_distribution distr, Random_generator& gen) :
		rows_(rows), cols_(cols), distr_(std::move(distr)), gen_(gen)
	{}

	std::size_t rows() const
	{
		return rows_;
	}

	std::size_t cols() const
	{
		return cols_;
	}

	Value operator()(std::size_t, std::size_t) const
	{
		return distr_(gen_);
	}

private:
	const std::size_t rows_;
	const std::size_t cols_;

	mutable Random_distribution distr_;
	Random_generator& gen_;
};
} // namespace es_la
