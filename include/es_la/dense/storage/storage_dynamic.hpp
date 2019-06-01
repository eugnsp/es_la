#pragma once
#include <es_la/dense/storage/allocator.hpp>
#include <es_la/dense/storage/storage_static.hpp>

#include <cstddef>
#include <memory>
#include <utility>

namespace es_la::internal
{
template<typename T, std::size_t alignment>
class Storage<T, 0, alignment>
{
private:
	using Alloc = Allocator<T, alignment>;

public:
	Storage() = default;

	explicit Storage(std::size_t size) : capacity_(size)
	{
		data_ = Alloc::allocate(size);
	}

	~Storage() noexcept
	{
		Alloc::deallocate(data_);
	}

	std::size_t capacity() const
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
	void shrink(std::size_t size)
	{
		if (size < capacity_)
		{
			data_ = Alloc::reallocate(data_, size);
			capacity_ = size;
		}
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

	[[gnu::assume_aligned(alignment)]] T* data() noexcept
	{
		return data_;
	}

	[[gnu::assume_aligned(alignment)]] const T* data() const noexcept
	{
		return data_;
	}

protected:
	T* data_ = nullptr;

private:
	std::size_t capacity_ = 0;
};
} // namespace es_la::internal
