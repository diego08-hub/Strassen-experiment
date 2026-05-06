#include "matrix_ops.hpp"

// Funciones auxiliares (Agrégalas arriba de multiply_strassen)
void add(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] + B[i];
}

void subtract(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] - B[i];
}
