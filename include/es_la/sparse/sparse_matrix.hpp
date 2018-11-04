#pragma once
#include <es_la/tags.hpp>
#include <es_la/base/extended.hpp>
#include <es_la/base/matrix.hpp>
#include "sparsity_pattern.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

// TODO : rename to
// row pointer
// column index

namespace la
{

template<typename T_Value, class Symmetry_tag_type = Not_symmetric>
class Sparse_matrix /*: public internal::Extended<Sparse_matrix<T_Value>, 0, 0>*/
{
private:
	//using Base = internal::Extended<Sparse_matrix<T_Value>, 0, 0>;

public:
	using Value = T_Value;
	using Symmetry_tag = Symmetry_tag_type;

public:
	Sparse_matrix() = default;

	Sparse_matrix(std::size_t rows, std::size_t cols)
		: rows_(rows), cols_(cols)
	{ }

	// HACK
	template<class T1, class T2, class T3>
	Sparse_matrix(std::size_t rows, std::size_t cols, const T1& values, const T2& row_indices, const T3& col_indices)
		: rows_(rows), cols_(cols), values_(values.size())
	{
//		assert(row_indices.size() == rows);
		assert(col_indices.size() == values.size());

		for (std::size_t i = 0; i < values.size(); ++i)
			values_[i] = values[i];

		row_indices_.resize(row_indices.size());
		col_indices_.resize(col_indices.size());
		std::copy(row_indices.begin(), row_indices.end(), row_indices_.begin());
		std::copy(col_indices.begin(), col_indices.end(), col_indices_.begin());
	}

	T_Value& operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);
// 		if (isSymmetric())
// 			assert(col >= row);

		auto start = row_indices_[row];
		auto end = row_indices_[row + 1];
		assert(start < end);
				
		const auto begin = col_indices_.begin();
		const auto pos = std::lower_bound(begin + start, begin + end, col);
		assert(pos != begin + end);
		assert(*pos == col);

		return values_[pos - begin];
	}

	T_Value element(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);

		auto start = row_indices_[row];
		auto end = row_indices_[row + 1];
		assert(start < end);

		const auto begin = col_indices_.begin();
		const auto pos = std::lower_bound(begin + start, begin + end, col);
		
		if (pos == begin + end || *pos != col)
			return 0;
		else
			return values_[pos - begin];
	}

// 	T_Value operator()(std::size_t row, std::size_t col) const
// 	{
// 		throw;
// 	}
// 	
	void zero_row(std::size_t row)
	{
		assert(row < rows_);

		auto start = row_indices_[row];
		auto end = row_indices_[row + 1];
		assert(start < end);

		for (auto i = start; i < end; ++i)
			values_[i] = 0;
	}

	void zero()
	{
		values_.zero();
	}

	void resize(std::size_t rows, std::size_t cols)
	{
		rows_ = rows;
		cols_ = cols;
	}

	void set_sparsity_pattern(const Sparsity_pattern<Symmetry_tag>& pattern)
	{
		assert(pattern.n_rows() == rows_);

		row_indices_.clear();
		col_indices_.clear();

		row_indices_.reserve(rows_ + 1);
		col_indices_.reserve(pattern.nnz());

		std::size_t index = 0;
		for (auto& row : pattern.rows())
		{
			assert(std::is_sorted(row.begin(), row.end()));

			col_indices_.insert(col_indices_.end(), row.begin(), row.end());
			row_indices_.push_back(index);

			index += row.size();
		}

		col_indices_.shrink_to_fit();
		row_indices_.push_back(index);
		values_.resize(col_indices_.size());

		assert(row_indices_.size() == rows_ + 1);

	#ifndef NDEBUG
//		checkStructure();
	#endif
	}

	std::size_t n_rows() const
	{
		return rows_;
	}

	std::size_t n_cols() const
	{
		return cols_;
	}

	std::size_t nnz() const
	{
		return values_.size();
	}

	const T_Value* data() const
	{
		return values_.data();
	}

	const std::size_t* row_indices() const
	{
		return row_indices_.data();
	}

	const std::size_t* col_indices() const
	{
		return col_indices_.data();
	}

	std::size_t memory_size() const
	{
		// TODO : use capacity, not size
		return values_.size() * sizeof(T_Value) +
			(row_indices_.capacity() + col_indices_.capacity()) * sizeof(std::size_t);
	}

	void toZeroBasedIndexing()
	{
		for (auto& i : row_indices_)
		{
			assert(i >= 1);
			--i;
		}

		for (auto& i : col_indices_)
		{
			assert(i >= 1);
			--i;
		}
	}

	void toOneBasedIndexing()
	{
		for (auto& i : row_indices_)
			++i;

		for (auto& i : col_indices_)
			++i;
	}

	void checkStructure() const
	{
		sparse_struct handle;

		sparse_matrix_checker_init(&handle);
		handle.n = cols_;
		handle.csr_ia = (MKL_INT*)row_indices_.data();
		handle.csr_ja = (MKL_INT*)col_indices_.data();
		handle.matrix_format = MKL_CSR;
		handle.indexing = MKL_ZERO_BASED;
	#ifdef NDEBUG
		handle.message_level = MKL_NO_PRINT;
	#else
		handle.message_level = MKL_PRINT;
	#endif
		handle.print_style = MKL_C_STYLE;

// 		switch (structure_)
// 		{
// 		case SparseMatrixStructure::SYMMETRIC:
// 		case SparseMatrixStructure::HERMITIAN:
// 			handle.matrix_structure = sparse_matrix_structures::MKL_UPPER_TRIANGULAR;
// 			break;
// 
// 		case SparseMatrixStructure::STRUCTURAL_SYMMETRIC:
// 			handle.matrix_structure = sparse_matrix_structures::MKL_STRUCTURAL_SYMMETRIC;
// 			break;
// 
// 		default:
			handle.matrix_structure = sparse_matrix_structures::MKL_GENERAL_STRUCTURE;
//		}

		auto result = sparse_matrix_checker(&handle);
		if (result != MKL_SPARSE_CHECKER_SUCCESS)
			throw std::runtime_error("MKL sparse matrix checker error: " + errorString(result));
	}

private:
	static std::string errorString(sparse_checker_error_values error)
	{
		switch (error)
		{
		case MKL_SPARSE_CHECKER_SUCCESS:
			return "No error";

		case MKL_SPARSE_CHECKER_NON_MONOTONIC:
			return "The input array is not 0 or 1 based (ia[0] is not 0 or 1) or elements of ia are not in non-decreasing order as required";

		case MKL_SPARSE_CHECKER_OUT_OF_RANGE:
			return "The value of the ja array is lower than the number of the first column or greater than the number of the last column";

		case MKL_SPARSE_CHECKER_NONTRIANGULAR:
			return "The matrix_structure parameter is MKL_UPPER_TRIANGULAR and both ia and ja are not upper triangular, or the matrix_structure parameter is MKL_LOWER_TRIANGULAR and both ia and ja are not lower triangular";

		case MKL_SPARSE_CHECKER_NONORDERED:
			return "The elements of the ja array are not in non-decreasing order in each row as required";

		default:
			return "Unknown error";
		}
	}

private:
 	Vector_x<T_Value> values_;
 	std::vector<std::size_t> row_indices_;
 	std::vector<std::size_t> col_indices_;

	std::size_t rows_;
	std::size_t cols_;
};
}
