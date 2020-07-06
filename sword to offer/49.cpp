#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "assert.h"


bool IsUgly(int number)
{
    while (number % 2 == 0)
        number /= 2;
    while (number % 3 == 0)
        number /= 3;
    while (number % 5 == 0)
        number /= 5;

    return (number == 1) ? true : false;
}

int GetUglyNumber(int index)
{
    if (index <= 0)
        return 0;

    int number = 0;
    int uglyFound = 0;
    while (uglyFound < index)
    {
        ++number;
        if (IsUgly(number))
            ++uglyFound;
    }
    return number;
}

int GetUglyNumber2(int index)
{
	if (index <= 0)
		return 0;

	int* uglyNums = new int[index];
	int T2, T3, T5;
	int curIdx = 0;

	while (curIdx < index)
	{
		if (curIdx == 0)
		{
			uglyNums[curIdx] = 1;
			T2 = T3 = T5 = 1;
		}
		curIdx++;
	}
	assert(curIdx == index);


}

int main(int argc, char* argv[])
{
    clock_t t0 = clock();
    auto res = GetUglyNumber(1500);
    clock_t t1 = clock();
    std::cout << static_cast<double>(t1 - t0) << "ms"<< std::endl;

    auto res2 = GetUglyNumber2(1500);
    return 0;
}