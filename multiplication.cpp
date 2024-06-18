#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    // Check validation
    if (matrix1[0].size() != matrix2.size()) {
        throw std::runtime_error("Matrices must have compatible dimensions for multiplication.");
    }

    // Check if maximum 6x6
    if (matrix1.size() > 6 || matrix1[0].size() > 6 || matrix2.size() > 6 || matrix2[0].size() > 6) {
        throw std::runtime_error("Matrix size must not exceed 100x100.");
    }

    std::size_t rows1 = matrix1.size();
    std::size_t cols2 = matrix2[0].size();
    std::size_t cols1 = matrix1[0].size();

    std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0.0));

    for (std::size_t i = 0; i < rows1; i++) {
        for (std::size_t j = 0; j < cols2; j++) {
            for (std::size_t k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}
