#pragma once
#include <es_la/base/type_traits.hpp>
#include <es_la/base/expression.hpp>
#include "functor.hpp"
#include <type_traits>

namespace es_la
{
namespace internal
{
template<class TExpr, typename TScalar, class TFunc>
class Unary_expr : public Expression<Unary_expr<TExpr, TScalar, TFunc>>
{
private:
	using Base = Expression<Unary_expr>;

public:
	Unary_expr(const TExpr&, const TScalar&);

	std::size_t rows() const;
	std::size_t cols() const;

	typename Base::Value operator()(std::size_t row, std::size_t col) const;

private:
	TScalar scalar_;
	Expr_storage_t<const TExpr> expr_;
};
} // namespace internal

//////////////////////////////////////////////////////////////////////////

template<class TExpr, typename TScalar, typename = std::enable_if_t<!internal::is_matrix<TScalar>>>
auto operator*(const Expression<TExpr>& expr, const TScalar& scalar)
{
	return internal::Unary_expr<TExpr, TScalar, internal::Scalar_mul_func<TExpr, TScalar>>{
		expr.self(), scalar};
}

template<class TExpr, typename TScalar, typename = std::enable_if_t<!internal::is_matrix<TScalar>>>
auto operator*(const TScalar& scalar, const Expression<TExpr>& expr)
{
	return internal::Unary_expr<TExpr, TScalar, internal::Scalar_mul_func<TExpr, TScalar>>{
		expr.self(), scalar};
}

template<class TExpr, typename TScalar>
auto operator/(const Expression<TExpr>& expr, const TScalar& scalar)
{
	return internal::Unary_expr<TExpr, TScalar, internal::Scalar_div_func<TExpr, TScalar>>{
		expr.self(), scalar};
}

/************************************************************************/
/* IMPLEMENTATION                                                       */
/************************************************************************/

namespace internal
{
template<class TExpr, typename TScalar, class TFunc>
inline Unary_expr<TExpr, TScalar, TFunc>::Unary_expr(const TExpr& expr, const TScalar& scalar) :
	scalar_(scalar), expr_(expr)
{}

template<class TExpr, typename TScalar, class TFunc>
inline std::size_t Unary_expr<TExpr, TScalar, TFunc>::rows() const
{
	return expr_.rows();
}

template<class TExpr, typename TScalar, class TFunc>
inline std::size_t Unary_expr<TExpr, TScalar, TFunc>::cols() const
{
	return expr_.cols();
}

template<class TExpr, typename TScalar, class TFunc>
inline auto Unary_expr<TExpr, TScalar, TFunc>::operator()(std::size_t row, std::size_t col) const ->
	typename Base::Value
{
	return TFunc::element(expr_, scalar_, row, col);
}
} // namespace internal
} // namespace la
