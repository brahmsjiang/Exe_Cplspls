#include <iostream>
#include <fstream>
#include "Utilities\BinaryTree.h"

using namespace std;

void Serialize(const BinaryTreeNode* pRoot, ostream& stream)
{
	if (pRoot == nullptr)
	{
		stream << "$,";
		return;
	}

	stream << pRoot->m_nValue << ",";
	Serialize(pRoot->m_pLeft, stream);
	Serialize(pRoot->m_pRight, stream);
}

bool ReadStream(istream& stream, int* number)
{
	if (stream.eof())
		return false;

	char buffer[32];
	buffer[0] = '\0';

	char ch;
	stream >> ch;
	int i = 0;
	while (!stream.eof() && ch != ',')
	{
		buffer[i++] = ch;
		stream >> ch;
	}

	bool isNumeric = false;
	if (i > 0 && buffer[0] != '$')
	{
		*number = atoi(buffer);
		isNumeric = true;
	}
	return isNumeric;
}

void Deserialize(BinaryTreeNode** pRoot, istream& stream)
{
	int number;
	if (ReadStream(stream, &number))
	{

	}
}

void Test(const char* testName, const BinaryTreeNode* pRoot)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	char* filename = "test.txt";
	ofstream fileOut;//included in fstream
	fileOut.open(filename);

	Serialize(pRoot, fileOut);

}

void test1()
{
	BinaryTreeNode* n1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* n2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* n3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* n4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* n5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* n6 = CreateBinaryTreeNode(6);
	ConnectTreeNodes(n1, n2, n3);
	ConnectTreeNodes(n2, n4, nullptr);
	ConnectTreeNodes(n3, n5, n6);
	Test("test1", n1);
}

int main(int argc, char* argv[])
{
	test1();


	return 0;
}