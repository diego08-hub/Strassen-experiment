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
    std::vector<int> sizes = {4, 6, 8, 10, 14, 16, 20, 28, 32, 36, 40, 48, 64, 90, 100, 128, 256, 302, 416, 512};
    int repetitions = 10;

    //Dirigir datos
    std::ofstream csv_file("resultados.csv");
    csv_file << "n,std_ms,strassen_ms\n";

    std::cout << "n,time_ms" << std::endl;
	std::cout << "n\tStd(ms)\tStr(ms)\tStatus" << std::endl;

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
    		multiply_strassen_any_size(A, B, C_str, n);
    		end = std::chrono::high_resolution_clock::now();
    		std::chrono::duration<double, std::milli> t_str = end - start;
			total_time_str += t_str.count();

			//si son iguales, solo primera
			if (r == repetitions-1 && !verify(C_std, C_str, n)) {
	                is_correct = false;
        	    }
       	 }
		//Promedio
		total_time_std /= repetitions;
		total_time_str /= repetitions;
		
		csv_file << n << "," << total_time_std << "," << total_time_str << "\n";
    	
    	
    	std::cout << n << "\t"
			<< total_time_std << "\t"
			<< total_time_str << "\t"
		    << (is_correct ? "OK" : "ERROR") << std::endl;
    }

    csv_file.close();
    std::cout << "Datos guardados en resultados.csv" << std::endl;
    return 0;
}
