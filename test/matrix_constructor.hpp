#pragma once
#include "check_elements.hpp"

#include <es_la/dense.hpp>

#include <cassert>
#include <cstddef>
#include <utility>

template<typename T>
struct Matrix_constructor_default
{
	auto name()
	{
		return "Matrix default constructors";
	}

	void operator()()
	{
		es_la::Matrix<T, 2, 3> m1;
		static_assert(m1.rows() == 2 && m1.cols() == 3);
		static_assert(m1.size() == 6);
		static_assert(m1.capacity() == 6);

		const es_la::Matrix<T, 2, 3> m1c{};
		static_assert(m1c.rows() == 2 && m1c.cols() == 3);
		static_assert(m1c.size() == 6);

		es_la::Matrix<T, 4, es_la::dynamic> m2;
		assert(m2.rows() == 4 && m2.cols() == 0);
		assert(m2.size() == 0);

		es_la::Matrix<T, es_la::dynamic, 5> m3;
		assert(m3.rows() == 0 && m3.cols() == 5);
		assert(m3.size() == 0);

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m4;
		assert(m4.rows() == 0 && m4.cols() == 0);
		assert(m4.size() == 0);

		const es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m4c;
		assert(m4c.rows() == 0 && m4c.cols() == 0);
		assert(m4c.size() == 0);
	}
};

template<typename T>
struct Matrix_constructor_size
{
	auto name()
	{
		return "Matrix constructors (size)";
	}

	void operator()()
	{
		es_la::Matrix<T, 2, es_la::dynamic> m1(3);
		assert(m1.rows() == 2 && m1.cols() == 3 && m1.size() == 6);
		assert(m1.capacity() >= 6);

		es_la::Matrix<T, es_la::dynamic, 2> m2(3);
		assert(m2.rows() == 3 && m2.cols() == 2 && m2.size() == 6);
		assert(m2.capacity() >= 6);

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m3(3, 4);
		assert(m3.rows() == 3 && m3.cols() == 4 && m3.size() == 12);
		assert(m3.capacity() >= 12);
	}
};

template<typename T>
struct Matrix_constructor_values
{
	auto name()
	{
		return "Matrix constructors (values)";
	}

