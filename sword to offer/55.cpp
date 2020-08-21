#include <iostream>
#include <math.h>
#include "Utilities/BinaryTree.h"


int TreeDepth(BinaryTreeNode* pRoot)
{
    if (nullptr == pRoot)
        return 0;
    
    int leftDepth = TreeDepth(pRoot->m_pLeft);
    int rightDepth = TreeDepth(pRoot->m_pRight);
    return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
}

bool IsBalanced(BinaryTreeNode* pRoot)
{
    if (nullptr == pRoot)
        return true;

    int leftDepth = TreeDepth(pRoot->m_pLeft);
    int rightDepth = TreeDepth(pRoot->m_pRight);
    return (abs(leftDepth - rightDepth) <= 1);

    return IsBalanced(pRoot->m_pLeft) && IsBalanced(pRoot->m_pRight);
}

//depth is a var can be transferred in parameter or return val
bool IsBalanced2(BinaryTreeNode* pRoot, int& depth)
{
    if (nullptr == pRoot)
    {
        depth = 0;
        return true;
    }

    bool ret = false;
    int leftDepth = 0, rightDepth = 0;
    if (IsBalanced2(pRoot->m_pLeft, leftDepth) && IsBalanced2(pRoot->m_pRight, rightDepth))
    {
        ret = abs(leftDepth - rightDepth) <= 1;
    }
    
    depth = 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
    printf("cur node: %d, leftDepth: %d, rightDepth: %d, depth: %d\n", pRoot->m_nValue, leftDepth, rightDepth, depth);
    return ret;
}


int main(int argc, char* argv[])
{
    BinaryTreeNode* root = CreateBinaryTreeNode(1);
    BinaryTreeNode* node2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* node3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* node4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* node5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* node6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* node7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* node8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* node9 = CreateBinaryTreeNode(9);
    ConnectTreeNodes(root, node2, node3);
    ConnectTreeNodes(node2, node4, node5);
    ConnectTreeNodes(node5, node7, nullptr);
    //ConnectTreeNodes(node7, node8, nullptr);
    ConnectTreeNodes(node3, nullptr, node6);
    //ConnectTreeNodes(node6, nullptr, node9);

    auto res = IsBalanced(root);

    int depth = 0;
    auto res1 = IsBalanced2(root, depth);
    return 0;
}