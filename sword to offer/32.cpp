#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>
#include "Utilities/BinaryTree.h"

using namespace std;

struct BTreeNode
{
	int m_nVal;
	BTreeNode* m_pLeft;
	BTreeNode* m_pRight;
};



void Print(BTreeNode* pRoot)
{
	if(pRoot == nullptr)
		return;
	
	queue<BTreeNode*> nodes;
	unsigned int toPrint = 0, nextLevel = 0;
	nodes.push(pRoot);
	toPrint++;
	while(!nodes.empty())
	{
		BTreeNode* pNode = nodes.front();
		cout << pNode->m_nVal << endl;
		toPrint--;

		if(toPrint == 0)
		{
			cout << endl;
			toPrint = nextLevel;
		}

		if (pNode->m_pLeft != nullptr)
		{
			nodes.push(pNode->m_pLeft);
			nextLevel++;

		}
		if (pNode->m_pRight != nullptr)
		{
			nodes.push(pNode->m_pRight);
			nextLevel++;
		}
		nodes.pop();
		
	}

}


int main(int argc, char* argv[])
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

	ConnectTreeNodes(pNode10)
	return 0;
}
















