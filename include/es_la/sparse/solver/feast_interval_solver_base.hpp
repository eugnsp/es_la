#pragma once
#include "../../base/matrix.hpp"
#include "../sparse_matrix.hpp"
#include <es_la/sparse/solver/pardiso_solver.hpp>

#include <mkl_solvers_ee.h>
#include <mkl_types.h>

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

namespace es_la::internal
{
class Feast_interval_solver_base
{
protected:
	class Params
	{
	public:
		operator MKL_INT*();

		void set_matrix_checker(bool = true);
		void set_status_printer(bool = true);

		// Returns the index of the first column of Q for RCI routines
		std::size_t q_start_col() const;

		// Returns the number of columns of Q for RCI routines
		std::size_t q_cols() const;

	private:
		MKL_INT params_[128];
	};

	enum class Status : MKL_INT
	{
		ERR_SYSTEM_SIZE = 202,
		ERR_INIT_SUBSPACE = 201,
		ERR_E_MIN_MAX = 200,
		SUCCESS_SUBSPACE = 4,
		WARN_SUBSPACE_TOO_SMALL = 3,
		WARN_NO_CONVERGENCE = 2,
		WARN_NO_EIGENVALUES = 1,
		SUCCESS = 0,
		ERR_ALLOC = -1,
		ERR_LINEAR_SOLVER = -2,
		ERR_EIGENVALUE_SOLVER = -3,
		ERR_B_NOT_POS_DEFINIT = -4
	};

	enum class Job : MKL_INT
	{
		DONE = 0,
		INIT = -1,
		FACTORIZE_Z = 10,
		SOLVE_Z = 11,
		FACTORIZE_ZH = 20,
		SOLVE_ZH = 21,
		MULTIPLY_A = 30,
		MULTIPLY_B = 40,
		RERUN = -2
	};

protected:
	Feast_interval_solver_base();

protected:
	static std::string error_string(Status);

	Status mkl_feast_rci(Job&, MKL_UINT n, std::complex<float>& ze, float* work1,
		std::complex<float>* work2, float* work3, float* work4, float& eps, MKL_UINT& n_loops,
		std::pair<float, float> eigen_values_interval, MKL_UINT n_eigen_values0,
		float* eigen_values, float* eigen_vectors, MKL_UINT& n_eigen_values, float* residues);

	Status mkl_feast_rci(Job&, MKL_UINT n, std::complex<double>& ze, double* work1,
		std::complex<double>* work2, double* work3, double* work4, double& eps, MKL_UINT& n_loops,
		std::pair<double, double> eigen_values_interval, MKL_UINT n_eigen_values0,
		double* eigen_values, double* eigen_vectors, MKL_UINT& n_eigen_values, double* residues);

	Status mkl_feast_rci(Job&, MKL_UINT n, std::complex<float>& ze, std::complex<float>* work1,
		std::complex<float>* work2, std::complex<float>* work3, std::complex<float>* work4,
		float& eps, MKL_UINT& n_loops, std::pair<float, float> eigen_values_interval,
		MKL_UINT n_eigen_values0, float* eigen_values, std::complex<float>* eigen_vectors,
		MKL_UINT& n_eigen_values, float* residues);

	Status mkl_feast_rci(Job&, MKL_UINT n, std::complex<double>& ze, std::complex<double>* work1,
		std::complex<double>* work2, std::complex<double>* work3, std::complex<double>* work4,
		double& eps, MKL_UINT& n_loops, std::pair<double, double> eigen_values_interval,
		MKL_UINT n_eigen_values0, double* eigen_values, std::complex<double>* eigen_vectors,
		MKL_UINT& n_eigen_values, double* residues);

protected:
	Params params_;
};
} // namespace es_la::internal
