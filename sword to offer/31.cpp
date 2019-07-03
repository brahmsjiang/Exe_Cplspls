#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>


bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool bPossible = false;
	int nMatchNum = 0;
	if(pPush != nullptr && pPop != nullptr && nLength > 0)
	{
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;
		
		stack<int> stackData;
		while(pNextPop - pPop < nLength){
			while(stackData.empty() || stackData.top() != *pNextPop)
			{
				if (pNextPush - pPush == nLength)
					break;
				stackData.push(*pNextPush);
				pNextPush++;
			}
			if(stackData.top() == *pNextPop)
				nMatchNum++;

		}
	}
	return bPossible;

}


int main(int argc, char* argc[])
{
	return 0;
}
