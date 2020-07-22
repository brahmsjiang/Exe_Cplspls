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
            {
                NumOfInverse++;
                printf("[%d, %d]\n", data[i], data[j]);
            }
                
        }
    }
    return NumOfInverse;
}

void merge(int* data, int low, int mid, int high, int& inverNum)
{
    int i = low;
    int j = mid + 1;
    int idx_tmp = 0;
    int* tmpdata = new int[high - low + 1];
    while (i <= mid && j <= high)
    {
        if (data[i] > data[j])
        {
            printf("[[%d, %d]]\n", data[i], data[j]);
            tmpdata[idx_tmp++] = data[j++];
            inverNum++;
        }
        else
        {
            tmpdata[idx_tmp++] = data[i++];
        }
    }
    while (i > mid && j <= high)
        tmpdata[idx_tmp++] = data[j++];
    while (i <= mid && j > high)
        tmpdata[idx_tmp++] = data[i++];

    memcpy(data + low, tmpdata, sizeof(tmpdata));
    delete[] tmpdata;
}

void merge_sort(int* data, int low, int high, int& inverNum)
{
    if (low >= high || nullptr == data)
        return;

    int mid = (low + high) / 2;
    merge_sort(data, low, mid, inverNum);
    merge_sort(data, mid + 1, high, inverNum);

    merge(data, low, mid, high, inverNum);
}



int InversePairs_2(int* data, int length)
{
    if (data == nullptr || length < 0)
        return 0;

    int inverNum = 0;
    merge_sort(data, 0, length - 1, inverNum);
    return inverNum;
}





int main(int argc, char* argv[])
{
    int data[] = { 7,5,6,4 };
    auto res1 = InversePairs_1(data, sizeof(data) / sizeof(int));
    auto res2 = InversePairs_2(data, sizeof(data) / sizeof(int));
    return 0;
}