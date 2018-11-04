#include "matfile.hpp"
//#include "math/MKL.h"
//#include "util/function.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace util
{
//void Matlab::write(const std::string& name, const math::LA::CSRSparseMatrix<double>& matrix)
//{
//	const auto n = matrix.cols();
//	auto nnz = matrix.nnz();
//
//	const auto size_in_bytes = nnz * sizeof(double);
//	if (size_in_bytes > INT32_MAX)
//		throw std::length_error("Level 5 MAT-files cannot hold variables exceeding 2GB.");
//
//	// Convert CSR to CSC first
//	std::vector<std::size_t> cscRows(nnz);
//	std::vector<std::size_t> cscColumnIndex(n + 1);
//	std::vector<double> cscValues(nnz);
//
//	std::size_t job[8] = { };
//	MKL_INT info;
//
//	job[0] = 0;				// The matrix in the CSR format is converted to the CSC format
//	job[1] = job[2] = 0;	// Zero-based indexing	
//	job[5] = 1;				// All output arrays (acsc, ja1, and ia1) are filled in for the output storage
//
//	math::MKL::CsrCsc(job, &n, const_cast<double*>(matrix.valuesData()), const_cast<std::size_t*>(matrix.colsData()),
//					  const_cast<std::size_t*>(matrix.rowIndexData()), cscValues.data(), cscRows.data(), cscColumnIndex.data(), &info);
//
//	if (info != 0)
//		throw std::runtime_error("Matrix format conversion error");
//
//	write_sparse_array_element(name, matrix.rows(), matrix.cols(), matrix.nnz(), cscRows.data(), cscColumnIndex.data(), cscValues.data());
//}
}
