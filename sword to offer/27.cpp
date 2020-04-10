#include <iostream>
#include "Utilities\BinaryTree.h"

void MirrorRecursively(BinaryTreeNode* pNode)
{
	if (pNode == nullptr)
		return;

	if (pNode->m_pLeft || pNode->m_pRight)
	{
		BinaryTreeNode* tmp = pNode->m_pLeft;
		pNode->m_pLeft = pNode->m_pRight;
		pNode->m_pRight = tmp;
	}
	MirrorRecursively(pNode->m_pLeft);
	MirrorRecursively(pNode->m_pRight);
}

void test1()
{
	BinaryTreeNode* head = CreateBinaryTreeNode(8);
	BinaryTreeNode* n6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* n10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* n5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* n7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* n9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* n11 = CreateBinaryTreeNode(11);
	ConnectTreeNodes(head, n6, n10);
	ConnectTreeNodes(n6, n5, n7);
	ConnectTreeNodes(n10, n9, n11);

	MirrorRecursively(head);
}

void test2()
{
	BinaryTreeNode* head = CreateBinaryTreeNode(8);
	BinaryTreeNode* n6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* n5 = CreateBinaryTreeNode(5);
	ConnectTreeNodes(head, n6, nullptr);
	ConnectTreeNodes(n6, n5, nullptr);

	MirrorRecursively(head);
}

void test3()
{
	BinaryTreeNode* head = CreateBinaryTreeNode(8);
	MirrorRecursively(head);
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	return 0;
}