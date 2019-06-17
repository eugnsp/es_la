#pragma once
#include "check_elements.hpp"

#include <es_la/dense.hpp>

#include <cassert>
#include <cstddef>
#include <utility>
#include <functional>

template<typename T>
struct Matrix_default_construction
{
	auto name()
	{
		return "Matrix default construction: Matrix<...> m;";
	}

	void operator()()
	{
		op<1, 1>();
		op<2, 3>();
		op<10, 11>();
	}

	template<std::size_t rows, std::size_t cols>
	void op()
	{
		op_static<rows, cols, es_la::Row_major>();
		op_static<rows, cols, es_la::Col_major>();

		op_static<rows, cols, es_la::Row_major>();
		op_static<rows, cols, es_la::Col_major>();
	}

	template<std::size_t rows, std::size_t cols, class Layout>
	void op_static()
	{
		es_la::Matrix<T, rows, cols, Layout> m;
		static_assert(m.rows() == rows);
		static_assert(m.cols() == cols);
		static_assert(m.size() == rows * cols);
		static_assert(m.capacity() == rows * cols);
	}

	template<std::size_t rows, std::size_t cols, class Layout>
	void op_dynamic()
	{
		es_la::Matrix<T, rows, es_la::dynamic, Layout> msd;
		assert(msd.rows() == rows);
		assert(msd.cols() == 0);
		assert(msd.size() == 0);

		es_la::Matrix<T, es_la::dynamic, cols, Layout> mds;
		assert(mds.rows() == 0);
		assert(mds.cols() == cols);
		assert(mds.size() == 0);

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, Layout> mdd;
		assert(mdd.rows() == 0);
		assert(mdd.cols() == 0);
		assert(mdd.size() == 0);

		const es_la::Matrix<T, es_la::dynamic, es_la::dynamic> mddc;
		assert(mddc.rows() == 0);
		assert(mddc.cols() == 0);
		assert(mddc.size() == 0);
	}
};

template<typename T>
struct Matrix_value_construction
{
	auto name()
	{
		return "Matrix value construction: Matrix<...> m{};";
	}

	void operator()()
	{
		op<1, 1>();
		op<2, 3>();
		op<10, 11>();
	}

	template<std::size_t rows, std::size_t cols>
	void op()
	{
		op2<rows, cols, es_la::Row_major>();
		op2<rows, cols, es_la::Col_major>();

		op2<rows, cols, es_la::Row_major>();
		op2<rows, cols, es_la::Col_major>();
	}

	template<std::size_t rows, std::size_t cols, class Layout>
	void op2()
	{
		es_la::Matrix<T, rows, cols, Layout> mv{};
		static_assert(mv.rows() == rows);
		static_assert(mv.cols() == cols);
		static_assert(mv.size() == rows * cols);
		static_assert(mv.capacity() == rows * cols);
		check_elements(mv, 0);

		const es_la::Matrix<T, rows, cols, Layout> mc{};
		static_assert(mc.rows() == rows);
		static_assert(mc.cols() == cols);
		static_assert(mc.size() == rows * cols);
		check_elements(mc, 0);
	}
};

template<typename T>
struct Matrix_construction_size
{
	auto name()
	{
		return "Matrix construction: Matrix<...> m(<size>);";
	}

	void operator()()
	{
		op<1, 1>();
		op<2, 3>();
		op<10, 11>();
	}

	template<std::size_t rows, std::size_t cols>
	void op()
	{
		op2<rows, cols, es_la::Row_major>();
		op2<rows, cols, es_la::Col_major>();
	}

	template<std::size_t rows, std::size_t cols, class Layout>
	void op2()
	{
		es_la::Matrix<T, rows, es_la::dynamic, Layout> msd(cols);
		assert(msd.rows() == rows);
		assert(msd.cols() == cols);
		assert(msd.size() == rows * cols);
		assert(msd.capacity() >= rows * cols);

		es_la::Matrix<T, es_la::dynamic, cols, Layout> mds(rows);
		assert(mds.rows() == rows);
		assert(mds.cols() == cols);
		assert(mds.size() == rows * cols);
		assert(mds.capacity() >= rows * cols);

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, Layout> mdd(rows, cols);
		assert(mdd.rows() == rows);
		assert(mdd.cols() == cols);
		assert(mdd.size() == rows * cols);
		assert(mdd.capacity() >= rows * cols);
	}
};

