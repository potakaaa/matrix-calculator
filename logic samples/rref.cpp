#include <iostream>
#include <vector>
#include <fstream>

// Start a fight club, brad reputation

using namespace std;

class Position
{
  public:
    int row;
    int col;
    Position(int row, int col)
    {
        this->row = row;
        this->col = col;
    }
    int GetValue(vector<vector<double> > matrix)
    {
        return matrix[row][col];
    }
};
void printM(vector<vector<double> > matrix){
    for (vector<vector<double> >::iterator i = matrix.begin(); i < matrix.end(); i++){
        for (vector<double>::iterator j = i->begin(); j < i->end(); j++)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
}
void row_scale(vector<vector<double> >::iterator row, double ratio){
    for (vector<double>::iterator i = row->begin(); i < row->end(); i++)
    {
        *i *= ratio;
    }
}
void row_replace(vector<vector<double> >::iterator base,
                 vector<vector<double> >::iterator op, double ratio)
{
    for (vector<double>::iterator i = base->begin(); i < base->end(); i++)
    {
        *i += *(op->begin() + (i - base->begin())) * ratio;
    }
}
void row_exchange(vector<vector<double> >::iterator a,
                  vector<vector<double> >::iterator b)
{
    for (vector<double>::iterator i = a->begin(); i < a->end(); i++)
    {

        float temp = *(b->begin() + (i - a->begin()));
        *(b->begin() + (i - a->begin())) = *i;
        *i = temp;
    }
}
int is_nonzero_column(vector<vector<double> > matrix, int column_id, int rows, int next_row_id)
{
    for (int row = next_row_id; row < rows; row++)
    {
        if (matrix[row][column_id] != 0)
            return row;
    }
    return -1;
}

int main()
{
    vector<vector<double> > matrix = {{2, 1, 2, 10},
                                      {1, 2, 1, 8},
                                      {3, 1, -1, 2}};
    int rows = 3, columns = 4;
   /*
    cout << "Input number of rows, followed by the numbner of columns: ";
    cin >> rows >> columns;
    for (int i = 0; i < rows; i++)
    {
        vector<double> row;
        for (int j = 0; j < columns; j++)
        {
            cout << "Row "<< i + 1 <<" Column " << j + 1 << ": ";
            double a;
            cin >> a;
            row.push_back(a);
        }
        matrix.push_back(row);
    } 
    */

    int next_row_id = 0;
    vector<Position> pivot_positions;
    for (int col = 0; col < columns; col++)
    {
        int nonzero_row_id = is_nonzero_column(matrix, col, rows, next_row_id);
        if (nonzero_row_id >= 0)
        {
            cout << "discovered leftmost nonzero column " << col
                 << ", and topmost nonzero row " << nonzero_row_id << endl;
            if (nonzero_row_id != next_row_id)
            {
                cout << "exchanged row " << next_row_id << " and row " << nonzero_row_id << endl;
                row_exchange(matrix.begin() + next_row_id, matrix.begin() + nonzero_row_id);
                nonzero_row_id = next_row_id;
            }
            cout << "selected pivot at position (row=" << nonzero_row_id << ",col=" << col << ") with value "
                 << matrix[nonzero_row_id][col] << endl;
            pivot_positions.push_back(Position(nonzero_row_id, col));
            for (int row = next_row_id; row < rows; row++)
            {
                if (matrix[row][col] == 0)
                    continue;
                if (row == nonzero_row_id)
                    continue;
                cout << "adding " << -matrix[row][col] / matrix[nonzero_row_id][col]
                     << " times of row " << nonzero_row_id << " onto row " << row << endl;
                row_replace(matrix.begin() + row,
                            matrix.begin() + nonzero_row_id,
                            -matrix[row][col] / matrix[nonzero_row_id][col]);
            }
            next_row_id++;
        }
        else
        {
            continue;
        }
    }

    for (vector<Position>::iterator pos = pivot_positions.begin(); pos != pivot_positions.end(); pos++) {

        if (matrix[pos->row][pos->col] != 1.0) {
        cout << "scaling row " << pos->row << " by " << 1.0 / matrix[pos->row][pos->col] << endl;
        row_scale(matrix.begin() + pos->row, 1.0 / matrix[pos->row][pos->col]);
    }

    for (int row = 0; row < rows; row++) {
        if (matrix[row][pos->col] != 0 && row != pos->row) {
        cout << "adding " << -matrix[row][pos->col] / matrix[pos->row][pos->col]
            << " times of row " << pos->row << " onto row " << row << endl;
        row_replace(matrix.begin() + row, matrix.begin() + pos->row,
                    -matrix[row][pos->col] / matrix[pos->row][pos->col]);
    }
  }
}
    printM(matrix);
    return 0;
}