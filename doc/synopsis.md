# Linear algebra library

:construction: Under construction.

## Synopsis

### Dense matrices

```cpp
namespace es_la
{
template<typename Value_, std::size_t ct_rows, std::size_t ct_cols, class Layout>
class Matrix;

class MatrixValue_, ct_rows, ct_cols, Layout>
{
	static_assert(ct_rows != dynamic && ct_cols != dynamic);

public:
	using Value = Value_;

	Matrix() = default;
	explicit Matrix(const Value&);

	template<typename... Values>
	explicit constexpr Matrix(Values&&...);

	static constexpr bool is_empty();
	static constexpr std::size_t rows();
	static constexpr std::size_t cols();
	static constexpr std::size_t size();
	static constexpr std::size_t capacity();

	constexpr Value& operator()(std::size_t, std::size_t);
	constexpr const Value& operator()(std::size_t, std::size_t) const;

	constexpr Value& operator()(std::size_t);
	constexpr const Value& operator()(std::size_t) const;

	constexpr Value& operator[](std::size_t);
	constexpr const Value& operator[](std::size_t) const;

	Value* data();
	const Value* data() const;
}

class Matrix<Value_, ct_rows, dynamic, Layout>
{
	static_assert(ct_rows != dynamic);

public:
	using Value = Value_;

	Matrix() = default;
	explicit Matrix(std::size_t cols);
	Matrix(std::size_t cols, const Value&);
	Matrix(std::size_t cols, std::initializer_list<Value>);
	Matrix(std::initializer_list<Value>);

	bool is_empty() const;
	static constexpr std::size_t rows();
	std::size_t cols() const;
	std::size_t size() const;
	std::size_t capacity() const;

	Value& operator()(std::size_t, std::size_t);
	const Value& operator()(std::size_t, std::size_t) const;

	Value& operator()(std::size_t);
	const Value& operator()(std::size_t) const;

	Value& operator[](std::size_t);
	const Value& operator[](std::size_t) const;

	Value* data();
	const Value* data() const;
}

class Matrix<Value_, dynamic, ct_cols, Layout>
{
	static_assert(ct_cols != dynamic);

public:
	using Value = Value_;

	Matrix() = default;
	explicit Matrix(std::size_t rows);
	Matrix(std::size_t rows, const Value&);
	Matrix(std::size_t rows, std::initializer_list<Value>);
	Matrix(std::initializer_list<Value>);

	bool is_empty() const;
	std::size_t rows() const;
	static constexpr std::size_t cols();
	std::size_t size() const;
	std::size_t capacity() const;

	Value& operator()(std::size_t, std::size_t);
	const Value& operator()(std::size_t, std::size_t) const;

	Value& operator()(std::size_t);
	const Value& operator()(std::size_t) const;

	Value& operator[](std::size_t);
	const Value& operator[](std::size_t) const;

	Value* data();
	const Value* data() const;
}

class Matrix<Value_, dynamic, dynamic, Layout>
{
public:
	using Value = Value_;

	Matrix() = default;
	explicit Matrix(std::size_t rows, std::size_t cols);
	Matrix(std::size_t rows, std::size_t cols, const Value&);
	Matrix(std::size_t rows, std::size_t cols, std::initializer_list<Value>);

	bool is_empty() const;
	std::size_t rows() const;
	std::size_t cols() const;
	std::size_t size() const;
	std::size_t capacity() const;

	Value& operator()(std::size_t, std::size_t);
	const Value& operator()(std::size_t, std::size_t) const;

	Value& operator()(std::size_t);
	const Value& operator()(std::size_t) const;

	Value& operator[](std::size_t);
	const Value& operator[](std::size_t) const;

	Value* data();
	const Value* data() const;
}
```

[Detailed description](matrix.md)
