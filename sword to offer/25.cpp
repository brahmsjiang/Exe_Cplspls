#include <iostream>
#include "Utilities\List.h"

using namespace std;


ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr)
		return pHead2;
	if (pHead2 == nullptr)
		return pHead1;
	if (pHead1 == nullptr && pHead2 == nullptr)
		return nullptr;

	ListNode* pHeadOri = nullptr;
	if (pHead1->m_nValue < pHead2->m_nValue)
	{
		pHeadOri = pHead1;
		pHeadOri->m_pNext = Merge(pHead1->m_pNext, pHead2);
#if 0	//the following code is err because regardless the case 1-2-3-7 & 3-4, 
		// become 1-3-4 2-3-7 => 1/2-3-3-4, 2 isn't before 1, err 
		ListNode* pHead1Nxt = pHead1->m_pNext;
		pHead1->m_pNext = pHead2;
		pHeadOri = pHead1;
		Merge(pHead1Nxt, pHead2);
#endif
	}
	else{
		pHeadOri = pHead2;
		pHeadOri->m_pNext = Merge(pHead1, pHead2->m_pNext);
	}
	return pHeadOri;
}

void Test1()
{
	ListNode* head1 = CreateListNode(1);
	AddToTail(&head1, 2);
	AddToTail(&head1, 3);
	AddToTail(&head1, 7);
	ListNode* head2 = CreateListNode(3);
	AddToTail(&head2, 4);
	ListNode* newhead = Merge(head1, head2);
}

void Test2()
{
	ListNode* head1 = CreateListNode(1);
	AddToTail(&head1, 3);
	AddToTail(&head1, 5);
	ListNode* head2 = CreateListNode(1);
	AddToTail(&head2, 3);
	AddToTail(&head2, 5);
	ListNode* newhead = Merge(head1, head2);
}

void Test3()
{
	ListNode* head1 = CreateListNode(1);
	ListNode* head2 = CreateListNode(2);
	ListNode* newhead = Merge(head1, head2);
}

void Test4()
{
	ListNode* head1 = CreateListNode(1);
	AddToTail(&head1, 3);
	AddToTail(&head1, 5);
	AddToTail(&head1, 7);
	ListNode* head2 = nullptr;
	ListNode* newhead = Merge(head1, head2);
}

void Test5()
{
	ListNode* head1 = nullptr;
	ListNode* head2 = nullptr;
	ListNode* newhead = Merge(head1, head2);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}