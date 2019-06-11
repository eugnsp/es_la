#pragma once
#include <es_la/core/tags.hpp>

#include <cassert>
#include <cstddef>

namespace es_la
{
template<std::size_t ct_value>
class Extent
{
public:
	Extent() = default;

	explicit Extent(std::size_t value)
	{
		assert(value = ct_value);
	}

	static constexpr std::size_t value()
	{
		return ct_value;
	}
};

template<>
class Extent<dynamic>
{
public:
	explicit Extent(std::size_t value) : value_(value)
	{}

	std::size_t value() const
	{
		return value_;
	}

private:
	const std::size_t value_;
};
} // namespace es_la
