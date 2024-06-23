#ifndef INVERSE_H
#define INVERSE_H
#include <vector>
using namespace std;
#endif // INVERSE_H

double determinant(const vector<vector<double>>& matrix) {
    int n = matrix.size();

    if (n == 1) {
        return matrix[0][0];
    }

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0;
    for (int i = 0; i < n; ++i) {
        vector<vector<double>> submatrix(n - 1, vector<double>(n - 1));
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (k < i) {
                    submatrix[j - 1][k] = matrix[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = matrix[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix);
    }

    return det;
}

// Function to calculate the matrix minor
vector<vector<double>> matrixMinor(const vector<vector<double>>& matrix, int row, int col) {
    int n = matrix.size();
    vector<vector<double>> minorMatrix(n - 1, vector<double>(n - 1));

    for (int i = 0, k = 0; i < n; ++i) {
        if (i == row) continue;
        for (int j = 0, l = 0; j < n; ++j) {
            if (j == col) continue;
            minorMatrix[k][l] = matrix[i][j];
            ++l;
        }
        ++k;
    }

    return minorMatrix;
}

// Function to calculate the matrix of cofactors
vector<vector<double>> matrixOfCofactors(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    vector<vector<double>> cofactors(n, vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double minorDet = determinant(matrixMinor(matrix, i, j));
            cofactors[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minorDet;
        }
    }

    return cofactors;
}

// Function to calculate the transpose of a matrix
vector<vector<double>> matrixTranspose(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    vector<vector<double>> transpose(n, vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transpose[i][j] = matrix[j][i];
        }
    }

    return transpose;
}

// Function to calculate the inverse of a matrix
vector<vector<double>> inverseMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    double det = determinant(matrix);

    // Check if determinant is zero, inverse doesn't exist

    vector<vector<double>> cofactors = matrixOfCofactors(matrix);
    vector<vector<double>> adjugate = matrixTranspose(cofactors);

    vector<vector<double>> inverse(n, vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverse[i][j] = adjugate[i][j] / det;
        }
    }

    return inverse;
}
