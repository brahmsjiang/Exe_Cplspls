#include "../sword to offer/Utilities/BinaryTree.h"
#include <queue>
#include <stack>
#include <iostream>
#include <string>

using namespace std;

struct Tree
{
    //horizontal build
    Tree(int vec[], int num):nodeNum(num)
    {
        root = CreateBinaryTreeNode(vec[0]);
        queue<BinaryTreeNode*> nodeQue;
        nodeQue.push(root);

        for (int i = 0; i < num;)
        {
            BinaryTreeNode* parNode = nodeQue.front();
            nodeQue.pop();

            if (parNode) {
                if (++i >= num) break;
                parNode->m_pLeft = CreateBinaryTreeNode(vec[i]);
                nodeQue.push(parNode->m_pLeft);
                
                if (++i >= num) break;
                parNode->m_pRight = CreateBinaryTreeNode(vec[i]);
                nodeQue.push(parNode->m_pRight);

                ConnectTreeNodes(parNode, parNode->m_pLeft, parNode->m_pRight);
            }
        }
    }

    BinaryTreeNode* root;
    int nodeNum;
};

bool IsSortedTreeCore(BinaryTreeNode* node, stack<int>& stk)
{
    if (nullptr == node)
        return true;

    //left tree
    if(!IsSortedTreeCore(node->m_pLeft, stk))
        return false;

    //middle
    if (stk.empty() || (node->m_nValue >= stk.top())) {
        stk.push(node->m_nValue);
    }
    else {
        return false;
    }

    //right tree
    if(!IsSortedTreeCore(node->m_pRight, stk))
        return false;

    return true;
}

bool IsSortedTree(Tree tree)
{
    stack<int> vals;
    return IsSortedTreeCore(tree.root, vals);
}

int main(int argc, char* argv[])
{
    int vec[] = { 5,3,7,2,4,6,9,1 };
    Tree tree1(vec, 8);
    string tmp = IsSortedTree(tree1) ? "true" : "false";
    cout << tmp << endl;
    return 0;
}