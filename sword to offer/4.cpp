#include <iostream>
#include <assert.h>
#include <stdlib.h>

using namespace std;
int offset;

bool Find(int* matrix, int rows, int columns, int number)
{
	bool res = false;
	static int* startaddr = matrix;
	if (matrix == nullptr || rows <= 0 || columns <= 0) {
		return res;
	}
	int comparEle = *(matrix + columns - 1);
	if (comparEle > number) {
		res = Find(startaddr, rows, columns - 1, number);
	}
	else if (comparEle < number) {
		startaddr = matrix + offset;
		res = Find(startaddr, rows - 1, columns, number);
	}
	else {
		res = true;
	}
	return res;

}

void test()
{
	int arrnum[16] = { 1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15 };
	offset = 4;
	cout << "res: " << Find(arrnum, 4, 4, 9) << endl;
}


int main(int argc, char* argv[])
{
    test();
	system("pause");
	return 0;
}


