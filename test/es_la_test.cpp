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
