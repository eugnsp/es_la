#pragma once
#include "../base/matrix.hpp"
#include "../sparse/sparse_matrix.hpp"
#include <mkl_types.h>
#include <mkl_pardiso.h>
#include <string>
#include <stdexcept>

namespace la
{
template<class Sparse_matrix_type,
	class T_Structure_tag = typename Sparse_matrix_type::Symmetry_tag,
	bool t_is_positive_definite = false>
class Pardiso_solver
{
public:
	using Sparse_matrix = Sparse_matrix_type;

private:
	using T_Value = typename Sparse_matrix::Value;

public:
	Pardiso_solver();
	~Pardiso_solver();

	void set_pardiso_parameter(std::size_t index, MKL_INT value);

	void analyze(const Sparse_matrix&);
	void analyze_factorize(const Sparse_matrix&);
	void analyze_factorize_solve(
		const Sparse_matrix&,
		const Vector_x<T_Value>& rhs, Vector_x<T_Value>& solution);

	void factorize(const Sparse_matrix&);
	void factorize_solve(
		const Sparse_matrix&,
		const Vector_x<T_Value>& rhs, Vector_x<T_Value>& solution);

	void solve(
		const Sparse_matrix&,
		const Vector_x<T_Value>& rhs, Vector_x<T_Value>& solution);
	
	// 	void solve(const Sparse_matrix<T_Value>&, const Vector<T_Value, 0>&, Vector<T_Value, 0>&)
// 	{ 
// //		assert(structure_ != SparseMatrixStructure::STRUCTURAL_SYMMETRIC || pattern.is_symmetric());
// 
// 	}

private:
	enum class Pardiso_matrix_type : MKL_INT
	{
		REAL_STRUCTURAL_SYMMETRIC = 1,
		REAL_SYMMETRIC_POS_DEFINITE = 2,
		REAL_SYMMETRIC_INDEFINITE = -2,
		COMPLEX_STRUCTURAL_SYMMETRIC = 3,
		COMPLEX_HERMITIAN_POS_DEFINITE = 4,
		COMPLEX_HERMITIAN_INDEFINITE = -4,
		COMPLEX_SYMMETRIC = 6,
		REAL_GENERAL = 11,
		COMPLEX_GENERAL = 13,
	};

	enum class Pardiso_phase : MKL_INT
	{
		ANALYZE = 11,
		ANALYZE_FACTORIZE = 12,
		ANALYZE_FACTORIZE_SOLVE = 13,
		FACTORIZE = 22,
		FACTORIZE_SOLVE = 23,
		SOLVE = 33,
		RELEASE_ALL = -1
	};

private:
	void call_pardiso(
		Pardiso_phase, const Sparse_matrix* = nullptr,
		const T_Value* rhs = nullptr, T_Value* solution = nullptr);

	static constexpr Pardiso_matrix_type pardiso_matrix_type();
	static std::string pardiso_error_string(MKL_INT error);

private:
	std::size_t handle_[64];

