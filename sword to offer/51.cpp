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

int InversePairs_2(int* data, int length)
{
    if (data == nullptr || length < 0)
        return 0;

    return 0;
}

int main(int argc, char* argv[])
{
    int data[] = { 7,5,6,4 };
    auto res1 = InversePairs_1(data, sizeof(data)/sizeof(int));
    return 0;
}