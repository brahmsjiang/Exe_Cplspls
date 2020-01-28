#include <iostream>
#include <assert.h>
#include "Utilities\BinaryTree.h"

using namespace std;

BinaryTreeNode* GetNext(BinaryTreeNode* pNode)
{
	if (nullptr == pNode)
		return nullptr;
	//have rtree
	BinaryTreeNode* rtreeCld = pNode->m_pRight;
	if (nullptr != rtreeCld)
	{
		while (nullptr != rtreeCld->m_pLeft) {
			rtreeCld = rtreeCld->m_pLeft;
		}
		return rtreeCld;
	}
	//no rtree
	else {
		//is parent, no next
		BinaryTreeNode* pNodePar = pNode->m_pParent;
		if (nullptr == pNodePar)
			return nullptr;

		//is parent's ltree
		if (pNodePar->m_pLeft == pNode) {
			return pNodePar;
		}
		//is parent's rtree
		else {
			//assert(pNodePar->m_pRight == pNode);
			BinaryTreeNode* pNodecur = pNode;
			while (nullptr != pNodePar && pNodePar->m_pRight == pNodecur)
			{
				pNodecur = pNodePar;
				pNodePar = pNodecur->m_pParent;
			}
			if (nullptr != pNodePar && pNodePar->m_pLeft == pNodecur)
				return pNodePar;
			else
				return nullptr;
		}
	}
}

void test()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode3, pNode6, pNode7);
	ConnectTreeNodes(pNode5, pNode8, pNode9);

	assert(GetNext(pNode7) == nullptr);
	cout << GetNext(pNode1)->m_nValue << endl;
	cout << GetNext(pNode2)->m_nValue << endl;
	cout << GetNext(pNode4)->m_nValue << endl;
	cout << GetNext(pNode9)->m_nValue << endl;
	cout << GetNext(pNode5)->m_nValue << endl;

	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	assert(GetNext(pNode10) == nullptr);
}

int main(int argc, char* argv[])
{
	test();
	return 0;
}