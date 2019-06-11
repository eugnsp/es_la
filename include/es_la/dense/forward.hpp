#pragma once
#include <es_la/dense/tags.hpp>

#include <cstddef>

namespace es_la
{
template<class Expr>
class Expression;

template<class Expr, class Category>
class Dense;

template<typename Value, std::size_t rows, std::size_t cols, class Layout = Col_major>
class Matrix;

template<class Expr, class Rows, class Cols, class Category>
class View;

template<class Expr, class Category>
class Transposed_view;

template<class Expr, class Category>
class Diag_view;

using Matrix_xd = Matrix<double, dynamic, dynamic>;
using Matrix_2d = Matrix<double, 2, 2>;
using Matrix_3d = Matrix<double, 3, 3>;

template<std::size_t rows, std::size_t cols, class Layout = Col_major>
using Matrix_d = Matrix<double, rows, cols, Layout>;

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

template<class Expr, typename Scalar, template<class, typename> class Fn>
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
class Mul_fn;

template<class Expr, typename Scalar>
class Scalar_mul_left_fn;

template<class Expr, typename Scalar>
class Scalar_mul_right_fn;
} // namespace internal
} // namespace es_la
