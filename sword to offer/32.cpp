#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>
#include "Utilities/BinaryTree.h"

using namespace std;


void Print(BinaryTreeNode* pRoot)
{
	if(pRoot == nullptr)
		return;
	
	queue<BinaryTreeNode*> nodes;
	unsigned int toPrint = 0, nextLevel = 0;
	nodes.push(pRoot);
	toPrint++;
	while(!nodes.empty())
	{
		BinaryTreeNode* pNode = nodes.front();
		cout << pNode->m_nValue << " ";
		toPrint--;

		
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
		if(toPrint == 0)
		{
			cout << endl;
			toPrint = nextLevel;
			nextLevel = 0;
		}

		nodes.pop();
		
	}

}

void PrintZhi(BinaryTreeNode* pRoot)
{
	if(pRoot == nullptr)
		return;

	stack<BinaryTreeNode*> nodes;
	unsigned int toPrint = 0, nextLevel = 0;
	bool odd = true;	//root
	nodes.push(pRoot);
	toPrint++;
	while(!nodes.empty())
	{
		BinaryTreeNode* pNode = nodes.top();
		cout << pNode->m_nValue << " ";
		toPrint--;
		if(odd == true)	//cur odd,next left to right stored
		{
			if (pNode->m_pLeft != nullptr)
			{
				nodes.push(pNode->m_pLeft);
				nextLevel++;
			}
			if (pNode->m_pLeft != nullptr)
			{
				nodes.push(pNode->m_pRight);
				nextLevel++;
			}		
		}
		else	//cur even,next right to left stored
		{
			if (pNode->m_pLeft != nullptr)
			{
				nodes.push(pNode->m_pRight);
				nextLevel++;
			}
			if (pNode->m_pRight != nullptr)
			{
				nodes.push(pNode->m_pLeft);
				nextLevel++;
			}		

		}
	
		if(toPrint == 0)
		{
			odd ^= odd;
			cout << endl;
			toPrint = nextLevel;
			nextLevel = 0;
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

	ConnectTreeNodes(pNode10, pNode6, pNode14);
	ConnectTreeNodes(pNode6, pNode4, pNode8);
	ConnectTreeNodes(pNode14, pNode12, pNode16);

	Print(pNode10);
	PrintZhi(pNode10);

	DestroyTree(pNode10);
	return 0;
}
















