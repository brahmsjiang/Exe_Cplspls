#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>
#include <string.h>
#include "Utilities/BinaryTree.h"

using namespace std;

void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
	if(pStr == nullptr)
		return;
	Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin)
{
	if(*pBegin == '\0'){
		cout<<pStr<<endl;
		return;
	}
	for(char* i = pBegin; *i != '\0'; ++i)
	{
		char ptmp = *i;
		*i = *pBegin;
		*pBegin = ptmp;

		Permutation(pStr, i+1);
		
		ptmp = *i;
		*i = *pBegin;
		*pBegin = ptmp;
	}
}

int main(int argc, char* argv[])
{
	char tmp[] = "abcde";
	Permutation(tmp);
	return 0;
}
















