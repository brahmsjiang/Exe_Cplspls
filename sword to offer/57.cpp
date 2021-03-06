#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

bool FindNumbersWithSum(int data[], int length, int sum, int& num1, int& num2)
{
    bool found = false;
    if (data == nullptr || length <= 1)//do not forget invalid judgment
        return found;

    int smallIdx = 0, largeIdx = length - 1;
    while (smallIdx <= largeIdx)
    {
        int smallVal = data[smallIdx], largeVal = data[largeIdx];
        if (sum == smallVal + largeVal)
        {
            num1 = smallVal;
            num2 = largeVal;
            found = true;
            break;
        }
        else if (sum < smallVal + largeVal)
            --largeIdx;
        else
            ++smallIdx;
    }
    return found;
}

void PrintContinousSequence(int smlIdx, int largIdx)
{
	using namespace std;
	cout << "(";
	while (smlIdx <= largIdx)
	{
		cout << smlIdx;
		if(smlIdx != largIdx)
			cout << "+";
		++smlIdx;
	}
	cout << ")" << endl;
}

void FindContinousSequence(int sum)
{
	if (sum < 3)
		return;

	int smlIdx = 1, largIdx = 2;
	int mid = (1 + sum) / 2;
	while (smlIdx < mid)
	{
		int curSum = (smlIdx + largIdx) * (largIdx - smlIdx + 1) / 2;
		if (curSum == sum)
		{
			PrintContinousSequence(smlIdx, largIdx);
			++smlIdx;
			largIdx = smlIdx + 1;
		}
		else if (curSum < sum)
			++largIdx;
		else
			++smlIdx;
	}
}

int main(int argc, char* argv[])
{
    int vec1[] = { 1,2,4,7,11,15 };
    int num1 = 0, num2 = 0;
    auto res1 = FindNumbersWithSum(vec1, sizeof(vec1) / sizeof(int), 15, num1, num2);

	FindContinousSequence(9);
	std::cout << "--------" << std::endl;
	FindContinousSequence(27);
    return 0;
}