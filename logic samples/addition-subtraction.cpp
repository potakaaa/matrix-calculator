#include <iostream>
using namespace std;

// Good!

int main()
{
    int row1, column1, row2, column2;
    cout << "Enter size of row for first matrix (1-6):";
    cin >> row1;
    cout << "Enter size of column for first matrix (1-6):";
    cin >> column1;
    int matx1[row1][column1];
    cout << "Enter first matrix element:";
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < column1; j++)
        {
            cin >> matx1[i][j];
        }
    }
    cout << "First matrix element:\n";
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < column1; j++)
        {
            cout << matx1[i][j] << " ";
        }
        cout << "\n";
    }

    // Second matrix
    cout << "Enter size of row for second matrix:";
    cin >> row2;
    cout << "Enter size of column for second matrix:";
    cin >> column2;
    int matx2[row2][column2];
    cout << "Enter second matrix element:";
    for (int i = 0; i < row2; i++)
    {
        for (int j = 0; j < column2; j++)
        {
            cin >> matx2[i][j];
        }
    }
    cout << "Second matrix element:\n";
    for (int i = 0; i < row2; i++)
    {
        for (int j = 0; j < column2; j++)
        {
            cout << matx2[i][j] << " ";
        }
        cout << "\n";
    }

    // Check if matrices are of the same size
    if (row1 == row2 && column1 == column2)
    {
        int result[row1][column2];
        char operation;
        cout << "Enter '+' for addition or '-' for subtraction: ";
        cin >> operation;


        if (operation == '+')
        {
            for (int i = 0; i < row1; i++)
            {
                for (int j = 0; j < column2; j++)
                {
                    result[i][j] = matx1[i][j] + matx2[i][j];
                }
            }
            cout << "Sum of matrices:\n";
        }
        else if (operation == '-')
        {
            for (int i = 0; i < row1; i++)
            {
                for (int j = 0; j < column2; j++)
                {
                    result[i][j] = matx1[i][j] - matx2[i][j];
                }
            }
            cout << "Difference of matrices:\n";
        }
        else
        {
            cout << "Invalid operation selected.";
            return 1; // Exit the program
        }

        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < column2; j++)
            {
                cout << result[i][j] << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        cout << "Unequal matrices and addition/subtraction is not possible";
    }

    return 0;
}
