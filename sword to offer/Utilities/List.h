
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

struct ComplexListNode
{
	int m_nValue;
	ComplexListNode* m_pNext;
	ComplexListNode* m_pSibling;
};

ListNode* CreateListNode(int value);
void ConnectListNodes(ListNode* pCurrent, ListNode* pNext);
void PrintListNode(ListNode* pNode);
void PrintList(ListNode* pHead);
void DestoryList(ListNode* pHead);
void AddToTail(ListNode** pHead, int value);
void RemoveNode(ListNode** pHead, int value);

ComplexListNode* CreateComplexListNode(int value);
void ConnectComplexListNodes(ComplexListNode* pCurrent, ComplexListNode* pNext, ComplexListNode* pSibling);
void AddToComplexTail(ComplexListNode** pHead, int value);
