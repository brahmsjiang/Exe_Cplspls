#include <iostream>

using namespace std;

int MinInOrder(int* numbers, int idx1, int idx2);
int Min(int* numbers, int length)
{
	if (nullptr == numbers || length <= 0)
		throw new std::exception("Invalid parameters");
	int idx1 = 0;
	int idx2 = length - 1;
	int idxM = idx1;

	while (numbers[idx1] >= numbers[idx2])
	{
		if (idx1 == idx2 - 1) {
			idxM = idx2;
			break;
		}

		idxM = (idx1 + idx2) / 2;
		if (numbers[idx1] == numbers[idxM] && numbers[idx2] == numbers[idxM])
			return MinInOrder(numbers, idx1, idx2);


		if (numbers[idx1] <= numbers[idxM]) {
			idx1 = idxM;
		}
		else if (numbers[idxM] <= numbers[idx2]) {
			idx2 = idxM;
		}
	}
	return numbers[idxM];
}

int MinInOrder(int* numbers, int idx1, int idx2)
{
	int res = numbers[idx1];
	for (int i = idx1; i <= idx2; i++) {
		if (numbers[i] < res)
			res = numbers[i];
	}
	return res;
}

int main(int argc, char* argv[])
{
	int vec1[] = { 4,5,6,7,8,1,2,3 };
	int vec11[] = { 4,5,6,6,7,8,1,2,2,2,3 };
	int vec2[] = { 2,2,4,4,5,6 };
	int vec3[] = { 1,1,0,1,1,1,1 };
	//cout << Min(vec1, -1) << endl;
	//cout << Min(nullptr, 1) << endl;
	cout << Min(vec1, sizeof(vec1) / sizeof(int)) << endl;
	cout << Min(vec11, sizeof(vec11) / sizeof(int)) << endl;
	cout << Min(vec2, sizeof(vec2) / sizeof(int)) << endl;
	cout << Min(vec3, sizeof(vec3) / sizeof(int)) << endl;
	return 0;
}