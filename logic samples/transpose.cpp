#include <iostream>
#include <vector>

using namespace std;

// Function to transpose a matrix
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<std::vector<double>> transposed(cols, std::vector<double>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

int main() {
    // Example 1: 3x2 matrix
    std::vector<std::vector<double>> matrix1 = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    std::vector<std::vector<double>> transposed1 = transpose(matrix1);

    std::cout << "Example 1:\nOriginal matrix:\n";
    for (const auto& row : matrix1) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nTransposed matrix:\n";
    for (const auto& row : transposed1) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    // Example 2: 2x3 matrix
    std::vector<std::vector<double>> matrix2 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    std::vector<std::vector<double>> transposed2 = transpose(matrix2);

    std::cout << "\nExample 2:\nOriginal matrix:\n";
    for (const auto& row : matrix2) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nTransposed matrix:\n";
    for (const auto& row : transposed2) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    // Example 3:1x4 matrix
    std::vector<std::vector<double>> matrix3 = {{1.0, 2.0, 3.0, 4.0}};
    std::vector<std::vector<double>> transposed3 = transpose(matrix3);

    std::cout << "\nExample 3:\nOriginal matrix:\n";
    for (const auto& row : matrix3) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nTransposed matrix:\n";
    for (const auto& row : transposed3) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