	MKL_INT message_level_ = 0;
	MKL_INT parameters_[64];
};

/************************************************************************/
/* IMPLEMENTATION                                                       */
/************************************************************************/

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::Pardiso_solver()
{
	MKL_INT matrix_type = static_cast<MKL_INT>(pardiso_matrix_type());
	pardisoinit(handle_, &matrix_type, parameters_);
	parameters_[34] = 1;		// Zero-based indexing

#ifndef NDEBUG
	parameters_[26] = 1;		// Matrix checker
#endif
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::~Pardiso_solver()
{
	call_pardiso(Pardiso_phase::RELEASE_ALL);
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
void Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::set_pardiso_parameter(
	std::size_t index, MKL_INT value)
{
	assert(index < 64);
	parameters_[index] = value;
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
void Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::analyze(
	const Sparse_matrix& matrix)
{
	call_pardiso(Pardiso_phase::ANALYZE, &matrix);
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
void Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::analyze_factorize(
	const Sparse_matrix& matrix)
{
	call_pardiso(Pardiso_phase::ANALYZE_FACTORIZE, &matrix);
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
void Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::analyze_factorize_solve(
	const Sparse_matrix& matrix, const Vector_x<T_Value>& rhs, Vector_x<T_Value>& solution)
{ 
	call_pardiso(Pardiso_phase::ANALYZE_FACTORIZE_SOLVE, &matrix, rhs.data(), solution.data());
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
void Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::factorize_solve(
	const Sparse_matrix& matrix, const Vector_x<T_Value>& rhs, Vector_x<T_Value>& solution)
{
	call_pardiso(Pardiso_phase::FACTORIZE_SOLVE, &matrix, rhs.data(), solution.data());
}

//////////////////////////////////////////////////////////////////////////

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
void Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::call_pardiso(
	Pardiso_phase phase, const Sparse_matrix* matrix,
	const T_Value* rhs, T_Value* solution)
{
	assert(phase == Pardiso_phase::RELEASE_ALL || matrix);

	const MKL_INT matrix_type = static_cast<MKL_INT>(pardiso_matrix_type());
	const MKL_INT max_factors = 1;
	const MKL_INT matrix_number = 1;
	const MKL_INT n_equations = matrix ? matrix->n_cols() : 0;
	const MKL_INT n_rhs = 1;

	MKL_INT error = 0;

	if (matrix)
		::pardiso(handle_, &max_factors, &matrix_number, &matrix_type,
			reinterpret_cast<const MKL_INT*>(&phase), &n_equations,
			matrix->data(),
			reinterpret_cast<const MKL_INT*>(matrix->row_indices()),
			reinterpret_cast<const MKL_INT*>(matrix->col_indices()),
			nullptr, &n_rhs, parameters_, &message_level_, const_cast<T_Value*>(rhs), solution, &error);
	else
		::pardiso(handle_, &max_factors, &matrix_number, &matrix_type,
			reinterpret_cast<const MKL_INT*>(&phase), &n_equations, nullptr,
			nullptr, nullptr, nullptr, &n_rhs, parameters_, &message_level_, const_cast<T_Value*>(rhs), solution, &error);

 	if (error)
 		throw std::runtime_error(pardiso_error_string(error));
}

template<typename T>
struct Is_complex : std::false_type { };

template<typename T>
constexpr bool is_complex_v = Is_complex<T>::value;

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
constexpr auto Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::pardiso_matrix_type() -> Pardiso_matrix_type
{ 
	constexpr bool is_complex = is_complex_v<T_Value>;

	if constexpr (std::is_same_v<T_Structure_tag, Symmetric_upper>)
	{
		if constexpr (is_complex)
			return Pardiso_matrix_type::COMPLEX_SYMMETRIC;
		else
			return t_is_positive_definite ? Pardiso_matrix_type::REAL_SYMMETRIC_POS_DEFINITE : Pardiso_matrix_type::REAL_SYMMETRIC_INDEFINITE;
	}
	
	if constexpr (std::is_same_v<T_Structure_tag, Structural_symmetric>)
		return is_complex ? Pardiso_matrix_type::COMPLEX_STRUCTURAL_SYMMETRIC : Pardiso_matrix_type::REAL_STRUCTURAL_SYMMETRIC;

	if constexpr (std::is_same_v<T_Structure_tag, Hermitian>)
	{
		static_assert(is_complex, "Hermitian tag should be used with complex matrices only");
		return t_is_positive_definite ? Pardiso_matrix_type::COMPLEX_HERMITIAN_POS_DEFINITE : Pardiso_matrix_type::COMPLEX_HERMITIAN_INDEFINITE;
	}

	return is_complex ? Pardiso_matrix_type::COMPLEX_GENERAL : Pardiso_matrix_type::REAL_GENERAL;
}

template<class Sparse_matrix, class T_Structure_tag, bool t_is_positive_definite>
std::string Pardiso_solver<Sparse_matrix, T_Structure_tag, t_is_positive_definite>::pardiso_error_string(MKL_INT error)
{
	std::string str = "Pardiso error " + std::to_string(error) + ": ";
	switch (error)
	{
	case 0:		str += "No error"; break;
	case -1:	str += "Input inconsistent"; break;
	case -2:	str += "Not enough memory"; break;
	case -3:	str += "Reordering problem"; break;
	case -4:	str += "Zero pivot, numerical factorization or iterative refinement problem"; break;
	case -5:	str += "Unclassified (internal) error";	break;
	case -6:	str += "Reordering failed (nonsymmetric real and complex matrices only)"; break;
	case -7:	str += "Diagonal matrix is singular"; break;
	case -8:	str += "32-bit integer overflow problem"; break;
	case -9:	str += "Not enough memory for OOC"; break;
	case -10:	str += "Error opening OOC files"; break;
	case -11:	str += "Read/write error with OOC files"; break;
	case -12:	str += "pardiso_64 called from 32-bit library";	break;
	default:	str += "Unknown error";
	}

	return str;
}

}
