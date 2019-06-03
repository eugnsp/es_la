#ifdef NDEBUG
	#undef NDEBUG
#endif

#include <iostream>

#include "non_trivial.hpp"
#include "type_string.hpp"

#include "matrix_constructor.hpp"
#include "matrix_view.hpp"
#include "type_traits.hpp"

#include <es_la/dense.hpp>
#include <es_la/sparse.hpp>

template<template<class T> class Test, typename S>
void run()
{
	Test<S> test;
	std::cout << type_string<S>() << " : " << test.name() << "... " << std::flush;
	test();
	std::cout << "OK" << std::endl;
}

template<class T>
void print(const T& mat)
{
	for (std::size_t row = 0; row < mat.rows(); ++row)
	{
		for (std::size_t col = 0; col < mat.cols(); ++col)
			std::cout << mat(row, col) << ' ';
		std::cout << std::endl;
	}
}

int main()
{
	::mkl_verbose(1);

	try
	{
		///////////////////////////////////////////////////////////////////////
		//* Type traits */

		run<Type_trait_is_dense, int>();

		///////////////////////////////////////////////////////////////////////
		//* Matrix class constructors */

		run<Matrix_constructor_default, int>();
		run<Matrix_constructor_default, Non_trivial>();
		run<Matrix_constructor_size, int>();
		run<Matrix_constructor_size, Non_trivial>();
		run<Matrix_constructor_values, int>();
		run<Matrix_constructor_init_list, int>();
		run<Matrix_constructor_copy, int>();
		run<Matrix_constructor_copy, Non_trivial>();
		run<Matrix_constructor_move, int>();
		run<Matrix_constructor_move, Non_trivial>();
		run<Matrix_constructor_expr, int>();
		run<Matrix_deduction_guides, int>();

		///////////////////////////////////////////////////////////////////////
		//* Views */

		run<Block_view_lvalue_copy_constructor, int>();
		run<Block_view_lvalue_size, int>();
		run<Block_view_lvalue_data, int>();
		run<Block_view_lvalue_const, int>();

		///////////////////////////////////////////////////////////////////////
		//* Binary expressions */

		auto m1 = es_la::make_matrix<es_la::Row_major>(2, 3, [](auto i, auto j) { return 1. + i + j; });
		print(m1);
		std::cout << std::endl;

		es_la::Matrix_x<double> m2(5, 6, 0);
		// es_la::Matrix_x<std::complex<double>, es_la::Row_major> m3(5, 6, 0);

		// es_la::Matrix_x<std::complex<double>> m4(6, 5, 0);
		// es_la::Matrix_x<std::complex<double>, es_la::Row_major> m5(6, 5, 0);

		m2.view(1, 2, 1, 3) = 5 * m1;
		print(m2);
		std::cout << std::endl;

		// m4.view(1, 2, 1, 3).tr_view() = m1.tr_view();
		// print(m4);
		// std::cout << std::endl;

		// m3.view(1, 3, 1, 2).tr_view() = m1;
		// print(m3);
		// std::cout << std::endl;

		// m5.view(1, 2, 1, 3).tr_view() = m1.tr_view();
		// print(m5);
		// std::cout << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
		return -1;
	}
	catch (...)
	{
		std::cout << "Exception!\n";
		return -1;
	}

	std::cout << "All OK." << std::endl;
	return 0;
}
