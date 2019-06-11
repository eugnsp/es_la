#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
struct Store_expr_as_reference_trait : std::false_type
{};

template<typename Value, auto ct_rows, auto ct_cols, class Layout>
struct Store_expr_as_reference_trait<Matrix<Value, ct_rows, ct_cols, Layout>> : std::true_type
{};

template<class Expr>
using Expr_storage_type = std::conditional_t<Store_expr_as_reference_trait<es_util::Remove_cv_ref<Expr>>::value,
	std::add_lvalue_reference_t<Expr>, std::remove_reference_t<Expr>>;
} // namespace es_la::internal
