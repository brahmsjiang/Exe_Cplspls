#include <iostream>

using namespace std;

const int MAXVAL = 6;
int* cntOfEverySum = nullptr;

int layer = 0;
void printTab(int layer)
{
	for (size_t i = 0; i < layer; i++)
		printf("    ");
}

void Probability(int curSum, int* cntOfEverySum, int curNum, int origNum);

void printProbability(int num)
{
	if (num < 1)
		return;

	const int lenOfArr = num * (MAXVAL - 1) + 1;
	cntOfEverySum = new int[lenOfArr];
	memset(cntOfEverySum, 0x0, sizeof(int) * lenOfArr);

	for (size_t i = 1; i <= MAXVAL; i++)
		Probability(i, cntOfEverySum, num - 1, num);

	double totalRatio = 0;
	for (size_t i = 0; i < lenOfArr; i++)
	{
		double ratio = static_cast<double>(cntOfEverySum[i] / pow(MAXVAL, num));
		cout << "sum " << (i + num) << "'s probability: " << ratio << endl;
		totalRatio += ratio;
	}

	delete[] cntOfEverySum;
	cntOfEverySum = nullptr;
}

void Probability(int curSum, int* cntOfEverySum, int curNum, int origNum)
{
	++layer;
	if (nullptr == cntOfEverySum)
	{
		--layer;
		return;
	}

	if (curNum <= 0)
	{
		printTab(layer);
		++cntOfEverySum[curSum - origNum];
		printf("cntOfEverySum[curSum: %d]: %d\n", curSum, cntOfEverySum[curSum - origNum]);
		--layer;
		return;
	}

	for (size_t i = 1; i <= MAXVAL; i++)
	{
		int tmpSum = curSum + i;
		Probability(tmpSum, cntOfEverySum, curNum - 1, origNum);
	}
	--layer;
}

void printProbability_loop(int num)
{
	if (num < 1)
		return;

	const int lenOfArr = num * MAXVAL + 1;
	int* pProbabilities[2];
	pProbabilities[0] = new int[lenOfArr];
	pProbabilities[1] = new int[lenOfArr];
	memset(pProbabilities[0], 0, sizeof(int) * lenOfArr);
	memset(pProbabilities[1], 0, sizeof(int) * lenOfArr);

	for (size_t i = 1; i <= MAXVAL; i++)
	{
		++pProbabilities[0][i];
		printf("pProbabilities[0][%d]: %d\n", i, pProbabilities[0][i]);

	}
	int usrIdx = 0;
	for (int i = 2; i <= num; i++)
	{
		int curIdx = (i + 1) % 2;
		int lstIdx = i % 2;

		for (int j = i; j <= (MAXVAL * i); j++)
		{
			int minIdx = ((j - 6) >= 0) ? (j - 6) : 0;
			for (int k = (j - 1); k >= minIdx; --k) //除非考虑到int正整数过大，否则用int而不是uint
			{
				pProbabilities[curIdx][j] += pProbabilities[lstIdx][k];
			}
			printf("pProbabilities[%d][%d]: %d\n", curIdx, j, pProbabilities[curIdx][j]);
		}
		usrIdx = curIdx;
	}

	double totalRatio = 0;
	for (size_t i = num; i < lenOfArr; i++)
	{
		double ratio = static_cast<double>(pProbabilities[usrIdx][i] / pow(MAXVAL, num));
		cout << "sum " << i << "'s probability: " << ratio << endl;
		totalRatio += ratio;
	}

	delete[] pProbabilities[0];
	delete[] pProbabilities[1];
}

int main(int argc, char* argv[])
{
	//printProbability(3);
	printProbability_loop(4);
	return 0;
}
