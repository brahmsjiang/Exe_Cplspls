#include <iostream>
#include "Utilities\BinaryTree.h"

using namespace std;

bool VerifySequenceOfBST(int sequence[], size_t length)
{
 	if (sequence == nullptr || length <= 0)
		return false;

	int root = sequence[length - 1];

	size_t i = 0;
	for (; i < length - 1; i++)
	{
		if (sequence[i] > root)
			break;
	}

	size_t j = i;
	for (; j < length - 1; j++)
	{
		if (sequence[j] < root)
			return false;
	}
	
	bool resL = true;
	if (i > 0)
		resL = VerifySequenceOfBST(sequence, i);

	bool resR = true;
	if (length - 1 > i)
		resR = VerifySequenceOfBST(sequence + i, length - 1 - i);

	return resL && resR;
}

void test1()
{
	int seq[] = { 5,7,6,9,11,10,8 };
	bool res = VerifySequenceOfBST(seq, sizeof(seq) / sizeof(int));
}


void test2()
{
	int seq[] = { 7,4,6,5 };
	bool res = VerifySequenceOfBST(seq, sizeof(seq) / sizeof(int));
}

void test3()
{
	int seq[] = { 3,4,5 };
	bool res = VerifySequenceOfBST(seq, sizeof(seq) / sizeof(int));
}

void test4()
{
	int seq[] = { 10,10,8 };
	bool res = VerifySequenceOfBST(seq, sizeof(seq) / sizeof(int));
}

void test5()
{
	int seq[] = { 8 };
	bool res = VerifySequenceOfBST(seq, sizeof(seq) / sizeof(int));
}

void test6()
{
	bool res = VerifySequenceOfBST(nullptr, 0);
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

	return 0;
}