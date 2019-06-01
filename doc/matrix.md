# Dense matrices

Header: `<es_la/dense.hpp>`\
Namespace: `es_la`

---

```cpp
template<typename Value_, std::size_t ct_rows, std::size_t ct_cols, class Layout>
class Matrix;
```

*Template parameters:*
* `Value_` - the type of elements,
* `ct_rows` - number of rows fixed at compile-time or `dynamic`,
* `ct_cols` - number of columns fixed at compile-time or `dynamic`,
* `Layout` - matrix memory layout (`Row_major` or `Col_major`).

Storage for matrix elements of static matrices (`ct_rows != dynamic` and `ct_cols != dynamic`) is allocated inside a `Matrix` object itself. Storage for matrix elements of dynamic matrices (`ct_rows == dynamic` or `ct_cols == dynamic`) is allocated dynamically.

The following notation is used for specializations below:
```cpp
SS = Matrix<Value, ct_rows, ct_cols, Layout> with ct_rows != dynamic && ct_cols != dynamic
SD = Matrix<Value, ct_rows, dynamic, Layout> with ct_rows != dynamic
DS = Matrix<Value, dynamic, ct_cols, Layout> with ct_cols != dynamic
DD = Matrix<Value, dynamic, dynamic, Layout>
```

---

## Member types

```cpp
using Value = Value_;
```
---

## Member functions

### `Matrix`
**Constructors**

1\. Specialization `Matrix<Value, ct_rows, ct_cols, Layout>` with `ct_rows != dynamic` and `ct_cols != dynamic`

```cpp
Matrix() = default;
```

Default constructor. Constructs the matrix with default or value initialized matrix elements.

```cpp
explicit Matrix(const Value& value);
```

Constructs the matrix with matrix elements initialized with the copies of `value`.

*Parameters:*
* `value` - the value to initialize matrix elements with.

```cpp
template<typename... Values>
explicit constexpr Matrix(Values&&... values);
```

Constructs the matrix with matrix elements contiguously initialized with the values `values`. This constructor participates in overload resolution only if the number of arguments is equal to `ct_rows * ct_cols` and if each argument is convertible to `Value` using implicit conversions.

*Parameters:*
* `values` - the values to initialize matrix elements with.

2\. Specialization `Matrix<Value, ct_rows, dynamic, Layout>` with `ct_rows != dynamic`

```cpp
Matrix() = default;
```

Default constructor. Constructs the empty matrix.

```cpp
explicit Matrix(std::size_t cols);
```

Constructs the matrix with `cols` columns and default constructed matrix elements.

*Parameters:*
* `cols` - the number of columns.

```cpp
Matrix(std::size_t cols, const Value& value);
```

Constructs the matrix with `cols` columns and matrix elements initialized with the copies of `value`.

*Parameters:*
* `cols` - the number of columns,
* `value` - the value to initialize matrix elements with.

```cpp
Matrix(std::size_t cols, std::initializer_list<Value> values);
```

```cpp
Matrix(std::initializer_list<Value> values);
```

3\. Specialization `Matrix<Value, dynamic, ct_cols, Layout>` with `ct_cols != dynamic`

Similar to the previous specialization.

4\. Specialization `Matrix<Value, dynamic, dynamic, Layout>`

```cpp
Matrix() = default;
```

Default constructor. Constructs the empty matrix.

```cpp
explicit Matrix(std::size_t rows, std::size_t cols);
```

Constructs the matrix with `rows` rows and `cols` columns and default constructed matrix elements.

*Parameters:*
* `rows` - the number of rows,
* `cols` - the number of columns.

```cpp
Matrix(std::size_t rows, std::size_t cols, const Value& value);
```

Constructs the matrix with `rows` rows and `cols` columns and matrix elements initialized with the copies of `value`.

*Parameters:*
* `rows` - the number of rows,
* `cols` - the number of columns,
* `value` - the value to initialize matrix elements with.

```cpp
Matrix(std::size_t rows, std::size_t cols, std::initializer_list<Value> values);
```

### `is_empty`, `rows`, `cols`, `size`, `capacity`

```cpp
// 1.
static constexpr bool is_empty();
// 2.
bool is_empty() const;
```

1. For the specialization `SS`.
2. For the specializations `SD`, `DS`, and `DD`.

Checks if the matrix has zero number of elements.

*Return value:*
`true` if the matrix is empty, and `false` otherwise.

```cpp
// 1.
static constexpr std::size_t rows();
// 2.
std::size_t rows() const;
```

1. For the specializations `SS`, and `SD`.
2. For the specializations `DS`, and `DD`.

Returns the number of rows in the matrix.

```cpp
// 1.
static constexpr std::size_t cols();
// 2.
std::size_t cols() const;
```

1. For the specializations `SS`, and `DS`.
2. For the specializations `SD`, and `DD`.

Returns the number of columns in the matrix.

```cpp
// 1.
static constexpr std::size_t size();
// 2.
std::size_t size() const;
```

1. For the specialization `SS`.
2. For the specializations `SD`, `DS`, and `DD`.

Returns the number of matrix elements (`= rows() * cols()`).

