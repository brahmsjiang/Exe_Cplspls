#include <iostream>
#include "Utilities\List.h"

using namespace std;

ListNode* MeetingNode(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
    ListNode* pSlow = pHead;
    ListNode* pFast = pHead;
    while (pFast->m_pNext != nullptr || pSlow->m_pNext != nullptr || pFast != pSlow)
    {
        pSlow = pSlow->m_pNext;//1 step forward 
        pHead = pFast->m_pNext->m_pNext;//2 step forward
    }
    if (pFast == pSlow && pFast != nullptr)
    {
        return pFast;
    }
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
}

int main(int argc, char* argv[])
{
    ListNode* p1 = CreateListNode(1);
    ListNode* p2 = CreateListNode(2);
    ListNode* p3 = CreateListNode(3);
    ListNode* p4 = CreateListNode(4);
    ListNode* p5 = CreateListNode(5);
    ListNode* p6 = CreateListNode(6);
    ConnectListNodes(p1, p2);
    ConnectListNodes(p2, p3);
    ConnectListNodes(p3, p4);
    ConnectListNodes(p4, p5);
    ConnectListNodes(p5, p6);
    ConnectListNodes(p5, p3);


	return 0;
}