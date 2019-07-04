#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>

using namespace std;

void IsPopOrder(const int* pPush, const int* pPop, int nLength)
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
			if(stackData.top() == *pNextPop) {
				nMatchNum++;
				pNextPop++;
				stackData.pop();
				continue;
			}
			else{
				break;
			}

		}
		bPossible = (nMatchNum == nLength) ? true : false;
	}
	cout << (bPossible ? "possible" : "impossible") << endl;

}


int main(int argc, char* argv[])
{
	int pushlist[] = {1,2,3,4,5};
	int poplist1[] = {4,5,3,2,1};
	int poplist2[] = {4,3,5,1,2};
	int poplist3[] = {5,4,3,2,1};
	int poplist4[] = {5,2,1,4,3};
	IsPopOrder(pushlist,poplist1,5);
	IsPopOrder(pushlist,poplist2,5);
	IsPopOrder(nullptr,nullptr,5);
	IsPopOrder(pushlist,poplist3,5);
	IsPopOrder(pushlist,poplist4,5);
	return 0;
}
