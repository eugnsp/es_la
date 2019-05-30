#ifdef NDEBUG
	#undef NDEBUG
#endif

#include <iostream>

#include "type_string.hpp"
#include "non_trivial.hpp"

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

int main()
{

int a[2] = {1,2};

auto [x,y] = a; // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]
//auto& [xr, yr] = a;

std::cout << type_string<decltype(x)>() << std::endl;

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
		run<Matrix_constructor_size_values, int>();
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

		// es_la::Vector_xd v1(10, 1), v2(10, 2), v3(10);

		// es_la::Csr_matrix<double> m1;
		// es_la::Mkl_sparse_matrix_ext mat(m1);

		//v1 = mat * v2;

		// v1 = 3 * v2;
		// v1 += v2;
		// v1 += 5 * v2;

		// auto z = (v1 + v2).view(0, 1, 0, 1);

		es_la::Matrix<int, (std::size_t)2, (std::size_t)2> m1({1, 2, 3, 4});
		es_la::Matrix<int, (std::size_t)2, (std::size_t)2> m2({5, 6, 7, 8});
		es_la::Matrix<int, es_la::dynamic, es_la::dynamic> m3;
		es_la::Matrix<int, es_la::dynamic, es_la::dynamic>& m4 = m3;
		m3 = m1 + m2;
		m3 = 0;

		m3 = m4;

		// auto z1 = m1.rows_view(0, 2).cols_view<0, 2>();
		// auto z2 = m1.row_view(0).col_view<2>();

		//std::cout << type_string<decltype(z1)>() << std::endl;
		// auto y1 = z1.view(0, 1, 0, 1);
		// std::cout << "z1: " << type_string<decltype(z1)>() << std::endl;
		// std::cout << "y1: " << type_string<decltype(y1)>() << std::endl;

		// m1 *= 2;

		// const es_la::Matrix<int, 3, 3> m2;
		// auto z2 = m2.view(0, 2, 0, 2);
		// auto y2 = z2.view(0, 1, 0, 1);
		// std::cout << "z2: " << type_string<decltype(z2)>() << std::endl;
		// std::cout << "y2: " << type_string<decltype(y2)>() << std::endl;

		// std::cout << z1(0, 0);
		// z1 *= 5;
		// m1 += z1;
		// z1 += m1;
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
