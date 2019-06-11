#pragma once
#include <es_la/dense/type_traits.hpp>

#include <cstddef>

namespace es_la
{
template<class Expr>
class Expression
{
public:
	using Value = Value_type<Expr>;

public:
	///////////////////////////////////////////////////////////////////////
	//* Extents */

	std::size_t rows() const
	{
		return self().rows();
	}

	std::size_t cols() const
	{
		return self().cols();
	}

	std::size_t size() const
	{
		return rows() * cols();
	}

	bool is_empty() const
	{
		return rows() == 0 || cols() == 0;
	}

	///////////////////////////////////////////////////////////////////////
	//* CRTP */

	Expr& self()
	{
		return static_cast<Expr&>(*this);
	}

	const Expr& self() const
	{
		return static_cast<const Expr&>(*this);
	}
};
} // namespace es_la
