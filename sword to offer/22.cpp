#include <iostream>
#include "Utilities\List.h"

using namespace std;

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (pListHead == nullptr || k == 0)
		return nullptr;
	ListNode* pA = pListHead;
	ListNode* pB = pListHead;

	for (int i = 0; i < k; ++i)//cannot while (pA != pListHead + k)! because list stored is not continued
	{
		if (pA->m_pNext != nullptr)
			pA = pA->m_pNext;
		else
			return nullptr;//judge
	}
	
	pB = pB->m_pNext;
	while (pA->m_pNext != nullptr)
	{
		pA = pA->m_pNext;
		pB = pB->m_pNext;
	}
	return pB;
}

int main(int argc, char* argv[])
{
	ListNode* pHead = CreateListNode(1);
	AddToTail(&pHead, 2);
	AddToTail(&pHead, 3);
	AddToTail(&pHead, 4);
	AddToTail(&pHead, 5);

	ListNode* pKh = FindKthToTail(pHead, 3);
	return 0;
}