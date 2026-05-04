#ifndef MATRIX_OPS_HPP
#define MATRIX_OPS_HPP

#include <vector>

using Matrix = std::vector<double>;

void multiply_std(const Matrix& A, const Matrix& B, Matrix& C, int n);

#endif
