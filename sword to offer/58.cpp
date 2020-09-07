#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

void Reverse(char* pBegin, char* pEnd)
{
    if (pBegin == nullptr || pEnd == nullptr)
        return;

    while (pBegin < pEnd)
    {
        char tmp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = tmp;

        ++pBegin;
        --pEnd;
    }
}

void ReverseSentence(char* pBegin, char* pEnd)
{
    if (pBegin == nullptr || pEnd == nullptr)
        return;
    Reverse(pBegin, pEnd - 1);

    char* pWordStart = pBegin;
    char* pWordEnd = pBegin;
    while (pWordEnd <= pEnd)
    {
        if (pWordStart != pWordEnd && (*pWordEnd == ' ' || *pWordEnd == '\0'))
        {
            Reverse(pWordStart, pWordEnd - 1);
            pWordStart = ++pWordEnd;
            continue;
        }
        ++pWordEnd;
    }
}

char* LeftRotateString(char* pStr, int n)
{
    if (pStr == nullptr)
        return pStr;

    char* pEnd = pStr + strlen(pStr) - 1;
    Reverse(pStr, pEnd);

    char* pSplit = pEnd - n;
    Reverse(pStr, pSplit);
    Reverse(pSplit + 1, pEnd);

    return pStr;
}

int main(int argc, char* argv[])
{
    char str1[] = "How many ready have you got";
    ReverseSentence(str1, str1 + strlen(str1));

    char str2[] = "abcdefg";
    char* pStr = LeftRotateString(str2, 2);
    return 0;
}