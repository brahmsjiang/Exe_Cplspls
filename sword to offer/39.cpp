#include <iostream>

using namespace std;

int Partition(int* numbers, int len, int start, int end)
{
	int pivot = numbers[start];
	int i = start, j = end, res = 0;

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
	return i;
}

bool CheckInvalidArray(int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		return true;
	return false;
}

bool CheckMoreThanHalf(int* numbers, int len, int number)
{
	int eqlNum = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (numbers[i] == number)
			++eqlNum;
	}
	if ((eqlNum << 1) > len)
		return true;
	return false;
}

int MoreThanHalfNum(int* numbers, int len)
{
    if (CheckInvalidArray(numbers, len))
		return 0;
	int middle = len >> 1;
	int start = 0, end = len - 1, res = 0;
	int index = Partition(numbers, len, start, end);
	while (middle != index)
	{
		if (index > middle)
		{
			end = index - 1;
			index = Partition(numbers, len, start, end);
		}
		else 
		{
			start = index + 1;
			index = Partition(numbers, len, start, end);
		}
	}
	
	res = numbers[index];
	if (!CheckMoreThanHalf(numbers, len, res))
		res = 0;
	return res;
}


void test1()
{
	int vec[] = { 3,2,3,3,3,2,4,3,5 };
	int res = MoreThanHalfNum(vec, sizeof(vec) / sizeof(int));
}

int main(int argc, char* argv[])
{
    test1();

    return 0;
}