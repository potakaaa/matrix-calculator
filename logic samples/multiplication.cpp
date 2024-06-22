#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    int m1_rows = matrix1.size();
    int m1_cols = matrix1[0].size();
    int m2_cols = matrix2[0].size();

    cout << matrix1.size() << endl;
    cout << matrix1[0].size() << endl;
    cout << matrix2[0].size() << endl;

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

double determinant(const std::vector<std::vector<double>>& matrix) {
    // Determinant function implementation
    return 0;
}

int main() {
    // Example usage 1
    
    std::vector<std::vector<double>> matrix1 = {{4, 7}, {2, 6}};
    std::vector<std::vector<double>> matrix2 = {{0.6, -0.7}, {-0.2, 0.4}};

    std::vector<std::vector<double>> result = multiplyMatrices(matrix1, matrix2);

    std::cout << "Example 1 - Multiplication Result:" << std::endl;
    for (const auto& row : result) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    double det = determinant(matrix1);
    std::cout << "Determinant: " << det << std::endl;

    // Example 2: Multiplying  2x3*3x2 
    std::vector<std::vector<double>> matrix3 = {{1, 2}, {3, 4}, {5, 6}};
    std::vector<std::vector<double>> matrix4 = {{7, 8}, {9, 10}, {11, 12}};

    std::vector<std::vector<double>> result2 = multiplyMatrices(matrix3, matrix4);

    std::cout << "Example 2 - Multiplication Result:" << std::endl;
    for (const auto& row : result2) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    // Example 3: Multiplying a 3x2*2x3
    std::vector<std::vector<double>> matrix5 = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> matrix6 = {{-2, 1}, {1.5, -0.5}};

    std::vector<std::vector<double>> result3 = multiplyMatrices(matrix5, matrix6);

    std::cout << "Example 3 - Multiplication Result:" << std::endl;
    for (const auto& row : result3) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
