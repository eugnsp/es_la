#pragma once
#include "check_elements.hpp"

#include <es_la/dense.hpp>

#include <cassert>
#include <cstddef>
#include <type_traits>

template<typename T>
struct Binary_expr_constructor
{
	auto name()
	{
		return "Binary expressions M + M and M - M constructor";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 4> mss;
		es_la::Matrix<T, 3, es_la::dynamic> msd(4);
		es_la::Matrix<T, es_la::dynamic, 4> mds(3);
		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> mdd(3, 4);

		op(mss, mss);
		op(mss, msd);
		op(mss, mds);
		op(mss, mdd);
		op(msd, msd);
		op(msd, mds);
		op(msd, mdd);
		op(mds, mds);
		op(mds, mdd);
		op(mdd, mdd);
	}

	template<class M1, class M2>
	void op(const M1& m1, const M2& m2)
	{
		auto add = m1 + m2;

		static_assert(std::is_same_v<decltype(add(0, 0)), T>);
		assert(add.rows() == m1.rows());
		assert(add.cols() == m1.cols());

		auto sub = m1 + m2;

		static_assert(std::is_same_v<decltype(sub(0, 0)), T>);
		assert(sub.rows() == m1.rows());
		assert(sub.cols() == m1.cols());
	}
};
