#pragma once
#include <es_util/type_traits.hpp>

namespace es_la
{
namespace internal
{
template<class Expr>
struct Value_trait_impl;
} // namespace internal

template<class Expr>
struct Value_trait : internal::Value_trait_impl<es_util::Remove_cv_ref<Expr>>
{};

template<class Expr>
using Value_type = typename Value_trait<Expr>::Type;
} // namespace es_la
