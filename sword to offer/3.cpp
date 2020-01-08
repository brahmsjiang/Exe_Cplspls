#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>
#include "Utilities/List.h"

using namespace std;

bool duplicate(int numbers[], int length, int* duplication)
{
	if(numbers == nullptr || length <= 0)
	{
		return false;
	}
	duplication = nullptr;

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

void test()
{
	int arrnum[] = {2,3,1,0,2,5,3};
	int dup;
	duplicate(arrnum, sizeof(arrnum)/sizeof(int),&dup);
	cout << dup << endl;
}


int main(int argc, char* argv[])
{
    test();
	
	return 0;
}


