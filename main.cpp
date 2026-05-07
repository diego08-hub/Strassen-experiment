#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <cmath>
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

//Si las matrices son iguales, con error flotante
bool verify(const Matrix& A, const Matrix& B, int n) {
    for (int i = 0; i < n * n; ++i) {
        if (std::abs(A[i] - B[i]) > 1e-5) return false;
    }
    return true;
}

int main() {
    std::vector<int> sizes = {4, 8, 16, 20, 28, 32, 36, 48, 64, 100, 128, 256, 512};
    int repetitions = 5;

    //Dirigir datos
    std::ofstream csv_file("resultados.csv");
    csv_file << "n,std_ms,strassen_ms\n";

    std::cout << "n,time_ms" << std::endl;

    for (int n : sizes) {
        double total_time_std = 0;
	double total_time_str = 0;
	bool is_correct = true;

        for (int r = 0; r < repetitions; ++r) {
        Matrix A = generate_random_matrix(n);
        Matrix B = generate_random_matrix(n);
        Matrix C_std(n * n, 0.0);
	Matrix C_str(n*n,0.0);

	//Medida estandar
	auto start = std::chrono::high_resolution_clock::now();
        multiply_std(A, B, C_std, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        total_time_std += elapsed.count();

	//Medida strassen
	start = std::chrono::high_resolution_clock::now();
    	multiply_strassen(A, B, C_str, n);
    	end = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double, std::milli> t_str = end - start;
	total_time_str += t_str.count();

	//si son iguales, solo primera
	if (r == 0 && !verify(C_std, C_str, n)) {
                is_correct = false;
            }
        }
    //Promedio
    std::cout << "n,std_ms,strassen_ms" << std::endl;
    std::cout << n << ","
          << total_time_std / repetitions << ","
          << total_time_str / repetitions << std::endl;

    csv_file << n << "," << total_time_std << "," << total_time_str << "\n";
    }
    csv_file.close();
    std::cout << "Datos guardados en resultados.csv" << std::endl;
    return 0;
}
