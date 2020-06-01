#include <iostream>
#include <string>


void curVal(int* nums, int idx, int len, std::string& res, int& maxVal)
{
    if (idx == len)
    {
        int newMaxval = atoi(res.c_str());
        maxVal = (newMaxval > maxVal) ? newMaxval : maxVal;
        res.pop_back();
        return;
    }
        
    int subNumval = nums[idx];
    for (int i = idx; i < len; ++i)
    {
        //exchange head's element with mid's element
        int tmp = subNumval;
        subNumval = nums[i];
        nums[i] = tmp;

        res += std::to_string(subNumval);
        curVal(nums, idx + 1, len, res, maxVal);
        res.pop_back();
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