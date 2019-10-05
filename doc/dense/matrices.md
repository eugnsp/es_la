# Dense expressions: Matrices

Header: `<es_la/dense.hpp>`\
Namespace: `es_la`

---

```cpp
template<typename Value_, std::size_t ct_rows, std::size_t ct_cols, class Layout = Col_major>
class Matrix : public Expression<Matrix<Value, ct_rows, ct_cols, Layout>>;
```

*Parameters:*
* `Value_` - the type of elements,
* `ct_rows` - number of rows fixed at compile-time or [`dynamic`][1],
* `ct_cols` - number of columns fixed at compile-time or [`dynamic`][1],
* `Layout` - matrix [memory layout tag][2].

Storage for matrix elements of static matrices (`ct_rows != dynamic` and `ct_cols != dynamic`) is allocated inside a `Matrix` object itself. Storage for matrix elements of dynamic matrices (`ct_rows == dynamic` or `ct_cols == dynamic`) is allocated dynamically.

The following notation is used below to denote specializations:
```cpp
SS = Matrix<Value, ct_rows, ct_cols, Layout> with ct_rows != dynamic && ct_cols != dynamic
SD = Matrix<Value, ct_rows, dynamic, Layout> with ct_rows != dynamic
DS = Matrix<Value, dynamic, ct_cols, Layout> with ct_cols != dynamic
DD = Matrix<Value, dynamic, dynamic, Layout>
```

---

## Member types

```cpp
// SS, SD, DS, and DD.
using Value = Value_;
```

---

## Member functions

### `Matrix`
**Constructors**

```cpp
// SS.
Matrix() = default;
```

Default constructor. Constructs the matrix with default or value initialized matrix elements.

```cpp
// SD, DS, and DD.
Matrix() = default;
```

Default constructor. Constructs the empty matrix.

```cpp
// SD.
Matrix(std::size_t cols);
// DS.
Matrix(std::size_t rows);
// DD.
Matrix(std::size_t rows, std::size_t cols);
```

Constructs the matrix with the given size and default constructed matrix elements.

*Parameters:*
* `rows` - the number of rows,
* `cols` - the number of columns.

```cpp
// SS.
explicit Matrix(const Value& value);
```

Constructs the matrix with matrix elements initialized with the copies of `value`.

*Parameters:*
* `value` - the value to initialize matrix elements with.

```cpp
// SD.
Matrix(std::size_t cols, const Value& value);
// DS.
Matrix(std::size_t rows, const Value& value);
// DD.
Matrix(std::size_t rows, std::size_t cols, const Value& value);
```

Constructs the matrix with the given size and matrix elements initialized with the copies of `value`.

*Parameters:*
* `rows` - the number of rows,
* `cols` - the number of columns,
* `value` - the value to initialize matrix elements with.

```cpp
// SS.
template<typename... Values>
explicit constexpr Matrix(Values&&... values);
```

Constructs the matrix with matrix elements contiguously initialized with the values `values`. This constructor participates in overload resolution only if the number of arguments is equal to `ct_rows * ct_cols` and if each argument is convertible to `Value` using implicit conversions.

*Parameters:*
* `values` - the values to initialize matrix elements with.

```cpp
// SD.
Matrix(std::size_t cols, std::initializer_list<Value> values);
// DS.
Matrix(std::size_t rows, std::initializer_list<Value> values);
// DD.
Matrix(std::size_t rows, std::size_t cols, std::initializer_list<Value> values);
```

Constructs the matrix with the given size and matrix elements initialized contiguously with the contents of the initializer list `values`. The size of the initializer list should be equal to the number of matrix elements.

*Parameters:*
* `rows` - the number of rows,
* `cols` - the number of columns,
* `values` - the initializer list to initialize the matrix elements with

```cpp
// SD, and DS.
Matrix(std::initializer_list<Value> values);
```

Constructs the matrix with matrix elements initialized contiguously with the contents of the initializer list `values`. The size of the initializer list should be equal to the number of matrix elements, the number of columns or rows is inferred from the initializer list size (`values.size() / ct_rows` or `values.size() / ct_cols`).

