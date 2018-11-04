#pragma once
#include <es_la/config.hpp>
#include <array>
#include <cstddef>
#include <type_traits>

namespace la::internal
{
template<typename T>
inline constexpr std::size_t get_default_alignment()
{
	if constexpr (std::is_arithmetic_v<T>)
	{
	#if defined __AVX__ || defined __AVX2__ || defined __SSE__
		return 32;
	#else
		return alignof(T);
	#endif
	}

	return alignof(T);
}

template<typename T, std::size_t static_size, std::size_t align = get_default_alignment<T>()>
class Storage
{
public:
	Storage() = default;

	constexpr Storage(const std::array<T, static_size>& values)
		: Storage(values, std::make_index_sequence<static_size>{})
	{ }

	static constexpr std::size_t size() noexcept
	{
		return static_size;
	}

	constexpr T& operator[](std::size_t index)
	{
		MATHLA_ASSERT(index < size());
		return data_[index];
	}
	
	constexpr const T& operator[](std::size_t index) const
	{
		MATHLA_ASSERT(index < size());
		return data_[index];
	}

	constexpr const T* data() const noexcept MATHLA_ALIGNED_ATTR(align)
	{
		return data_;
	}

	constexpr T* data() noexcept MATHLA_ALIGNED_ATTR(align)
	{
		return data_;
	}

private:
	template<std::size_t... Is>
	constexpr Storage(const std::array<T, static_size>& values, std::index_sequence<Is...>)
		: data_{values[Is]...}
	{ }

protected:
	alignas(align) T data_[static_size];
};
}
