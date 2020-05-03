#include <iostream>

int Partition(int* numbers, int len, int start, int end)
{
    if (numbers == nullptr || len <= 0 || len <= (end - start))
        return -1;

    int pivot = numbers[0], i = start, j = end;
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
		if (i<j && numbers[i] > pivot)
		{
			numbers[j] == numbers[i];
			--j;
		}
    }
	numbers[i] = pivot;
	return i;
}

void GetleastNumbers(int* input, int n, int* output, int k)
{
	if (input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
		return;

	int start = 0;
	int end = n - 1;
	int index = Partition(input, n, start, end);
	while (index != k - 1)
	{
		if (index > k - 1)
		{
			end = index - 1;
			index = Partition(input, n, start, end);
		}
		else {
			start = index + 1;
		}
	}
}

int main(int argc, char* argv[])
{
    return 0;
}