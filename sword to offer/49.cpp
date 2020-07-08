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

int NxtUgly(int t2, int t3, int t5)
{
	int minVal = (t2 < t3) ? t2 : t3;
	minVal = (minVal < t5) ? minVal : t5;
	return minVal;
}

int GetUglyNumber2(int index)
{
	if (index <= 0)
		return 0;

	int* uglyNums = new int[index];
	int T2, T3, T5;

	uglyNums[0] = 1;
	T2 = T3 = T5 = 1;
	int curIdx = 1;//idx start from 1

	while (curIdx < index)
	{
		uglyNums[curIdx] = NxtUgly(T2 * 2, T3 * 3, T5 * 5);
		for (size_t i = 0; i <= curIdx; ++i) {
			if (uglyNums[i] >= T2 && uglyNums[i] * 2 > uglyNums[curIdx]) {
				T2 = uglyNums[i];
				break;
			}
		}

		for (size_t i = 0; i <= curIdx; ++i) {
			if (uglyNums[i] >= T3 && uglyNums[i] * 3 > uglyNums[curIdx]) {
				T3 = uglyNums[i];
				break;
			}
		}

		for (size_t i = 0; i <= curIdx; ++i) {
			if (uglyNums[i] >= T5 && uglyNums[i] * 5 > uglyNums[curIdx]) {
				T5 = uglyNums[i];
				break;
			}
		}

		curIdx++;
	}

	int res = uglyNums[curIdx - 1];
	delete[] uglyNums;
	return res;
}

int main(int argc, char* argv[])
{
    clock_t t0 = clock();
    auto res = GetUglyNumber(150);
    clock_t t1 = clock();
    std::cout << static_cast<double>(t1 - t0) << "ms"<< std::endl;

	t0 = clock();
    auto res2 = GetUglyNumber2(150);
	t1 = clock();
	std::cout << static_cast<double>(t1 - t0) << "ms" << std::endl;
    return 0;
}