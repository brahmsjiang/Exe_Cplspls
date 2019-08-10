#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>
#include "Utilities/BinaryTree.h"

using namespace std;

void FindPath(BinaryTreeNode* pRoot, int expSum, vector<int>& path, int curSum)
{
	curSum += pRoot->m_nValue;
	path.push_back(pRoot->m_nValue);
	if(pRoot->m_pLeft == nullptr && pRoot->m_pRight == nullptr)
	{
		if(curSum == expSum){
			vector<int>::iterator it = path.begin();
			for(;it != path.end();++it)
				printf("%d\t", *it);
			printf("\n");
		}
		else
		{
		}
	}
	if(pRoot->m_pLeft != nullptr)
	{
		FindPath(pRoot->m_pLeft, expSum, path, curSum);
	}
	if(pRoot->m_pRight != nullptr)
	{
		FindPath(pRoot->m_pRight, expSum, path, curSum);
	}	
	path.pop_back();

}

void FindPath(BinaryTreeNode* pRoot, int expSum)
{
	if(pRoot == nullptr)
		return;

	vector<int> path;
	int curSum = 0;
	FindPath(pRoot, expSum, path, curSum);
}



int main(int argc, char* argv[])
{

	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode1, pNode3, pNode2);
	ConnectTreeNodes(pNode3, pNode4, pNode6);
	ConnectTreeNodes(pNode2, pNode5, pNode7);
	
	FindPath(pNode1, 10);	
	
	DestroyTree(pNode1);
	return 0;
}
















