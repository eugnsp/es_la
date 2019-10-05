#pragma once
#include <es_la/dense/forward.hpp>
#include <es_la/dense/tags.hpp>
#include <es_la/dense/utility/ct_extent.hpp>

#include <es_util/type_traits.hpp>

#include <algorithm>
#include <cstddef>

namespace es_la
{
namespace internal
{
template<class Expr>
struct Ct_size_trait_impl
{};
} // namespace internal

template<class Expr>
using Ct_size_trait = internal::Ct_size_trait_impl<es_util::Remove_cv_ref<Expr>>;

namespace internal
{
template<std::size_t ct_begin, std::size_t ct_size>
struct Ct_size_trait_impl<internal::Range<ct_begin, ct_size>> : std::integral_constant<std::size_t, ct_size>
{};

template<std::size_t ct_size>
struct Ct_size_trait_impl<internal::Slice<ct_size>> : std::integral_constant<std::size_t, ct_size>
{};
} // namespace internal
} // namespace es_la
