#include <iostream>
#include <stack>
#include "Utilities/BinaryTree.h"
#include "assert.h"


BinaryTreeNode* findKNode(BinaryTreeNode* root, int& k)
{
	using namespace std;

    if (root == nullptr)
        return nullptr;

	if (root->m_pLeft != nullptr)
	{
		auto res = findKNode(root->m_pLeft, k);
		if (nullptr != res)
			return res;
	}
	else 
	{
		if (--k == 0)
			return root;
		else
			return nullptr;
	}

	if (--k == 0)
		return root;

	if (root->m_pRight != nullptr)
	{
		auto res = findKNode(root->m_pRight, k);
		if (nullptr != res)
			return res;
	}
	else
	{
		if (--k == 0)
			return root;
		else
			return nullptr;
	}
}

BinaryTreeNode* findKNode1(BinaryTreeNode* root, int& k)
{
    using namespace std;

    if (root == nullptr)
        return nullptr;

    stack<BinaryTreeNode*> nodeStk;
    BinaryTreeNode* curNode = root;
    nodeStk.push(curNode);

    while (!nodeStk.empty())
    {
        curNode = nodeStk.top();
        while (curNode->m_pLeft != nullptr)
        {
            nodeStk.push(curNode->m_pLeft);
            curNode = curNode->m_pLeft;
        }

        while (!nodeStk.empty())
        {
            curNode = nodeStk.top();
            nodeStk.pop();
            if (0 == --k)
                return curNode;

            if (curNode->m_pRight != nullptr)
            {
                nodeStk.push(curNode->m_pRight);
                break;
            }
        }
    }  
}

int main(int argc, char* argv[])
{
    BinaryTreeNode* root = CreateBinaryTreeNode(5);
    BinaryTreeNode* node3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* node7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* node2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* node4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* node6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* node8 = CreateBinaryTreeNode(8);
    ConnectTreeNodes(root, node3, node7);
    ConnectTreeNodes(node3, node2, node4);
    ConnectTreeNodes(node7, node6, node8);

	int k = 3;
    auto res = findKNode(root, k);
    k = 7;
    auto res1 = findKNode1(root, k);
    return 0;
}