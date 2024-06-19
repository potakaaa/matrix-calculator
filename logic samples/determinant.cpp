#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the determinant of a matrix
double determinant(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    
    // Base case: 1x1 matrix
    if (n == 1) {
        return matrix[0][0];
    }
    
    // Base case: 2x2 matrix
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    
    double det = 0;
    
    // Calculate the determinant using the Laplace expansion
    for (int i = 0; i < n; i++) {
        // Create the submatrix
        vector<vector<double>> submatrix(n - 1, vector<double>(n - 1));
        for (int j = 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (k < i) {
                    submatrix[j - 1][k] = matrix[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = matrix[j][k];
                }
            }
        }
        
        // Add the contribution of the current element to the determinant
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix);
    }
    
    return det;
}

int main() {
    // Example 1: 3x3 matrix with non-zero and non-negative determinant
    vector<vector<double>> matrix3x3 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 11}
    };
    
    double det3x3 = determinant(matrix3x3);
    cout << "Determinant of the 3x3 matrix: " << det3x3 << endl;
    
    // Example 2: 2x2 matrix
    vector<vector<double>> matrix2x2= {
        {3, 0},
        {4, 5}
    };
    
    double det2x2 = determinant(matrix2x2);
    cout << "Determinant of the 2x2 matrix: " << det2x2 << endl;
    
    // Example 3: 5x5 matrix
    vector<vector<double>> matrix5x5 = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    
    double det5x5 = determinant(matrix5x5);
    cout << "Determinant of the 5x5 matrix: " << det5x5 << endl;
    
    return 0;
}
