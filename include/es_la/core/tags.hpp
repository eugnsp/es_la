#pragma once

namespace es_la
{
namespace internal
{
enum class Dynamic_extent
{};

struct Internal
{};
}

inline constexpr auto dynamic = internal::Dynamic_extent{};

struct Rvalue
{};

struct Lvalue
{};

// Symmetry tags
struct Not_symmetric
{};
struct Structural_symmetric
{};
struct Symmetric_upper
{};
struct Symmetric_lower
{};
// struct Hermitian
// {};

} // namespace es_la
