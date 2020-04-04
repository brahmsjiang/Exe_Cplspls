#include <iostream>
#include "assert.h"
#include "Utilities\List.h"

using namespace std;

ListNode* MeetingNode(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
    ListNode* pSlow = pHead;
    ListNode* pFast = pHead;
    do 
    {
        pSlow = pSlow->m_pNext;//1 step forward 
        pFast = pFast->m_pNext->m_pNext;//2 step forward
    } 
    while (pFast != nullptr && pSlow != nullptr && pFast != pSlow);

    if (pFast == pSlow && pFast != nullptr)
    {
        return pFast;
    }
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    ListNode* metNode = MeetingNode(pHead);
    if (nullptr != metNode)
    {
        int LoopNum = 0;
        ListNode* pNxt = metNode;
        do 
        {
            pNxt = pNxt->m_pNext;
            ++LoopNum;
        }
        while (pNxt != metNode);
        assert(pNxt == metNode);

        ListNode* pSlow = pHead;
        ListNode* pFast = pHead;
        for (int i = 0; i < LoopNum; ++i)
        {
            pFast = pFast->m_pNext;
        }

        while (pFast != pSlow)
        {
            pSlow = pSlow->m_pNext;//1 step forward 
            pFast = pFast->m_pNext;//1 step forward
        }
        assert(pSlow == pFast);
        return pFast;
    }
    return metNode;
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
    ConnectListNodes(p6, p3);

    ListNode* res = MeetingNode(p1);
    ListNode* res2 = EntryNodeOfLoop(p1);
	return 0;
}