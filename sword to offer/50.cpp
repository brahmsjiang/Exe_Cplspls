#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "assert.h"

char FirstNotRepeating_1(char* pString)
{
    if (pString == nullptr)
        return '\0';

    for (int i = 0; i < strlen(pString); ++i)
    {
        char curChr = pString[i];
        bool DuplicateFlg = false;
        for (int j = i + 1; j < strlen(pString); ++j)
        {
            if (curChr == pString[j])
            {
                DuplicateFlg = true;
                break;
            }
        }
        if (!DuplicateFlg)
            return curChr;
    }
    return '\0';
}

char FirstNotRepeating_2(char* pString)
{
    if (pString == nullptr)
        return '\0';

    int hashTbl[256] = {0};
    char* pHashKey = pString;
    while (*pHashKey != '\0')
        hashTbl[*(pHashKey++)]++;

    pHashKey = pString;
    while (*pHashKey != '\0')
    {
        if (hashTbl[*pHashKey] == 1)
            return *pHashKey;
        pHashKey++;
    }
        
    return '\0';
}

int main(int argc, char* argv[])
{
    char res0 = FirstNotRepeating_1("dfxccdeff");
    char res1 = FirstNotRepeating_2("dfxccdeff");
    return 0;
}