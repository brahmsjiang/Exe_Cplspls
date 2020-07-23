#include <iostream>
#include <stack>
#include <math.h>

#include "Utilities/List.h"

ListNode* firstCommNode_1(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr || pHead2 == nullptr)
        return nullptr;

    ListNode* curOfHead1 = pHead1;
    while (curOfHead1 != nullptr)
    {
        ListNode* curOfHead2 = pHead2;
        while (curOfHead2 != nullptr)
        {
            if (curOfHead1 == curOfHead2)
                return curOfHead1;
            curOfHead2 = curOfHead2->m_pNext;
        }
        curOfHead1 = curOfHead1->m_pNext;
    }
}

ListNode* firstCommNode_2(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr || pHead2 == nullptr)
        return nullptr;

    std::stack<ListNode*> stack1, stack2;
    ListNode* curOfHead1 = pHead1;
    ListNode* curOfHead2 = pHead2;

    while (curOfHead1 != nullptr)
    {
        stack1.push(curOfHead1);
        curOfHead1 = curOfHead1->m_pNext;
    }
    while (curOfHead2 != nullptr)
    {
        stack2.push(curOfHead2);
        curOfHead2 = curOfHead2->m_pNext;
    }

    ListNode* lastEqlNode = nullptr;
    while (!stack1.empty() && !stack2.empty())
    {
        if (stack1.top() == stack2.top())
        {
            lastEqlNode = stack1.top();
            
            stack1.pop();
            stack2.pop();
        }
        else
            if (nullptr != lastEqlNode)
                return lastEqlNode;
    }
    return nullptr;
}

int getListLength(ListNode* pHead)
{
    int len = 0;
    ListNode* curNode = pHead;
    while (nullptr != curNode)
    {
        ++len;
        curNode = curNode->m_pNext;
    }
    return len;
}

ListNode* firstCommNode_3(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr || pHead2 == nullptr)
        return nullptr;

    int len1 = getListLength(pHead1);
    int len2 = getListLength(pHead2);
    int diff = abs(len1 - len2);

    ListNode* cur1 = pHead1;
    ListNode* cur2 = pHead2;
    if (len1 > len2)
        while (0 < diff-- )
            cur1 = cur1->m_pNext;
    else if(len1 > len2)
        while (0 < diff--)
            cur2 = cur2->m_pNext;
    
    while (nullptr != cur1 && nullptr != cur2)
    {
        if (cur1 == cur2)
            return cur1;
        cur1 = cur1->m_pNext;
        cur2 = cur2->m_pNext;
    }

    return nullptr;
}

int main(int argc, char* argv[])
{
    auto head1 = CreateListNode(1);
    auto node2 = CreateListNode(2);
    auto node3 = CreateListNode(3);
    auto node6 = CreateListNode(6);
    auto node7 = CreateListNode(7);
    auto head4 = CreateListNode(4);
    auto node5 = CreateListNode(5);

    ConnectListNodes(head1, node2);
    ConnectListNodes(node2, node3);
    ConnectListNodes(node3, node6);
    ConnectListNodes(node6, node7);

    ConnectListNodes(head4, node5);
    ConnectListNodes(node5, node6);
    ConnectListNodes(node6, node7);

    auto res1 = firstCommNode_1(head1, head4);
    auto res2 = firstCommNode_2(head1, head4);
    auto res3 = firstCommNode_3(head1, head4);
	return 0;
}