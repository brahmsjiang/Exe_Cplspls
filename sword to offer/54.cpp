#include <iostream>
#include <stack>
#include "Utilities/BinaryTree.h"


BinaryTreeNode* findKNode(const BinaryTreeNode* root, int k)
{
    if (root == nullptr)
        return nullptr;

    BinaryTreeNode* res = nullptr;
    int curCount = 0;

    res = 

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

    auto res = findKNode(root, 3);

    return 0;
}