#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <stdlib.h>
#include <queue>
#include "Utilities/List.h"

using namespace std;

bool duplicate1(int numbers[], int length, int* duplication)
{
	if(numbers == nullptr || length <= 0)
	{
		return false;
	}

	for(int i = 0; i < length; i++)
	{
		while(numbers[i] != i){
			int curval = numbers[i];
			if(numbers[curval] != curval){
				//swap numbers[i] and numbers[numbers[i]]
				numbers[i] = numbers[curval];
				numbers[curval] = curval;
			}
			else{
				*duplication = curval;
				return true;
			}
		}
	}
	return false;
}

int countRange(const int* numbers, int length, int start, int end)
{
	int count = 0;
	if (numbers == nullptr)
		return count;

	for (int i = 0; i < length; ++i)
	{
		if (numbers[i] >= start && numbers[i] <= end)
			count++;
	}
	return count;
}

int duplicate2(const int* numbers, int length)
{
	if(numbers == nullptr || length <= 0)
	{
		return -1;
	}

	int start = 1;
	int end = length - 1;
	while(start <= end)
	{
		int mid = ((end - start) >> 1) + start;
		int count = countRange(numbers, length, start, mid);
		if (start == end)
		{
			if(count > 1)
				return start;
			else
				break;
		}

		if (count > (mid - start + 1))
			end = mid;
		else
			start = mid + 1;
	}
	return -1;
}

void test()
{
	int arrnum1[] = {4,3,1,0,4,5,3};
	int arrnum2[] = {2,3,5,4,3,2,6,7};
	int dup = 0;
	//duplicate1(arrnum1, sizeof(arrnum1)/sizeof(int),&dup);
	dup = duplicate2(arrnum2, sizeof(arrnum2) / sizeof(int));
	cout << dup << endl;
}


int main(int argc, char* argv[])
{
    test();
	system("pause");
	return 0;
}


