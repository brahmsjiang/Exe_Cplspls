#include <iostream>

using namespace std;

int Numof1(unsigned int n)
{
	int res = 0;
	while (n > 0)
	{
		if (n % 10 == 1)
			++res;
		n /= 10;
	}
	return res;
}

int NumberOf1Between1AndN(unsigned int n)
{
	int countOf1 = 0;
	for (unsigned int curNum = 1; curNum <= n; curNum++)
	{
		countOf1 += Numof1(curNum);
	}
	return countOf1;
}

int PowerBase10(unsigned int n)
{
	int res = 1;
	for (size_t i = 0; i < n; i++)
	{
		res *= 10;
	}
	return res;
}

int NumberOf1(const char* strN)
{
	if (!strN || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;

	int first = *strN - '0';//得到最高位的值,即'3'-'1'
	unsigned int length = static_cast<unsigned int>(strlen(strN));//num有多少位

	if (length == 1 && first == 0)
		return 0;
	if (length == 1 && first > 0)
		return 1;

	//假设strN是21345
	//numFirstDigit是数字10000～19999的第一（万）位中的数目，结果为10^4
	int numFirstDigit = 0;
	if (first > 1)
		numFirstDigit = PowerBase10(length - 1);
	else if (first == 1)
		//第一位已经是1，如11345，则numFirstDigit是数字10000～11345中的数目，结果为1346
		cout << strN + 1 << endl;
		//指针类型和int类型相加，表示指针所指位置向后偏移n个单位的位置
		numFirstDigit = atoi(strN + 1) + 1;

	//numOtherDigits是1346～21345除第一（万）位之外的数位中的数目
	int numOtherDigits = first * (length - 1) * PowerBase10(length - 2);
	//numRecursive是1～1345中的数目
	int numRecursive = NumberOf1(strN + 1);

	return numFirstDigit + numOtherDigits + numRecursive;
}

int NumberOf1Between1AndN_(unsigned int n)
{
	if (n <= 0)
		return 0;

	char strN[50];
	sprintf(strN, "%d", n);//内存布局 [0]'3' [1]'1' [2]'\0'...
	return NumberOf1(strN);
}

int main(int argc, char* argv[])
{
	auto res = NumberOf1Between1AndN(31);
	auto res2 = NumberOf1Between1AndN_(21345);
	return 0;
}