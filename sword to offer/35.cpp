#include <iostream>
#include <unordered_map>
#include "Utilities\List.h"

using namespace std;

ComplexListNode* Clone1(ComplexListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;

	ComplexListNode* newhead = nullptr;
	ComplexListNode* curToOri = pHead;
	ComplexListNode* prev = nullptr;
	while (curToOri != nullptr)
	{
		ComplexListNode* copy = new ComplexListNode;
		copy->m_nValue = curToOri->m_nValue;
		if (newhead == nullptr)
			newhead = copy;
		if (prev)
			prev->m_pNext = copy;

		prev = copy;
		curToOri = curToOri->m_pNext;
	}

	curToOri = pHead;
	ComplexListNode* curToNew = newhead;
	while (curToOri != nullptr)
	{
		if (curToOri->m_pSibling != nullptr)
		{
			size_t step = 0;
			ComplexListNode* toSibling = pHead;
			while (toSibling != curToOri->m_pSibling)
			{
				toSibling = toSibling->m_pNext;
				++step;
			}

			toSibling = newhead;
			for (size_t i = 0; i < step; i++)
			{
				toSibling = toSibling->m_pNext;
			}
			curToNew->m_pSibling = toSibling;
		}

		curToNew = curToNew->m_pNext;
		curToOri = curToOri->m_pNext;
	}

	return newhead;
}

ComplexListNode* Clone2(ComplexListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;

	ComplexListNode* newhead = nullptr;
	ComplexListNode* curToOri = pHead;
	ComplexListNode* prev = nullptr;
	std::unordered_map<ComplexListNode*, ComplexListNode*> mmap;

	while (curToOri != nullptr)
	{
		ComplexListNode* copy = new ComplexListNode;
		copy->m_nValue = curToOri->m_nValue;
		if (newhead == nullptr)
			newhead = copy;
		if (prev)
			prev->m_pNext = copy;

		prev = copy;
		mmap[curToOri] = copy;
		curToOri = curToOri->m_pNext;
	}

	curToOri = pHead;
	while (curToOri != nullptr)
	{
		if (curToOri->m_pSibling != nullptr)
			mmap[curToOri]->m_pSibling = mmap[curToOri->m_pSibling];

		curToOri = curToOri->m_pNext;
	}

	return newhead;
}


/////////////////////
void CloneNodes(ComplexListNode* pHead)
{
	if (pHead == nullptr)
		return;

	ComplexListNode* pCurOri = pHead;
	while (pCurOri != nullptr)
	{
		ComplexListNode* pCurNew = new ComplexListNode;
		pCurNew->m_nValue = pCurOri->m_nValue;
		ComplexListNode* pNxtOri = pCurOri->m_pNext;
		pCurOri->m_pNext = pCurNew;
		pCurNew->m_pNext = pNxtOri;

		pCurOri = pNxtOri;
	}
}

void ConnectSiblingNodes(ComplexListNode* pHead)
{
	if (pHead == nullptr)
		return;

	ComplexListNode* pCurOri = pHead;
	while (pCurOri != nullptr)
	{
		if (pCurOri->m_pSibling != nullptr)
		{
			if (pCurOri->m_pNext != nullptr)
				pCurOri->m_pNext->m_pSibling = pCurOri->m_pSibling->m_pNext;
		}
		pCurOri = pCurOri->m_pNext->m_pNext;
	}
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;

	ComplexListNode* pMergOri = pHead;
	ComplexListNode* pCurNew = nullptr;
	ComplexListNode* pNewHead = nullptr;
	while (pMergOri != nullptr)
	{
		pCurNew = pMergOri->m_pNext;
		if (pNewHead == nullptr && pCurNew != nullptr)
			pNewHead = pCurNew;


	}
}

ComplexListNode* Clone3(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	ConnectSiblingNodes(pHead);
	return ReconnectNodes(pHead);
}



void test1()
{
	ComplexListNode* p1 = CreateComplexListNode(1);
	ComplexListNode* p2 = CreateComplexListNode(2);
	ComplexListNode* p3 = CreateComplexListNode(3);
	ComplexListNode* p4 = CreateComplexListNode(4);
	ComplexListNode* p5 = CreateComplexListNode(5);
	ConnectComplexListNodes(p1, p2, p3);
	ConnectComplexListNodes(p2, p3, p5);
	ConnectComplexListNodes(p3, p4, nullptr);
	ConnectComplexListNodes(p4, p5, p2);
	ComplexListNode* phead1 = Clone1(p1);
}

void test2()
{
	ComplexListNode* p1 = CreateComplexListNode(1);
	ComplexListNode* p2 = CreateComplexListNode(2);
	ComplexListNode* p3 = CreateComplexListNode(3);
	ComplexListNode* p4 = CreateComplexListNode(4);
	ComplexListNode* p5 = CreateComplexListNode(5);
	ConnectComplexListNodes(p1, p2, p3);
	ConnectComplexListNodes(p2, p3, p5);
	ConnectComplexListNodes(p3, p4, nullptr);
	ConnectComplexListNodes(p4, p5, p2);
	ComplexListNode* phead1 = Clone2(p1);
}

void test3()
{
	ComplexListNode* p1 = CreateComplexListNode(1);
	ComplexListNode* p2 = CreateComplexListNode(2);
	ComplexListNode* p3 = CreateComplexListNode(3);
	ComplexListNode* p4 = CreateComplexListNode(4);
	ComplexListNode* p5 = CreateComplexListNode(5);
	ConnectComplexListNodes(p1, p2, p3);
	ConnectComplexListNodes(p2, p3, p5);
	ConnectComplexListNodes(p3, p4, nullptr);
	ConnectComplexListNodes(p4, p5, p2);
	ComplexListNode* phead1 = Clone3(p1);
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	return 0;
}