```cpp
// 1.
static constexpr std::size_t capacity();
// 2.
std::size_t capacity() const;
```

1. For the specialization `SS` (`= size()`).
2. For the specializations `SD`, `DS`, and `DD`.

Returns the number of elements that the matrix has currently allocated space for.

### `operator()`, `operator[]`
**Retrieves the given matrix element**

```cpp
// 1.
constexpr Value& operator()(std::size_t row, std::size_t col);
constexpr const Value& operator()(std::size_t row, std::size_t col) const;
// 2.
Value& operator()(std::size_t row, std::size_t col);
const Value& operator()(std::size_t row, std::size_t col) const;
```

1. For the specialization `SS`.
2. For the specializations `SD`, `DS`, and `DD`.

Returns the matrix element located in the row `row` and column `col`.

*Parameters:*
* `row` - row position of the element to return,
* `col` - column position of the element to return.

```cpp
// 1.
constexpr Value& operator()(std::size_t index);
constexpr const Value& operator()(std::size_t index) const;
constexpr Value& operator[](std::size_t index);
constexpr const Value& operator[](std::size_t index) const;
// 2.
Value& operator()(std::size_t index);
const Value& operator()(std::size_t index) const;
Value& operator[](std::size_t index);
const Value& operator[](std::size_t index) const;
```

1. For the specialization `SS`.
2. For the specializations `SD`, `DS`, and `DD`.

Returns the matrix element located in the row `index` and column `0`. These functions can only be called for compile-time vectors (`ct_cols == 1`), otherwise a static assert violation will be generated.

*Parameters:*
* `index` - row position of the element to return.

### `data`
**Direct access to the underlying array**

```cpp
Value* data() noexcept;
const Value* data() const noexcept;
```

Returns the pointer to the underlying array serving as matrix element storage, the returned pointer is equal to the address of the `(0, 0)` matrix element.

<!--
### `get`
**Retrieves all elements**

```cpp
template<class Random_access_iterator>
void get(Random_access_iterator dest);
```

Stores all elements in the range `[dest, dest + size)`, where `size` is the size of the container.

*Parameters:*
* `dest` - the beginning of the destination range, should be a random access iterator.

*Time complexity:* linear in the size of the container, `O(size())`.

### `sum`
**Range sum calculation**

```cpp
// 1.
Value sum(Size first, Size last) const;
// 2.
Value sum(Size index) const;
// 3.
Value sum() const;
```

1. Returns the sum of elements in the closed range `[first, last]`.
2. Returns the prefix sum, i.e. the sum of elements in the closed range `[0, index]`.
3. Returns the sum of all element in the container. *Precondition:* the container should be non-empty.

*Parameters:*
* `first`, `last` - the range of elements to calculate the sum of.
* `index` - index of the last element in the range to calculate the sum of.

*Time complexity:* logarithmic in the size of the container, `O(log(size()))`.

### `lower_bound`, `upper_bound`
**Lower/upper bound binary search in a Fenwick tree with non-decreasing prefix sums**

```cpp
// 1.
Size lower_bound(Value value) const;
// 2.
Size upper_bound(Value value) const;
```

1. Returns the smallest index such that the prefix sum is not less than the value `value`, or the container's size if no such index exists.
2. Returns the smallest index such that the prefix sum is greater than the value `value`, or the container's size if no such index exists.

*Precondition:* the container should be non-empty and all elements should be non-negative, so that the sequence of all prefix sums is non-decreasing (sorted).

*Time complexity:* logarithmic in the size of the container, `O(log(size()))`.

### `reset`
**Replaces the contents of the container**

```cpp
// 1.
void reset(Size size);
// 2.
void reset(std::vector<Value> data);
// 3.
void reset(Input_iterator1 first, Input_iterator2 last);
```

1. Replaces the contents with `size` copies of the zero value (`= Value{}`).
2. Replaces the contents with the contents of `data`.
3. Replaces the contents with copies of values in the range `[first, last)`.

*Parameters:*
* `size` - the new size of the container,
* `data` - the vector to move the contents from,
* `first`, `last` - the range to copy the elements from.

*Time complexity:* linear in the new size of the container, 1. `O(size)`, 2. `O(data.size())`, 3. `O(last - first)`.

### `add`
**Increments the given element**

```cpp
void add(Size index, const Value& value);
```

Adds the value `value` to the element with the index `index`.

*Parameters:*
* `index` - index of the element to add to,
* `value` - value to add.

*Time complexity:* logarithmic in the size of the container, `O(log(size()))`.

### `set`
**Sets the given element**

```cpp
void set(Size index, const Value& value);
```

Sets the value of the element with the index `index` to `value`.

*Parameters:*
* `index` - index of the element to add to,
* `value` - value to set.

*Time complexity:* logarithmic in the size of the container, `O(log(size()))`.

### `push`
**Adds an element to the end*

```cpp
void push(const Value& value);
```

Appends the given element value to the end of the container.

*Parameters:*
* `value` - value to append.

*Time complexity:* logarithmic in the size of the container, `O(log(size()))`.

### `pop`
**Removes the last element*

```cpp
void pop();
```

Removes the last element of the container.

*Time complexity:* constant.
-->
