#include <iostream>
#include <unordered_map>
#include "Utilities\BinaryTree.h"

using namespace std;

void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList);

BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
    BinaryTreeNode* pLastNodeInList = nullptr;
    ConvertNode(pRootOfTree, &pLastNodeInList);

    BinaryTreeNode* pHeadOfList = pLastNodeInList;
    while (pHeadOfList != nullptr && pHeadOfList->m_pLeft != nullptr)
        pHeadOfList = pHeadOfList->m_pLeft;
    
    return pHeadOfList;
}

void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
    if (pNode == nullptr)
        return;

    BinaryTreeNode* pCurrent = pNode;//const parameter should store in val in cur scope

	//lastnode jump to left node or not
	if (pCurrent->m_pLeft != nullptr)
        ConvertNode(pCurrent->m_pLeft, pLastNodeInList);
    
	//connect lastnode(maybe lnode or midnode) to curnode, curnode must be larger
	pCurrent->m_pLeft = *pLastNodeInList;
	if (*pLastNodeInList != nullptr)
		(*pLastNodeInList)->m_pRight = pCurrent;

	//lastnode jump to middle node
    *pLastNodeInList = pCurrent;

	//lastnode jump to right node or not
    if (pCurrent->m_pRight != nullptr)
        ConvertNode(pCurrent->m_pRight, pLastNodeInList);
}

void test1()
{
    BinaryTreeNode* n10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* n6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* n14 = CreateBinaryTreeNode(14);
    BinaryTreeNode* n4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* n8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* n12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* n16 = CreateBinaryTreeNode(16);
    ConnectTreeNodes(n10, n6, n14);
    ConnectTreeNodes(n6, n4, n8);
    ConnectTreeNodes(n14, n12, n16);

	BinaryTreeNode* head = Convert(n10);
}

int main(int argc, char* argv[])
{
    test1();


    return 0;
}