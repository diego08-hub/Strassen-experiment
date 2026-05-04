#include <vector> //Matriz 1D

// Alias al vector
using Matrix = std::vector<double>;

// Complejidad O(n^3)

void multiply_std(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k) {
                // Formula
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}
