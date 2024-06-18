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
