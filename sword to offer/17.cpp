#include <iostream>
#include <math.h>

using namespace std;

void Print1ToMaxOfDigits_1(int n)
{
	int num = static_cast<int>(pow(10,n));
	int i = 0;
	while (++i < num)
	{
		printf("%d ", i);
	}
}


void PrintNum(char* nums)
{
	int i = 0;
	while (nums[i] == '0')
		i++;
	printf("%s ", nums + i);
}

bool Increment(char* nums)
{
	int pos = strlen(nums) - 1;
	//int atoi(const char *str), para isn't char and won't use
	while (pos >= 0 && (nums[pos] - '0' + 1) == 10) {
		nums[pos] = '0';
		--pos;
	}
	if (pos < 0)
		return false;
	++nums[pos];
	return true;
}

void Print1ToMaxOfDigits(int n)
{
	if (n <= 0)
		return;

	char* nums = new char[n + 1];//new type[], not ()
	memset(nums,'0', n + 1);//void *memset(void *str, int c, size_t n)
	nums[n] = '\0';//last char is '\0'
	
	while (Increment(nums)) {
		PrintNum(nums);
	}
	delete[] nums;
}

////////////////////full pemutation////////////////////
void Print1ToMaxOfNDigitsRecursively(char* nums, int length, int index)
{
	if (index == length - 1) {
		PrintNum(nums);
		return;
	}
	for (int i = 0; i < 10; ++i)
	{
		nums[++index] = '0' + i;
		Print1ToMaxOfNDigitsRecursively(nums, length, index);
	}
}

void Print1ToMaxOfDigits_2(int n)
{
	if (n <= 0)
		return;
	char* nums = new char[n + 1];//new type[], not ()
	memset(nums, '0', n + 1);//void *memset(void *str, int c, size_t n)
	nums[n] = '\0';//last char is '\0'

	for (int i = 0; i < 10; ++i) {
		nums[0] = '0' + i;
		Print1ToMaxOfNDigitsRecursively(nums, n, 0);
	}
	delete[] nums;
}


int main(int argc, char* argv[])
{
	//Print1ToMaxOfDigits_1(6);
	Print1ToMaxOfDigits(3);
	return 0;
}