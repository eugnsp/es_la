#pragma once
//#include "../config.hpp"
#include <cstddef>
#include <es_la/dense/storage/memory.hpp>
#include <es_util/type_traits.hpp>
#include <new>
#include <stdexcept>
#include <type_traits>

namespace es_la::internal
{
template<typename T, std::size_t alignment>
class Allocator
{
private:
	static constexpr auto max_size = static_cast<std::size_t>(-1) / sizeof(T);

public:
	[[gnu::assume_aligned(alignment)]] static T* allocate(std::size_t size)
	{
		if (size == 0)
			return nullptr;

		if (size > max_size)
			throw std::bad_array_new_length();

		auto ptr = mem_alloc<alignment>(size * sizeof(T));
		if (!ptr)
			throw std::bad_alloc();

		return static_cast<T*>(ptr);
	}

	[[gnu::assume_aligned(alignment)]] static T* reallocate(T* old_ptr, std::size_t size)
	{
		static_assert(es_util::is_trivially_relocatable<T>);

		if (old_ptr == nullptr)
			return allocate(size);

		if (size == 0)
		{
			deallocate(old_ptr);
			return nullptr;
		}

		if (size > max_size)
			throw std::bad_array_new_length();

		auto ptr = mem_realloc<alignment>(old_ptr, size * sizeof(T));
		if (!ptr)
			throw std::bad_alloc();

		return static_cast<T*>(ptr);
	}

	static void deallocate(T* ptr) noexcept
	{
		mem_free(ptr);
	}
};
} // namespace es_la::internal
