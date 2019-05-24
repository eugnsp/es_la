#pragma once
#include <es_la/dense/tags.hpp>

#include <cstddef>

namespace es_la
{
template<class Expr>
class Expression;

template<class Expr, class Category>
class Dense;

template<typename Value, auto ct_rows, auto ct_cols, class Layout = Col_major>
class Matrix;

template<class Expr, class Rows, class Cols, class Category>
class View;

template<class Expr, class Category>
class Transposed_view;

using Matrix_xd = Matrix<double, dynamic, dynamic>;
using Matrix_2d = Matrix<double, std::size_t{2}, std::size_t{2}>;
using Matrix_3d = Matrix<double, std::size_t{3}, std::size_t{3}>;

template<auto t_rows, auto t_cols>
using Matrix_d = Matrix<double, t_rows, t_cols>;

template<typename Value>
using Matrix_x = Matrix<Value, dynamic, dynamic>;

template<typename Value, auto size>
using Vector = Matrix<Value, size, std::size_t{1}>;

using Vector_xd = Vector<double, dynamic>;
using Vector_2d = Vector<double, std::size_t{2}>;
using Vector_3d = Vector<double, std::size_t{3}>;

template<auto size>
using Vector_d = Vector<double, size>;

template<typename Value>
using Vector_x = Matrix<Value, dynamic, std::size_t{1}>;

template<class Expr, typename Scalar, class Fn>
class Scalar_expr;

template<class Expr1, class Expr2, template<class, class> class Fn>
class Binary_expr;

template<class Random_distribution, class Random_generator>
class Random_matrix;

namespace internal
{
template<auto ct_start, auto ct_size>
class Range;

template<std::size_t t_size>
class Slice;

template<class Expr1, class Expr2>
struct Mul_func;

template<class Expr1, class Expr2>
struct Default_assign_scalar_op;

template<class Expr1, class Expr2>
struct Default_assign_expr_op;
} // namespace internal
} // namespace es_la
