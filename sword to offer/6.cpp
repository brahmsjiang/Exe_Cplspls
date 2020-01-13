#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>
#include "Utilities/List.h"

using namespace std;


void PrintListReversingly_Iteratively(ListNode* pHead)
{
    if(pHead == nullptr)
        return;

    stack<ListNode*> nodes;

    ListNode* pNode = pHead;
    nodes.push(pNode);
    while(pNode->m_pNext != nullptr)
    {
        pNode = pNode->m_pNext;
        nodes.push(pNode);
    }
    while(!nodes.empty())
    {
        cout<<(nodes.top())->m_nValue<<"\t";
        nodes.pop();
    }
    cout<<endl;
}

void PrintListReversingly_Recursively(ListNode* pHead)
{
    ListNode* pNode = pHead;
    if(pNode != nullptr)
    {
        PrintListReversingly_Recursively(pNode->m_pNext);
        cout<<pNode->m_nValue<<"\t";
    }
}

void test()
{

    ListNode* pHead = CreateListNode(1);
    for(int i = 2; i <= 5; ++i)
    {
        AddToTail(&pHead, i);
    }
    PrintList(pHead);
    PrintListReversingly_Iteratively(pHead);
    PrintListReversingly_Recursively(pHead);cout<<endl;
}



int main(int argc, char* argv[])
{
    test();
	
	return 0;
}