*Parameters:*
* `values` - the initializer list to initialize the matrix elements with

### `is_empty`, `rows`, `cols`, `size`, `capacity`, `lead_dim`, `row_stride`, `col_stride`
**Matrix extents and capacity**

```cpp
// SS.
static constexpr bool is_empty();
// SD, DS, and DD.
bool is_empty() const;
```

Checks if the matrix has zero number of elements.

*Return value:*
`true` if the matrix is empty, and `false` otherwise.

```cpp
// SS, SD.
static constexpr std::size_t rows();
// DS, DD.
std::size_t rows() const;
```

Returns the number of rows in the matrix.

```cpp
// SS, DS.
static constexpr std::size_t cols();
// SD, DD.
std::size_t cols() const;
```

Returns the number of columns in the matrix.

```cpp
// SS.
static constexpr std::size_t size();
// SD, DS, and DD.
std::size_t size() const;
```

Returns the number of matrix elements (`= rows() * cols()`).

```cpp
// SS.
static constexpr std::size_t capacity();	// = size()
// SD, DS, and DD.
std::size_t capacity() const;
```

Returns the number of elements that the matrix has currently allocated space for.

```cpp
// 1.
std::size_t lead_dim() const;
// 2.
std::size_t row_stride() const;
// 3.
std::size_t col_stride() const;
```

1. Returns the leading dimension of a matrix. The leading dimension is the increment used to determine the starting position for the matrix elements in each successive column (column-major order) or row (row-major order).
2. Returns the increment used to determine the starting position of the matrix element in the next row of the same column.
3. Returns the increment used to determine the starting position of the matrix element in the next column of the same row.

For matrices (not submatrices) the following equalities hold:

| [`Layout`][2] | `lead_dim()` | `row_stride()` | `col_stride()` |
|:--------------|:------------:|:--------------:|:--------------:|
| `Col_major`   | `= rows()`   | `= 1`          | `= rows()`     |
| `Row_major`   | `= cols()`   | `= cols()`     | `= 1`          |


### `operator()`, `operator[]`
**Access the specified element**

```cpp
// SS.
constexpr Value& operator()(std::size_t row, std::size_t col);
constexpr const Value& operator()(std::size_t row, std::size_t col) const;
// SD, DS, and DD.
Value& operator()(std::size_t row, std::size_t col);
const Value& operator()(std::size_t row, std::size_t col) const;
```

Returns the matrix element located in the row `row` and column `col`.

*Parameters:*
* `row` - row position of the element to return,
* `col` - column position of the element to return.

```cpp
// SS.
constexpr Value& operator()(std::size_t index);
constexpr const Value& operator()(std::size_t index) const;
constexpr Value& operator[](std::size_t index);
constexpr const Value& operator[](std::size_t index) const;
// SD, DS, and DD.
Value& operator()(std::size_t index);
const Value& operator()(std::size_t index) const;
Value& operator[](std::size_t index);
const Value& operator[](std::size_t index) const;
```

Returns the matrix element located in the row `index` and column `0`. These functions can only be called for compile-time vectors (`ct_cols == 1`), otherwise a static assertion violation will be generated.

*Parameters:*
* `index` - row position of the element to return.

### `data`
**Direct access to the underlying array**

```cpp
Value* data() noexcept;
const Value* data() const noexcept;
```

Returns the pointer to the underlying array of matrix element storage, the returned pointer is equal to the address of the `(0, 0)` matrix element.

### `eval`
**Evaluated expression**

```cpp
template<class Layout = Col_major>
Matrix<Value, ct_rows, ct_cols, Layout> eval() const
```

Returns a copy of the matrix.

*Parameters:*
* `Layout` - the [memory layout tag][2] of the resulting matrix.

### `view`, `view`
**Block views**

```cpp
template<std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols>
/* unspecified */ view();

template<std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols>
/* unspecified */ view() const;

template<std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols>
/* unspecified */ cview() const;

/* unspecified */ view(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols);
/* unspecified */ view(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols) const;
/* unspecified */ cview(std::size_t start_row, std::size_t rows, std::size_t start_col, std::size_t cols) const;
```

