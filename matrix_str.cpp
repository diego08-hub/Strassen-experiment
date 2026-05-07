#include "matrix_ops.hpp"

// Funciones auxiliares (Agrégalas arriba de multiply_strassen)
void add(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] + B[i];
}

void subtract(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] - B[i];
}
int next_power_of_2(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}
void multiply_strassen(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    //Umbral empírico
    if (n <= 32) {
        multiply_std(A, B, C, n);
        return;
    }

    int k = n / 2;
    int size = k * k;

    // Submatrices
    Matrix a11(size), a12(size), a21(size), a22(size);
    Matrix b11(size), b12(size), b21(size), b22(size);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            a11[i * k + j] = A[i * n + j];           // Top-left
            a12[i * k + j] = A[i * n + (j + k)];     // Top-right
            a21[i * k + j] = A[(i + k) * n + j];     // Bottom-left
            a22[i * k + j] = A[(i + k) * n + (j + k)];// Bottom-right

            b11[i * k + j] = B[i * n + j];
            b12[i * k + j] = B[i * n + (j + k)];
            b21[i * k + j] = B[(i + k) * n + j];
            b22[i * k + j] = B[(i + k) * n + (j + k)];
        }
    }
    Matrix p1(size), p2(size), p3(size), p4(size), p5(size), p6(size), p7(size);
    Matrix aux1(size), aux2(size);
    // P1 = A11 * (B12 - B22)
    subtract(b12, b22, aux2, k);
    multiply_strassen(a11, aux2, p1, k);
    // P2 = (A11 + A12) * B22
    add(a11, a12, aux1, k);
    multiply_strassen(aux1, b22, p2, k);
    // P3 = (A21 + A22) * B11
    add(a21, a22, aux1, k);
    multiply_strassen(aux1, b11, p3, k);
    // P4 = A22 * (B21 - B11)
    subtract(b21, b11, aux2, k);
    multiply_strassen(a22, aux2, p4, k);
    // P5 = (A11 + A22) * (B11 + B22)
    add(a11, a22, aux1, k);
    add(b11, b22, aux2, k);
    multiply_strassen(aux1, aux2, p5, k);
    // P6 = (A12 - A22) * (B21 + B22)
    subtract(a12, a22, aux1, k);
    add(b21, b22, aux2, k);
    multiply_strassen(aux1, aux2, p6, k);
    // P7 = (A21 - A11) * (B11 + B12)
    subtract(a21, a11, aux1, k);
    add(b11, b12, aux2, k);
    multiply_strassen(aux1, aux2, p7, k);
    
    //  Unir
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            int idx = i * k + j;
            // C11
            C[i * n + j] = p5[idx] + p4[idx] - p2[idx] + p6[idx];
            // C12
            C[i * n + (j + k)] = p1[idx] + p2[idx];
            // C21
            C[(i + k) * n + j] = p3[idx] + p4[idx];
            // C22
            C[(i + k) * n + (j + k)] = p5[idx] + p1[idx] - p3[idx] + p7[idx];
        }
    }
}
void multiply_strassen_any_size(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    // Ya es potencia de 2?
    int m = next_power_of_2(n);
    
    if (m == n) {
        multiply_strassen(A, B, C, n);
        return;
    }

    // Padding con ceros
    Matrix A_padded(m * m, 0.0);
    Matrix B_padded(m * m, 0.0);
    Matrix C_padded(m * m, 0.0);

    // Copiar 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_padded[i * m + j] = A[i * n + j];
            B_padded[i * m + j] = B[i * n + j];
        }
    }

    // Ejecutar Strassen
    multiply_strassen(A_padded, B_padded, C_padded, m);

    // Copiar el resultado de vuelta a la matriz C original (recortar)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = C_padded[i * m + j];
        }
    }
}