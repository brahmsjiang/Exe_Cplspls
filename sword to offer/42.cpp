#include <iostream>

using namespace std;

int FindGreatestSumOfSubArray(int* pData, int nLength)
{
	if (pData == nullptr || nLength <= 0)
	{
		return 0;
	}

	int accSubArraySum = 0, maxSubArraySum = 0;
	for (size_t i = 0; i < nLength; i++)
	{
		accSubArraySum += pData[i];
		if (accSubArraySum < 0)
			accSubArraySum = 0;

		if (accSubArraySum > maxSubArraySum)
			maxSubArraySum = accSubArraySum;
	}
	return maxSubArraySum;
}

int main(int argc, char* argv[])
{
	int vec[] = { 1,-2,3,10,-4,7,2,-5 };
	auto res = FindGreatestSumOfSubArray(vec, sizeof(vec)/sizeof(int));

	return 0;
}