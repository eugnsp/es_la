// #pragma once
// #include "type_traits.hpp"
// #include <es_la/core/expression.hpp>
// #include <es_la/dense/ct_extent.hpp>
// #include <es_la/util/macros.hpp>
// #include <es_la/util/mkl.hpp>

// #include <cassert>
// #include <type_traits>

// namespace es_la::internal
// {
// // Default element-by-element assigment
// template<class To, class From, class = std::void_t<>>
// struct Assign
// {
// 	static_assert(is_ct_extent_dynamic_or_eq(ct_rows_value<To>, ct_rows_value<From>));
// 	static_assert(is_ct_extent_dynamic_or_eq(ct_cols_value<To>, ct_cols_value<From>));

// 	static void run(To& to, const From& from)
// 	{
// 		assert(to.rows() == from.rows());
// 		assert(to.cols() == from.cols());

// 		for (std::size_t col = 0; col < to.cols(); ++col)
// 			for (std::size_t row = 0; row < to.rows(); ++row)
// 				to(row, col) = from(row, col);
// 	}
// };

// #if ES_LA_USE_MKL
// // template<class To, class From>
// // struct Assign<To, From, std::void_t<std::enable_if_t<
// // 	is_double_dynamic_matrix_v<To> && is_double_dynamic_matrix_v<From>>>>
// // {
// // 	static void assign(To& to, const From& from)
// // 	{
// // 		cblas_dcopy(to.size(), from.data(), 1, to.data(), 1);
// // 	}
// // };

// // TODO : for dynamic only
// template<class To, class From>
// struct Assign<To, From,
// 	std::void_t<std::enable_if_t<std::conjunction_v<Has_fd_or_complex_fd_element<To>,
// 		Is_dyn_matrix_or_dyn_matrix_block<To>, Has_fd_or_complex_fd_element<From>, Is_product_expr<From>,
// 		Is_dyn_matrix_or_dyn_matrix_block<typename From::Lhs>, Is_dyn_matrix_or_dyn_matrix_block<typename From::Rhs>>>>>
// {
// 	static void run(To& to, const From& from)
// 	{
// 		// TODO CHECK BOUNDS

// 		auto& left = from.left();
// 		auto& right = from.right();

// 		mkl_blas_gemm(Mkl_blas_layout::ROW_MAJOR, Mkl_blas_transpose::NO_TRANS, Mkl_blas_transpose::NO_TRANS,
// 			left.rows(), right.cols(), left.cols(), 1., left.data(), left.lead_dim(), right.data(), right.lead_dim(),
// 			0., to.data(), to.lead_dim());
// 	}
// };
// #endif
// } // namespace es_la::internal