	void operator()()
	{
		es_la::Matrix<T, 2, 2> m1(123);
		assert(check_elements(m1, {123, 123, 123, 123}));

		es_la::Matrix<T, 2, es_la::dynamic> m2(2, 123);
		assert(check_elements(m2, {123, 123, 123, 123}));

		es_la::Matrix<T, es_la::dynamic, 2> m3(2, 123);
		assert(check_elements(m3, {123, 123, 123, 123}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m4(2, 2, 123);
		assert(check_elements(m4, {123, 123, 123, 123}));

		es_la::Matrix<T, 2, 2, es_la::Col_major> m5c{1, 2, 3, 4};
		assert(check_elements(m5c, {1, 2, 3, 4}));

		es_la::Matrix<T, 2, 2, es_la::Row_major> m5r{1, 2, 3, 4};
	 	assert(check_elements(m5r, {1, 3, 2, 4}));

		es_la::Matrix<T, 2, es_la::dynamic, es_la::Col_major> m6c(2, {1, 2, 3, 4});
	 	assert(check_elements(m6c, {1, 2, 3, 4}));

		es_la::Matrix<T, 2, es_la::dynamic, es_la::Row_major> m6r(2, {1, 2, 3, 4});
	 	assert(check_elements(m6r, {1, 3, 2, 4}));

		es_la::Matrix<T, es_la::dynamic, 2, es_la::Col_major> m7c(2, {1, 2, 3, 4});
		assert(check_elements(m7c, {1, 2, 3, 4}));

		es_la::Matrix<T, es_la::dynamic, 2, es_la::Row_major> m7r(2, {1, 2, 3, 4});
	 	assert(check_elements(m7r, {1, 3, 2, 4}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, es_la::Col_major> m8c(2, 2, {1, 2, 3, 4});
		assert(check_elements(m8c, {1, 2, 3, 4}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, es_la::Row_major> m8r(2, 2, {1, 2, 3, 4});
	 	assert(check_elements(m8r, {1, 3, 2, 4}));
	}
};

template<typename T>
struct Matrix_constructor_init_list
{
	auto name()
	{
		return "Matrix constructors (initializer_list)";
	}

	void operator()()
	{
		es_la::Matrix<T, 2, 2, es_la::Col_major> m1c{1, 2, 3, 4};
		assert(check_elements(m1c, {1, 2, 3, 4}));

		es_la::Matrix<T, 2, 2, es_la::Row_major> m1r{1, 2, 3, 4};
	 	assert(check_elements(m1r, {1, 3, 2, 4}));

		// es_la::Matrix<T, 2, es_la::dynamic, es_la::Col_major> m6c(2, {1, 2, 3, 4});
	 	// assert(check_elements(m6c, {1, 2, 3, 4}));

		// es_la::Matrix<T, 2, es_la::dynamic, es_la::Row_major> m6r(2, {1, 2, 3, 4});
	 	// assert(check_elements(m6r, {1, 3, 2, 4}));

		// es_la::Matrix<T, es_la::dynamic, 2, es_la::Col_major> m7c(2, {1, 2, 3, 4});
		// assert(check_elements(m7c, {1, 2, 3, 4}));

		// es_la::Matrix<T, es_la::dynamic, 2, es_la::Row_major> m7r(2, {1, 2, 3, 4});
	 	// assert(check_elements(m7r, {1, 3, 2, 4}));

		// es_la::Matrix<T, es_la::dynamic, es_la::dynamic, es_la::Col_major> m8c(2, 2, {1, 2, 3, 4});
		// assert(check_elements(m8c, {1, 2, 3, 4}));

		// es_la::Matrix<T, es_la::dynamic, es_la::dynamic, es_la::Row_major> m8r(2, 2, {1, 2, 3, 4});
	 	// assert(check_elements(m8r, {1, 3, 2, 4}));
	}
};

template<typename T>
struct Matrix_constructor_copy
{
	auto name()
	{
		return "Matrix copy constructors";
	}

	void operator()()
	{
		es_la::Matrix<T, 2, 2> m1{1, 2, 3, 4};
		es_la::Matrix<T, 2, 2> m1c(m1);
	 	assert(check_elements(m1c, {1, 2, 3, 4}));

		es_la::Matrix<T, 2, es_la::dynamic> m2(2, {1, 2, 3, 4});
		es_la::Matrix<T, 2, es_la::dynamic> m2c(m2);
	 	assert(check_elements(m2c, {1, 2, 3, 4}));

		es_la::Matrix<T, es_la::dynamic, 2> m3(2, {1, 2, 3, 4});
		es_la::Matrix<T, es_la::dynamic, 2> m3c(m3);
	 	assert(check_elements(m3c, {1, 2, 3, 4}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m4(2, 2, {1, 2, 3, 4});
		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m4c(m4);
	 	assert(check_elements(m4c, {1, 2, 3, 4}));
	}
};

template<typename T>
struct Matrix_constructor_move
{
	auto name()
	{
		return "Matrix move constructors";
	}

	void operator()()
	{
	 	es_la::Matrix<T, 2, es_la::dynamic> m1(2, {1, 2, 3, 4});
	 	auto d1 = m1.data();
	 	es_la::Matrix<T, 2, es_la::dynamic> m1m(std::move(m1));
	 	assert(m1.data() == nullptr && m1m.data() == d1);
	 	assert(check_elements(m1m, {1, 2, 3, 4}));

	 	es_la::Matrix<T, es_la::dynamic, 2> m2(2, {1, 2, 3, 4});
	 	auto d2 = m2.data();
	 	es_la::Matrix<T, es_la::dynamic, 2> m2m(std::move(m2));
	 	assert(m2.data() == nullptr && m2m.data() == d2);
		assert(check_elements(m2m, {1, 2, 3, 4}));

	 	es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m3(2, 2, {1, 2, 3, 4});
	 	auto d3 = m3.data();
	 	es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m3m(std::move(m3));
	 	assert(m3.data() == nullptr && m3m.data() == d3);
	 	assert(check_elements(m3m, {1, 2, 3, 4}));
	}
};

template<typename T>
struct Matrix_constructor_expr
{
	auto name()
	{
		return "Matrix construction from expressions";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 3> m1{1, 2, 3, 4, 5, 6, 7, 8, 9};

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m2(m1);
		assert(m2.rows() == 3 && m2.cols() == 3);
		assert(check_elements(m2, {1, 2, 3, 4, 5, 6, 7, 8, 9}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m3(m1 + m1);
		assert(m3.rows() == 3 && m3.cols() == 3);
		assert(check_elements(m3, {2, 4, 6, 8, 10, 12, 14, 16, 18}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> m4(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
		es_la::Matrix<T, 3, 3> m5(m4);
		assert(check_elements(m5, {1, 2, 3, 4, 5, 6, 7, 8, 9}));

		es_la::Matrix<T, 3, 3> m6(m4 + m4);
		assert(check_elements(m6, {2, 4, 6, 8, 10, 12, 14, 16, 18}));
	}
};

template<typename T>
struct Matrix_deduction_guides
{
	auto name()
	{
		return "Matrix deduction guides";
	}

	void operator()()
	{
		es_la::Matrix<T, 3, 3> m1{1, 2, 3, 4, 5, 6, 7, 8, 9};
		es_la::Matrix m2(2 * m1);
		static_assert(std::is_same_v<es_la::Value_type<decltype(m2)>, T>);
		static_assert(m2.rows() == 3 && m2.rows() == 3);
		assert(check_elements(m2, {2, 4, 6, 8, 10, 12, 14, 16, 18}));

		es_la::Matrix<T, 3, 3> m3{1, 2, 3, 4, 5, 6, 7, 8, 9};
		es_la::Matrix m4(2 * m3);
		static_assert(std::is_same_v<es_la::Value_type<decltype(m4)>, T>);
		assert(m4.rows() == 3 && m4.rows() == 3);
		assert(check_elements(m4, {2, 4, 6, 8, 10, 12, 14, 16, 18}));
	}
};
