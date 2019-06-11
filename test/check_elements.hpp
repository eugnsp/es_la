#pragma once
#include <cstddef>
#include <initializer_list>

template<class Expr, typename T>
bool check_elements(const Expr& expr, std::initializer_list<T> list)
{
	auto it = list.begin();
	for (std::size_t col = 0; col < expr.cols(); ++col)
		for (std::size_t row = 0; row < expr.rows(); ++row)
			if (it == list.end() || expr(row, col) != *it++)
				return false;

	return it == list.end();
}

template<class Expr, typename T>
bool check_elements_data(const Expr& expr, std::initializer_list<T> list)
{
	auto it = list.begin();
	auto ptr_c = expr.data();
	for (std::size_t col = 0; col < expr.cols(); ++col)
	{
		auto ptr_r = ptr_c;
		for (std::size_t row = 0; row < expr.rows(); ++row)
		{
			if (it == list.end() || *ptr_r != *it)
				return false;
			ptr_r += expr.row_stride();
			++it;
		}
		ptr_c += expr.col_stride();
	}

	return it == list.end();
}