template<typename T>
struct Matrix_construction_value
{
	auto name()
	{
		return "Matrix construction: Matrix<...> m([<size>,] value);";
	}

	void operator()()
	{
		op<1, 1>(11);
		op<2, 2>(12);
		op<2, 3>(13);
		op<10, 11>(14);
	}

	template<std::size_t rows, std::size_t cols>
	void op(T value)
	{
		op2<rows, cols, es_la::Row_major>(value);
		op2<rows, cols, es_la::Col_major>(value);
	}

	template<std::size_t rows, std::size_t cols, class Layout>
	void op2(T value)
	{
		es_la::Matrix<T, rows, cols> mss(value);
		assert(check_elements(mss, value));

		es_la::Matrix<T, rows, es_la::dynamic> msd(cols, value);
		assert(check_elements(msd, value));

		es_la::Matrix<T, es_la::dynamic, cols> mds(rows, value);
		assert(check_elements(mds, value));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> mdd(rows, cols, value);
		assert(check_elements(mdd, value));
	}
};

template<typename T>
struct Matrix_construction_values
{
	auto name()
	{
		return "Matrix construction: Matrix<...> m(values...);";
	}

	void operator()()
	{
		op<1, 1>(1);
		op<2, 2>(1, 2, 3, 4);
		op<2, 3>(1, 2, 3, 4, 5, 6);
		op<3, 2>(1, 2, 3, 4, 5, 6);
	}

	template<std::size_t rows, std::size_t cols, typename... Ts>
	void op(Ts... list)
	{
		op2<rows, cols, es_la::Col_major>(list...);
		op2<rows, cols, es_la::Row_major>(list...);
	}

	template<std::size_t rows, std::size_t cols, class Layout, typename... Ts>
	void op2(Ts... list)
	{
		es_la::Matrix<T, rows, cols, Layout> mss{list...};
		assert(check_matrix_elements(mss, {list...}));
	}
};

template<typename T>
struct Matrix_construction_init_list
{
	auto name()
	{
		return "Matrix construction: Matrix<...> m(<size>, {values...});";
	}

	void operator()()
	{
		op<1, 1>(1);
		op<2, 2>(1, 2, 3, 4);
		op<2, 3>(1, 2, 3, 4, 5, 6);
		op<3, 2>(1, 2, 3, 4, 5, 6);
	}

	template<std::size_t rows, std::size_t cols, typename... Ts>
	void op(Ts... list)
	{
		op2<rows, cols, es_la::Col_major>(list...);
		op2<rows, cols, es_la::Row_major>(list...);
	}

