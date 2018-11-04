#pragma once
#include <es_la/tags.hpp>
#include <cstddef>
#include <type_traits>

namespace la
{

template<class T_Derived>
class Expression;

template<typename T_Value, std::size_t t_rows, std::size_t t_cols, class Layout = Col_major>
class Matrix;

namespace internal
{
template<class Ex, class Rows, class Cols, class Access_tag>
class Sub_expr;

template<std::size_t t_begin, std::size_t t_size>
class Range;

template<std::size_t t_size>
class Slice;

template<class TExpr, typename TScalar, class TFunc>
class Unary_expr;

template<class Left, class Right, template<class, class> class Func>
class Bin_expr;

template<class TLhs_expr, class TRhs_expr>
struct Mul_func;
}

//////////////////////////////////////////////////////////////////////////
// Type aliases

using Matrix_xd = Matrix<double, dynamic, dynamic>;
using Matrix_2d = Matrix<double, 2, 2>;
using Matrix_3d = Matrix<double, 3, 3>;

template<std::size_t t_rows, std::size_t t_cols>
using Matrix_d = Matrix<double, t_rows, t_cols>;

template<typename Value>
using Matrix_x = Matrix<Value, dynamic, dynamic>;

template<typename Value, std::size_t size>
using Vector = Matrix<Value, size, 1>;

using Vector_xd = Vector<double, dynamic>;
using Vector_2d = Vector<double, 2>;
using Vector_3d = Vector<double, 3>;

template<std::size_t size>
using Vector_d = Vector<double, size>;

template<typename Value>
using Vector_x = Matrix<Value, dynamic, 1>;
}

// namespace internal
// {
// template<std::size_t begin, std::size_t size>
// class Range;
// 
// template<std::size_t size>
// class Slice;
// 
// struct Read_only_tag { };
// struct Read_write_tag { };
// 
// template<class TRows, class TCols, class View_at, class Access_tag>
// class Block_view;
// 
// template<class TRows, class TCols, class View_at>
// using Block_view_t = Block_view<TRows, TCols, View_at,
// 	std::conditional_t<std::is_const_v<View_at>, Read_only_tag, Read_write_tag>>;
// 
// template<class Lhs_expr, class Rhs_expr>
// class Elementwise_op;
// 
// template<class Lhs_expr, class Rhs_expr, template<class, class> class Op>
// class Bin_expr;
// 
// template<class Base_expr, typename Scalar, template<class, typename> class Op>
// class Unary_expr;
// 
// //////////////////////////////////////////////////////////////////////////
// 
// template<std::size_t x, std::size_t y>
// constexpr bool ct_size_equal_v = (x == 0 || y == 0 || x == y);
// 
// template<std::size_t x, std::size_t y>
// constexpr bool ct_size_greater_v = (x == 0 || y == 0 || x > y);
// 
// template<std::size_t x, std::size_t y>
// constexpr bool ct_size_greater_equal_v = ct_size_equal_v<x, y> || ct_size_greater_v<x, y>;
// 
// template<std::size_t x, std::size_t y>
// constexpr std::size_t first_nonzero_v = (x > 0) ? x : y;
// }
// }