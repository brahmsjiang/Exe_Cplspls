#include <iostream>
#include <string>
#include "stdio.h"


using namespace std;

int layer = 0;
bool layprinted = false;
void curVal(int* nums, int pBegin, int len, int& maxVal)
{
    if (layer > 0)
    {
        for (size_t i = 0; i < layer; i++)
            printf("    ");
    }
    ++layer;

    std::string res;
    for (size_t i = 0; i < len; i++)
    {
        res += std::to_string(nums[i]);
    }
    int newMaxval = atoi(res.c_str());

    printf("pBegin: %d  nums: %d    ", pBegin, newMaxval);
    if (pBegin == len)
    {
        printf("==>maxVal: %d", newMaxval);
        maxVal = (newMaxval > maxVal) ? newMaxval : maxVal;
    }
    else 
    {
        for (size_t pCur = pBegin; pCur < len; pCur++)
        {
            printf("pBegin[%d] pCur[%d]  in loop\n", pBegin, pCur);
            //exchange head's element with mid's element
            int tmp = nums[pCur];
            nums[pCur] = nums[pBegin];
            nums[pBegin] = tmp;

            curVal(nums, pCur + 1, len, maxVal);

            tmp = nums[pCur];
            nums[pCur] = nums[pBegin];
            nums[pBegin] = tmp;
        }
    }
    
    cout << endl;
    layprinted = false;
}

void PrintMinNum1(int* nums, int len)
{
    using namespace std;
    if (nums == nullptr)
        return;

    int maxVal = 0;
    curVal(nums, 0, len, maxVal);

    //cout << maxVal << endl;
}

void PrintMinNum2(int* nums, int len)
{

}

int main(int argc, char* argv[])
{
    int vec1[] = { 4, 3, 5 };
    PrintMinNum1(vec1, sizeof(vec1)/sizeof(int));
    return 0;
}