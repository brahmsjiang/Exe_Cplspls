#include <iostream>
#include <unordered_map>
#include "Utilities\BinaryTree.h"

using namespace std;

BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
    if (pRootOfTree == nullptr)
        return nullptr;
    

}

void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{

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
}

int main(int argc, char* argv[])
{
    test1();


    return 0;
}