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

int countRange(const int* numbers, int length, int end)
{

}

int duplicate2(const int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
	{
		return -1;
	}
	int scope = length - 1;
	for (int i = 1; i <= scope; ++i)
	{
		
	}

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


