#include "Utilities/List.h"
#include "assert.h"
#include <iostream>

using namespace std;

ListNode* ReverseList(ListNode* pHead)
{
    ListNode* RevHead = pHead;
    ListNode* curNode = pHead;
    ListNode* nxtNode = nullptr;
    ListNode* nxtnxtNode = nullptr;

    while (curNode != nullptr)
    {
        //deal with head
        if (curNode == pHead) {
            nxtNode = curNode->m_pNext;
            curNode->m_pNext = nullptr;
        }
        else {
            nxtNode = nxtnxtNode;
        }

        if (nxtNode != nullptr) {
            nxtnxtNode = nxtNode->m_pNext;
            nxtNode->m_pNext = curNode;
        }
        RevHead = curNode;
        //curNode change
        curNode = nxtNode;
        
    }
    return RevHead;
}

int main(int argc, char* argv[])
{
    ListNode* pHead = CreateListNode(1);
    AddToTail(&pHead, 2);
    AddToTail(&pHead, 3);
    AddToTail(&pHead, 4);
    AddToTail(&pHead, 5);
    AddToTail(&pHead, 6);

    ListNode* pHead2 = CreateListNode(2);

    ListNode* newHead = ReverseList(pHead);
    ListNode* newHead2 = ReverseList(pHead2);
    ListNode* newHead3 = ReverseList(nullptr);
    return 0;
}