Returns the block (submatrix) view to the matrix with rows in the range `[start_row, start_row + rows)` and columns in the range `[start_col, start_col + cols)`. Views returned by `const`-qualified member functions provide an immutable access to the underlying matrix.

*Parameters:*
* `start_row` - index of the first row in the view,
* `rows` - number of rows in the view,
* `start_col` - index of the first column in the view,
* `cols` - number of columns in the view.

### `row_view`, `row_cview`, `rows_view`, `rows_cview`
**Row(s) views**

```cpp
// 1.
template<std::size_t index>
/* unspecified */ row_view();

template<std::size_t index>
/* unspecified */ row_view() const;

template<std::size_t index>
/* unspecified */ row_cview() const;

/* unspecified */ row_view(std::size_t index);
/* unspecified */ row_view(std::size_t index) const;
/* unspecified */ row_cview(std::size_t index) const;

// 2.
template<std::size_t start_row, std::size_t rows>
/* unspecified */ rows_view();

template<std::size_t start_row, std::size_t rows>
/* unspecified */ rows_view() const;

template<std::size_t start_row, std::size_t rows>
/* unspecified */ rows_cview() const;

/* unspecified */ rows_view(std::size_t start_row, std::size_t rows);
/* unspecified */ rows_view(std::size_t start_row, std::size_t rows) const;
/* unspecified */ rows_cview(std::size_t start_row, std::size_t rows) const;
```

1. Returns the view to the matrix row with the given index.
2. Returns the block view (submatrix) to the matrix with rows in the range `[start_row, start_row + rows)`.

Views returned by `const`-qualified member functions provide an immutable access to the underlying matrix.

*Parameters:*
* `index` - index of the row in the view,
* `start_row` - index of the first row in the view,
* `rows` - number of rows in the view.

### `col_view`, `col_cview`, `cols_view`, `cols_cview`
**Column(s) views**

Similar member functions for a column(s) view.

### `tr_view`
**Transposed view**

```cpp
/* unspecified */ tr_view();
/* unspecified */ tr_view() const;
/* unspecified */ tr_cview() const;
```

Returns the view to the transposed matrix. Views returned by `const`-qualified member functions provide an immutable access to the underlying matrix.

### `diag_view`
**Diagonal view**

```cpp
/* unspecified */ diag_view();
/* unspecified */ diag_view() const;
/* unspecified */ diag_cview() const;
```

Returns the (vector) view to the diagonal matrix elements. Views returned by `const`-qualified member functions provide an immutable access to the underlying matrix.

---

## Type aliases

```cpp
using Matrix_xd = Matrix<double, dynamic, dynamic>;
using Matrix_2d = Matrix<double, 2, 2>;
using Matrix_3d = Matrix<double, 3, 3>;

using Matrix_xf = Matrix<float, dynamic, dynamic>;
using Matrix_2f = Matrix<float, 2, 2>;
using Matrix_3f = Matrix<float, 3, 3>;

template<std::size_t rows, std::size_t cols, class Layout = Col_major>
using Matrix_d = Matrix<double, rows, cols, Layout>;

template<std::size_t rows, std::size_t cols, class Layout = Col_major>
using Matrix_f = Matrix<float, rows, cols, Layout>;

template<typename Value, class Layout = Col_major>
using Matrix_x = Matrix<Value, dynamic, dynamic, Layout>;

template<typename Value, std::size_t size>
using Vector = Matrix<Value, size, 1>;

using Vector_xd = Vector<double, dynamic>;
using Vector_2d = Vector<double, 2>;
using Vector_3d = Vector<double, 3>;

using Vector_xf = Vector<float, dynamic>;
using Vector_2f = Vector<float, 2>;
using Vector_3f = Vector<float, 3>;

template<std::size_t size>
using Vector_d = Vector<double, size>;

template<std::size_t size>
using Vector_f = Vector<float, size>;

template<typename Value>
using Vector_x = Matrix<Value, dynamic, 1>;
```

[1]: tags.md#extents
[2]: tags.md#memory-layouts
