#pragma once
#include <es_la/dense.hpp>

template<typename T>
struct Type_trait_is_dense
{
	auto name()
	{
		return "Type trait is_dense<Expr>";
	}

	void operator()()
	{
		static_assert(es_la::is_dense<es_la::Matrix<T, std::size_t{2}, std::size_t{2}>>);
		static_assert(es_la::is_dense<es_la::Matrix<T, std::size_t{2}, es_la::dynamic>>);
		static_assert(es_la::is_dense<es_la::Matrix<T, es_la::dynamic, 2>>);
		static_assert(es_la::is_dense<es_la::Matrix<T, es_la::dynamic, es_la::dynamic>>);
	}
};
