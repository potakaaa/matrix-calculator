#include <iostream>
using namespace std;

int main() {
    int matrix_rows = 3; int matrix_cols = 3; int matrix_size = matrix_rows * matrix_cols;
    
    int grid_row = 0; int grid_col = 0;
    
    for (grid_row = 0; grid_row <= matrix_rows; grid_row++) {
        for (grid_col = 0; grid_col <= matrix_cols; grid_col++) {
            cout << "Grid Rows: " << grid_row << " Grid Cols: " << grid_col << endl;
        }
    }
}
