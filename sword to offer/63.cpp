#include <iostream>

int MaxDiff1(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	int minVal = 0, maxVal = 0, diff = 0;
	for (size_t i = 0; i < length; i++)
	{
		minVal = numbers[i];
		for (size_t j = i + 1; j < length; j++)
		{
			maxVal = numbers[j];
			diff = ((maxVal - minVal) > diff) ? (maxVal - minVal) : diff;
		}
	}
	return diff;
}

int MaxDiff2(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	int min = numbers[0];
	int maxDiff = numbers[1] - min;

	for (size_t i = 2; i < length; i++)
	{
		if (numbers[i - 1] < min)
			min = numbers[i - 1];

		int curDiff = numbers[i] - min;
		if (curDiff > maxDiff)
			maxDiff = curDiff;
	}
	return maxDiff;
}

int main(int argc, char* argv[])
{
	int vec[] = { 9,11,8,5,7,12,16,14 };

	auto res1 = MaxDiff1(vec, sizeof(vec) / sizeof(int));
	auto res2 = MaxDiff2(vec, sizeof(vec) / sizeof(int));
	return 0;
}