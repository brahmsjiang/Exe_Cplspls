#include <iostream>

using namespace std;

int getMaxValue_sol1(const int* values, int rows, int cols)
{
    if (values == nullptr || rows <= 0 || cols <= 0)
        return 0;

    int** maxValues = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        maxValues[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maxValues[i][j] = *(values + i*cols + cols);
            int lastTraceVal = 0;
            if (i > 0)
                lastTraceVal = maxValues[i - 1][j];
            if (j > 0 && maxValues[i][j - 1] > lastTraceVal)
                lastTraceVal = maxValues[i][j - 1];

            maxValues[i][j] += lastTraceVal;
        }
    }
    return maxValues[rows - 1][cols - 1];
}

int main(int argc, char* argv[])
{
    return 0;
}