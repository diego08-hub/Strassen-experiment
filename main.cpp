#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "matrix_ops.hpp"

Matrix generate_random_matrix(int n) {
    Matrix mat(n * n);
    std::random_device rd;
    static std::mt19937 gen(42); //Motor Mersenne Twister
    std::uniform_real_distribution<> dis(1.0, 10.0);
    
    for (int i = 0; i < n * n; ++i) {
        mat[i] = dis(gen);
    }
    return mat;
}

int main() {
    std::vector<int> sizes = {16, 32, 64, 128, 256, 512};
    int repetitions = 10;

    std::cout << "n,time_ms" << std::endl;

    for (int n : sizes) {
        double total_time = 0;

        for (int r = 0; r < repetitions; ++r) {
        Matrix A = generate_random_matrix(n);
        Matrix B = generate_random_matrix(n);
        Matrix C(n * n, 0.0);

        auto start = std::chrono::high_resolution_clock::now();

        multiply_std(A, B, C, n);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;

        total_time += elapsed.count();
        }
    //Promedio
    std::cout << n << "," << total_time / repetitions << std::endl;
    }
return 0;
}
