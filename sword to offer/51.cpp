#include <iostream>
#include <set>

int InversePairs_1(int* data, int length)
{
    if (data == nullptr || length < 0)
        return 0;

    int NumOfInverse = 0;
    for (int i = 0; i < length; ++i)
    {
        for (int j = i; j < length; ++j)
        {
            if (data[i] > data[j])
                NumOfInverse++;
        }
    }
    return NumOfInverse;
}


int merge_sort(int* data, int low, int high);

void merge(int* data, int low, int mid, int high);

int InversePairs_2(int* data, int length)
{
    if (data == nullptr || length < 0)
        return 0;

    merge_sort(data, 0, length - 1);
    return 0;
}

int merge_sort(int* data, int low, int high)
{

}

void merge(int* data, int low, int mid, int high)
{

}



int main(int argc, char* argv[])
{
    int data[] = { 7,5,6,4 };
    auto res1 = InversePairs_1(data, sizeof(data)/sizeof(int));
    return 0;
}