#pragma once
#include <es_la/config.hpp>
#include <es_la/storage/allocator.hpp>
#include <cstddef>
#include <utility>

namespace la::internal
{
template<typename T, std::size_t align>
class Storage<T, 0, align>
{
private:
	using Alloc = Allocator<T, align>;

public:
	Storage() noexcept : data_(nullptr), capacity_(0)
	{}

	explicit Storage(std::size_t size) : capacity_(size)
	{
		data_ = Alloc::allocate(size);
	}

	~Storage() noexcept
	{
		Alloc::deallocate(data_);
	}

	std::size_t capacity() const noexcept
	{
		return capacity_;
	}

	void resize(std::size_t size)
	{
		if (size <= capacity_)
			return;

		data_ = Alloc::reallocate(data_, size);
		capacity_ = size;
	}

	// Shrinks the storage to reduce its capacity to fit its size
	void shrink_to_size(std::size_t size)
	{
		ES_LA_ASSERT(size <= capacity_);
		if (size == capacity_)
			return;

		data_ = Alloc::reallocate(data_, size);
		capacity_ = size;
	}

	void swap(Storage& other) noexcept
	{
		std::swap(data_, other.data_);
		std::swap(capacity_, other.capacity_);
	}

	T& operator[](std::size_t index)
	{
		return data_[index];
	}

	const T& operator[](std::size_t index) const
	{
		return data_[index];
	}

	T* data() noexcept MATHLA_ALIGNED_ATTR(align)
	{
		return data_;
	}

	const T* data() const noexcept MATHLA_ALIGNED_ATTR(align)
	{
		return data_;
	}

protected:
	T* data_;

private:
	std::size_t capacity_;
};
} // namespace la::internal
