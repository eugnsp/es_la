# Linear algebra library

This is a linear algebra library that was written mostly for educational purposes.
It is also extensively used in the [`es_fe` library](https://github.com/eugnsp/es_fe)
for finite elements.

Main features:
* Dense matrices and vectors of strandard and user-defined types
with static and dynamic extents.
* Matrices with static extents can be used in `constexpr` context.
* Sub-matrix (block) and transposed views.
* Expression templates.
* Sparse matrices with CSR storage scheme.
* Some expressions like `X * Y` or `aX + bY` with `double` matrix
elements are evaluated using MKL routines.
* Export in MATLAB `.mat` and Gnuplot binary matrix files.
* MKL Pardiso linear solver and MKL Feast eigensolver wrappers.
