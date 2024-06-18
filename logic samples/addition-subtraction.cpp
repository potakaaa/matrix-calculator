#include <iostream>
#include <vector>

using namespace std;

std::vector<std::vector<double>> addMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw std::runtime_error("Matrices must have the same dimensions for addition.");
    }

    if (matrix1.size() > 6 || matrix1[0].size() > 6 || matrix2.size() > 6 || matrix2[0].size() > 6) {
        throw std::runtime_error("Matrix size must not exceed 6x6.");
    }

    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t j = 0; j < matrix1[0].size(); j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> subtractMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw std::runtime_error("Matrices must have the same dimensions for subtraction.");
    }

    if (matrix1.size() > 6 || matrix1[0].size() > 6 || matrix2.size() > 6 || matrix2[0].size() > 6) {
        throw std::runtime_error("Matrix size must not exceed 6x6.");
    }

    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t j = 0; j < matrix1[0].size(); j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    return result;
}

int main() {
    // Example 1: Adding two 2x2 matrices
    std::vector<std::vector<double>> matrix1 = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> matrix2 = {{5, 6}, {7, 8}};

    try {
        std::vector<std::vector<double>> result = addMatrices(matrix1, matrix2);
        std::cout << "Addition of matrices:" << std::endl;
        for (const auto& row : result) {
            for (double element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Example 2: Subtracting two 3x3 matrices
    std::vector<std::vector<double>> matrix3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<double>> matrix4 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    try {
        std::vector<std::vector<double>> result = subtractMatrices(matrix3, matrix4);
        std::cout << "\nSubtraction of matrices:" << std::endl;
        for (const auto& row : result) {
            for (double element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Example 3: Trying to add matrices with different dimensions
    std::vector<std::vector<double>> matrix5 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> matrix6 = {{7, 8}, {9, 10}, {11, 12}};

    try {
        std::vector<std::vector<double>> result = addMatrices(matrix5, matrix6);
        std::cout << "\nAddition of matrices:" << std::endl;
        for (const auto& row : result) {
            for (double element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
