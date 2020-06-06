#include <iostream>
#include <string>
#include <algorithm>
#include "stdio.h"

using namespace std;

int layer = 0;

int printNum(int* nums, int len)
{
	std::string res;
	for (size_t i = 0; i < len; i++)
		res += std::to_string(nums[i]);

    return atoi(res.c_str());
}

void printTab(int layer)
{
    for (size_t i = 0; i < layer; i++)
        printf("    ");
}

void permutation(int* nums, int pBegin, int len, int& maxVal)
{
	printTab(layer);
    ++layer;

	int curNum = printNum(nums, len);
    printf("==>enter curVal, permu_head: %d  nums: %d\n", pBegin, curNum);
    if (pBegin == len)
    {
		printTab(layer);
        printf("=>=>maxVal: %d\n", curNum);
        maxVal = (curNum > maxVal) ? curNum : maxVal;
    }
    else 
    {
        for (size_t pCur = pBegin; pCur < len; pCur++)
        {
			printTab(layer);
            printf("||start thisloop, nums: %d permu_head[%d] exchg_idx[%d]  in loop\n", printNum(nums, len), pBegin, pCur);

            //exchange head's element with mid's element
            int tmp = nums[pCur];
            nums[pCur] = nums[pBegin];
            nums[pBegin] = tmp;

			printTab(layer);
			printf("|before curVal, nums: %d\n", printNum(nums, len));

            permutation(nums, pBegin + 1, len, maxVal);

			printTab(layer);
			printf("|end thisloop, nums: %d\n", printNum(nums, len));
        }
    }
    
	--layer;
}

void PrintMinNum1(int* nums, int len)
{
    using namespace std;
    if (nums == nullptr)
        return;

    int maxVal = 0;
    permutation(nums, 0, len, maxVal);

    cout << "[maxVal]====>" << maxVal << endl;
}

//////////////////////////////////////
const int g_MaxNumberLength = 10;
char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

int compare(const void* strNumber1, const void* strNumber2)
{
	//why use char** not char*?
	strcpy(g_StrCombine1, *(const char**)strNumber1);
	strcat(g_StrCombine1, *(const char**)strNumber2);

	strcpy(g_StrCombine2, *(const char**)strNumber2);
	strcat(g_StrCombine2, *(const char**)strNumber1);

	return strcmp(g_StrCombine1, g_StrCombine2);
}

void PrintMinNum2(int* nums, int len)
{
    if (nums == nullptr)
        return;
	char** numsStr = (char**)(new int[len]);// no new (char** ==> or pointer),char** is a addr so int could be converted to.
	for (size_t i = 0; i < len; i++)
	{
		numsStr[i] = new char[g_MaxNumberLength];
		sprintf(numsStr[i], "%d", nums[i]);//sprintf format str, printf format output-stream 
	}
	std::qsort(numsStr, len, sizeof(char*), compare);
	for (size_t i = 0; i < len; i++)
	{
		printf("%s", numsStr[i]);
	}
}

int main(int argc, char* argv[])
{
    int vec1[] = { 4, 3, 5, 1 };
    PrintMinNum1(vec1, sizeof(vec1)/sizeof(int));
	PrintMinNum2(vec1, sizeof(vec1) / sizeof(int));
    return 0;
}