#include <iostream>
#include <string>


void curVal(int* nums, int idx, int len, std::string& res, int& maxVal)
{
    if (idx == len)
    {
        int newMaxval = atoi(res.c_str());
        maxVal = (newMaxval > maxVal) ? newMaxval : maxVal;
		res.clear();
        return;
    }
        
    int subNumval = nums[idx];
	res += std::to_string(subNumval);
	curVal(nums, idx + 1, len, res, maxVal);

    for (int i = idx; i < len; ++i)
    {
        //exchange head's element with mid's element
        int tmp = subNumval;
        subNumval = nums[i];
        nums[i] = tmp;

		curVal(nums, idx, len, res, maxVal);
    }
}

void PrintMinNum1(int* nums, int len)
{
    using namespace std;
    if (nums == nullptr)
        return;

    int maxVal = 0;
    std::string res;
    curVal(nums, 0, len, res, maxVal);

    cout << maxVal << endl;
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