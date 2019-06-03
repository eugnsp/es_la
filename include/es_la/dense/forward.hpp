#pragma once
#include <es_la/dense/tags.hpp>

#include <cstddef>

namespace es_la
{
template<class Expr>
class Expression;

template<class Expr, class Category>
class Dense;

template<typename Value, std::size_t ct_rows, std::size_t ct_cols, class Layout = Col_major>
class Matrix;

template<class Expr, class Rows, class Cols, class Category>
class View;

template<class Expr, class Category>
class Transposed_view;

using Matrix_xd = Matrix<double, dynamic, dynamic>;
using Matrix_2d = Matrix<double, 2, 2>;
using Matrix_3d = Matrix<double, 3, 3>;

template<std::size_t t_rows, std::size_t t_cols>
using Matrix_d = Matrix<double, t_rows, t_cols>;

template<typename Value, class Layout = Col_major>
using Matrix_x = Matrix<Value, dynamic, dynamic, Layout>;

template<typename Value, std::size_t size>
using Vector = Matrix<Value, size, 1>;

using Vector_xd = Vector<double, dynamic>;
using Vector_2d = Vector<double, 2>;
using Vector_3d = Vector<double, 3>;

template<std::size_t size>
using Vector_d = Vector<double, size>;

template<typename Value>
using Vector_x = Matrix<Value, dynamic, 1>;

template<class Expr, typename Scalar, class Fn>
class Scalar_expr;

template<class Expr1, class Expr2, template<class, class> class Fn>
class Binary_expr;

template<class Random_distribution, class Random_generator>
class Random_matrix;

namespace internal
{
template<std::size_t ct_start, std::size_t ct_size>
class Range;

template<std::size_t t_size>
class Slice;

template<class Expr1, class Expr2>
struct Mul_func;

struct Default_assign_scalar_op;
struct Default_assign_expr_op;

struct Mkl_matrix_assign_op;
struct Mkl_matrix_assign_op2;

template<class Expr, typename Scalar>
class Scalar_mul_left_fn;
} // namespace internal
} // namespace es_la
