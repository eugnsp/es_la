#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>

namespace es_la::internal
{
template<typename T>
inline constexpr std::size_t get_default_alignment()
{
	if constexpr (std::is_arithmetic_v<T>)
		return std::max(std::size_t{32}, alignof(T));
	else
		return alignof(T);
}

template<typename T, std::size_t static_size, std::size_t alignment = get_default_alignment<T>()>
class Storage
{
public:
	Storage() = default;

	constexpr Storage(const std::array<T, static_size>& values) :
		Storage(values, std::make_index_sequence<static_size>{})
	{}

	static constexpr std::size_t size() noexcept
	{
		return static_size;
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
		return data_;
	}

	[[gnu::assume_aligned(alignment)]] constexpr T* data() noexcept
	{
		return data_;
	}

private:
	template<std::size_t... Is>
	constexpr Storage(const std::array<T, static_size>& values, std::index_sequence<Is...>) : data_{values[Is]...}
	{}

protected:
	alignas(alignment) T data_[static_size];
};
} // namespace es_la::internal
