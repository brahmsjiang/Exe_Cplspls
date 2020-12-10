#include <iostream>
#include <stdlib.h>

using namespace std;

int compare(const void* arg1, const void* arg2)
{
	return *(int*)arg1 - *(int*)arg2;
}

bool isContinuous(int* numbers, int len)
{
	if (nullptr == numbers || len < 1)
		return false;

	qsort(numbers, len, sizeof(int), compare); //qsort, from stdlib.h
	
	int numZero = 0;
	int numGap = 0;
	
	int lstVal = numbers[0], curVal = 0;
	bool invalid = false;
	for (size_t i = 0; i < len; i++)
	{
		if (numbers[i] == 0)
			++numZero;

        curVal = numbers[i];
        if (curVal != 0 && lstVal != 0)
        {
            if (curVal == lstVal)
                return false;
            if (curVal != lstVal + 1)
            {
                numGap += (curVal - lstVal - 1);
            }
        }
        lstVal = curVal;
	}
	return (numZero >= numGap);
}

int main(int argc, char* argv[])
{
	int vec[5] = { 6,4,0,1,0 };
	auto res = isContinuous(vec, 5);
	return 0;
}
