#pragma once
#include <cstddef>
#include <utility>

namespace es_la
{
namespace internal
{
struct Internal
{};

// Dynamic extent
struct Dynamic : std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>
{};

///////////////////////////////////////////////////////////////////////
//* Expression tags */

template<typename Value>
struct Lvalue_block_tag
{};

struct Fn_mul_tag
{};

template<class Expr, typename Scalar, class Fn>
struct Scalar_expr_tag
{};

template<class Expr1, class Expr2, class Fn>
struct Binary_expr_tag
{};
} // namespace internal

// Dynamic extent
inline constexpr auto dynamic = internal::Dynamic::value;

//////////////////////////////////////////////////////////////////////
//* Value categories of expressions */

struct Rvalue
{};

struct Lvalue
{};

//////////////////////////////////////////////////////////////////////
//* Expressions symmetry tags */

struct Not_symmetric
{};

struct Structural_symmetric
{};

struct Symmetric_upper
{};

struct Symmetric_lower
{};
// struct Hermitian
// {};

//////////////////////////////////////////////////////////////////////
//* Dense matrix memory layouts */

struct Col_major
{};

struct Row_major
{};

///////////////////////////////////////////////////////////////////////
//* Matrix operations */

struct No_transpose
{};

struct Transpose
{};

struct Conj_transpose
{};
} // namespace es_la
