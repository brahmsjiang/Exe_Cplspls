#include <iostream>

using namespace std;

void RecorderOddEven_n2(int* pData, unsigned int length)
{
	if (pData == nullptr || length == 0)
		return;

	for (size_t i = 0; i < length; i++)
	{
		if (*(pData + i) % 2 == 0) {
			int oddFound = *(pData + i);
			for (size_t j = i + 1; j < length; j++)
			{
				*(pData + j - 1) = *(pData + j);
			}
			*(pData + length - 1) = oddFound;
		}
	}
}

void RecorderOddEven_n1(int* pData, unsigned int length)
{
	if (pData == nullptr || length == 0)
		return;

	int* p1 = pData;
	int* p2 = pData + length - 1;

	while (p1 <= p2)
	{
		while (p1 <= p2 && (*p1 & 0x1) != 0)//判断奇偶位运算： & 0x1
			p1++;

		while (p1 <= p2 && (*p2 & 0x1) == 0)//每次移动前都要判别指针p1<=p2
			p2--;

		if (p1 <= p2) {
			int tmp = *p1;
			*p1 = *p2;
			*p2 = tmp;
		}
	}
}


int main(int argc, char* argv[])
{
	int vec[] = { 1,2,3,4,5,6,7 };
	//RecorderOddEven_n2(vec, 7);
	RecorderOddEven_n1(vec, 7);

	return 0;
}