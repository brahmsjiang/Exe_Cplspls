#include <iostream>
#include <string>


void curVal(int* nums, int idx, int len, std::string& res, int& maxVal)
{
    if (idx == len)
    {
		std::string res0;
		for (size_t i = 0; i < len; i++)
		{
			res0 += std::to_string(nums[i]);
		}

        int newMaxval = atoi(res0.c_str());
        maxVal = (newMaxval > maxVal) ? newMaxval : maxVal;
		res.clear();
		std::cout << newMaxval << std::endl;
        return;
    }
        
    int subNumval = nums[idx];
	res += std::to_string(subNumval);
	curVal(nums, idx + 1, len, res, maxVal);

    for (int i = idx + 1; i < len; ++i)
    {
        //exchange head's element with mid's element
        int tmp = subNumval;
        subNumval = nums[i];
        nums[i] = tmp;

		curVal(nums, idx, len, res, maxVal);
    }
}

void curVal1(int* nums, int idx, int len, int& maxVal)
{
	if (idx == len)
	{
		std::string res;
		for (size_t i = 0; i < len; i++)
		{
			res += std::to_string(nums[i]);
		}
		int newMaxval = atoi(res.c_str());
		maxVal = (newMaxval > maxVal) ? newMaxval : maxVal;
		return;
	}

	curVal1(nums, idx + 1, len, maxVal);

	for (size_t i = idx + 1; i < len; i++)
	{
		//exchange head's element with mid's element
		int tmp = nums[i];
        nums[i] = nums[idx];
        nums[idx] = tmp;

		curVal1(nums, idx, len, maxVal);//wrong, 
	}
}

void PrintMinNum1(int* nums, int len)
{
    using namespace std;
    if (nums == nullptr)
        return;

    int maxVal = 0;
    std::string res;
	curVal1(nums, 0, len, maxVal);

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