#include <iostream>

using namespace std;

int maxProductAfterCutting1(int length)
{
	//length stands for original max length
	if (length < 2)
		return 0;//1*0
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	//products[i] stores sub rope's max product,whose original length is equal to i
	int* products = new int[length + 1];
	products[0] = 0;//actually products[0] wouldn't be used, "0 1 2 3" is boundary val
	products[1] = 1;
	products[2] = 2;
	products[3] = 3;

	for (int i = 4; i <= length; ++i)
	{
		products[i] = 0;//calculate products[i]
		for (int j = 1; j <= i/2; ++j)//j < i/2, pay attention
		{
			int tmp = products[j] * products[i - j];
			if (tmp > products[i]) {
				products[i] = tmp;
			}
		}
	}
	int max = products[length];
	delete[] products;
	return max;
}

int maxProductAfterCutting2(int length)
{
	if (length < 2)
		return 0;//1*0
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	int timesOf3 = length / 3;//can cut times of 3, for whole length

	if (length - timesOf3 * 3 == 1)//remainder is 1 can't be divided by 2, so try to cut 2
		timesOf3 -= 1;

	int timesOf2 = (length - timesOf3 * 3) / 2;

	return (int)(pow(3, timesOf3)) * (int)(pow(2, timesOf2));
}

int main(int argc, char* argv[])
{
	cout << maxProductAfterCutting1(0) << endl;
	cout << maxProductAfterCutting1(1) << endl;
	cout << maxProductAfterCutting1(2) << endl;
	cout << maxProductAfterCutting1(3) << endl;
	cout << maxProductAfterCutting1(4) << endl;
	cout << maxProductAfterCutting1(8) << endl << endl;

	cout << maxProductAfterCutting2(0) << endl;
	cout << maxProductAfterCutting2(1) << endl;
	cout << maxProductAfterCutting2(2) << endl;
	cout << maxProductAfterCutting2(3) << endl;
	cout << maxProductAfterCutting2(4) << endl;
	cout << maxProductAfterCutting2(8) << endl;
	return 0;
}