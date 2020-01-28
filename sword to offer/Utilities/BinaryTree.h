
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	BinaryTreeNode* m_pParent;
};

BinaryTreeNode* CreateBinaryTreeNode(int value);
void ConnectTreeNodes(BinaryTreeNode* parent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
void PrintTreeNode(const BinaryTreeNode* pNode);
void PrintTree(const BinaryTreeNode* pNode);
void DestroyTree(BinaryTreeNode* pRoot);


