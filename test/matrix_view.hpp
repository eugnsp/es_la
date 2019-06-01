#pragma once
#include "check_elements.hpp"

#include <es_la/dense.hpp>

#include <cassert>
#include <cstddef>
#include <type_traits>

template<typename T>
struct Block_view_lvalue_copy_constructor
{
	auto name()
	{
		return "Block view copy constructor";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 3, es_la::Col_major> m1{1, 2, 3, 4, 5, 6, 7, 8, 9};
		const es_la::Matrix<T, 3, 3, es_la::Col_major> m2{1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto v1 = m1.view(1, 2, 1, 3);
		auto v1c = v1;

		static_assert(std::is_same_v<decltype(v1(0, 0)), T&>);
		static_assert(std::is_same_v<decltype(v1c(0, 0)), T&>);
		assert(v1.rows() == v1c.rows() && v1.cols() == v1c.cols());
		assert(v1.l_dim() == v1c.l_dim());
		assert(v1.data() == v1c.data());
	}
};

template<typename T>
struct Block_view_lvalue_size
{
	auto name()
	{
		return "Block view size";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 4, es_la::Col_major> m1c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		es_la::Matrix<T, 3, 4, es_la::Row_major> m1r{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

		auto v1c = m1c.view(1, 2, 1, 3);
		assert(v1c.rows() == 2 && v1c.cols() == 3);
		assert(v1c.l_dim() == 3);
		static_assert(std::is_same_v<es_la::Layout_tag<decltype(v1c)>, es_la::Col_major>);

		auto v1r = m1r.view(1, 2, 1, 3);
		assert(v1r.rows() == 2 && v1r.cols() == 3);
		assert(v1r.l_dim() == 4);
		static_assert(std::is_same_v<es_la::Layout_tag<decltype(v1r)>, es_la::Row_major>);
	}
};

template<typename T>
struct Block_view_lvalue_data
{
	auto name()
	{
		return "Block view data access";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 4, es_la::Col_major> m1c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		es_la::Matrix<T, 3, 4, es_la::Row_major> m1r{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		const es_la::Matrix<T, 3, 4, es_la::Col_major> m2c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

		auto v1c = m1c.view(1, 2, 1, 3);
		static_assert(std::is_same_v<decltype(v1c(0, 0)), T&>);
		static_assert(std::is_same_v<decltype(v1c.data()), T*>);
		assert(check_elements(v1c, {5, 6, 8, 9, 11, 12}));
		assert(check_elements_data(v1c, {5, 6, 8, 9, 11, 12}));

		v1c(1, 1) = 13;
		assert(m1c(2, 2) == 13);

		auto v2c = m2c.view(1, 2, 1, 3);
		static_assert(std::is_same_v<decltype(v2c(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v2c.data()), const T*>);
		assert(check_elements(v2c, {5, 6, 8, 9, 11, 12}));
		assert(check_elements_data(v2c, {5, 6, 8, 9, 11, 12}));

		auto v1r = m1r.view(1, 2, 1, 3);
		static_assert(std::is_same_v<decltype(v1r(0, 0)), int&>);
		static_assert(std::is_same_v<decltype(v1r.data()), T*>);
		assert(check_elements(v1r, {6, 10, 7, 11, 8, 12}));
		assert(check_elements_data(v1r, {6, 10, 7, 11, 8, 12}));

		v1r(1, 1) = 13;
		assert(m1r(2, 2) == 13);
	}
};

template<typename T>
struct Block_view_lvalue_const
{
	auto name()
	{
		return "Block view const-correctness";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 3> m1;
		const es_la::Matrix<T, 3, 3> m1c{};

		auto v1 = m1.view(0, 1, 0, 1);
		auto v1c = m1c.view(0, 1, 0, 1);
		static_assert(std::is_same_v<decltype(v1(0, 0)), T&>);
		static_assert(std::is_same_v<decltype(v1c(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v1.data()), T*>);
		static_assert(std::is_same_v<decltype(v1c.data()), const T*>);

		const auto v2 = m1.view(0, 1, 0, 1);
		const auto v2c = m1c.view(0, 1, 0, 1);

		static_assert(std::is_same_v<decltype(v2(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v2c(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v2.data()), const T*>);
		static_assert(std::is_same_v<decltype(v2c.data()), const T*>);

		auto v3 = m1.cview(0, 1, 0, 1);
		auto v3c = m1c.cview(0, 1, 0, 1);
		static_assert(std::is_same_v<decltype(v3(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v3c(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v3.data()), const T*>);
		static_assert(std::is_same_v<decltype(v3c.data()), const T*>);

		const auto v4 = m1.cview(0, 1, 0, 1);
		const auto v4c = m1c.cview(0, 1, 0, 1);
		static_assert(std::is_same_v<decltype(v4(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v4c(0, 0)), const T&>);
		static_assert(std::is_same_v<decltype(v4.data()), const T*>);
		static_assert(std::is_same_v<decltype(v4c.data()), const T*>);
	}
};
