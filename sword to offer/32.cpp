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

	stack<BinaryTreeNode*> PriNodes;
	stack<BinaryTreeNode*> NexLevNodes;
	unsigned int toPrint = 0, nextLevel = 0;
	bool odd = true;	//root
	PriNodes.push(pRoot);
	while(!PriNodes.empty())
	{
		BinaryTreeNode* pNode = PriNodes.top();
		cout << pNode->m_nValue << " ";
		if(odd == true)	//cur odd,next left to right stored
		{
			if (pNode->m_pLeft != nullptr)
			{
				NexLevNodes.push(pNode->m_pLeft);
			}
			if (pNode->m_pRight != nullptr)
			{
				NexLevNodes.push(pNode->m_pRight);
			}		
		}
		else	//cur even,next right to left stored
		{
			if (pNode->m_pRight != nullptr)
			{
				NexLevNodes.push(pNode->m_pRight);
			}
			if (pNode->m_pLeft != nullptr)
			{
				NexLevNodes.push(pNode->m_pLeft);
			}		

		}
	
		PriNodes.pop();
		if(PriNodes.empty())
		{
			PriNodes.swap(NexLevNodes);
			odd = ((odd == true) ? false : true);
			cout << endl;
		}
	}
}



int main(int argc, char* argv[])
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
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode13 = CreateBinaryTreeNode(13);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode15 = CreateBinaryTreeNode(15);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode3, pNode6, pNode7);
	ConnectTreeNodes(pNode4, pNode8, pNode9);
	ConnectTreeNodes(pNode5, pNode10, pNode11);
	ConnectTreeNodes(pNode6, pNode12, pNode13);
	ConnectTreeNodes(pNode7, pNode14, pNode15);

	Print(pNode1);
	cout << "------------" << endl;
	PrintZhi(pNode1);

	DestroyTree(pNode1);
	return 0;
}
















