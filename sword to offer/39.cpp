#include <iostream>

using namespace std;

int MoreThanHalfNum(int* numbers, int length)
{
    if (CheckInvalidArray(numbers, length))
        return 0;

    int pivot = numbers[0];
    int i = 0, j = length - 1, res = 0;

    while (i < j)
    {
        while (i < j && numbers[j] >= pivot)
            --j;
        if (i < j && numbers[j] < pivot)
        {
            numbers[i] = numbers[j];
            ++i;
        }

        while (i < j && numbers[i] <= pivot)
            ++i;
        if (i < j && numbers[i] > pivot)
        {
            numbers[j] = numbers[i];
            --j;
        }
    }
    numbers[i] = pivot;
    if (i == length / 2)
        res = numbers[i];
    else
    {
        res = MoreThanHalfNum() || MoreThanHalfNum();
    }
    return res;

}


void test1()
{

}

int main(int argc, char* argv[])
{
    test1();

    return 0;
}