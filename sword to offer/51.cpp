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
    int i = mid;
    int j = high;
    int idx_tmp = high - low;
	const int len_tmp = high - low + 1;
    int* tmpdata = new int[len_tmp];
    while (i >= low && j >= mid + 1)
    {
        if (data[i] > data[j])
        {
			int idx = j;
			while (idx >= mid + 1)
			{
				printf("(data[%d]:%d, data[%d]:%d)\n", i, data[i], idx, data[idx]);
				--idx;
			}
            
			inverNum += (j - mid);
			tmpdata[idx_tmp--] = data[i--];
        }
        else
        {
            tmpdata[idx_tmp--] = data[j--];
        }
    }
	while (i < low && j >= mid + 1)
	{
		tmpdata[idx_tmp--] = data[j--];
	}
	while (i >= low && j < mid + 1)
	{
		tmpdata[idx_tmp--] = data[i--];
	}

	for (size_t i = 0; i < len_tmp; i++)
	{
		printf("tmpdata[%d]:%d ", i, tmpdata[i]);
	}
	std::cout << std::endl;

    memcpy(data + low, tmpdata, sizeof(int) * len_tmp);
	for (size_t i = low; i <= high; i++)
	{
		printf("data[%d]:%d ", i, data[i]);
	}
	std::cout << std::endl;

	delete[] tmpdata;
	tmpdata = nullptr;
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
    int data[] = { 7,5,3,6,4 };
    auto res1 = InversePairs_1(data, sizeof(data) / sizeof(int));
    auto res2 = InversePairs_2(data, sizeof(data) / sizeof(int));
    return 0;
}