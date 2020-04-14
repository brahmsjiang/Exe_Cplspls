#include "List.h"
#include <stdio.h>
#include <stdlib.h>

ListNode* CreateListNode(int value)
{
    ListNode* pNode = new ListNode();
    pNode->m_nValue = value;
    pNode->m_pNext = nullptr;

    return pNode;
}

void ConnectListNodes(ListNode* pCurrent, ListNode* pNext)
{
    if(pCurrent == nullptr || pNext == nullptr)
    {
        printf("Error to connect two nodes.\n");
        exit(1);
    }

    pCurrent->m_pNext = pNext;
}

void PrintListNode(ListNode* pNode)
{
    if(pNode == nullptr)
    {
        printf("The node is nullptr,\n");
    }
    else
    {
        printf("The key in node is %d.\n", pNode->m_nValue);
    }
}

void PrintList(ListNode* pHead)
{
    printf("PrintList starts.\n");

    ListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        printf("%d\t", pNode->m_nValue);
        pNode = pNode->m_pNext;
    }

    printf("\nPrintList ends.\n");
}

void DestoryList(ListNode* pHead)
{
    ListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        pHead = pNode->m_pNext;
        delete pNode;
        pNode = pHead;
    }
}

void AddToTail(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;

    if(*pHead == nullptr)
    {
        *pHead = pNew; //type** for here, could modify head node, type* only modify headnode's element
    }
    else{
        ListNode* pNode = *pHead;
        while(pNode->m_pNext != nullptr)
        {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = pNew;

    }
}

void RemoveNode(ListNode** pHead, int value)
{
    if(pHead == nullptr || *pHead == nullptr)
        return;

    ListNode* pToBeDeleted = nullptr;
    if((*pHead)->m_nValue == value)
    {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pNext;
    }
    else{
        ListNode* pNode = *pHead;
        while(pNode->m_pNext->m_nValue != value && pNode->m_pNext != nullptr)
            pNode = pNode->m_pNext;

        if(pNode->m_pNext->m_nValue == value && pNode->m_pNext != nullptr)
        {
            pToBeDeleted = pNode->m_pNext;
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }

    if(pToBeDeleted != nullptr)
    {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }


}

ComplexListNode* CreateComplexListNode(int value)
{
	ComplexListNode* pNode = new ComplexListNode();
	pNode->m_nValue = value;
	pNode->m_pNext = nullptr;
	pNode->m_pSibling = nullptr;
	return pNode;
}

void ConnectComplexListNodes(ComplexListNode* pCurrent, ComplexListNode* pNext, ComplexListNode* pSibling)
{
	if (pCurrent == nullptr || (pNext == nullptr && pSibling == nullptr))
	{
		printf("Error to connect two nodes.\n");
		exit(1);
	}

	if(pNext != nullptr)
		pCurrent->m_pNext = pNext;
	if (pSibling != nullptr)
		pCurrent->m_pSibling = pSibling;
}

void AddToComplexTail(ComplexListNode** pHead, int value)
{
	ComplexListNode* pNew = new ComplexListNode();
	pNew->m_nValue = value;
	pNew->m_pNext = nullptr;
	pNew->m_pSibling = nullptr;

	if (*pHead == nullptr)
	{
		*pHead = pNew; //type** for here, could modify head node, type* only modify headnode's element
	}
	else {
		ComplexListNode* pNode = *pHead;
		while (pNode->m_pNext != nullptr)
		{
			pNode = pNode->m_pNext;
		}
		pNode->m_pNext = pNew;

	}
}


















