#include <iostream>
#include "Utilities\BinaryTree.h"

using namespace std;
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if (nullptr == preorder || nullptr == inorder || length <= 0)
		return nullptr;

	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
	int rootele = *startPreorder;
	BinaryTreeNode* root = CreateBinaryTreeNode(rootele);
	int* rootInInorder = nullptr;
	for (int* it = startInorder; it <= endInorder; it++) 
	{
		if (rootele == *it) {
			rootInInorder = it;
			break;
		}
	}
	if (nullptr == rootInInorder)
		throw exception("Invalid input");

	int lTreeNum = rootInInorder - startInorder;
	int rTreeNum = endInorder - rootInInorder;
	if (lTreeNum > 0) {
		BinaryTreeNode* lTree = ConstructCore(startPreorder + 1, startPreorder + lTreeNum,
			startInorder, rootInInorder - 1);
		if (nullptr != lTree) {
			root->m_pLeft = lTree;
		}
	}
	
	if (rTreeNum > 0) {
		BinaryTreeNode* rTree = ConstructCore(endPreorder - rTreeNum + 1, endPreorder,
			rootInInorder + 1, endInorder);
		if (nullptr != rTree) {
			root->m_pRight = rTree;
		}
	}

	return root;
}

void test()
{
	int preVec[] = { 1,2,4,7,3,5,6,8 };
	int inVec[] = { 4,7,2,1,5,3,8,6 };
	BinaryTreeNode* root = Construct(preVec, inVec, sizeof(preVec)/sizeof(int));
	PrintTree(root);
}

int main(int argc, char* argv[])
{
	test();
	return 0;
}