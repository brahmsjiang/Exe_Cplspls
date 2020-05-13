#include <iostream>

using namespace std;


int digitAtIndex(int index)
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
    totalIdx = 

    while (totalIdx++ != index)
    {
        curNum
    }
    return curDigit;
}


int main(int argc, char* argv[])
{
    return 0;
}