#ifndef GAUSS_H
#define GAUSS_H
#include <vector>
#endif // GAUSS_H
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
