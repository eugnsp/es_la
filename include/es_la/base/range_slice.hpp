#pragma once
#include "forward.hpp"
#include "../util/type_traits.hpp"
#include <cstddef>
#include <type_traits>
#include <cassert>

namespace la::internal
{
template<std::size_t ct_begin, std::size_t ct_size>
class Range
{
	static_assert(ct_begin != dynamic && ct_size != dynamic);
	static_assert(ct_size > 0, "Static range size should be positive");

public:
	Range() = default;

	Range(std::size_t begin, std::size_t size)
	{
		MATHLA_ASSERT(begin == ct_begin && size == ct_size);
	}

	static constexpr std::size_t begin()
	{
		return ct_begin;
	}

	static constexpr std::size_t size()
	{
		return ct_size;
	}

	constexpr std::size_t operator[](std::size_t index) const
	{
		MATHLA_ASSERT(index < ct_size);
		return ct_begin + index;
	}

	static constexpr bool are_all_less(std::size_t max)
	{
		return ct_begin + ct_size <= max;
	}
};

template<std::size_t ct_begin>
class Range<ct_begin, la::dynamic>
{
public:
	Range(std::size_t begin, std::size_t size)
		: begin_(begin), size_(size)
	{
		MATHLA_ASSERT(size_ > 0);
	}

	std::size_t begin() const
	{
		return begin_;
	}

	std::size_t size() const
	{
		return size_;
	}

	std::size_t operator[](std::size_t index) const
	{
		MATHLA_ASSERT(index < size_);
		return begin_ + index;
	}

	bool are_all_less(std::size_t max) const
	{
		return begin_ + size_ <= max;
	}

private:
	const std::size_t begin_;
	const std::size_t size_;
};

template<std::size_t t_size>
class Slice
{
public:
	explicit Slice(Vector<std::size_t, t_size> indices);

	std::size_t size() const;
	std::size_t operator[](std::size_t index) const;

	bool are_all_less(std::size_t max) const;

private:
	const Vector<std::size_t, t_size> indices_;
};

template<std::size_t rows, std::size_t cols>
class Matrix_slice
{
public:
private:
};

//////////////////////////////////////////////////////////////////////////

/************************************************************************/

template<std::size_t t_size>
inline Slice<t_size>::Slice(Vector<std::size_t, t_size> indices)
	: indices_(std::move(indices))
{
	MATHLA_ASSERT(!indices_.is_empty());
}

template<std::size_t t_size>
inline std::size_t Slice<t_size>::size() const
{
	return indices_.size();
}

template<std::size_t t_size>
inline std::size_t Slice<t_size>::operator[](std::size_t index) const
{
	return indices_[index];
}

template<std::size_t t_size>
inline bool Slice<t_size>::are_all_less(std::size_t max) const
{
	for (std::size_t i = 0; i < indices_.size(); ++i)
		if (indices_[i] >= max)
			return false;
	return true;
}
}

