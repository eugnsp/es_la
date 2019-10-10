# Linear algebra library

:construction: Under construction.

## Synopsis

This is a linear algebra library that is being developed mostly for educational purposes. It is also extensively used in the [`esf` library](https://github.com/eugnsp/esf) for finite elements.

## Main features

* Dense matrices and vectors of strandard and user-defined types with static and dynamic extents
* Matrices with static extents can be used in `constexpr` context
* Sub-matrix (block) and transposed views
* Expression templates
* Sparse matrices with CSR storage scheme
* Some operations like `X = Y` or `X += Y` with `float`, `double`, `std::complex<float>`, and `std::complex<double>` matrix elements are mapped into MKL routines
* Export in MATLAB `.mat` and Gnuplot binary matrix files
* MKL inspector-executor sparse matrix wrapper
* MKL Pardiso linear solver and MKL Feast eigensolver wrappers

## Dependencies

* Intel MKL
* [`esu` utilities library](https://github.com/eugnsp/esu)

Requires C++17 compiler. Tested with GCC 8.3.0 and Clang 7.0.0.

## Documentation

See [here](doc/README.md).
