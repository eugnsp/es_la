#pragma once
#include <es_la/base/expression.hpp>
#include <es_la/base/traits.hpp>
#include <es_la/expr/functor.hpp>

namespace la
{
namespace internal
{
template<class Left_expr, class Right_expr, template<class, class> class Func>
class Bin_expr : public Expression<Bin_expr<Left_expr, Right_expr, Func>>
{
public:
	using Left = Left_expr;
	using Right = Right_expr;

private:
	using Functor = Func<Left, Right>;

public:
	Bin_expr(const Left& left, const Right& right) : left_(left), right_(right)
	{
		Functor::check_sizes(left_, right_);
	}

	std::size_t rows() const
	{
		return Functor::rows(left_, right_);
	}

	std::size_t cols() const
	{
		return Functor::cols(left_, right_);
	}

	typename Functor::Value operator()(std::size_t row, std::size_t col) const
	{
		return Functor::element(left_, right_, row, col);
	}

	const Left& left() const
	{
		return left_;
	}

	const Right& right() const
	{
		return right_;
	}

private:
	Expr_storage_t<const Left> left_;
	Expr_storage_t<const Right> right_;
};
} // namespace internal

//////////////////////////////////////////////////////////////////////////

template<class Left, class Right>
auto operator+(const Expression<Left>& left, const Expression<Right>& right)
{
	using namespace internal;
	return Bin_expr<Left, Right, Add_func>{left.self(), right.self()};
}

template<class Left, class Right>
auto operator-(const Expression<Left>& left, const Expression<Right>& right)
{
	using namespace internal;
	return Bin_expr<Left, Right, Sub_func>{left.self(), right.self()};
}

template<class Left, class Right>
auto operator*(const Expression<Left>& left, const Expression<Right>& right)
{
	using namespace internal;
	return Bin_expr<Left, Right, Mul_func>{left.self(), right.self()};
}
} // namespace la