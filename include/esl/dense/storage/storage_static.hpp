#pragma once
#include <esl/dense/storage/memory.hpp>

#include <array>
#include <cassert>
#include <cstddef>

namespace esl::internal
{
template<typename T, std::size_t ct_size, std::size_t alignment = get_alignment<T>()>
class Storage
{
public:
	Storage() = default;

	template<typename... Ts,
		typename = std::enable_if_t<sizeof...(Ts) == ct_size && (std::is_convertible_v<Ts, T> && ...)>>
	constexpr Storage(Ts&&... values) : data_{{std::forward<Ts>(values)...}}
	{}

	static constexpr std::size_t size() noexcept
	{
		return ct_size;
	}

	constexpr T& operator[](std::size_t index)
	{
		assert(index < size());
		return data_[index];
	}

	constexpr const T& operator[](std::size_t index) const
	{
		assert(index < size());
		return data_[index];
	}

	[[gnu::assume_aligned(alignment)]] constexpr const T* data() const noexcept
	{
		return data_.data();
	}

	[[gnu::assume_aligned(alignment)]] constexpr T* data() noexcept
	{
		return data_.data();
	}

protected:
	alignas(alignment) std::array<T, ct_size> data_;
};
} // namespace esl::internal
