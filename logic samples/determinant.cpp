#include <iostream>
#include <vector>
#include <cmath>

// Function to multiply two matrices
std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    int m1_rows = matrix1.size();
    int m1_cols = matrix1[0].size();
    int m2_cols = matrix2[0].size();

    std::vector<std::vector<double>> result(m1_rows, std::vector<double>(m2_cols, 0.0));

    for (int i = 0; i < m1_rows; i++) {
        for (int j = 0; j < m2_cols; j++) {
            for (int k = 0; k < m1_cols; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main() {
    // Example 1: Multiply two 3x2 and 2x3 matrices
    std::vector<std::vector<double>> matrix1 = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    std::vector<std::vector<double>> matrix2 = {{7.0, 8.0, 9.0}, {10.0, 11.0, 12.0}};
    std::vector<std::vector<double>> result1 = multiplyMatrices(matrix1, matrix2);

    std::cout << "Example 1:\nMatrix 1:\n";
    for (const auto& row : matrix1) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix 2:\n";
    for (const auto& row : matrix2) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nResult:\n";
    for (const auto& row : result1) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    // Example 2: Multiply two 2x3 and 3x2 matrices
    std::vector<std::vector<double>> matrix3 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    std::vector<std::vector<double>> matrix4 = {{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};
    std::vector<std::vector<double>> result2 = multiplyMatrices(matrix3, matrix4);

    std::cout << "\nExample 2:\nMatrix 1:\n";
    for (const auto& row : matrix3) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix 2:\n";
    for (const auto& row : matrix4) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nResult:\n";
    for (const auto& row : result2) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    // Example 3: Multiply two 1x4 and 4x1 matrices
    std::vector<std::vector<double>> matrix5 = {{1.0, 2.0, 3.0, 4.0}};
    std::vector<std::vector<double>> matrix6 = {{5.0}, {6.0}, {7.0}, {8.0}};
    std::vector<std::vector<double>> result3 = multiplyMatrices(matrix5, matrix6);

    std::cout << "\nExample 3:\nMatrix 1:\n";
    for (const auto& row : matrix5) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix 2:\n";
    for (const auto& row : matrix6) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nResult:\n";
    for (const auto& row : result3) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
