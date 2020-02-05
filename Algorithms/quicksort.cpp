#include <iostream>

using namespace std;

void QuickSort(int data[], int length, int start, int end)
{
	if (start < 0 || end >= length || length <= 0 || nullptr == data)
		throw new std::exception("Invalid parameters");

	if (start >= end)
		return;
	int idx1 = start;
	int idx2 = end;
	int compNum = data[idx1];

	while (idx1 < idx2)
	{
		while (data[idx2] > compNum && idx1 < idx2)
			--idx2;
		if (idx1 < idx2)
			data[idx1++] = data[idx2];

		while (data[idx1] < compNum && idx1 < idx2)
			++idx1;
		if (idx1 < idx2)
			data[idx2--] = data[idx1];
	}
	data[idx1] = compNum;
	if (idx1 > start)
		QuickSort(data, length, 0, idx1 - 1);
	if (idx1 < end)
		QuickSort(data, length, idx1 + 1, end);
}

int main(int argc, char* argv[])
{
	int arrtosort1[] = { 10,2,3,7,9,1,4,5,6,11,32,8 };
	int arrtosort2[] = { 5,2,13,29,9,1,4,5,44,11,32,8 };
	QuickSort(arrtosort1, sizeof(arrtosort1) / sizeof(int), 0, sizeof(arrtosort1) / sizeof(int) - 1);
	QuickSort(arrtosort2, sizeof(arrtosort2) / sizeof(int), 0, sizeof(arrtosort2) / sizeof(int) - 1);
	return 0;
}