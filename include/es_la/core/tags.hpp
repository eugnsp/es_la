#pragma once
#include <cstddef>

namespace es_la
{
namespace internal
{
struct Internal
{};
}

inline constexpr std::size_t dynamic = -1;

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
