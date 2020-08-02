#include <iostream>
#include <stack>
#include <math.h>

int GetFirstK(int* data, int k, int start, int end)
{
    if (start > end)
        return -1;

    int mid = (start + end) / 2;
    int midData = data[mid];
    if (midData == k)
    {
        if (mid > 0 && data[mid - 1] != k || mid == 0)
            return mid;
        else
            end = mid - 1;
    }
    else if (midData > k)
        end = mid - 1;
    else
        start = mid + 1;

    return GetFirstK(data, k, start, end);

}

int GetLastK(int* data, int k, int start, int end)
{
    if (start > end)
        return -1;

    int mid = (start + end) / 2;
    int midData = data[mid];
    if (midData == k)
    {
        if (mid < end && data[mid + 1] != k || mid == end)
            return mid;
        else
            start = mid + 1;
    }
    else if (midData < k)
        start = mid + 1;
    else
        end = mid - 1;

    return GetLastK(data, k, start, end);

}

int GetNumberOfK(int* data, int length, int k)
{
    int number = 0;
    if (data != nullptr || 0 < length)
    {
        int first = GetFirstK(data, k, 0, length - 1);
        int last = GetLastK(data, k, 0, length - 1);

        if (first > -1 && last > -1)
            number = last - first + 1;
    }

    return number;
}

int GetMissingNumber(const int* numbers, int start, int end)
{
	if (numbers == nullptr || start > end)
		return -1;

	int midIdx = (end - start + 1) / 2;
	int midData = numbers[midIdx];

	if (midData > midIdx)
	{
		if (0 == midIdx)
			return (midData - 1);
		if (0 < midIdx)
		{
			if (numbers[midIdx - 1] == midIdx - 1)
				return (midData - 1);
			else
				end = midIdx - 1;
		}
	}
	else //midData == midIdx
	{
		if (midIdx < end && numbers[midIdx + 1] > (midIdx + 1))
			return (numbers[midIdx + 1] - 1);
		else
			start = midIdx + 1;

	}
	return GetMissingNumber(numbers, start, end);
}

int main(int argc, char* argv[])
{
    //int vec[] = { 1,1,2,3,3,3,3,4,4 };
    //auto res = GetNumberOfK(vec, sizeof(vec) / sizeof(int), 4);

	int vec0[] = { 0,1,2,3,5 };
	auto res1 = GetMissingNumber(vec0, 0, sizeof(vec0) / sizeof(int) - 1);
    return 0;
}