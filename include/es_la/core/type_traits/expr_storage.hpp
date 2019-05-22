#pragma once
#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class Expr>
struct Store_expr_as_reference_trait : std::false_type
{};

template<class Expr>
using Expr_storage_type = std::conditional_t<Store_expr_as_reference_trait<es_util::Remove_cv_ref<Expr>>::value,
	std::add_lvalue_reference_t<Expr>, std::remove_reference_t<Expr>>;
} // namespace es_la::internal
