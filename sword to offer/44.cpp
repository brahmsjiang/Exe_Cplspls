#include <iostream>

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
    
}

//how many nums included in m digits. m=3, thus nums is 90(10~99)
int countOfIntegers(int digits)
{

}

int digitAtIndex_2(int index, int digits)
{
    if (index < 0)
        return -1;

}

int digitAtIndex_2(int index)
{
    if (index < 0)
        return -1;

}


int main(int argc, char* argv[])
{
	int res = digitAtIndex_1(15);
    res = digitAtIndex_2(15);
    return 0;
}