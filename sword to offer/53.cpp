#include <iostream>
#include <stack>
#include <math.h>

int GetFirstK(int* data, int length, int k, int start, int end)
{
    if (start > end)
        return -1;
    int mid = (start + end) / 2;

}

int GetLastK(int* data, int length, int k, int start, int end)
{

}

int GetNumberOfK(int* data, int length, int k)
{
    if (data == nullptr || 0 >= length)
        return -1;
    int midIdx = (length - 1) / 2;
    int firstKIdx = GetFirstK(data, length, k, 0, midIdx);
    int LastKIdx = GetLastK(data, length, k, midIdx + 1, length - 1);

}

int main(int argc, char* argv[])
{

    return 0;
}