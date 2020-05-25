#include <iostream>
#include <string>

using namespace std;


int digitAtIndex_1(int index)
{
    if (index < 0)  //don't forget it
        return -1;

    int totalIdx = 0, curIdx = 0;
    unsigned int curNum = 0, curDigit = 0;
    while (totalIdx < index)
    {
        ++curNum;

        curIdx = 0;
        unsigned int curNumTmp = curNum;
        while (curNumTmp)
        {
            curNumTmp /= 10;
            ++curIdx;
        }
        totalIdx += curIdx;
    }
	//now totalIdx >= idx, the target digit should be found from curNum, whose num of digit is curIdx
	int tarIdx = totalIdx - index;//tarIdx is from right to left, if curNum is "132", par index point to "3", tarIdx should be 1
	cout << "curNum is:" << curNum << " curIdx is:" << curIdx << " totalIdx is:" << totalIdx <<  endl;
	do
	{
		curDigit = curNum % 10;
		curNum /= 10;
		--tarIdx;
	} while (tarIdx >= 0);

    return curDigit;
}

//first digit of m-bit num
int beginNumber(int digits)
{
	if (digits == 1)
		return 0;

	return (int)std::pow(10, digits - 1);
}

//how many nums included in m digits. m=2, thus nums is 90(10~99)
int countOfIntegers(int digits)
{
	if (digits == 1)
		return 10;

	string minDigitStr("1");
	string maxDigitStr("9");
	--digits;
	while (digits > 0)
	{
		minDigitStr.append("0");
		maxDigitStr.append("9");
		--digits;
	}
	return (atoi(maxDigitStr.c_str()) - atoi(minDigitStr.c_str()) + 1);
}

int digitAtIndex_2(int index, int digits)
{
	int number = beginNumber(digits) + index / digits;//for expl, target idx here is 811=270*3+1, index/digits = 270, number=100+270=370
	int indexFromRight = digits - index % digits;//index % digits = 811%3 = 1
	for (int i = 1; i < indexFromRight; i++)//from right, have to divide by 10 one by one
		number /= 10;
	
	return number % 10;
}

int digitAtIndex_2(int index)
{
    if (index < 0)
        return -1;
	int digits = 1;
	while (1)
	{
		int numbers = countOfIntegers(digits);
		if (index < numbers * digits)
			return digitAtIndex_2(index, digits);

		index -= digits * numbers;//skip 90 * 2-digits nums
		digits++;//digits means how many nums included in m digits. m=2, scope is 10~99
	}
	return -1;
}


int main(int argc, char* argv[])
{
	int res = digitAtIndex_1(1525);
	int res2 = digitAtIndex_2(1525);
    return 0;
}