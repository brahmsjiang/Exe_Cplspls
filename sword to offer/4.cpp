#include <iostream>
#include <assert.h>
#include <stdlib.h>

using namespace std;
int offset;

bool Find1(int* matrix, int rows, int columns, int number)
{
	bool res = false;
	static int* startaddr = matrix;
	if (matrix == nullptr || rows <= 0 || columns <= 0) {
		return res;
	}
	int comparEle = *(matrix + columns - 1);
	if (comparEle > number) {
		res = Find1(startaddr, rows, columns - 1, number);
	}
	else if (comparEle < number) {
		startaddr = matrix + offset;
		res = Find1(startaddr, rows - 1, columns, number);
	}
	else {
		res = true;
	}
	return res;
}

bool Find2(int* matrix, int rows, int columns, int number)
{
	bool res = false;
	int curCol = columns;
	int curRow = 0;
	if (matrix == nullptr || rows <= 0 || columns <= 0) {
		return res;
	}

	while (curCol > 0 && curRow < rows)
	{
		int comparEle = *(matrix + columns * curRow + curCol - 1);
		if (comparEle > number) {
			--curCol;
		}
		else if (comparEle < number) {
			++curRow;
		}
		else {
			res = true;
			break;
		}
	}

	return res;
}

void test()
{
	int arrnum[16] = { 1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15 };
	offset = 4;
	//cout << "res: " << Find1(arrnum, 4, 4, 9) << endl;
	cout << "res: " << Find2(arrnum, 4, 4, 111) << endl;
}


int main(int argc, char* argv[])
{
    test();
	system("pause");
	return 0;
}


