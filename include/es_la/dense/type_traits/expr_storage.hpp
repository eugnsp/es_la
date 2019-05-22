#pragma once
#include <es_la/core/type_traits/expr_storage.hpp>
#include <es_la/dense/forward.hpp>

#include <type_traits>

namespace es_la::internal
{
template<typename Value, auto ct_rows, auto ct_cols, class Layout>
struct Store_expr_as_reference_trait<Matrix<Value, ct_rows, ct_cols, Layout>> : std::true_type
{};
} // namespace es_la::internal
