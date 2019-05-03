#pragma once
#include <es_la/dense.hpp>
#include <es_la/sparse.hpp>
#include <es_la/sparse/solver/feast_interval_solver_base.hpp>
#include <es_la/sparse/solver/pardiso_solver.hpp>

#include <mkl_types.h>

#include <cassert>
#include <stdexcept>
#include <utility>

namespace es_la
{
template<class Sparse_matrix>
class Feast_interval_solver;

template<typename Value, class Symmetry_tag, typename Index>
class Feast_interval_solver<Csr_matrix<Value, Symmetry_tag, Index>> :
	private internal::Feast_interval_solver_base
{
	//static_assert(internal::is_symmetric<Symmetry_tag>);

public:
	using Sparse_matrix = Csr_matrix<Value, Symmetry_tag, Index>;

public:
	Feast_interval_solver(const Sparse_matrix& mat_a, const Sparse_matrix& mat_b) :
		mat_a_(mat_a), mat_b_(mat_b)
	{
		assert(mat_a.rows() == mat_a.cols());
		assert(mat_a.rows() == mat_b.rows() && mat_a.cols() == mat_b.cols());
	}

	bool solve(Matrix_x<Value>& eigen_vectors, Vector_x<Value>& eigen_values,
		std::pair<double, double> eigen_values_interval)
	{
		assert(eigen_values_interval.first < eigen_values_interval.second);

		const auto n = static_cast<MKL_UINT>(mat_a_.rows());
		const auto m0 = static_cast<MKL_UINT>(eigen_values.size());

		MKL_UINT n_loops = 0;
		n_eigen_values_ = 0;
		double eps = 0;
		Vector_x<double> rel_errors(m0, 0.);

		Matrix_x<Value> work1(n, m0);
		Matrix_x<Z_value> work2(n, m0), work5(n, m0);
		Vector_x<Value> work3(m0 * m0), work4(m0 * m0);

		Mkl_sparse_matrix_ext mkl_mat_a(mat_a_), mkl_mat_b(mat_b_);

		using Z = Csr_matrix<Z_value, Symmetric_upper>;
		Z mat_z;
		mat_z.assign_pattern(mat_a_);

		Pardiso_solver solver(mat_z);

		auto job = Job::INIT;
		while (true)
		{
			Z_value ze;

			const auto status = mkl_feast_rci(job, n, ze, work1.data(), work2.data(), work3.data(),
				work4.data(), eps, n_loops, eigen_values_interval, m0, eigen_values.data(),
				eigen_vectors.data(), n_eigen_values_, rel_errors.data());

			if (job == Job::DONE)
			{
				if (status == Status::WARN_SUBSPACE_TOO_SMALL)
					return false;
				else if (status == Status::SUCCESS)
					return true;
				else
					throw std::runtime_error(error_string(status));
			}

			if (status != Status::SUCCESS)
				throw std::runtime_error(error_string(status));

			if (job == Job::FACTORIZE_Z)
			{
				for (MKL_UINT i = 0; i < mat_z.nnz(); ++i)
					mat_z[i] = ze * mat_b_[i] - mat_a_[i];
				solver.analyze_factorize();
			}
			else if (job == Job::SOLVE_Z)
			{
				solver.solve(work2, work5);
				work2 = work5;
			}
			else if (job == Job::MULTIPLY_A)
			{
				const auto sc = params_.q_start_col();
				const auto nc = params_.q_cols();
				//work1.cols(sc, nc) = mkl_mat_a * eigen_vectors.cols(sc, nc);
			}
			else if (job == Job::MULTIPLY_B)
			{
				const auto sc = params_.q_start_col();
				const auto nc = params_.q_cols();
				//work1.cols(sc, nc) = mkl_mat_b * eigen_vectors.cols(sc, nc);
			}

			// else if (job == Job::MULTIPLY_A)
			// {
			// char uplo = 'U';
			// auto n1 = static_cast<MKL_INT>(n);
			// for (auto i = params_.q_start_col(); i < params_.q_start_col() + params_.q_cols();
			// 	 ++i)
			// 	mkl_cspblas_dcsrsymv(&uplo, &n1, mat_a_.values(),
			// 		(const MKL_INT*)mat_a_.row_indices(), (const MKL_INT*)mat_a_.col_indices(),
			// 		eigen_vectors.data() + n * i, work1.data() + n * i);
			// }
			// else if (job == Job::MULTIPLY_B)
			// {
			// char uplo = 'U';
			// auto n1 = static_cast<MKL_INT>(n);
			// for (auto i = params_.q_start_col(); i < params_.q_start_col() + params_.q_cols();
			// 	 ++i)
			// 	mkl_cspblas_dcsrsymv(&uplo, &n1, mat_b_.values(),
			// 		(const MKL_INT*)mat_b_.row_indices(), (const MKL_INT*)mat_b_.col_indices(),
			// 		eigen_vectors.data() + n * i, work1.data() + n * i);
			// }
		}
	}

	std::size_t n_eigen_values() const
	{
		return static_cast<std::size_t>(n_eigen_values_);
	}

private:
	using Z_value = internal::Add_complex<Value>;

	const Sparse_matrix& mat_a_;
	const Sparse_matrix& mat_b_;

	MKL_UINT n_eigen_values_;
};
} // namespace es_la
