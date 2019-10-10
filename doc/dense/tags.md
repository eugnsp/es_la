# Dense expressions: Tags

Header: `<esl/dense.hpp>`\
Namespace: `esl`

---

## Extents

```cpp
inline constexpr std::size_t dynamic = -1;
```

The constant used to denote dynamic extents of expressions.

## Memory layouts

```cpp
// 1.
struct Col_major {};
// 2.
struct Row_major {};
```

Tags that define the memory layout of a matrix.
1. Represents the column-major order: `a(0, 0), a(1, 0), a(2, 0), ..., a(0, 1), a(1, 1), ...`.
2. Represents the row-major order: `a(0, 0), a(0, 1), a(0, 2), ..., a(1, 0), a(1, 1), ...`.
