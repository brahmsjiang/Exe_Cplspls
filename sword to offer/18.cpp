#include "Utilities/List.h"
#include <iostream>

using namespace std;

void DeleteNode(ListNode** pListHead, ListNode* pToDeleted)
{
    if (pListHead == nullptr || pToDeleted == nullptr)
    {
        return;
    }
    //pToDeleted isn't tail
    if (pToDeleted->m_pNext != nullptr)
    {
        ListNode* curNode_nxt = pToDeleted->m_pNext;
        pToDeleted->m_nValue = curNode_nxt->m_nValue;
        pToDeleted->m_pNext = curNode_nxt->m_pNext;
        delete curNode_nxt;
        curNode_nxt = nullptr;
    }
    //pToDeleted is tail & head
    else if (pToDeleted->m_pNext == nullptr && *pListHead == pToDeleted)
    {
        delete pToDeleted;
        pToDeleted = nullptr;
        *pListHead = nullptr;
    }
    //pToDeleted is tail & not head
    else {
        ListNode* curNode = *pListHead;
        while (curNode && curNode->m_pNext != pToDeleted)
        {
            curNode = curNode->m_pNext;
        }
        delete pToDeleted;
        pToDeleted = nullptr;
        curNode->m_pNext = nullptr;
    }
}

void DeleteDuplication2(ListNode** pHead)
{
    if (nullptr == pHead || nullptr == (*pHead)->m_pNext)
        return;

    ListNode* node = *pHead;
    ListNode* Prenode = nullptr;

    while (node)
    {
        int dupVal = 0;
        bool dupFlg = false;
        bool dupAtHead = false;
        ListNode* delNode = nullptr;

        if (node->m_pNext && node->m_pNext->m_nValue == node->m_nValue)
        {
            dupFlg = true;
            dupVal = node->m_nValue;
            if (node == *pHead)
                dupAtHead = true;
        }
        else
        {
            Prenode = node;
            node = node->m_pNext;
        }

        if (dupFlg) {
            while (node && node->m_nValue == dupVal)
            {
                delNode = node;
                node = node->m_pNext;
                delete delNode;
                delNode = nullptr;
            }
            if (dupAtHead)
                *pHead = node;
            else
                Prenode->m_pNext = node;
        }
    }
}

void DeleteDuplication(ListNode** pHead)
{
    if (nullptr == pHead || nullptr == (*pHead)->m_pNext)
        return;

    ListNode* node = *pHead;
    while (node)
    {
        int dupVal = 0;
        ListNode* delNode = nullptr;
        //dup at head
        if (node == *pHead && node->m_pNext && node->m_pNext->m_nValue == node->m_nValue)
        {
            dupVal = node->m_nValue;
            while (node && node->m_nValue == dupVal)
            {
                delNode = node;
                node = node->m_pNext;
                delete delNode;
                delNode = nullptr;
            }
            *pHead = node;
        }
        // dup at middle
        else
        {
            ListNode* nxtNode = node->m_pNext;
            if (nxtNode && nxtNode->m_pNext && nxtNode->m_pNext->m_nValue == nxtNode->m_nValue)
            {
                dupVal = nxtNode->m_nValue;
                while (nxtNode && nxtNode->m_nValue == dupVal)
                {
                    delNode = nxtNode;
                    nxtNode = nxtNode->m_pNext;
                    delete delNode;
                    delNode = nullptr;
                }
                node->m_pNext = nxtNode;
            }
            else
            {
                node = node->m_pNext;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    ListNode* headNode = CreateListNode(1);
    ListNode* Node2 = CreateListNode(2);
    ConnectListNodes(headNode, Node2);
    ListNode* Node3 = CreateListNode(3);
    ConnectListNodes(Node2, Node3);
    ListNode* Node4 = CreateListNode(4);
    ConnectListNodes(Node3, Node4);
    ListNode* Node5 = CreateListNode(5);
    ConnectListNodes(Node4, Node5);

    DeleteNode(&headNode, Node5);
    /////////////////
    ListNode* headNode2 = CreateListNode(1);
    AddToTail(&headNode2, 2);
    AddToTail(&headNode2, 3);
    AddToTail(&headNode2, 3);
    
    DeleteDuplication2(&headNode2);
    return 0;
}