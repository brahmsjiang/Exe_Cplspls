#include <iostream>
#include <algorithm>

using namespace std;

int getMaxValue_sol1(const int* values, int rows, int cols)
{
    if (values == nullptr || rows <= 0 || cols <= 0)
        return 0;

    int** maxValues = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        maxValues[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int left = 0;
            int up = 0;
            
            if (i > 0)
                up = maxValues[i - 1][j];
            if (j > 0)
                left = maxValues[i][j - 1];
            maxValues[i][j] = std::max(left, up) + values[i * cols + j];
        }
    }

    int res = maxValues[rows - 1][cols - 1];

    for (int i = 0; i < rows; ++i)
        delete[] maxValues[i];
    delete[] maxValues;

    return res;
}

int getMaxValue_sol2(const int* values, int rows, int cols)
{
    if (values == nullptr || rows <= 0 || cols <= 0)
        return 0;
    //need to store left and up, left is in the [i] line. up is in the [i-1] line
    //line1: 1 10 3 8
    //line2: 12 2 9 6
    // for upper case, cur ele is 9. before line1, vec=[1 11 13 21]
    // at line2 and before 9, vec=[12+1 12+1+2 13 21]; from 9, vec=[13 15 15+9 15+9+6]
    int* maxValues = new int[cols];
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int left = 0;
            int up = 0;

            if (i > 0)
                up = maxValues[j];
            if (j > 0)
                left = maxValues[j - 1];

            maxValues[j] = std::max(left, up) + values[i * cols + j];
        }
    }

    int res = maxValues[cols - 1];

    delete[] maxValues;

    return res;
}


int main(int argc, char* argv[])
{
    int vec1[] = { 1,10,3,8,12,2,9,6,5,7,4,11,3,7,16,5 };
    int res = getMaxValue_sol1(vec1, 4, 4);
    res = getMaxValue_sol2(vec1, 4, 4);
    return 0;
}