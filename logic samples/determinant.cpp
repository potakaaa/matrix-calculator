#include <iostream>
#include <vector>
#include <cmath>

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