	template<std::size_t rows, std::size_t cols, class Layout, typename... Ts>
	void op2(Ts... list)
	{
		es_la::Matrix<T, rows, es_la::dynamic, Layout> msd(cols, {list...});
		assert(check_matrix_elements(msd, {list...}));

		es_la::Matrix<T, rows, es_la::dynamic, Layout> msd2({list...});
		assert(check_matrix_elements(msd2, {list...}));

		es_la::Matrix<T, es_la::dynamic, cols, Layout> mds(rows, {list...});
		assert(check_matrix_elements(mds, {list...}));

		es_la::Matrix<T, es_la::dynamic, cols, Layout> mds2({list...});
		assert(check_matrix_elements(mds2, {list...}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, Layout> mdd(rows, cols, {list...});
		assert(check_matrix_elements(mdd, {list...}));
	}
};

template<typename T>
struct Matrix_copy_construction
{
	auto name()
	{
		return "Matrix copy construction";
	}

	void operator()()
	{
		op<2, 2>(1, 2, 3, 4);
		op<2, 3>(1, 2, 3, 4, 5, 6);
		op<3, 2>(1, 2, 3, 4, 5, 6);
	}

	template<std::size_t rows, std::size_t cols, typename... Ts>
	void op(Ts... list)
	{
		op2<rows, cols, es_la::Col_major>(list...);
		op2<rows, cols, es_la::Row_major>(list...);
	}

	template<std::size_t rows, std::size_t cols, class Layout, typename... Ts>
	void op2(Ts... list)
	{
		es_la::Matrix<T, rows, cols, Layout> mss{list...};
		es_la::Matrix<T, rows, cols, Layout> mssc(mss);
		assert(check_matrix_elements(mssc, {list...}));

		es_la::Matrix<T, rows, es_la::dynamic, Layout> msd(cols, {list...});
		es_la::Matrix<T, rows, es_la::dynamic, Layout> msdc(msd);
		assert(check_matrix_elements(msdc, {list...}));

		es_la::Matrix<T, es_la::dynamic, cols, Layout> mds(rows, {list...});
		es_la::Matrix<T, es_la::dynamic, cols, Layout> mdsc(mds);
		assert(check_matrix_elements(mdsc, {list...}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, Layout> mdd(rows, cols, {list...});
		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, Layout> mddc(mdd);
		assert(check_matrix_elements(mddc, {list...}));
	}
};

template<typename T>
struct Matrix_move_construction
{
	auto name()
	{
		return "Matrix move construction";
	}

	void operator()()
	{
		op<2, 2>(1, 2, 3, 4);
		op<2, 3>(1, 2, 3, 4, 5, 6);
		op<3, 2>(1, 2, 3, 4, 5, 6);
	}

	template<std::size_t rows, std::size_t cols, typename... Ts>
	void op(Ts... list)
	{
		op2<rows, cols, es_la::Col_major>(list...);
		op2<rows, cols, es_la::Row_major>(list...);
	}

	template<std::size_t rows, std::size_t cols, class Layout, typename... Ts>
	void op2(Ts... list)
	{
		es_la::Matrix<T, rows, es_la::dynamic> msd(cols, {list...});
		auto dsd = msd.data();
		es_la::Matrix<T, rows, es_la::dynamic> msdm(std::move(msd));
		assert(msd.data() == nullptr);
		assert(msdm.data() == dsd);
		assert(check_matrix_elements(msdm, {list...}));

		es_la::Matrix<T, es_la::dynamic, cols> mds(rows, {list...});
		auto dds = mds.data();
		es_la::Matrix<T, es_la::dynamic, cols> mdsm(std::move(mds));
		assert(mds.data() == nullptr);
		assert(mdsm.data() == dds);
		assert(check_matrix_elements(mdsm, {list...}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> mdd(rows, cols, {list...});
		auto ddd = mdd.data();
		es_la::Matrix<T, es_la::dynamic, es_la::dynamic> mddm(std::move(mdd));
		assert(mdd.data() == nullptr);
		assert(mddm.data() == ddd);
		assert(check_matrix_elements(mddm, {list...}));
	}
};

template<typename T>
struct Matrix_construction_expr
{
	auto name()
	{
		return "Matrix construction: Matrix<...> m(<expression>);";
	}

	void operator()()
	{
		op<2, 2>(1, 2, 3, 4);
		op<2, 3>(1, 2, 3, 4, 5, 6);
		op<3, 2>(1, 2, 3, 4, 5, 6);
	}

	template<std::size_t rows, std::size_t cols, typename... Ts>
	void op(Ts... list)
	{
		op2<rows, cols, es_la::Col_major>(std::plus<>{}, 3, 5, list...);
		op2<rows, cols, es_la::Row_major>(std::plus<>{}, 3, 5, list...);

		op2<rows, cols, es_la::Col_major>(std::minus<>{}, 3, 5, list...);
		op2<rows, cols, es_la::Row_major>(std::minus<>{}, 3, 5, list...);
	}

	template<std::size_t rows, std::size_t cols, class Layout, class Fn, typename A, typename B, typename... Ts>
	void op2(Fn fn, A a, B b, Ts... list)
	{
		const es_la::Matrix<T, rows, cols, Layout> m1{(a * list)...};
		const es_la::Matrix<T, rows, cols, Layout> m2{(b * list)...};

		const auto expr = fn(m1, m2);
		const auto ab = fn(a, b);

		es_la::Matrix<T, rows, cols, Layout> mss(expr);
		assert(check_matrix_elements(mss, {(ab * list)...}));

		es_la::Matrix<T, rows, es_la::dynamic, Layout> msd(expr);
		assert(msd.rows() == rows);
		assert(msd.cols() == cols);
		assert(check_matrix_elements(msd, {(ab * list)...}));

		es_la::Matrix<T, es_la::dynamic, cols, Layout> mds(expr);
		assert(mds.rows() == rows);
		assert(mds.cols() == cols);
		assert(check_matrix_elements(mds, {(ab * list)...}));

		es_la::Matrix<T, es_la::dynamic, es_la::dynamic, Layout> mdd(expr);
		assert(mdd.rows() == rows);
		assert(mdd.cols() == cols);
		assert(check_matrix_elements(mdd, {(ab * list)...}));
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
