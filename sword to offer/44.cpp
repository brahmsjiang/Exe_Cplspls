#include <iostream>

using namespace std;


int digitAtIndex_1(int index)
{
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


int main(int argc, char* argv[])
{
	int res = digitAtIndex_1(15);
    return 0;
}