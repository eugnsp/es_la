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
	Random_matrix(const std::size_t rows, const std::size_t cols, Random_distribution distr, Random_generator& gen) :
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

	Value operator()(const std::size_t, const std::size_t) const
	{
		return distr_(gen_);
	}

private:
	const std::size_t rows_;
	const std::size_t cols_;

	mutable Random_distribution distr_;
	Random_generator& gen_;
};

///////////////////////////////////////////////////////////////////////
//> Type traits

template<class Random_distribution, class Random_generator>
struct Traits<Random_matrix<Random_distribution, Random_generator>>
{
	using Type = typename Random_distribution::result_type;
	using Layout = void;

	static constexpr std::size_t rows = dynamic;
	static constexpr std::size_t cols = dynamic;
};
} // namespace es_la
