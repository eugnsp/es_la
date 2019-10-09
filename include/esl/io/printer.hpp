#pragma once
#include <cassert>
#include <cstddef>
#include <ostream>

namespace esl
{
template<class Expr>
class Printer
{
public:
	explicit Printer(const Expr& expr, const int width) : expr_(expr), width_(width)
	{
		assert(width >= 0);
	}

	void operator()(std::ostream& os) const
	{
		for (std::size_t row = 0; row < expr_.rows(); ++row)
		{
			for (std::size_t col = 0; col < expr_.cols(); ++col)
			{
				if (col != 0)
					os << ' ';
				if (width_ != 0)
					os.width(width_);
				os << expr_(row, col);
			}
			os << '\n';
		}
	}

private:
	const Expr& expr_;
	const int width_;
};

template<class Expr>
Printer<Expr> printer(const Expr& expr, const int width = 0)
{
	return Printer{expr, width};
}

template<class Expr>
std::ostream& operator<<(std::ostream& os, const Printer<Expr>& printer)
{
	printer(os);
	return os;
}
} // namespace esl
