#pragma once
#include "forward.hpp"
#include "type_traits.hpp"

#include <array>
#include <cstddef>
#include <type_traits>

namespace es_la::internal
{
template<class T_Derived>
class Base
{
public:
	using Value = Value_t<T_Derived>;

public:
	std::size_t rows() const;
	std::size_t cols() const;
	std::array<std::size_t, 2> shape() const;

	bool is_empty() const;
	std::size_t size() const;	

	T_Derived& self();
	const T_Derived& self() const;
};

/************************************************************************/
/* IMPLEMENTATION                                                       */
/************************************************************************/

template<class T_Derived>
inline std::size_t Base<T_Derived>::rows() const
{
	return self().rows();
}

template<class T_Derived>
inline std::size_t Base<T_Derived>::cols() const
{
	return self().cols();
}

template<class T_Derived>
std::array<std::size_t, 2> Base<T_Derived>::shape() const
{
	return {rows(), cols()};
}

template<class T_Derived>
inline bool Base<T_Derived>::is_empty() const
{
	return rows() == 0 || cols() == 0;
}

template<class T_Derived>
inline std::size_t Base<T_Derived>::size() const
{
	return rows() * cols();
}

template<class T_Derived>
inline T_Derived& Base<T_Derived>::self()
{
	return static_cast<T_Derived&>(*this);
}

template<class T_Derived>
inline const T_Derived& Base<T_Derived>::self() const
{
	return static_cast<const T_Derived&>(*this);
}
} // namespace la::internal
