#include <iostream>
#include "Utilities\BinaryTree.h"

using namespace std;

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr || pRoot2 == nullptr)
		return false;

	bool res = false;
	if (pRoot1->m_nValue == pRoot2->m_nValue)
		res = DoesTree1HaveTree2(pRoot1, pRoot2));//only equal then match subtree in oritree, otherwise no need to match again
	if (!res)
		res = HasSubtree(pRoot1->m_pLeft, pRoot2);
	if (!res)
		res = HasSubtree(pRoot1->m_pRight, pRoot2);
	
	return false;
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot2 == nullptr)
		return true;

	if (pRoot1 == nullptr)
		return false;

	if (pRoot1->m_nValue == pRoot2->m_nValue)
	{
		if(pRoot2->m_pLeft == nullptr && pRoot2->m_pRight == nullptr)
			return true;
		else
			return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
	}		

	return false;
}

void test1()
{
	BinaryTreeNode* head = CreateBinaryTreeNode(8);
	BinaryTreeNode* node8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* node7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* node9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* node2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* node4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* node7_ = CreateBinaryTreeNode(7);
	ConnectTreeNodes(head, node8, node7);
	ConnectTreeNodes(node8, node9, node2);
	ConnectTreeNodes(node2, node4, node7_);

	BinaryTreeNode* head_ = CreateBinaryTreeNode(8);
	BinaryTreeNode* node9_ = CreateBinaryTreeNode(9);
	BinaryTreeNode* node2_ = CreateBinaryTreeNode(2);
	ConnectTreeNodes(head_, node9_, node2_);

	bool res = HasSubtree(head, head_);
}

void test2()
{
	BinaryTreeNode* head = CreateBinaryTreeNode(1);
	BinaryTreeNode* node2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* node3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* node4 = CreateBinaryTreeNode(4);
	ConnectTreeNodes(head, node2, nullptr);
	ConnectTreeNodes(node2, node3, nullptr);
	ConnectTreeNodes(node3, node4, nullptr);

	BinaryTreeNode* head_ = CreateBinaryTreeNode(3);
	BinaryTreeNode* node4_ = CreateBinaryTreeNode(4);
	ConnectTreeNodes(head_, node4_, nullptr);

	bool res = HasSubtree(head, head_);//test failed
}

int main(int argc, char* argv[])
{
	test1();
	test2();

	return 0;
}