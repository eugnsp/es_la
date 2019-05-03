#include <es_la/sparse/solver/feast_interval_solver_base.hpp>

namespace es_la::internal
{
Feast_interval_solver_base::Params::operator MKL_INT*()
{
	return params_;
}

void Feast_interval_solver_base::Params::set_matrix_checker(bool flag)
{
	params_[26] = flag;
}

void Feast_interval_solver_base::Params::set_status_printer(bool flag)
{
	params_[0] = flag;
}

std::size_t Feast_interval_solver_base::Params::q_start_col() const
{
	return static_cast<std::size_t>(params_[23] - 1);
}

// Returns the number of columns of Q for RCI routines
std::size_t Feast_interval_solver_base::Params::q_cols() const
{
	return static_cast<std::size_t>(params_[24]);
}
} // namespace es_la::internal
