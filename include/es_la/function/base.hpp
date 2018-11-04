#pragma once
#include <array>
#include <cstddef>
#include <type_traits>

namespace la
{
// template<class TLhs_expr, class TRhs_expr>
// inline bool operator==(const TLhs_expr& lhs, const TRhs_expr& rhs)
// {
// 	if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
// 		return false;
// 
// 	for (std::size_t col = 0; col < lhs.cols(); ++col)
// 		for (std::size_t row = 0; row < lhs.rows(); ++row)
// 			if (lhs(row, col) != rhs(row, col))
// 				return false;
// 
// 	return true;
// }

//template<std::size_t t_rows, std::size_t t_cols, class T_Func>
//constexpr auto make_matrix(T_Func func)
//{
//	using Value = std::result_of_t<T_Func&(std::size_t, std::size_t)>;
//
//	std::array<Value, t_rows * t_cols> values{};
//	for (std::size_t row = 0; row < t_rows; ++row)
//		for (std::size_t col = 0; col < t_cols; ++col)
//			values[row + col * t_rows] = func(row, col);
//
//	return Matrix<Value, t_rows, t_cols>{values};
//}
}
