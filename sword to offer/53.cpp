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

int GetMissingNumber(const int* numbers, int len, int start, int end)
{
	if (numbers == nullptr || start > end)
		return -1;

	int midIdx = (end + start) / 2;
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
        if (midIdx < end && numbers[midIdx + 1] >(midIdx + 1))
            return (numbers[midIdx + 1] - 1);
        else if (midIdx == len - 1)
            return (midData + 1);
        else
			start = midIdx + 1;

	}
	return GetMissingNumber(numbers, len, start, end);
}

int GetMissingNumber1(const int* numbers, int len)
{
    if (numbers == nullptr || len <= 0)
        return -1;

    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
        int mid = (right + left) >> 1;
        if (numbers[mid] != mid)
        {
            if (mid == 0 || numbers[mid - 1] == mid - 1)//judge from left to right
                return mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    if (left == len)
        return len;

    return -1;
}

int GetNumberSameAsIndex(const int* numbers, int length)
{
    if (numbers == nullptr || length <= 0)
        return -1;

    int left = 0;
    int right = length - 1;

    while (left <= right)
    {
        int mid = (right + left) >> 1;//right move operator

        if (numbers[mid] != mid)
        {
            if (numbers[mid] > mid)
                right = mid - 1;
            else
                left = mid + 1;
        }
        else
            return mid;
    }

    return -1;
}

int main(int argc, char* argv[])
{
    //int vec[] = { 1,1,2,3,3,3,3,4,4 };
    //auto res = GetNumberOfK(vec, sizeof(vec) / sizeof(int), 4);

	int vec0[] = { 0,1,2,3,4 };
    int len0 = sizeof(vec0) / sizeof(int);
	auto res1 = GetMissingNumber(vec0, len0, 0, len0 - 1);

    int vec1[] = { 0 };
    int len1 = sizeof(vec1) / sizeof(int);
    auto res2 = GetNumberSameAsIndex(vec1, len1);

    return 0;
}