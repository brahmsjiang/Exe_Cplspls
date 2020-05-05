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

	int first = *strN - '0';//�õ����λ��ֵ,��'3'-'1'
	unsigned int length = static_cast<unsigned int>(strlen(strN));//num�ж���λ

	if (length == 1 && first == 0)
		return 0;
	if (length == 1 && first > 0)
		return 1;

	//����strN��21345
	//numFirstDigit������10000��19999�ĵ�һ����λ�е���Ŀ�����Ϊ10^4
	int numFirstDigit = 0;
	if (first > 1)
		numFirstDigit = PowerBase10(length - 1);
	else if (first == 1)
		//��һλ�Ѿ���1����11345����numFirstDigit������10000��11345�е���Ŀ�����Ϊ1346
		cout << strN + 1 << endl;
		//ָ�����ͺ�int������ӣ���ʾָ����ָλ�����ƫ��n����λ��λ��
		numFirstDigit = atoi(strN + 1) + 1;

	//numOtherDigits��1346��21345����һ����λ֮�����λ�е���Ŀ
	int numOtherDigits = first * (length - 1) * PowerBase10(length - 2);
	//numRecursive��1��1345�е���Ŀ
	int numRecursive = NumberOf1(strN + 1);

	return numFirstDigit + numOtherDigits + numRecursive;
}

int NumberOf1Between1AndN_(unsigned int n)
{
	if (n <= 0)
		return 0;

	char strN[50];
	sprintf(strN, "%d", n);//�ڴ沼�� [0]'3' [1]'1' [2]'\0'...
	return NumberOf1(strN);
}

int main(int argc, char* argv[])
{
	auto res = NumberOf1Between1AndN(31);
	auto res2 = NumberOf1Between1AndN_(21345);
	return 0;
}